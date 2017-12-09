#Some concepts about the thread

## POSIX threads
POSIX标准的线程API，所有的函数都以`pthread_`开头。

## NPTL and LinuxThreads
都是对POSIX的实现，后者几乎已经完全被NPTL取代了。NPTL现在内置于GNU libc里，包括一些头文件和链接库。值得注意的是，在其他的POSIX系统里，比如(AIX,Solaris)，你也可以用pthread，但它们并不是NPTL实现。

[NPTL的作者发表的论文](https://www.akkadia.org/drepper/nptl-design.pdf),从中我们可以了解到NPTL的实现过程，已经和其他线程库的比较。待读。
