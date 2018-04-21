"""装饰者模式

扩展一个类，用继承的话，是在编译期就确定的。
但是用下面这样的包装的话，可以在运行时确定。
这是一个很好的思路。
"""


class Drink:

    def cost(self):
        return 1


class Milk(Drink):

    def __init__(self, a):
        self.drink = a

    def cost():
        return self.drink.cost() + 1.2


class Sugar(Drink):

    def __init__(self, a):
        self.drink = a

    def cost():
        return self.drink.cost() + 1.4


drink = Drink()
milk_drink = Milk(drink)
sugar_milk_drink = Sugar(milk_drink)
