import jieba
import jieba.analyse


class Segment(object):
    def __init__(self):
        self.seg_list = ''

    def cut(self, string_):
        # 返回的是 generator
        self.seg_list = jieba.cut(string_)  # 默认是精确模式
        return self.seg_list

    def extract_keywords(self, string_):
        # 返回的是 list
        # jieba.analyse.extract_tags(
        #   sentence, topK=20, withWeight=False, allowPOS=())
        return jieba.analyse.extract_tags(
            string_, topK=2, withFlag=False, allowPOS=())


if __name__ == '__main__':
    s = Segment()
    content = '中国人民日报'
    print('/'.join(s.cut(content)))
    print(s.extract_keywords(content))
