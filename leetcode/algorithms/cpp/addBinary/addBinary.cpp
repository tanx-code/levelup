// 我怎么写了三十行。。。chenhao的才15行。。。
class Solution {
public:
    string addBinary(string a, string b) {
        auto i = a.rbegin();
        auto j = b.rbegin();
        int carry = 0;
        string result;
        for( ;i!=a.rend()&&j!=b.rend();i++,j++) {
            int t = (((*i)-'0') + ((*j)-'0')) + carry;
            if(t==3)
                t = 1,carry = 1;
            else if(t==2)
                t = 0,carry = 1;
            else
                carry = 0;
            result.insert( result.begin(), t  + '0');
        }
        // attention, don't forget carry if it is 1
        for(;i!=a.rend();i++){
            int t = (*i)-'0' + carry;
            t>1?t=0,carry = 1:carry=0;
            result.insert(result.begin(),t+'0');
        }
        for(;j!=b.rend();j++){
            int t = (*j)-'0' + carry;
            t>1?t=0,carry=1:carry=0;
            result.insert(result.begin(),t+'0');
        }
        if(carry == 1)
            result.insert(result.begin(),'1');
        return result;
    }
};
// 复制过来学习一下。。
string addBinary(string a, string b) {
    int alen = a.size();
    int blen = b.size();
    bool carry = false;
    string result;
    while( alen>0 || blen>0) {
        int abit = alen<=0 ? 0 : a[alen-1]-'0';
        int bbit = blen<=0 ? 0 : b[blen-1]-'0';
        int cbit = carry ? 1 : 0;
        result.insert(result.begin(), '0' + ((abit+bbit+cbit) & 1) );
        carry = (abit+bbit+cbit>1);
        alen--; blen--;
    }
    if (carry){
        result.insert(result.begin(), '1');
    }
    return result;
}
// Source : https://oj.leetcode.com/problems/add-binary/
// Author : Hao Chen
// Date   : 2014-07-05

/********************************************************************************** 
* 
* Given two binary strings, return their sum (also a binary string).
* 
* For example,
* a = "11"
* b = "1"
* Return "100".
* 
*               
**********************************************************************************/

#include <iostream>
#include <string>
using namespace std;

string addBinary(string a, string b) {
    int alen = a.size();
    int blen = b.size();
    bool carry = false;
    string result;
    while( alen>0 || blen>0) {
        int abit = alen<=0 ? 0 : a[alen-1]-'0';
        int bbit = blen<=0 ? 0 : b[blen-1]-'0';
        int cbit = carry ? 1 : 0;
        result.insert(result.begin(), '0' + ((abit+bbit+cbit) & 1) );
        carry = (abit+bbit+cbit>1);
        alen--; blen--;
    }
    if (carry){
        result.insert(result.begin(), '1');
    }
    return result;
}


int main(int argc, char** argv) 
{
    string a = "11";
    string b = "1";
    if (argc>2){
        a = argv[1];
        b = argv[2];
    }

    cout << a << "+" << b << "=" << addBinary(a, b) << endl;
    
}
