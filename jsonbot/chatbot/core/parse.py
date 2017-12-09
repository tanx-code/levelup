# coding=utf-8
import json
import random
import re
from ..utils.third_part_api import get_weather, get_baidu

find_all_placeholders = re.compile(r'{(.+)}')
meta_element = {
    '天气': get_weather,
    '百度': get_baidu,
}


def parse_trainning_data(input_file_path):
    with open(input_file_path) as json_file:
        return json.loads(json_file.read(), encoding='utf8')


def parse_template_json(template_string):
    """return a specify answer"""
    template = json.loads(template_string)
    return random.choice(template)


def generate_string_from_tpl(template_string, asking_sentence):
    meta_list = find_all_placeholders.findall(template_string)
    return template_string.format(**{
        key: meta_element[key](asking_sentence) for key in meta_list
    })
