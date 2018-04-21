"""适配者模式

将一个类的接口，转换成客户期望的另一个接口。适配器让原本接口不兼容
的类可以合作无间。

就是你已经有一个A类在做事了，但是突然来了个异端B类，要做同样的事情，
但是B类却没有实现同样的方法，这时候就需要一个适配类，来把B类转换成
与A类有同样接口的新类C，这时候C可以放心的去替换任何A可以做的工作了。

所以场景是：
当你必须将若干个类整合在一起来提供你的客户所期望的接口。

说实话，是不是和装饰器模式有些许相似呢。不同之处在于使用意图。

讨论：
同样是包装一个接口，
装饰模式：接口不变，新增了一些责任
适配者模式：将接口变成不同接口，最终使用的目的不变。
外观模式：简化接口，将使用接口的代码，从原本复杂的子系统里解耦。
（定义是：提供了一个统一的接口，用来访问子系统中的一群接口，使得
子系统更容易使用）
"""

class Server:
    pass

class ServerAdapter:
    def interact_with_server(self):
        pass


class ClientA(ServerAdapter):
    def interact_with_server(self):
        return self.send_utf8()

    def send_utf8(self):
        pass


class ClientB(ServerAdapter):
    def interact_with_server():
        return self.send_utf16()

    def send_utf16(self):
        pass

class People:
    pass

if __name__ == '__main__':
    s = Server()
    a = ClientA()
    b = ClientB()
    """
    People use b.interact_with_server() to get Response
    but don't know the exists of ServerAdapter
    """
    b.interact_with_server()
