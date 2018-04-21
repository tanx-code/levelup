"""迭代器模式
提供一种方法顺序访问一个聚合对象中的各个元素，
而又不暴露其内部的表示。

就是把遍历一个collection的代码解耦。使得那些
需要遍历它们的代码，不用为每个collection都写
一套遍历算法。

设计原则：一个类应该只有一个引起变化的原因

组合模式

当你有数个对象的集合，它们彼此之间有整体/部分的关系
并且你想用一致的方式对待这些对象时，就需要用组合
模式。

具体做法是，写一个新的类，叫组件类，这个类可以同时
是菜单，也可以是一个菜单项，但是你对它的操作是统一
的。
"""

class HashMap:
    def __iter__():
        pass

class List:
    def __iter__():
        pass

class MenuComponent:
    def __iter__():
        pass

# 因为都是 列表组件，所以它们在迭代的时候，下一个元素
# 也是列表组件，因此可能是Menu也可能是MenuItem。
class Menu(MenuComponent)
    def __iter__():
        pass
        
class MenuItem(MenuComponent):
    def __iter__():
        pass

