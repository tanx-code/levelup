# coding=utf-8
import logging
import os

from pymongo import MongoClient

LOGGING_FORMAT = '%(asctime)-15s %(levelname)s %(message)s'
logging.basicConfig(format=LOGGING_FORMAT, level=logging.INFO)

if os.path.exists('.env'):
    print('Importing environment from .env...')
    for line in open('.env'):
        var = line.strip().split('=')
        if len(var) == 2:
            os.environ[var[0]] = var[1]

MONGODB_USERNAME = os.environ.get('MONGODB_USER','XiaoTan')
MONGODB_PSW = os.environ.get('MONGODB_PSW', 'as6559339')
MONGODB_LOCAL = 'mongodb://' + MONGODB_USERNAME + ':' + MONGODB_PSW + '@127.0.0.1:27017/admin'
db_client = MongoClient(MONGODB_LOCAL)

# 需要单独处理所有的声母是x，y的词，因为 x,y碰到u就会变成耶(类似英文音标的 :j:)
# xu yu, xun yun (j,q,x 的韵母还是 un, 但是y的韵母将会是 vn ，并且舍弃自身声母)
# iu组成的词 和 所有的 you(解析成了 iou)
# ie组成的词 和 所有的 ye (不用管的，ye的韵母将被解析成 ie)
# ian组成的词 和 (yan 同上会被解析成ian)
# 所有的 j,q,xuan, yuan(van)
CUSTOM_SAME_VOWEL = [
    ['a', 'ua', 'ia'],
    ['o', 'uo'],
    ['e'],
    ['i'],
    ['u'],
    ['v'],
    ['an', 'uan'],
    ['ao', 'iao'],
    ['ai', 'uai'],
    ['ang', 'uang', 'iang'],
    ['ong', 'iong'],
    ['er'],
    ['ei', 'ui', 'uei'],
    ['en', 'un', 'uen'],
    ['eng'],
    ['iu', 'iou', 'ou'],
    ['ie'],
    ['in', 'ing'],
    ['ue', 've'],
    ['ian'],
]

def generate_vowel(vowels, initials, syllable_indexs=None):
    if not syllable_indexs:
        syllable_indexs = [0] # 默认为查单押韵
    zcs = ['z', 'c', 's']
    zcsh = ['zh', 'ch', 'sh']
    query = {}
    for i, vowel in enumerate(vowels):
        if i not in syllable_indexs:
            continue
        if vowel == 'vn' or (vowel == 'un' and initials[i] in ['j', 'q', 'x']):
            query.update({
                '$or':[
                    {
                        'pinyin.vowels.{}'.format(i): 'vn',
                    },
                    {
                        'pinyin.vowels.{}'.format(i): 'un',
                        'pinyin.initials.{}'.format(i): {'$in': ['j', 'x', 'q']} 
                    }
                ]
                })

        elif vowel == 'van' or (vowel == 'uan' and initials[i] in ['j', 'q', 'x']):
            query.update({
                '$or':[
                    {
                        'pinyin.vowels.{}'.format(i): 'van',
                    },
                    {
                        'pinyin.vowels.{}'.format(i): 'uan',
                        'pinyin.initials.{}'.format(i): {'$in': ['j', 'x', 'q']} 
                    }
                ]
                })

        elif vowel == 'i':
            if initials[i] in (zcs+zcsh):
                query.update({
                    'pinyin.vowels.{}'.format(i): 'i',
                    'pinyin.initials.{}'.format(i): {'$in': zcs if initials[i] in zcs else zcsh}
                })
            else:
                query.update({
                    'pinyin.vowels.{}'.format(i): 'i',
                    'pinyin.initials.{}'.format(i): {'$nin': zcs + zcsh}
                }) 
        else:
            for item in CUSTOM_SAME_VOWEL:
                if vowel in item:
                    query.update({
                        'pinyin.vowels.{}'.format(i): {'$in': item}
                    })
                    break
            else:
                query.update({
                    'pinyin.vowels.{}'.format(i): vowel
                })

    return query