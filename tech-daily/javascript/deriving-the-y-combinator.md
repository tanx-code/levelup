## Y combinator推导
(js 版) 比较关键的几个步骤。 [原文](http://igstan.ro/posts/2010-12-01-deriving-the-y-combinator-in-7-easy-steps.html)

```js
// 问： 怎么让匿名函数自己调用自己呢？
// 答:  那就间接给匿名函数命名呗。((fn)=>fn(fn))((myself)=>myself(myself))
// 上面就是lambda运算实现递归的最简单的形式
(function(f) {
    f(f);
})(fucntion(f){
    f(f);
});

// 所以，求阶乘的函数，就可以这么写
var recur = function (f) {
    return f(f);
};

var fact = recur(
    function (f) {
        return function (n) {
                if (n < 2) return 1;

                // 因为f返回一个函数，所以这有一个双重调用。
                return n * f(f)(n - 1); // 由于闭包的特性，其实这里的f已经把自身给保存在了这个函数里了。
            };
    }
);

// 有没有发现，我们以前是在脑子里运算出一个函数的内容，而现在是在程序里运算出一个函数的内容。
// 这里面的事实是，递归每下降一层，就通过f(f)运算出一个新的函数来，这里我们可以轻易的看到匿名调用匿名函数的真相是什么。

// 我们的目标是把与递归的实现和函数本身的逻辑，分离成两个部分，所以这还不够。
// 下面把f(f)给单独弄出来
var recur = function (f) {
    return f(f);
};

var fact = recur(
    function (f) {
        var g = function (f) {
            return f(f);
        };
        return function (n) {
                if (n < 2) return 1;
                return n*g(n-1);
            };
    }
);

// 还是没有分开，继续
var recur = function (f) {
    return f(f);
};

var wrap = function (h) {
    return recur(function(f){
        var g = function (n) {
            return f(f)(n);
        };
        h(g);
    });
};

var fact = wrap(function (g) {
    return function (n) {
        if (n < 2) return 1;
        return n * g(n - 1);
    };
});


// 把函数wrap、g都内联进去，于是就完全分成两部分了，闪现递归的那部分就是传说中的 Y combinator

var Y = function (h) {
    return (function (f) {
        return f(f);
    })(function (f) {
        return h(function (n) {
            return f(f)(n);
        });
    });
};

var fact = Y(function (g) {
		return n * g(n - 1);
    };
});

```
