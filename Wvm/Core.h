//
// Created by TanGreen on 16/2/4.
//

#ifndef WVM_CORE_H
#define WVM_CORE_H
#include<iostream>
#include<string>
#include<vector>
#include<list>
#include<map>
using namespace std;

struct valueType {
    valueType(const valueType &v) {
        *this=v;
    }

    valueType() { }
    bool isInt=0;
    bool isStr=0;
    int ival=0;
    string sval="";
};
struct stackitem {
    string funcName;
    vector<string> args;
    map<string, valueType> localVars;
    int phead;
    string ret="";
};
enum mode{
    LOCAL,
    TOP
};

class Core {
public:
    Core(string s);
    ~Core(){}

    string srcpath;
    void handle();
    map<string,pair<int,int> > functionTable;
    map<string, valueType> dataTable;
    map<string,int> labelTable;

    valueType runstack();
    void cpu(int m);
    list<stackitem* > activeItems;
    vector<string *> code;

    void clocal();

    void ctop();

    void IMOV(string &s1, string &s2, int m);

    void ISTR(string &s1, valueType &v1, int m);

    void ILDR(string &s1, valueType &v1, int m);

    void IOUT(string &s1 ,int m);

    void ICMP(string &s1, string &s2, string &syb, int m);

    void IADD(string &s1,string &s2, string &s3, int m);

    void ISUB(string &s1, string &s2, string &s3, int m);

    void IJMP(int i, string s);

    void runtimeError();



    void IMUL(string &s1, string &s2, string &s3, int m);

    void IDIV(string &s1, string &s2, string &s3, int m);
};


#endif //WVM_CORE_H
