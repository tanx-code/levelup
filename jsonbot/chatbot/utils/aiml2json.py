# coding=utf-8
import xml.etree.ElementTree as ET
import glob
import os
import json

from .settings import AIML_CORPUS_DIR, TRAINNING_DATA_DIR


def parse_aiml_to_jsonbot():
    """aiml's xml to jsonbot's json
    ignore elements: <that> , <srai>..<star>.., <template>..<li>..<star>
    """
    for filename in glob.glob(os.path.join(AIML_CORPUS_DIR, '*.xml')):
        result = []
        tree = ET.parse(filename)
        root = tree.getroot()
        for child in root:
            # category
            mini_unit = {}
            pattern = child.find('pattern')
            template = child.find('template')
            template_list = []

            # remove space
            pattern = _r_b(pattern.text)
            pattern = pattern.replace('*', 'S')
            pattern = pattern.replace('_', 'U')
            mini_unit['ask'] = [pattern]

            common_text = template.text or ''
            if common_text:
                common_text = _r_b(common_text)
            srai_tag = template.find('srai')
            if srai_tag is not None:
                tmpl_text = ''
                tmpl_text = tmpl_text + (srai_tag.text or '')
                # parse <star/>
                if srai_tag.find('star'):
                    tmpl_text = tmpl_text + 'S' + \
                        'S'.join([d.tail for d in srai_tag if (
                            d.tail != ' ' and d.tail)])
                # parse srai_tag.tail
                tmpl_text = tmpl_text + (srai_tag.tail or '')
                template_list.append('R' + _r_b(tmpl_text))
            random_tag = template.find('random')
            if random_tag is not None:
                template_list = template_list + \
                    [_r_b(common_text + (li.text or '') +
                          (random_tag.tail or '')) for li in random_tag]
            else:
                if common_text:
                    template_list.append(common_text)
            mini_unit['reply'] = template_list
            result.append(mini_unit)

        with open(os.path.join(TRAINNING_DATA_DIR,
                               os.path.basename(filename).split('.')[0]
                               + '.json'),
                  'w+', encoding='utf8') as fp:
            fp.write(json.dumps(result, ensure_ascii=False,
                                sort_keys=True, indent=4,
                                separators=(',', ': ')))


def _r_b(string):
    """remove blank"""
    return ''.join(string.split())
