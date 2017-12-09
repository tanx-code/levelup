# NachOS

5.7
## makefile

`$<`表示第一个prerequest。

```
all: a b c
echo $<       就是输出a
```

`$@`表示当前的这个request。

`$^`表示所有的prerequest。
在命令前面的`@`表示这条命令只输出结果，而不输出命令本身。

在命令前面加`-`表示，即便这条命令出错，也不终止make，make将继续后面的动作。

`.PHONY`有两种功能，一是这种情况，比如文件目录里产生了一个clean文件，这时候就不能执行，`make clean`了，因为它会提示你clean已经是最新的。第二种情况比较复杂，暂时不太理解，它的目的是提高make的效率。

`make -C dir`表示切换到dir目录，再执行make命令。

## GCC

`gcc -M main.c` 输出main包含的所有所有头文件，包括标准库里的文件。`-MM`只包括用户定义的头文件。
