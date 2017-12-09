# coding=utf-8
import os
import json
import shutil
from ..utils.settings import RUNNING_DATA_DIR, TRAINNING_DATA_DIR
from ..utils import Scanner
from .parse import parse_template_json, generate_string_from_tpl


class Brain(object):
    def __init__(self, path1=RUNNING_DATA_DIR, path2=TRAINNING_DATA_DIR):
        self._re_init_(path1, path2)

    def _re_init_(self, path1, path2):
        """每次更新之后需要重新初始化对象。
        """
        with open(os.path.join(path1, 'index.json'),
                  encoding='utf-8') as json_file:
            self.running_data_dir = path1
            self.trainnig_data_dir = path2
            self.tree_root = json.loads(json_file.read())
            self.nodes_count = self.tree_root['nodes_count']
            self.current_node = self.tree_root

    def open_template(self, path):
        path = path[1:]  # since os.path.join can't join name start with slash
        with open(os.path.join(self.running_data_dir, path, 'template.json'),
                  encoding='utf8') as template:
            reply = parse_template_json(template.read())
            # redirect
            if reply[0] == 'R':
                return self.open_template(self.search_brain(reply[1:]))
            elif reply[0] == 'T':
                return generate_string_from_tpl(reply[1:],
                                                self.current_asking_sentence)
            else:
                return reply

    def destroy_brain(self):
        shutil.rmtree(self.running_data_dir)
        os.makedirs(self.running_data_dir)
        # initial index.json
        with open(os.path.join(self.running_data_dir, 'index.json'), 'w+',
                  encoding='utf8') as json_file:
            initial_json_data = {
                'word': '',
                'child_nodes': [],
                'nodes_count': 0
            }
            json_file.write(json.dumps(initial_json_data, ensure_ascii=False))
        self._re_init_(self.running_data_dir, self.trainnig_data_dir)

    def update_brain(self, new_words):
        """Update the index.json

        new_words: 已经分词的问句。
        """
        self._update(new_words)
        # 重新覆盖一次 index.json，或许效率有点低。
        with open(os.path.join(self.running_data_dir, 'index.json'), 'w',
                  encoding='utf8') as json_file:
            json_file.write(json.dumps(self.tree_root, ensure_ascii=False))
        # 重新初始化对象
        self._re_init_(self.running_data_dir, self.trainnig_data_dir)

    def saving_and_update_brain(self, input_dict):
        """
        input_dict:
                训练样本里最小的单位，包含 asking 和 reply 字段。
        """
        # need split the sentence into words
        s = Scanner()
        for asking_str in input_dict['ask']:
            pattern_list = s.get_tag(asking_str, remove_punctuations=True)
            # construct the path
            # U -> %U
            pattern_list = ['%' + d if d in ['U', 'S'] else d
                            for d in pattern_list]
            generated_dir = os.path.join(self.running_data_dir,
                                         '/'.join(pattern_list))
            generated_full_path = os.path.join(generated_dir, 'template.json')

            template_json = input_dict['reply']
            # save file
            if not os.path.exists(generated_dir):
                os.makedirs(generated_dir)
            with open(generated_full_path, 'w+', encoding='utf8') as fp:
                fp.write(json.dumps(template_json, ensure_ascii=False))
            self.update_brain(pattern_list)

    def _generate_node_by_words(self, words):
        current_node = None
        for d in words:
            if not current_node:
                result = current_node = {
                    'word': d,
                    'child_nodes': [],
                }
            else:
                new_node = {
                    'word': d,
                    'child_nodes': [],
                }
                current_node['child_nodes'].append(new_node)
                current_node = new_node
        current_node['isLeaf'] = True
        return result

    def _get_index_in_nodes_list(self, chars, node):
        """
        return:
        The index correspond char if exists, False if not exists.
        """
        for i, d in enumerate(node['child_nodes']):
            if d['word'] == chars:
                return i
        # if not exists, return -1
        return -1

    def _update(self, words):
        for i, word in enumerate(words):
            index = self._get_index_in_nodes_list(word, self.current_node)
            if index != -1:
                self.current_node = self.current_node['child_nodes'][index]
            else:
                self.current_node['child_nodes'].append(
                    self._generate_node_by_words(words[i:]))
                return
        # found an exist node, so tags it as a leaf node
        self.current_node['isLeaf'] = True

    def search_brain(self, ask_sentence):
        """搜索 index.json 内是否有条记录。返回对应的路径。
        """
        # need split
        s = Scanner()
        words = s.get_tag(ask_sentence, remove_punctuations=True)
        self.current_asking_sentence = ' '.join(words)  # 保留一下分词后的结果
        return self._search(words, self.tree_root)

    def _search(self, words, root):
        """
        return:
        The template's path if found, None if not found.
        Note:
        Only leaf node has template.
        """
        # for 'U(nderscore)'
        if len(words) == 0:
            return root['word'] if root.get('isLeaf') else None

        index = self._get_index_in_nodes_list("%U", root)
        if index != -1:
            next_node = root['child_nodes'][index]

            for i in range(len(words)):
                suffix = words[i + 1:]
                mid_result = self._search(suffix, next_node)
                if mid_result:
                    return root['word'] + '/' + mid_result

        # for 'W(ord)'
        index = self._get_index_in_nodes_list(words[0], root)
        if index != -1:
            next_node = root['child_nodes'][index]
            mid_result = self._search(words[1:], next_node)
            if mid_result:
                return root['word'] + '/' + mid_result

        # for 'S(tar)'
        index = self._get_index_in_nodes_list('%S', root)
        if index != -1:
            next_node = root['child_nodes'][index]
            for i in range(len(words)):
                suffix = words[i + 1:]
                mid_result = self._search(suffix, next_node)
                if mid_result:
                    return root['word'] + '/' + mid_result

        return None
