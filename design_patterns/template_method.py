"""模板方法

就是把两个类的某个公共方法里的步骤细分，
抽出重复的代码放到父类，然后把不重复的代码，封装成抽象函数，
让那两个子类自己去实现。
"""

class Drink:
    # 泛化了的制作步骤，这个 make 就是模板方法，任何子类都不应该修改它
    def make(self):
        self.procedure1()
        self.procedure2()
        if self.hook():
            self.procedure3()

    # 每个子类对这个步骤都不同，所以变成抽象方法
    @abstractmethod
    def procedure1():
        pass

    # 下面两个方法都在父类里实现了具体的内容
    def procedure2():
        pass

    def procedure3():
        pass

    # 上面说任何子类都不能修改 make，那假如以后有一个新的子类
    # 有新的需求，需要修改 make 怎么办呢
    # 这就是 hook 函数的作用了，一般会提供一个默认值
    # 如果子类要改变，那子类自己去实现它
    def hook():
        return True

class Tea:
    def procedure1():
        print('tea procedure1')

class Coffe:
    def procedure1():
        print('coffe procedure1')

    # 询问客户是否需要 procedure3 。
    def hook():
        answer = ask_uer()
        if answer == 'y':
            return True
        return False


if __name__ == '__main__':
    Coffe().make()
    Tea().make()