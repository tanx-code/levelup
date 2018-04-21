"""代理模式

为另一个对象提供一个替身或占位符(一个代表)
以控制或者说保护对这个对象的访问

现实中的例子就是，明星需要一个经济人来帮她
搭理一些繁琐的事情，经纪人就充当代理的作用，
电话打进来先经过经纪人。

使用场景：当两个类之间要交流，但是让他们获
得交流能力的代码，变得复杂的时候，就需要用
代理模式来把客户和服务解耦。虽然和适配器有
点像，但是意图不一样，适配器是为了很多个不
同客户端，这里是为了将交流代码解耦。
"""

class Server:
    pass

class Proxy:
    def __init__(self, a_server_instance):
        pass

    def send():
        pass

    def recv():
        pass

class Client:
    def interact_with_server(self, server):
        pass

if __name__ == '__main__':
    client = Client()
    server = Server()
    server = Proxy(server)
    client.interact_with_server(server)
