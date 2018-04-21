"""观察者模式

你是推送者，你要让你的订阅者们同时收到推送。。
"""


class WeatherData:
    """天气数据"""

    def __init__(self):
        self.observers = []
        self.temperature = 0
        self.humidity = 0
        self.pressure = 0
        self.heatindex = 0

    def add_observer(self, o):
        self.observers.append(o)

    def remove_observer(self, o):
        self.observers.append

    def notify_observers(self):
        for o in self.observers:
            o.update(self.temperature, self.humidity, self.pressure)

    def pull(self):
        print("w: observer pull my data")
        return self.heatindex

    def measurements_changed(self):
        self.notify_observers()

    def set_measurements(self, t, h, p, heatindex=None):
        print("w: weather data changed !")
        self.temperature = t
        self.humidity = h
        self.pressure = p
        self.heatindex = heatindex
        self.measurements_changed()


class DisplayerBase:

    def __init__(self, weather_data):
        self.weather_data = weather_data
        self.weather_data.add_observer(self)

    def update(self, t, h, p):
        """数据更新"""
        self.temperature = t
        self.humidity = h
        self.pressure = p
        self.display()

    def display(self):
        print(
            f'{type(self).__name__} {self.temperature} {self.humidity} {self.pressure}'
        )


class Displayer1(DisplayerBase):
    """显示器1"""


class Displayer2(DisplayerBase):
    """显示器2"""

    def __init__(self, weather_data):
        self.heatindex = 0
        super().__init__(weather_data)

    def pull(self):
        heatindex = self.weather_data.pull()
        if heatindex:
            self.heatindex = heatindex
            self.display()

    def display(self):
        print(
            f"{type(self).__name__} {self.temperature} {self.humidity} {self.pressure} {self.heatindex or ''}"
        )


if __name__ == '__main__':
    w = WeatherData()
    d1 = Displayer1(w)
    d2 = Displayer2(w)
    # 数据主体更新状态，并且自动推送给所有观察者
    w.set_measurements(1, 2, 3)
    w.set_measurements(2, 3, 4, 10)  # 10 heatindex的值已经更新，但是不会推给它的观察者们
    # 观察者主动获取数据
    d2.pull()
# output:
# w: weather data changed !
# Displayer1 1 2 3
# Displayer2 1 2 3
# w: weather data changed !
# Displayer1 2 3 4
# Displayer2 2 3 4
# w: observer pull my data
# Displayer2 2 3 4 10
