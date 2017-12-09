#include <iostream>
#include "Core.h"

using namespace std;

int main() {
    cout << "###### WVM is running ,created by TanGreen ######" << endl;
    cout << "input the file path: ";
    string s;
    cin >> s;
    //s = "/Users/TanGreen/ClionProjects/Woo/Debug/asm.txt";
    Core core(s);
    core.handle();
    return 0;
}