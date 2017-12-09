# coding=utf-8
import json
import re

from bs4 import BeautifulSoup

from . import Scanner, session
from .settings import BAIDU_BAIKE_URL, WEATHER_KEY, WEATHER_LANG,\
    WEATHER_NOW_URL, DEFAULT_LOCATION, UNIT


# pylint: disable=W0613
def get_weather(asking_sentence, location=DEFAULT_LOCATION):
    respond = session.get(WEATHER_NOW_URL, params={
        'key': WEATHER_KEY,
        'location': location,
        'language': WEATHER_LANG,
        'unit': UNIT
    }, timeout=1)
    result_json = json.loads(respond.text)['results']
    ret_location = result_json[0]['location']
    ret_detail_info = result_json[0]['now']
    ret_update_time = result_json[0]['last_update']
    result = [
        '位置：' + ret_location['name'],
        '天气：' + ret_detail_info['text'],
        '外界温度(摄氏度)：' + ret_detail_info['temperature'],
        # API需要付费才能返回更多信息，QAQ
        #'体感温度(摄氏度)：' + ret_detail_info['feels_like'],
        #'相对湿度(百分比)：' + ret_detail_info['humidity'],
        #'能见度(公里)：' + ret_detail_info['visibility'],
        #'风力等级：' + ret_detail_info['wind_scale'],
        #'风速(公里每小时)：' + ret_detail_info['wind_speed'],
        '更新时间：' + ' '.join(re.findall(r"[^T\+]+", ret_update_time))
    ]
    return "您本地的天气是：\n{}".format('\n'.join(result))


def get_baidu(asking_sentence):
    s = Scanner()
    query = s.get_key_word(asking_sentence, segmented=True)
    return "你是说 {} 吗？{}".format(
        query, _search_baidu_baike(query))


def _search_baidu_baike(query):
    page = session.get(BAIDU_BAIKE_URL.format(query))
    # Wtf.. bs4's encoding detect method is better than requests's,
    # So if i use `page.text` here, it will raise encoding error.
    soup = BeautifulSoup(page.content, 'html.parser')
    # 目前的网站内容是 <meta name="description" content="校花...">
    desc = soup.find(attrs={'name': 'description'})
    return desc['content'] if desc else '不知道QAQ'
