"""
Save segment files to mongodb

format:
        word_dict:
        {
            "word": "代驾",
            "length": 2,
            "pinyin": {
                "vowels": [
                "ia",
                "ai"
                ],
                "tones": [
                "4",
                "4"
                ],
                "initials": [
                "j",
                "d"
                ]
            },
            "updated_date": ISODate("2017-05-21T15:43:48.062Z")
        }
        char_dict:
            {
            "hanzi": "东",
            "unicode": "U+4E1C",
            "pinyin": [
                "dōng"
            ],
            "updated_date": ISODate("2017-05-15T13:56:20.886Z"),
            "freq_level": 1
        }
"""

import os
import logging
import concurrent.futures

from utils import word_dict, char_dict, upsert_db, get_pinyin


logger = logging.getLogger(__name__)
executor = concurrent.futures.ThreadPoolExecutor(max_workers=2)
DIR_DICTIONARY = 'dictionaries'


def add_task(func):
    def __decorator(coll):
        logger.info('Starting deal with %s', coll.full_name)
        # func(coll)
        executor.submit(func, coll)
    return __decorator


@add_task
def insert_word_dict(db_collection):
    good = 0
    files = ['seg-added-words-v6.txt', 'seg-cn-word-dictionary.txt']
    files = [os.path.join(DIR_DICTIONARY, d) for d in files]
    for fn in files:
        with open(fn, 'r', encoding='utf-8') as fp:
            content = [line.strip() for line in fp]
            for word in content:
                # 去掉中文逗号 ，
                word.replace('，', '')
                upsert_db(
                    ['word'],
                    {
                        'word': word,
                        'length': len(word),
                        'pinyin': get_pinyin(word)
                    },
                    db_collection
                )
                good = good + 1
    logger.info('Done with %s, success item: %d, failed item: 0',
                db_collection.full_name, good)


def _deal_with_char_dict(filename, db_collection):
    good, bad = 0, 0
    with open(filename, 'r', encoding='utf-8') as fp:
        for line in fp:
            line = line.strip()
            if line.startswith('#'):
                continue

            result = line.split()
            if (len(result) != 4) or ('#' not in result):
                bad = bad + 1
                logger.warning(
                    '%s, Invalid line schema, can not insert to db.',
                    str(result))
                continue
            upsert_db(
                ['hanzi'],
                {
                    'unicode':
                        result[0][:-1] if result[0][-1] == ':' else result[0],
                    'pinyin':
                        get_pinyin(result[3]),
                    'hanzi':
                        result[3],
                },
                db_collection
            )
            good = good + 1
    return good, bad


@add_task
def insert_char_dict(db_collection):
    files = ['seg-pinyin.txt', 'seg-zdic.txt']
    files = [os.path.join(DIR_DICTIONARY, d) for d in files]

    # 先存 seg-zdic 的，再用 seg-pinyin 的去覆盖
    # 格式举例：U+3469: luó  # 㑩
    good, bad = _deal_with_char_dict(files[1], db_collection)
    append = _deal_with_char_dict(files[0], db_collection)
    good, bad = good + append[0], bad + append[1]
    logger.info('Done with %s, success item: %d, failed item: %d',
                db_collection.full_name, good, bad)

    logger.info('Starting deal with frequent hanzi table in %s',
                db_collection.full_name)
    insert_char_freq(db_collection)


def insert_char_freq(db_collection):
    good, bad = 0, 0
    level = 0
    files = ['seg-常用汉字表.txt', 'seg-通用汉字规范表.txt']
    files = [os.path.join(DIR_DICTIONARY, d) for d in files]

    with open(files[0], 'r', encoding='utf-8') as fp:
        content = [line.strip() for line in fp if len(line.strip()) == 1]
        for d in content:
            upsert_db(
                ['hanzi'],
                {
                    'hanzi': d,
                    'freq_level': level
                },
                char_dict
            )
            good = good + 1
    with open(files[1], 'r', encoding='utf-8') as fp:
        for line in fp:
            line = line.strip()
            if line.startswith('#'):
                level = level + 1
                continue
            if len(line) != 1:
                logger.warning('%s, Invalid line schema, can not insert to db.',
                               line)
                bad = bad + 1
                continue
            upsert_db(
                ['hanzi'],
                {
                    'hanzi': line,
                    'freq_level': level
                },
                char_dict
            )
            good = good + 1
    logger.info('Done with %s, success item: %d, failed item: %d',
                db_collection.full_name, good, bad)


def run():
    insert_char_dict(char_dict)
    insert_word_dict(word_dict)
    executor.shutdown(wait=True)


if __name__ == '__main__':
    run()
