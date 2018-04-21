"""策略模式

定义的是算法族，分别封装起来，让他们之间可以互相替换。此模式让算
法的变化独立于使用算法的客户(程序员)。

细节实现：
把不变的那部分逻辑放到父类里，然后把会经常变化的那部分逻辑抽象成
另外一个类，把这个类的实例作为父类(以及将来的子类)的一个属性，需
要把接口的名字定死，以建立一个编写的准则。

其实python里面因为变量可以随便绑定到不同的类型上，所以非常简单粗
暴的以另一种方式实现了c++等语言里的多态。
"""
from abc import ABC, abstractmethod


# =====
class Duck:
    brief = "I'm a normal duck."

    def __init__(self):
        print(self.brief)

    def perform_fly(self):
        self.flyBehavior.fly()


class FlyBehavior(ABC):

    @abstractmethod
    def fly(self):
        ...


class FlyStraight(FlyBehavior):

    def fly(self):
        print("I'm flying straight.")


class FlyWithTalking(FlyBehavior):

    def fly(self):
        print("I'm flying with talking.")


# =====
class GreenDuck(Duck):
    brief = "I'm a green duck, i can fly straight."

    def __init__(self):
        self.flyBehavior = FlyStraight()
        super().__init__()


class TalkingDuck(Duck):
    brief = "I'm a talking duck, i can fly with talking."

    def __init__(self):
        self.flyBehavior = FlyWithTalking()
        super().__init__()


if __name__ == '__main__':
    GreenDuck().perform_fly()
    TalkingDuck().perform_fly()
