//
// Created by TanGreen on 15/12/31.
//

#ifndef SCAN_H
#define SCAN_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <list>


using namespace std;

class Scan {
public:
    Scan(string s);
    virtual ~Scan() { }

    vector<string *> code;
};

#endif //SCAN_H
