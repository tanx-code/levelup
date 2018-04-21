"""状态机模式

允许对象在内部状态改变时改变它的行为，对象
看起来好像改了它的类。
"""
class State:
    def __init__(self, m):
        self.machine = m

class AState(State):
    def db_a(self):
        print('do a')
        self.machine.set_state(self.machine.b_state)

class BState(State):
    def do_b(self):
        print('do b')


class Machine:

    current_state = None

    def run(self):
        self.a_state = AState(self)
        self.b_state = BState(self)
        self.current_state = self.a_state

    def do_a(self):
        self.current_state.do_a()

    def do_b():
        self.current_state.do_b()

    def set_state(state):
        self.current_state  =  state


if __name__ == '__main__':
    m = Machine()
    # 对于客户来说，不知道机器内部状态在怎么变化
    m.do_a()
    m.do_b()
