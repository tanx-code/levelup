import re


def cn_word_dictionary_segment():
    with open('cn-word-dictionary-raw.txt', 'rb') as fp:
        content = fp.read()
        result = re.findall(r'【(.*?)】', content.decode('utf-16'))

    with open('seg-cn-word-dictionary.txt', 'wb') as fp:
        for d in set(result):
            if len(d) > 1:
                fp.write((d + '\n').encode('utf-8'))


def added_words_in_cn_dict_v6():
    result = []
    with open('added-words-in-cn-dict-v6.txt', 'rb') as fp:
        content = fp.read().decode('utf-8').split('\n')
        for line in content:
            if line.split() == []:
                continue
            for d in line.split('、'):
                result.append(''.join(d.split()))
    with open('seg-added-words-v6.txt', 'wb') as fp:
        for d in result:
            fp.write((d + '\n').encode('utf-8'))


if __name__ == '__main__':
    cn_word_dictionary_segment()
    added_words_in_cn_dict_v6()
