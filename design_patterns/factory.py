"""工厂模式


所有工厂模式都是用来封装对象的创建。
之所以不用函数，是因为函数不好扩展。

工厂本身也可以作为抽象类，视为一个简单工厂（这时候把创建对象的
那个函数当做虚函数），然后在其上派生出具体工厂类，再覆盖那个用
来创建对象的函数，就可以使得加工方式改变的时候不必重写某个工厂
了，只需要继承基类然后重新申明一个工厂类就行了。
"""
from abc import ABC, abstractclassmethod


class Pizza(ABC):

    @abstractclassmethod
    def making_step_1():
        ...
    
    @abstractclassmethod
    def making_step_2():
        ...


class NYChessePizza(Pizza):
    """做一个pizza的基本步骤不会怎么变化，所以接口不会变化
    面向接口编程。
    
    这样即使里面的实现调整了，也不会影响商店代码。
    """
    def making_step_1():
        pass
    
    def making_step_2():
        pass


class PizzaStore(ABC):
    @abstractclassmethod
    def create_pizza(pizza_type):
        ...


class NYPizzaStore(PizzaStore):
    def order_pizze(self, pizza_type):
        pizza = None
        pizza = self.create_pizza(pizza_type)
        # 这里的关键就在于先确定了做披萨的基本步骤不会变，并且确定了要变的是有新店加盟和新pizza出来
        # 因此只要去想那两种变化到来的时候，可以弹性扩展，不用写恶心的代码就行了。
        pizza.making_step_1()
        pizza.making_step_2()

        return pizza

    def create_pizza():
        if pizza_type == "chesse":
            return NYChessePizza()
        else:
            pass


def order(store):
    pizza = None
    if store == 'NY:
        # 纽约披萨
        store = NYPizzaStore()
        pizza = store.order_pizze('chesse')
    return pizza
