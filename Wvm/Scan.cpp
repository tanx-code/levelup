//
// Created by TanGreen on 15/12/31.
//
#include "Scan.h"
#include <fstream>

enum keyword{

};


Scan::Scan(string s) {
    fstream in;
    //ofstream out;
    in.open(s, ios::in);
    //out.open("/Users/TanGreen/ClionProjects/Wvm/asm_token.txt", ios::trunc);
    string *ts = new string;
    if (!in.is_open()) cout << "file doesn't exist" << endl;
    else {
        while (getline(in, *ts)) {
            code.push_back(ts);
            ts = new string;
        }
        in.close();
    }


    //out.close();
}


