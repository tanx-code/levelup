4.2
### Windows Coding Conventions
windows编程经常看见很多大写的宏类型，看着很吓人。里面有的类型其实重复了，因为历史的原因。
* P和LP开头的意思是指针，L是long的意思。
* windows原生支持Unicode，你可以用`wchar_t`或者`WCHAR`来定义一个16位的宽字符，需要这样写`L"helloworld"`，它将被编码为UTF-16。常见的有PSTR(char*),PWSTR(wchar_t*)
* VC++默认在预编译头里设置了UNICODE。
