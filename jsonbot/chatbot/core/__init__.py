# coding=utf-8
import os
import glob
from .brain import Brain
from .parse import parse_trainning_data
from ..utils.settings import TRAINNING_DATA_DIR


class Core(object):
    def __init__(self):
        self.brain = Brain()
        self.asking_list = []

    def ask(self, sentence):
        self.asking_list.append(sentence)
        path = self.brain.search_brain(sentence)
        if path:
            return self.brain.open_template(path)
        else:
            return "发生了某个错误。"

    def trainning(self):
        """trainning all the file in dir: trainning/"""
        for filename in glob.glob(os.path.join(TRAINNING_DATA_DIR, '*.json')):
            json_list = parse_trainning_data(filename)
            for item_dict in json_list:
                self.brain.saving_and_update_brain(item_dict)

    def trainning_request(self, item_dict):
        """trainning for flask request"""
        # TODO: 由于用户的输入极容易出错，增加logger的必要性就更强了
        self.brain.saving_and_update_brain(item_dict)

    def rebuild(self):
        """destroy then invoke trainning"""
        self.brain.destroy_brain()
        self.trainning()

    def run(self):
        c = ''
        while 1:
            c = input('> ')
            if c == '退出':
                break
            print(self.ask(c))
