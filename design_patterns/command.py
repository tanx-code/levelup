"""命令模式

命令和命令接受者，与，顾客和调度程序，之间的解耦

跟任务队列的思想是一样的。
"""

class Command:
    def run(self):
        pass

class CmdA(Command):
    pass

class CmdB(Command):
    pass

class Receiver:
    def deal(self, cmd):
        pass


class Schedule:
    def __init__(r: Receiver):
        self.receiver = r

    def schedule(cmd: Command):
        r.deal(cmd)


if __name__ == '__main__':
    r = Receiver()
    ca = CmdA()
    cb = CmdB()
    s = Schedule(r)
    Schedule.schedule(ca)
    Schedule.schedule(cb)
