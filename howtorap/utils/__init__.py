import datetime

from pypinyin import lazy_pinyin, FINALS_TONE3, INITIALS

from .settings import db_client
from .scanner import Segment

# 总集：现代汉语词典，加上第六版新增的词汇
word_dict = db_client['cn_vocabulary']['word_dict']

# 总集：Unihan 中拥有的汉字，包括拼音
char_dict = db_client['cn_vocabulary']['char_dict']

# 子集：
# 常用汉字表 2000+
# (freq_level = 0) 用于表示日常生活的字
# 通用汉字规范表 8000+
# (freq_level = 1,2) 一、二级字表主要满足出版印刷、辞书编纂和信息处理等方面的一般用字需要
# (freq_level = 3) 三级字表由姓氏人名、地名、科技术语和中小学敎材常见文言文用字构成
# char_freq_dict = db_client['cn_vocabulary']['char_freq_dict']


def upsert_db(query, changing, collection):
    """update db, if failed then insert to db

    query: fields list, must exist in changing dict
    changing: dict
    collection: a specify collection
    """
    changing['updated_date'] = datetime.datetime.utcnow()
    collection.update_one(
        {d: changing[d] for d in query},
        {'$set': changing},
        upsert=True)


def get_pinyin(word):
    vowels_list = lazy_pinyin(word, style=FINALS_TONE3)
    tones_list = [d[-1] if d[-1].isdigit() else '' for d in vowels_list]
    # modify vowels_list
    vowels_list = [d[:-1] if d[-1].isdigit() else d for d in vowels_list]
    initials_list = lazy_pinyin(word, style=INITIALS)
    if not all(len(item) == len(vowels_list)
               for item in [vowels_list, tones_list, initials_list]):
        raise ValueError(
            'some list\'s length not equals to others\'s')
    # the purpose of reversing is to abtain the convienent of mongodb query
    vowels_list.reverse()
    tones_list.reverse()
    initials_list.reverse()
    return {
        'vowels': vowels_list,
        'tones': tones_list,
        'initials': initials_list
    }
