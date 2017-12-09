# Effective Python

<!-- TOC -->

- [Effective Python](#effective-python)
    - [tip1 确认你用的python版本](#tip1-确认你用的python版本)
    - [tip2 遵循 PEP8 风格指南](#tip2-遵循-pep8-风格指南)
    - [tip3 了解 bytes、str、unicode 的区别](#tip3-了解-bytesstrunicode-的区别)
    - [tip4 辅助函数代替复杂的表达式](#tip4-辅助函数代替复杂的表达式)
    - [tip5 学会切割序列的方法](#tip5-学会切割序列的方法)
    - [tip6 切割序列的时候，不要同时指定三个参数](#tip6-切割序列的时候不要同时指定三个参数)
    - [tip7 列表推导](#tip7-列表推导)
    - [tip8 列表推导虽好，别嵌套太多层](#tip8-列表推导虽好别嵌套太多层)
    - [tip9 生成器替代列表推导](#tip9-生成器替代列表推导)
    - [tip10 知道enumerate吗](#tip10-知道enumerate吗)
    - [tip11 知道zip吗](#tip11-知道zip吗)
    - [tip12 不要使用for else/while else 语法](#tip12-不要使用for-elsewhile-else-语法)
    - [tip13 合理使用try/except/else/finally](#tip13-合理使用tryexceptelsefinally)
    - [tip14 函数返回 None 的弊端](#tip14-函数返回-none-的弊端)
    - [tip15 闭包里需要注意的问题](#tip15-闭包里需要注意的问题)
    - [tip16 用 yield 写的生成器](#tip16-用-yield-写的生成器)
    - [tip17 迭代器从函数参数里传进函数里的时候需要注意的问题](#tip17-迭代器从函数参数里传进函数里的时候需要注意的问题)
    - [tip18 数量可变的位置参数](#tip18-数量可变的位置参数)
    - [tip19 可选参数（带默认值的参数）](#tip19-可选参数带默认值的参数)
    - [tip20 动态默认值参数](#tip20-动态默认值参数)
    - [tip21 用关键字形式指定函数参数来确保代码清晰](#tip21-用关键字形式指定函数参数来确保代码清晰)
    - [tip22 当你需要一个含有多个dict/tuple嵌套的数据结构时，考虑使用类来让代码清晰](#tip22-当你需要一个含有多个dicttuple嵌套的数据结构时考虑使用类来让代码清晰)
    - [tip23 给接口传一个函数(hook)当做参数，有时候带来很多好处](#tip23-给接口传一个函数hook当做参数有时候带来很多好处)
    - [tip24 感觉@classmethod的作用有一部分是补充python的多态能力](#tip24-感觉classmethod的作用有一部分是补充python的多态能力)
    - [tip25 请用super来调用父类](#tip25-请用super来调用父类)
    - [tip26 多继承最好只用在混合功能(其他类的功能)的时候](#tip26-多继承最好只用在混合功能其他类的功能的时候)
    - [tip27 public\_method, \_\_private\_method, \_protected\_method](#tip27-public\_method-\_\_private\_method-\_protected\_method)
    - [tip28 定义你自己的容器类的时候，继承 collections.abc 里面的那些抽象基类(序列，集合等等)，会减少你的工作](#tip28-定义你自己的容器类的时候继承-collectionsabc-里面的那些抽象基类序列集合等等会减少你的工作)
    - [tip29 直接使用attribute本身，而不是get\set函数](#tip29-直接使用attribute本身而不是get\set函数)
    - [tip30 使用 \@property 来使成员获得更多功能](#tip30-使用-\property-来使成员获得更多功能)
    - [tip31 使用描述符来使 \@property 可复用](#tip31-使用描述符来使-\property-可复用)
    - [tip32 \_\_getattr\_\_, \_\_getattribute, \_\_setattr\_\_ 的使用](#tip32-\_\_getattr\_\_-\_\_getattribute-\_\_setattr\_\_-的使用)
    - [tip33 元类](#tip33-元类)
    - [tip34 用元类来注册子类](#tip34-用元类来注册子类)
    - [tip35 用元类来注解类的属性](#tip35-用元类来注解类的属性)
    - [tip36 用 subprocess 来管理子进程](#tip36-用-subprocess-来管理子进程)
    - [tip37 threading 来执行阻塞式IO](#tip37-threading-来执行阻塞式io)
    - [tip38 在线程中使用 Lock 来防止数据竞争](#tip38-在线程中使用-lock-来防止数据竞争)
    - [tip39 学会用 Queue](#tip39-学会用-queue)
    - [tip40 协程](#tip40-协程)
    - [tip41 concurrent.futures 你用对了吗](#tip41-concurrentfutures-你用对了吗)
    - [tip42 用 functools.wraps 来保留装饰器里的的函数签名等信息](#tip42-用-functoolswraps-来保留装饰器里的的函数签名等信息)
    - [tip43 用 contextlib 和 with 来改写可复用的 try/finally](#tip43-用-contextlib-和-with-来改写可复用的-tryfinally)
    - [tip44 用 copyreg 实现可靠的 pickle 操作](#tip44-用-copyreg-实现可靠的-pickle-操作)
    - [tip45 请用 datetime 来处理本地时间](#tip45-请用-datetime-来处理本地时间)
    - [tip46 内置数据结构](#tip46-内置数据结构)
    - [tip47 在重视精度的场合请使用 decimal](#tip47-在重视精度的场合请使用-decimal)
    - [tip48 使用社区的包](#tip48-使用社区的包)
    - [tip49 模块、类、类的public接口、都要写docstring](#tip49-模块类类的public接口都要写docstring)
    - [tip50 用包来管理模块，并提供稳固的API](#tip50-用包来管理模块并提供稳固的api)
    - [tip51 为自建的模块提供根异常类](#tip51-为自建的模块提供根异常类)
    - [tip52 出现循环 import](#tip52-出现循环-import)
    - [tip53 虚拟环境 3.4开始可以用pyvenv](#tip53-虚拟环境-34开始可以用pyvenv)
    - [tip54 不同环境的部署](#tip54-不同环境的部署)
    - [tip55 print调试大法](#tip55-print调试大法)
    - [tip56 python代码的动态性决定你必须要好好为它写测试](#tip56-python代码的动态性决定你必须要好好为它写测试)
    - [tip57 可以用 pdb 来调试](#tip57-可以用-pdb-来调试)
    - [tip58 先profile，再优化代码](#tip58-先profile再优化代码)
    - [tip59 tracemalloc 来掌握内存的使用以及泄露情况，py3.4+](#tip59-tracemalloc-来掌握内存的使用以及泄露情况py34)

<!-- /TOC -->

## tip1 确认你用的python版本

估计等到这个书下次修订的时候，这一条已经删了，（逃

## tip2 遵循 PEP8 风格指南

https://www.python.org/dev/peps/pep-0008/

## tip3 了解 bytes、str、unicode 的区别

python3 里只有两种表示字符序列的类型，bytes(原始的8位字节类型) 和 str(=unicode)

## tip4 辅助函数代替复杂的表达式

这一条就是叫你们不要为了追求一行而装逼

## tip5 学会切割序列的方法

a[x1:x2:x3] 里参数x1是start index,x2是end index,x3是stride

b = a[:] 这样会在内存里产生一份新的a列表的拷贝。
a[:] = [1,2,3] 这样会把赋值语句右边的list的内容拷贝到a指向的那块内存！这里不是a的重新绑定！我一直以为python里根本没法赋值的同时避免重新绑定，直到看到了这个。

## tip6 切割序列的时候，不要同时指定三个参数

拆分成两步来做，代码更容易看懂。

我才知道 list reverse 这个问题，在python里，只需要 list[::-1] 就行了。


## tip7 列表推导
list, dict, set 都可以用这种推导的机制。

```python
list_a = [d for d in range(5)]
dict_a = {d:d for d in range(5)}
set_a  = {d for d in range(5)}
```
语法上比 map\filter\.. 简洁许多，但不意味着你应该总选择它。因为当二者同时用到相同的外部函数时，map 效率更高，当 map 用到匿名函数时，list comprehension效率更高。[见这个讨论](https://stackoverflow.com/questions/1247486/python-list-comprehension-vs-map)

总结就是简单的都用list comprehension，需要调用非匿名函数的时候用 map\filter...。


## tip8 列表推导虽好，别嵌套太多层

完

## tip9 生成器替代列表推导

列表推导是每一步立即执行的，生成器会立即返回，延迟计算。

生成器是个好东西，只是用过一次，状态就变了，`next(it)`一次，迭代器就前进一步，所以你并不能像重复使用一个list那样重复使用一个迭代器。

## tip10 知道enumerate吗

完

## tip11 知道zip吗

zip生成器的长度取决于输入中长度低的那个列表

如果非得要留长的，请考虑 itertools 内置模块中的 zip_longest

## tip12 不要使用for else/while else 语法

因为这种语法语义不清晰，用别的方式取代

## tip13 合理使用try/except/else/finally

try/finally

try/except/finally

try/except/else

try/except/else/finally

## tip14 函数返回 None 的弊端

如果使用者拿函数返回值来做条件判断，如果返回值中0是合法的，但在 `if not result` 里也会被当做与None等价。

因此这种情况，在函数里抛出异常，并写进函数的文档里，让使用者自己来处理异常，是一个明智的选择。

## tip15 闭包里需要注意的问题

这一条里讲了个技巧，(0, 3) 元组或者列表之间比较，是按索引从0开始比较对应的元素。这在 list.sort 的时候写 key 函数很有用。

然后，`nonlocal` 允许你在相关变量赋值的时候，查找它的上一层作用域，但是不会延伸到模块级别，怕污染全局作用域。起到的作用和`global`类似，相当于对`global`的补充。（这看起来是一个好的补充）

如果你的函数很长，`nonlocal`声明的变量可能离你真正的赋值语句很远，这时候可能会很难看懂代码。一般，可以把这个函数弄成一个类，并且实现一个`__call__`方法就行了。这样的实例将变成一个等价于`__call__`方法的函数。


## tip16 用 yield 写的生成器
以前一直不知道yield怎么用，其实正确的抽象，应该是，yield某个内容到一个虚拟的暂存列表里，然后每次next，函数就推进到下一个yield，直到遇到return或者函数末尾。

生成器在取代有大量内容的列表的时候，非常高效。


## tip17 迭代器从函数参数里传进函数里的时候需要注意的问题
我们知道一个迭代器用过一次就没用了。当你把它当做函数参数传进来的时候，你可能会在函数里多次用到它，但是第一次用完之后，它将永远返回`[]`。这个问题怎么解决呢？

写一个class，实现里面的`__iter__`方法就行了。那些for，list推导什么的，在迭代迭代器(或者容器类实例)的时候，先会调用`iter()`函数，当`iter()`函数接收到一个迭代器的时候，它会返回这个迭代器；当`iter()`函数接收到一个容器类实例的时候，它会调用这个实例的`__iter__`方法，所以每次都会返回一个新的迭代器。最后`next()`开始真正的迭代。

## tip18 数量可变的位置参数
`def test(a, b, *values)` 这样就可以接收用`,`分隔的多个参数，或者用`*`开头的一个列表(迭代器)。e.g.`test(1,2,3,4) or test(1,2,3,*[1,2,3,4])`

## tip19 可选参数（带默认值的参数）
`def test(a,b, exist=True)`，exist就是可选的参数，调用的时候，但是a,b,exist都可以用关键字参数来调用，`test(a=1,b=2,exist=False)`，其中参数的顺序可以随意`test(exist=False,a=1,b=2)`，但是一定要注意位置参数必须出现在关键字参数之前(定义的时候不这么做就会错，调用的时候当然也错)。这种`def test(exist=False,a,b) 以及 test(exist=False,1,2)`就是错的。

## tip20 动态默认值参数
有时候默认值参数的类型或者值需要动态的得出，所以这种情况，一般都把它设置为None，并且在docstring里写清楚这个值的是关于什么的，有哪些可能出现的结果，调用的时候该怎么注意。


## tip21 用关键字形式指定函数参数来确保代码清晰

python3 中，这样写 `def test(a, b, height=1,width=1)`，所有的参数可以直接按照参数位置调用或者关键字参数调用，`test(1,2,3,4)`；这样写 `def test(a, b, *, height=1, width=1)`，就能限定只能使用关键字调用而不能依赖位置了。

python2 虽然不同，但好像可以不用关心了。（逃

## tip22 当你需要一个含有多个dict/tuple嵌套的数据结构时，考虑使用类来让代码清晰

讲了一个成绩单，学生，成绩，科目的例子。这一条看起来是教你怎么解耦复杂难看的代码。

## tip23 给接口传一个函数(hook)当做参数，有时候带来很多好处

python的函数是第一级别对象(first-class我觉得代表自由度最高吧)，所以你可以传一个def 定义的函数当参数，也可以传类的实例的方法(得益于bound method的self参数在调用的时候会默认填充)当参数。这样当你想获得hook里的状态的时候，可以通过闭包实现，也可以通过构造类来实现，后者代码看上去更清晰一些。

当然，如果定义了`__call__`方法，类的对象可以直接被调用，意味着也能在这种情况下充当函数了。显然比上面说的进一步清晰了。


## tip24 感觉@classmethod的作用有一部分是补充python的多态能力


@classmethod 修饰的是类的方法，如果该方法返回值是类的实例，那么起到的效果就和你重载了`__init__`方法一样。由于这个方法可以被子类继承，传进来的cls参数就具有了多态性，你用硬编码是做不到的。

```python
class animal(object):
    @classmethod
    def copyMySelf(cls):
        return cls()
[animal.copyMySelf() for animal in [Dog(),Cat(),Pig()]]
```


## tip25 请用super来调用父类

用super才能保证在多继承里不会出错，用super的时候大家继承链搜索的规则是统一的。


## tip26 多继承最好只用在混合功能(其他类的功能)的时候

平行的多继承怎么用才对呢，就是在每一个即将继承的父类中，实现的新功能要是实例级别的功能，这个功能将在混合类中使用。换句话说，当你知道自己要将这个类混合到一个新的孩子类中时，你就要在这个类里为混合的孩子类做打算，要混合的其他的父类的功能对你来说都是可用的了。保证最后，孩子类获得的是一个简单的接口。

跟朋友讨论了一下多继承，如果是取两个不相干的类，以达到将它们功能简单叠加的目的，是用不着多继承的，直接把两个类写进类的成员里就行了。所以一般是当你需要将两个类的某些功能合到一起，并且创造一个新的功能的时候，可以用多继承，这个功能写在某个父类里也行(如上面所讲，这条tip就是写在父类)，写在这个新类里也行。

（这一条有点没弄清作者说的意图）

## tip27 public\_method, \_\_private\_method, \_protected\_method

python在语法上只有两种类方法权限，公有和私有，但是单个下划线开头一般也被当成私有（虽然是假的实现），针对的是类的使用者，因为单个下划线能保证在多继承的时候不出问题。

## tip28 定义你自己的容器类的时候，继承 collections.abc 里面的那些抽象基类(序列，集合等等)，会减少你的工作

原因是那些抽象基类会提示你，要让你的类将来可以和python里的各种内置函数适应的话，需要至少实现哪些功能。


## tip29 直接使用attribute本身，而不是get\set函数

就是叫你直接用a.attr来读写这个属性，而不是在上面包一层get\set函数，如果你真的需要函数的话，那么也用python的@property来做。

## tip30 使用 \@property 来使成员获得更多功能

但是 @property 装饰的函数也不能做太多事，这个函数的定位是快速的，不能太笨重。

## tip31 使用描述符来使 \@property 可复用

就是在外部定义一个描述符类，来代替@property。

## tip32 \_\_getattr\_\_, \_\_getattribute, \_\_setattr\_\_ 的使用

`__getatrr__` 会拦截所有不在实例的dict里的成员变量获取

`__getattribute__` 会拦截所有的成员变量获取

`__setattr__` 会拦截所有的成员变量设置

为了避免无限循环调用`__getattr__`等，记得用`super()`来调用。

## tip33 元类

```python
class Meta(type):
    def __new__(meta, name, bases, class_dict):
        # meta 本身的名字
        # name 新类的名字
        # bases 新类继承的类的名字
        # class_dict 新类里的所有成员dict，(可以取到类的所有内容)
        return type.__new__(meta, name, bases, class_dict)
class NewClass(object, metaclass=Meta):
    ...
```
在新类的整个定义全部结束时，才会调用元类的`__new__`函数。

元类是可以被继承的，比如上面NewClass，如果被继承，那么子类同样会有元类。

p.s. 动态创建类可以这么做。(所以元类起到的作用应该是在不修改已有类代码的基础上对该类进行修改。)
```python
new_class = type("NewClassName", (BaseClass), {"new_method": lambda self: ...})
```


## tip34 用元类来注册子类

为了讲明这一条，作者举了个序列化反序列化的例子，看的略费劲，好在看懂了，我来总结一下。

让你把一个对象序列化为一个字符串，然后立即从这个字符串反序列化出一个内容与原对象保持一致的对象，你会怎么设计程序？

你说设计一个有序列化和反序列化成员函数的类，就行了。那么反序列化的时候，需要你知道这个字符串是由什么类转换过来的，然后通过调用`class_name.deserialize(str_data)`来做。那如果我要求将 记忆类名 这件事交给程序来做，该怎么办呢？

你说序列化的时候同时往字符串里插上类名({class_name:xxx,value:xxx})，然后反序列化只要根据字符串里的类名，就能知道这个类能不能用某个通用的反序列化函数。当然这里有个前提，你得维护一个类名->是否能使用反序列化函数的字典。

你说，在每个写好的类后面，写一句`注册到字典(类名)`的函数，就行了。那么类一多，你很可能忘记。

你说，放在元类里做。完。

## tip35 用元类来注解类的属性

你知道 @property 可以管理类的属性，当你想把某个属性的实际值放在一个保护起来的实例内部属性里时，事情可能会有点麻烦。

```python
class Field(object):
    def __init__(self, name):
        self.internal_name = 'db_' + name
    def __get__xxx:
        getattr(xxx)
    def __set__(self, instance, value):
        settattr(instance, self.internal_name, value)

class Student(object):
    name = Field('name')
    id = Field('id')
    .
    . 这里假如数据库里一行有很多属性
```

每一个属性都要写两遍名字，很烦。

```python
class Meta(type):
    def __new__(meta, name, ases, class_dict):
        for k, v in class_dict:
            if isinstance(v, Filed):
                settattr(v, 'internal_name', 'db_' + k)
        return type.__new__(meta, name, bases, class_dict)

class Field(object, metaclass=Meta):
    def __get__xxx:
        getattr(xxx)
    def __set__(self, instance, value):
        settattr(instance, self.internal_name, value)

class Student(object):
    name = Field()
    id = Field()
```

少写一点啰嗦的代码了。完。


## tip36 用 subprocess 来管理子进程

subprocess 可以运行命令行的子进程，还可以用管道(e.g. stdin=subprocess.PIPE,stdout=subprocess.PIPE)。这是CPU上的并行。


## tip37 threading 来执行阻塞式IO

python 的 threading 库虽然叫多线程，但在同一时刻只有一个线程在跑，大概就是用户空间的多线程，由python虚拟机调度的，所以一定不能拿它来做计算密集型的任务。可以用来做阻塞任务的并行，因为阻塞任务会触发系统调用。

## tip38 在线程中使用 Lock 来防止数据竞争

python 即使有 GIL，但是它的线程切换，会无差别打断当前字节码的执行，即便这个字节码上下文处于非原子状态（就是在说python才不管你是不是原子操作），碰到这种情况，对一个数据的更改会被弄乱(e.g. a+=1)，于是你可以用threading.Lock来锁住临界空间。python里可以用`with`语句。


## tip39 学会用 Queue

流水线在程序里是提高系统效率的一个聪明的方法，你可以用基本的队列deque自己构造，然而Queue为你实现流水线代码提供了更好的支持。在生产者消费者模型中，Queue就是那个装产品的容器。如果第一级消费者继续作为第二级生产者，那么就可以有一个流水链形成，链里面的每个工作者都是并行在运行的，效率非常高。

## tip40 协程

首先，用生成器来让两个程序看起来能"交替"执行，可以这么写。
```python
In [1]: def run1():
   ...:     it_2 = run2()
   ...:     while True:
   ...:         yield
   ...:         next(it_2)
   ...:         print('run1 running ')
   ...:

In [2]: def run2():
   ...:     while True:
   ...:         yield
   ...:         print('run2 running ')
In [2]: t = run1()

In [3]: next(t)

In [4]: next(t)
run1 running

In [5]: next(t)
run2 running
run1 running

In [6]: next(t)
run2 running
run1 running
```
然后协程机制，就是让你从"生产"变成了"消耗"，而消耗的就是调用协程时send的信息。
```python
In [1]: def run1():
   ...:     it_2 = run2()
   ...:     next(it_2)
   ...:     while True:
   ...:         a = (yield)
   ...:         it_2.send(a)
   ...:         print('run1 running ',a)
   ...:
In [2]: def run2():
   ...:     while True:
   ...:         b = (yield)
   ...:         print('run2 running ', b)
   ...:
```
这么一看其实协成实际上提供的并不是程序的"并行"，上面第一段代码我光用生成器就实现了"并行"啊。（生产代码中内置的协程根本没人用？

关于协程机制的详细介绍。 http://www.dabeaz.com/coroutines/

## tip41 concurrent.futures 你用对了吗

threading 不适合做计算密集型的任务， concurrent.futures.ThreadPoolExecutor 也是线程池，同样有这个局限，你应该选择 concurrent.futures.ProcessPoolExecutor 来做，它会生成多个(取决于max_worker)子进程，并且通过socket在主进程和子进程之间通信，通信的内容是序列化后的python对象等信息，主要开销就在这，不过取得的效果当然要比线程的好，不然谁用。

## tip42 用 functools.wraps 来保留装饰器里的的函数签名等信息

它会将原函数重要的元数据都复制到将返回的函数里。
```python
def decorator(func):
    @functools.wraps
    def wrap():
        ...
    return wrap
```

## tip43 用 contextlib 和 with 来改写可复用的 try/finally

```python
@contextlib.contextmanager
def open(*args, **kwargs):
    fp = open(*args, **kwargs)
    try:
        yield fp
    finally:
        fp.close()
with open('zz.text','w') as fp:
    do something
```

## tip44 用 copyreg 实现可靠的 pickle 操作
pickle 可以将python对象序列化，也可以反序列化还原这个对象，只是如果这个对象对应的类在序列化前后环境里的定义发生改变时，就需要通过 copyreg 模块里的函数来注册 pickle 来保证结果符合预期。

主要的应用场景是在相互信任的程序之间传递这种序列化的程序信息。书上有个例子，比如你玩游戏的存档。可能写起来真的很方便。

## tip45 请用 datetime 来处理本地时间

完

## tip46 内置数据结构

除了 list, dict还有 deque，heapq模块（基于list），defaultdict，OrderedDict。

可以用 bisect 方法二分搜索，取代 list.index 的线性搜索。

熟悉 itertools 里的方法。

## tip47 在重视精度的场合请使用 decimal 

完

## tip48 使用社区的包

完

## tip49 模块、类、类的public接口、都要写docstring

完

## tip50 用包来管理模块，并提供稳固的API

可以在包的 `__init__.py` 里面用 __all__ 导出想要暴露的api，其实 from xx import * 的写法，在各模块间构造内部的API的时候是不赞成的这么写的，会有命名覆盖的风险，所以 __all__ 用到的场景应该是你编写独立发布的模块，以便将那些主要的公共接口按照你的意愿统一暴露出来。

## tip51 为自建的模块提供根异常类

比如你的模块是个简单的爬虫，你就可以定义一个叫 CrawlError 的基类，然后基于它可以有 NetworkError, URLError 等，这样对调用者来说，他只要 try，然后 except NetworkError/CrawlError 就能合理的应对(打出错的log或者默认处理)这些由调用者自身造成的异常，这样被调用模块的异常和调用者代码的异常就隔离开了。

其实抛出异常的准则就是，你希不希望异常往上蔓延，如果希望，那么说明这个异常是你上层代码使用不当造成的，你这一层根本没办法帮上忙；如果不希望，那么说明这个异常在你自己这一层就需要被解决。

## tip52 出现循环 import 
a.py 里 import 了 b，b.py 也 import 了 a，然而 a，b里的内容又不会在同一刻初始化完，这就会造成在某个模块里找不到另一个模块的某个内容之类的问题。

解决方法里比较推荐的是重构，把各自需要的那部分都拿出来放到一个新的模块里。

## tip53 虚拟环境 3.4开始可以用pyvenv

完

## tip54 不同环境的部署

可以在模块里用个 ENV 变量来判断是生产环境还是测试环境，这个 ENV 变量你可以取自环境变量 os.environ 或者 从配置文件`dev.py&prod.py`里面，怎么样都行。


## tip55 print调试大法

`print("%r", some_variable)` 或者 `print(repr(some_variable))` 可以打印出 repr 后的字符串，这种表示形式更为清晰，因为内置类型都可以 `eval(repr(a))` 成原来的内容。

至于自定义的类，想便于调试的话，那就实现一下`__repr__`方法吧。

## tip56 python代码的动态性决定你必须要好好为它写测试

写测试，当然好了，既保证第一次写的代码能正确的work，又方便以后的代码重构

## tip57 可以用 pdb 来调试

完

## tip58 先profile，再优化代码

分析性能这个似乎做的很少，有种说法是运行速度在开发效率面前不值一提。。OTL

## tip59 tracemalloc 来掌握内存的使用以及泄露情况，py3.4+

tracemalloc 可以在调用的时候给当前时刻的程序拍个快照，然后多个快照之间可以做比较，打印出内存增大的代码行，以及相关信息。