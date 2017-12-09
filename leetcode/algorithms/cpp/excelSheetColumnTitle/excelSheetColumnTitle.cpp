class Solution {
public:
    string convertToTitle(int n) {
        string ret;
        if(n<0)
            return ret;
        while(n!=0){
            ret.insert(ret.begin(),'A'+(n-1)%26);
            n-=1;   // 关键在这里，n为什么要-1，我认为，要让n等于26的倍数的这种情况求出来的数是正确的，就必须-1。
                    // 比如n=52，不减的时候，n/=26就等于2了，可是明显1*26+26，进位应该为1的
                    // **也就是说，因为这道题从1开始计数的原因，导致%和/的运算结果不对，都需要把n减1**
            n/=26;
        }
        return ret;
    }
};
string base10_intTostr(int n){
    string s;
    if(n<0){
        n=-n;
        s.insert(s.begin(),'-');
    }
    if(n==0){
        s.insert(s.begin(),'0');
        return s;
    }
    while(n!=0){
        s.insert(s.begin(),n%10);
        n/=10;
    }
}
// Source : https://oj.leetcode.com/problems/excel-sheet-column-title/
// Author : Hao Chen
// Date   : 2014-12-25

/********************************************************************************** 
 * 
 * Given a positive integer, return its corresponding column title as appear in an Excel sheet.
 * 
 * For example:
 * 
 *     1 -> A
 *     2 -> B
 *     3 -> C
 *     ...
 *     26 -> Z
 *     27 -> AA
 *     28 -> AB 
 * 
 * Credits:Special thanks to @ifanchu for adding this problem and creating all test cases.
 *               
 **********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;


string base26_int2str(long long n) {
    string ret;
    while(n>0){
        char ch = 'A' + (n-1)%26;
        ret.insert(ret.begin(), ch  );
        n -= (n-1)%26;
        n /= 26;
    }
    return ret;
}

long long base26_str2int(string& s){
    long long ret=0;
    for (int i=0; i<s.size(); i++){
        int n = s[i] - 'A' + 1;
        ret = ret*26 + n;
    }
    return ret;
}


string convertToTitle(int n) {
    return base26_int2str(n);
}

int main(int argc, char**argv)
{
    long long n = 27; 
    if (argc>1){
        n = atoll(argv[1]);
    }
    string ns = base26_int2str(n);
    n = base26_str2int(ns);

    cout << n << " = " << ns << endl;


    ns = "ABCDEFG";
    if (argc>2){
        ns = argv[2];
    }
    cout << ns << " = " << base26_str2int(ns) << endl;
}
