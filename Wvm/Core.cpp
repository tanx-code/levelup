//
// Created by TanGreen on 16/2/4.
//

#include "Core.h"
#include "Scan.h"

int pc;
bool condState = false;

Core::Core(string s) {
    srcpath = s;
}
static vector<string> getToken(string &s){
    vector<string> store;
    unsigned long last = 0;
    for (unsigned long i = 0; i < s.size(); i++) {
        if(s[i]==' '){
            store.push_back(s.substr(last,i-last));
            if (s.substr(last, i - last) == "s:") {
                store.push_back(s.substr(i + 1));
                return store;
            }
            last = i + 1;
        }
    }
    store.push_back(s.substr(last,s.size()-last));
    return store;
}

void Core::runtimeError(){
    throw runtime_error("virtual machine running bad");
}

void Core::IJMP(int i=-1,string s=""){
    if(s!=""){
        pc = labelTable[s];
        return;
    }
    if (i >= 0) {
        pc =i;
        return;
    }
}
void Core::IMOV(string &s1,string &s2,int m= TOP){
    if(m==LOCAL){
        map<string, valueType> &localmap = activeItems.back()->localVars;
        if(localmap.find(s2)==localmap.end())
        {
            runtimeError();
        }else
        {
            localmap[s1]=localmap[s2];
        }
    }else{
        if((dataTable.find(s2)==dataTable.end()) )
        {
            runtimeError();
        }else {
            dataTable[s1]=dataTable[s2];
        }

    }
}

void Core::ISTR(string &s1, valueType &v1, int m = TOP) {
    if (m==LOCAL){
        activeItems.back()->localVars[s1]=v1;
    }else{
        dataTable[s1]=v1;
    }
}

void Core::ILDR(string &s1, valueType &v1, int m = TOP) {
    if (m==LOCAL){
        v1 = activeItems.back()->localVars[s1];
    }else{
        v1 = dataTable[s1];
    }
}
void Core::IOUT(string &s1,int m=TOP){
    if(m==LOCAL){
        map<string, valueType> lmap = activeItems.back()->localVars;
        if(lmap.find(s1)!=lmap.end()){
            valueType v = lmap[s1];
            if (v.isStr) {
                for (auto ch = v.sval.begin(); ch != v.sval.end(); ++ch) {
                    if (*ch == '\\') {
                        ++ch;
                        if (ch == v.sval.end()) break;
                        switch (*ch) {
                            case 'n':
                                cout << endl;
                                break;
                            case 's':
                                cout << ' ';
                                break;
                            default:
                                break;
                        }
                        ++ch;
                    }
                    if (ch == v.sval.end()) break;
                    cout << *ch;
                }
            }
            else if(v.isInt) cout<<v.ival;
            else runtimeError();
        }
    }else{
        if(dataTable.find(s1)!=dataTable.end()){
            valueType v = dataTable[s1];
            if (v.isStr) {
                for (auto ch = v.sval.begin(); ch != v.sval.end(); ++ch) {
                    if (*ch == '\\') {
                        ++ch;
                        if (ch == v.sval.end()) break;
                        switch (*ch) {
                            case 'n':
                                cout << endl;
                                break;
                            case 's':
                                cout << ' ';
                                break;
                            default:
                                break;
                        }
                        ++ch;
                    }
                    cout << *ch;
                }
            }
            else if(v.isInt) cout<<v.ival;
            else runtimeError();
        }
    }
}

void Core::ICMP(string &s1, string &s2, string &syb, int m = TOP) {
    if (m == LOCAL) {
        int i = activeItems.back()->localVars[s1].ival;
        int j = activeItems.back()->localVars[s2].ival;
        if (syb == ">") condState = i > j;
        else if (syb == "<") condState = i < j;
        else if (syb == ">=") condState = i >= j;
        else if (syb == "<=") condState = i <= j;
        else condState = false;
    } else {
        int i = dataTable[s1].ival;
        int j = dataTable[s2].ival;
        if (syb == ">") condState = i > j;
        else if (syb == "<") condState = i < j;
        else if (syb == ">=") condState = i >= j;
        else if (syb == "<=") condState = i <= j;
        else condState = false;
    }
}
void Core::IADD(string &s1,string &s2,string &s3,int m= TOP){
    if(m==LOCAL){
        map<string, valueType> &lmap = activeItems.back()->localVars;
        if(lmap.find(s3)==lmap.end()||lmap.find(s2)==lmap.end()){
            runtimeError();
        }else{
            valueType v;
            v.isInt = true;
            v.ival = lmap[s2].ival+lmap[s3].ival;
            lmap[s1] = v;
        }
    }else{
        if(dataTable.find(s3)==dataTable.end()||dataTable.find(s2)==dataTable.end()){
            runtimeError();
        }else{
            valueType v;
            v.isInt = true;
            v.ival = dataTable[s2].ival+dataTable[s3].ival;
            dataTable[s1] = v;
        }

    }
}

void Core::ISUB(string &s1, string &s2, string &s3, int m = TOP) {
    if (m == LOCAL) {
        map<string, valueType> &lmap = activeItems.back()->localVars;
        if (lmap.find(s3) == lmap.end() || lmap.find(s2) == lmap.end()) {
            runtimeError();
        } else {
            valueType v;
            v.isInt = true;
            v.ival = lmap[s2].ival - lmap[s3].ival;
            lmap[s1] = v;
        }
    } else {
        if (dataTable.find(s3) == dataTable.end() || dataTable.find(s2) == dataTable.end()) {
            runtimeError();
        } else {
            valueType v;
            v.isInt = true;
            v.ival = dataTable[s2].ival - dataTable[s3].ival;
            dataTable[s1] = v;
        }

    }
}

void Core::IMUL(string &s1, string &s2, string &s3, int m = TOP) {
    if (m == LOCAL) {
        map<string, valueType> &lmap = activeItems.back()->localVars;
        if (lmap.find(s3) == lmap.end() || lmap.find(s2) == lmap.end()) {
            runtimeError();
        } else {
            valueType v;
            v.isInt = true;
            v.ival = lmap[s2].ival * lmap[s3].ival;
            lmap[s1] = v;
        }
    } else {
        if (dataTable.find(s3) == dataTable.end() || dataTable.find(s2) == dataTable.end()) {
            runtimeError();
        } else {
            valueType v;
            v.isInt = true;
            v.ival = dataTable[s2].ival * dataTable[s3].ival;
            dataTable[s1] = v;
        }

    }
}

void Core::IDIV(string &s1, string &s2, string &s3, int m = TOP) {
    if (m == LOCAL) {
        map<string, valueType> &lmap = activeItems.back()->localVars;
        if (lmap.find(s3) == lmap.end() || lmap.find(s2) == lmap.end()) {
            runtimeError();
        } else {
            valueType v;
            v.isInt = true;
            v.ival = lmap[s2].ival / lmap[s3].ival;
            lmap[s1] = v;
        }
    } else {
        if (dataTable.find(s3) == dataTable.end() || dataTable.find(s2) == dataTable.end()) {
            runtimeError();
        } else {
            valueType v;
            v.isInt = true;
            v.ival = dataTable[s2].ival / dataTable[s3].ival;
            dataTable[s1] = v;
        }

    }
}
void Core::handle() {
    Scan s(srcpath);
    code=s.code;
    for (vector<string *>::iterator it = code.begin(); it != code.end(); it++) {
        vector<string> token = getToken(**it);
        if (token[0] == "FUNCTION") {
            string funcName = token[1];
            long i = distance(code.begin(), it);
            vector<string *>::iterator it_tmp = it;
            for(;it!=code.end();it++) {
                token = getToken(**it);
                if (token[0] == "EXIST")
                    break;
                else if(token[0]=="LABEL")
                {
                    long li = distance(code.begin(), it);
                    labelTable[token[1]] = (int)li;
                }
            }
            long j = distance(it_tmp,it);
            functionTable[funcName] = pair<int,int>(i,j);
        }
        else if(token[0]=="LABEL")
        {
            long i = distance(code.begin(), it);
            labelTable[token[1]] = (int)i;
        }
    }

    pc = 0;
    try {
        cpu(TOP);
    } catch (runtime_error e) {
        cerr << "********* " << e.what() << endl;
    }
}

valueType Core::runstack() {
    valueType v;
    if(activeItems.size()!=0) {
        stackitem *item = activeItems.back();
        IJMP(functionTable[item->funcName].first);
        cpu(LOCAL);
        if(item->ret=="")
            return v;
        else
        {
            v = activeItems.back()->localVars[item->ret];
            return v;
        }
    }else return v;
}

void Core::ctop(){
    stackitem * item = new stackitem;
    while (pc<code.size()){
        if (!item)
            item = new stackitem;

        vector<string> token = getToken(*code[pc]);

        if (token[0] == "FUNCTION") {
            pc = pc + functionTable[token[1]].second;
        }
        else if (token[0] == "PARAM") {
            item->args.push_back(token[1]);
        }
        else if (token[0] == "IF")  //IF a < b GOTO label 1
        {
            if (token.size() != 7) runtimeError();
            else {
                ICMP(token[1], token[3], token[2]);
                if (!condState) {
                    IJMP(-1, token[6]);
                    condState = false;
                }
            }

        }
        else if (token[0] == "IFFALSE")
        {
            if (token.size() != 7) runtimeError();
            else {
                ICMP(token[1], token[3], token[2]);
                if (!condState) {
                    IJMP(-1, token[6]);
                    condState = false;
                }
            }
        }
        else if (token[0] == "RETURN") { //no use
            return;
        }
        else if (token[0] == "EXIST") { //no use
            return;
        }
        else if (token[0] == "GOTO") {
            IJMP(-1, token[2]);
        }
        else if (token.size() >= 4 && token[2] == "CALL") {
            if (token[3] == "print") {          //相当于调用外部函数
                for (auto it : item->args)
                    IOUT(it);
                delete item;
                item = NULL;
            } else {
                item->funcName = token[3];
                item->phead = pc; //record pc
                activeItems.push_back(item);
                valueType v = runstack();
                ISTR(token[0], v); //return a 'valueType' type
                pc = item->phead;
                IJMP(pc);
                activeItems.pop_back();
                item = NULL;
            }
        }
        else if(token.size()>=3)
        {
            if(token[1]=="=")
            {
                if(token[2]=="d:")
                {
                    valueType v;
                    v.isInt= true;
                    v.ival = atoi(token[3].c_str());
                    ISTR(token[0],v);
                }
                else if(token[2]=="s:")
                {
                    valueType v;
                    v.isStr = true;
                    v.sval = token[3];
                    ISTR(token[0],v);
                }
                else
                {
                    IMOV(token[0],token[2]);
                }
            }else if(token[1]=="+")
            {
                IADD(token[0],token[2],token[3]);
            }
            else if (token[1] == "-") {
                ISUB(token[0], token[2], token[3]);
            }
            else if (token[1] == "*") {
                IMUL(token[0], token[2], token[3]);
            }
            else if (token[1] == "/") {
                IDIV(token[0], token[2], token[3]);
            }
        }
        ++pc;
    }
}
void Core::clocal(){
    vector<string>::iterator it = activeItems.back()->args.begin();
    stackitem * litem = new stackitem;
    while (pc<code.size()){
        if (!litem)
            litem = new stackitem;

        vector<string> token = getToken(*code[pc]);

        if (token[0] == "FUNCTION") {
            ++pc;
            for (auto its: activeItems.back()->args) { //args deal
                vector<string> stoken = getToken(*code[pc]);
                valueType v;
                ILDR(its, v);
                ISTR(stoken[1], v, LOCAL);
                ++pc;
            }
            continue;
        }
        else if (token[0] == "PARAM") { // reverse call
            litem->args.push_back(token[1]);
        }
        else if (token[0] == "IF") {
            if (token.size() != 7) runtimeError();
            else {
                ICMP(token[1], token[3], token[2], LOCAL);
                if (!condState) {
                    IJMP(-1, token[6]);
                    condState = false;
                }
            }
        }
        else if (token[0] == "IFFALSE") {
            if (token.size() != 7) runtimeError();
            else {
                ICMP(token[1], token[3], token[2], LOCAL);
                if (!condState) {
                    IJMP(-1, token[6]);
                    condState = false;
                }
            }
        }
        else if (token[0] == "RETURN") {
            IMOV(token[1], token[2],LOCAL);
            activeItems.back()->ret = token[1];
            return;
        }
        else if (token[0] == "EXIST") {
            return;
        }
        else if (token[0] == "GOTO") // GOTO LABEL 1
        {
            IJMP(-1, token[2]);
        }
        else if (token.size() >= 4 && token[2] == "CALL") {
            if (token[3] == "print") {          // 相当于调用外部函数
                for (auto lit : litem->args)
                    IOUT(lit, LOCAL);
                delete litem;
                litem = NULL;
            } else {
                litem->funcName = token[3];
                litem->phead = pc; //record pc
                activeItems.push_back(litem);
                valueType v = runstack();
                IJMP(litem->phead);
                activeItems.pop_back();
                ISTR(token[0], v, LOCAL);
                litem = NULL;
            }
        }
        else if(token.size()>=3)
        {
            if(token[1]=="=")
            {
                if(token[2]=="d:")
                {
                    valueType v;
                    v.isInt= true;
                    v.ival = atoi(token[3].c_str());
                    ISTR(token[0],v,LOCAL);
                }
                else if(token[2]=="s:")
                {
                    valueType v;
                    v.isStr = true;
                    v.sval = token[3];
                    ISTR(token[0],v,LOCAL);
                }
                else
                {
                    IMOV(token[0],token[2],LOCAL);
                }
            }else if(token[1]=="+") {
                IADD(token[0], token[2], token[3], LOCAL);
            }
            else if (token[1] == "-") {
                ISUB(token[0], token[2], token[3], LOCAL);
            }
            else if (token[1] == "*") {
                IMUL(token[0], token[2], token[3], LOCAL);
            }
            else if (token[1] == "/")
            {
                IDIV(token[0], token[2], token[3], LOCAL);
            }
        }
        ++pc;
    }
}

void Core::cpu(int m) {
    switch(m){
        case TOP:
            ctop();
            break;
        case LOCAL:
            clocal();
            break;
        default:
            break;
    }
}


