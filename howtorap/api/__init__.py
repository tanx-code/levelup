'''
howtorap 网站后端 Flask API
'''
import json
import logging

from flask import Flask, request
from flask.json import jsonify
from flask_cors import CORS

from utils import char_dict, word_dict, get_pinyin
from utils.settings import generate_vowel

logger = logging.getLogger(__name__)
app = Flask(__name__)
CORS(app)

@app.route('/htr')
def index():
    return 'Hello World!'

@app.route('/htr/get_char_by_vowel', methods=['POST'])
def get_char_by_vowel():
    data = request.get_json()
    logger.info('Someone queried a char: %s', data['word'])
    pinyin_msg = get_pinyin(data['word'])
    tones = pinyin_msg['tones']
    vowels = pinyin_msg['vowels']
    initials = pinyin_msg['initials']
    num_limit = data.get('num_limit', 100)
    skip_num = int(data.get('db_skip_num') or 0)
    result = _get_char_helper(generate_vowel(vowels, initials), tones, num_limit, skip_num)
    return jsonify(result)

def _get_char_helper(query, tones, num_limit, skip_num):
    query.update({'pinyin.tones.{}'.format(i): d for i, d in enumerate(tones)})
    query.update({'freq_level': {'$in': list(range(2))}})
    print(query)
    projection = {'hanzi': 1, '_id': 0}
    total_words = char_dict.find(query, projection).count()
    cursor = char_dict.find(query, projection).skip(skip_num)
    data = [d.get('hanzi', '') for d in cursor.limit(num_limit)]
    respond = {
        'total_words': total_words,
        'data': data,
        # 'db_skip_num': skip_num + len(data) # Deprecated
    }
    return respond

@app.route('/htr/get_word_by_vowels', methods=['POST'])
def get_word_by_vowels():
    '''
    获得对应韵脚的词汇

    word:
        一个中文词汇
    syllable_indexs:
        词汇中需要押韵的索引列表，e.g 你好，索引为[0]，即押'好'的音(注意顺序是反的)
        当押一个字的时候，会默认优化返回结果，即同一个字的词最多出现不超过三次。
    tone_indexs:(OPTIONAL)
        词汇中需要保证音调一样的索引列表, e.g 你好, 索引为[0]，即最后一个字保证为第三声
    num_limit:
        返回结果的个数限制，默认为100，即一页的大小
    db_skip_num:
        指定mongodb查询时传给`skip()`的值
    '''
    # 接收一个待查词汇的列表
    data = request.get_json()
    logger.info('Someone queried a word: %s', data['word'])
    pinyin_msg = get_pinyin(data['word'])
    vowels = pinyin_msg['vowels']
    tones = pinyin_msg['tones']
    initials = pinyin_msg['initials']
    syllable_indexs = data.get('syllable_indexs', [0])
    tone_indexs = data.get('tone_indexs', [])
    num_limit = data.get('num_limit', 100)
    skip_num = int(data.get('db_skip_num') or 0)
    respond = _get_word_by_vowels_helper(generate_vowel(vowels, initials, syllable_indexs), syllable_indexs, tones, tone_indexs, num_limit, skip_num)
    return jsonify(respond)


def _get_word_by_vowels_helper(query, syllable_indexs, tones, tone_indexs, num_limit, skip_num):
    query.update({'pinyin.tones.{}'.format(i): d for i, d in enumerate(tones)
                  if i in tone_indexs})
    projection = {'word': 1, '_id': 0}
    total_words = word_dict.find(query, projection).count()
    cursor = word_dict.find(query, projection).skip(skip_num)
    # 针对单押韵的返回结果优化，同一个字的词最多出现不超过一次
    if len(syllable_indexs) == 1:
        index = syllable_indexs[0]
        data = []
        repeat_tmp = {}
        i = 0
        while i < num_limit:
            try:
                word = next(cursor).get('word', '')
            except StopIteration:
                # 数量不够num_limit时会提前终止
                break
            skip_num += 1
            word_spec = word[-index - 1]
            repeat_tmp.setdefault(word_spec, 0)
            if repeat_tmp[word_spec] >= 1:
                continue
            repeat_tmp[word_spec] += 1
            data.append(word)
            i += 1
        respond = {
            'total_words': total_words,
            'data': data,
            # 'db_skip_num': skip_num # Deprecated
        }
        return respond
    # 多押韵不用优化直接返回
    data = [d.get('word', '') for d in cursor.limit(num_limit)]
    respond = {
        'total_words': total_words,
        'data': data,
        # 'db_skip_num': skip_num + len(data) # Deprecated
    }
    return respond


if __name__ == '__main__':
    app.run()
