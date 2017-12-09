# node.js

## node.js?CommonJS?AMD?RequireJS?
* node.js是一个基于GoogleV8 js引擎的js runtime环境，用搭建一些web应用
* CommonJS，以前js只广泛应用在前端，比如浏览器上操作下dom之类的，后来有人说要弄些后端的api规范让js能处理更多的事情，于是维护了一个CommonJS的项目，在这之前叫ServerJs。它其实说的这么复杂，最基础且重要的就一个东西，用`export`来实现模块化。它有很多个版本的实现，node.js就是其中一个。
* AMD是Asynchronous Module Definition(异步模块规范)，RequireJS就是这个规范的一个实现，它的实现是为了能在browser上面也能有异步加载的功能。AMD的api规范跟CommonJS不一样，模块引入不是`export`而是`define`，但是它们两在一开始都是遵守的同样的规范的。
* RequireJS刚刚说了是AMD的一个实现，只不过它遵循了CommonJS的约定，尤其是在模块定义的时候。因为RequireJS提供了一个CommonJS的包装，所以可以在RequireJS规范的文件里混用两种(`define`&`export`)模块定义方式。
* 总结就是，AMD和CommonJS都是js的模块定义api规范，只不过是不同的实现罢了。RequireJS是为了在浏览器上用上新规范的兼容二者的杂交物。

## node的组成
* ECMAScript + CommonJS + some libaries&modles

## node重要的特性
* 异步I/O。就是执行读写的动作不会阻塞程序，它会立即返回，并且把读写的动作交给下层处理，对于不同的平台，异步IO的底层实现机制是不一样的，有的是线程池模拟的。反正node是封装出了API，让你无视平台。
* 异步函数。就是调用过后会把函数的返回值返回给`event handler`，就是回调函数，然后继续执行接下来的语句，在之前那个函数执行完之后，你可以随时调用回调函数把该函数的返回结果取出来。

## node的组成部分(通过这个完全能推测出这东西的能耐)
node能干的事真是太多了，挑感兴趣的先写
### c/c++ Addons
* 首先，你写的c++是要编译成二进制代码的，而链接过程用到的是node.js内部的依赖，比如V8(所有的插件都会链接这个的)，libuv，OpenSSL等。因为最后所有的代码都是被V8引擎执行的，所以你的cpp文件也需要基于V8的api来写才行，官方有个[helloworld的例子](http://nodejs.cn/doc/node/addons.html#addons_hello_world)。
* 编译的方法是，在插件的根目录下创建一个`binding.gyp`文件，类似makefile这种记录工作目录的，然后命令行`node-gyp configure`，在这之前要更新一下node-gyp(`npm install -g node-gyp`)，因为node.js自带的那个功能不全，这时候就生成了一个build文件夹，然后再invoke `node-gyp build` command，生成addon.node文件，这是编译好的。插件使用起来也很简单,`require`就行了。还有个叫[node-bindings](https://github.com/TooTallNate/node-bindings)的helper module，如果load这些c++写的addons的时候出问题，它能提供些帮助。
* [node-qt](https://github.com/arturadib/node-qt)，真心会玩。

    ![](https://github.com/arturadib/node-qt/raw/master/examples/helloworld.png)

* 不知道生成的.node文件里面长啥样子，应该不会是二进制，不然咋跟js交互。

### Child Process
* 这个模块的功能是生成子进程。异步和同步方式都有。子进程可以执行shell命令，也可以执行一个脚本文件。win和unix下方式有点不同。
* 这功能意味着你可以与命令行交互了，把需要用的小功能写成脚本让node调用应该会很方便。
