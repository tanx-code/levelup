"""单件模式

在程序整个生命周期内都只有一个实例存在
"""

# 这个没有考虑多线程创建的情况
class Singleton:
    the_only_instance = None

    def __init__(self):
        if Singleton.the_only_instance:
            raise Exception('only one singleton')
        Singleton.the_only_instance = self


# 这个多线程创建也不会有问题
# stackoverflow 上看到的，一开始还不懂，撇了一眼评论
# 所有的实例分享同一个__dict___，真是邪恶。
class Borg:
    __shared_state = {}
    def __init__(self):
        self.__dict__ = self.__shared_state
