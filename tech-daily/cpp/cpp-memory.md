## c++使用经验，以及一些pitfalls

### shared_ptr使用不当，造成一个对象被delete两次
举个最简单的例子：
```
class A{};
shared_ptr<A> a = shared_ptr<A>(new A);
shared_ptr<A> b = shared_ptr<A>(a.get()); 
// b不会和a共享这个内存，而是独立接管那块内存。
// 意味着b和a在析构的时候，都会对这块内存进行delete

A* b = a.get();
delete b;
// 这个和上面是一样的，也是delete了两次
```

它们出现的错误提示往往都是这个：

![](http://7xrkyy.com1.z0.glb.clouddn.com/16-7-4/33274948.jpg)

你可能会说，不调用get()就没事了。真的吗？看看下面这种较常碰到的情况：
```
class A {
    A* func() {
        return this;
    }
}
shared_ptr<A> a = shared_ptr<A>(new A);
shared_ptr<A> b(a->func()); 
// 这就和上面犯了同样的错误了
// 有时候这种问题是比较隐蔽的
// 当然，弄懂了还是不会犯了

```

### shared_ptr里面保存的是变量的实际类型
也就是说在sptr对象析构的时候，delete掉的是实际类型，而不是你模版参数传进去的那个类型。

```
template <typename Tp>
class shared_ptr{
public:
    template <typename Tp1>
    explict shared_ptr(Tp1* p) : holder(p){}
    //...
};
```

holder是根据p的实际类型决定的。这里的代码只是表达思想的大概意思，Memory头文件里真实实现不是这样的。我记得以前有个论文，将shared_ptr实现的，估计读了就能清楚的知道这些东西吧。

所以，初始化一个shared_ptr的时候，要么传进去一个和模版参数一样类型的指针(或者对应的智能指针)，要么用`dynamic_pointer_cast`，把派生类智能指针转换为基类智能指针。
```
1.
Derived *d = new Derived;
shared_ptr<Base> b(d);// 虽然可以顺利调用d的析构函数，原因在上面。但是最好别这样写。

2.
shared_ptr<Derived> d(new Derive);
shared_ptr<Base> b = dynamic_pointer_cast<Base>(d); // 比较好的写法
```


这个问题，源自我在segmentfault的[一个提问](https://segmentfault.com/q/1010000005869722)。

