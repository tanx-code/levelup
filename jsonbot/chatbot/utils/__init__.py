# coding=utf-8
import itertools

import requests
from bosonnlp import BosonNLP

from .settings import API_TOKEN_BOSONNLP

session = requests.Session()


class Scanner(object):
    """
    bosonnlp 中文分词
    """

    def __init__(self):
        self.nlp_handler = BosonNLP(API_TOKEN_BOSONNLP)

    def get_tag(self, content, remove_punctuations=False):
        """
        分词后的结果，返回的是每个词的列表
        """
        result = self.nlp_handler.tag(content)[0]
        if remove_punctuations:
            return [x for x, y in zip(result['word'], result['tag'])
                    if y[0] != 'w']
        return result['word']

    def get_key_word(self, content, segmented=False):
        """提取关键词"""
        keywords = self.nlp_handler.extract_keywords(content, 2, segmented)
        firstkey, secondkey = keywords[0], keywords[1]
        return firstkey[1] if (firstkey[0] - secondkey[0]) > 0.3\
            else ' '.join([firstkey[1], secondkey[1]])
