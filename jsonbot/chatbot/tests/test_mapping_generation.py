# coding=utf-8
import os
import pytest
import re

from httmock import urlmatch, HTTMock

from chatbot.core.parse import parse_trainning_data
from chatbot.core.brain import Brain
from chatbot.core import Core
from .setting import TEST_RUNNING_DIR, TEST_TRAIN_DIR

brain = Brain(TEST_RUNNING_DIR, TEST_TRAIN_DIR)


def test_mapping():
    data = parse_trainning_data(os.path.join(
        TEST_TRAIN_DIR, 'test_train.json'))
    for d in data:
        brain.saving_and_update_brain(d)


def test_searching():
    assert '/%U/天空/是/什么/颜色/%S' == brain.search_brain('你知道天空是什么颜色吗？')
    assert '/%U/再见' == brain.search_brain('那再见')
    assert '/%U/再见/%S' == brain.search_brain('那就再见吧！')
    assert '/再见' == brain.search_brain('再见')


def test_redirect_searching():
    target_answer = ["谢谢你陪我聊天", "再见了", "下次再聊哦"]
    assert brain.open_template(brain.search_brain('那再见')) in target_answer
    assert brain.open_template(brain.search_brain('那就再见吧')) in target_answer
    target_answer = [
        "抱歉，这个问题无法回答。",
        "您能换一种问法吗？",
        "抱歉，我听不懂。"
    ]
    assert brain.open_template(brain.search_brain('未知问题1')) in target_answer
    assert brain.open_template(brain.search_brain('未知问题2')) in target_answer


def test_reply_template_generate():
    @urlmatch(netloc=r'(.*\.)?baike\.baidu\.com$', path=r'.*')
    def baidu_mock(url, request):
        return ''
    with HTTMock(baidu_mock):
        assert "你是说 圆周率 吗？不知道QAQ" == \
            brain.open_template(brain.search_brain('你知道圆周率是多少吗'))
        assert "你是说 圆周率 吗？不知道QAQ" == \
            brain.open_template(brain.search_brain('帮我搜一下圆周率'))


def test_destroy_brain():
    brain = Brain(TEST_RUNNING_DIR, TEST_TRAIN_DIR)
    brain.destroy_brain()
    assert None == brain.search_brain('你好吗')
