/*
这题感觉有点繁琐，还得去查规则，就懒得写了，这是别人的答案。
罗马数字的规则：
Symbol  Value
I   1
V   5
X   10
L   50
C   100
D   500
M   1,000

I placed before V or X indicates one less, so four is IV (one less than five) and nine is IX (one less than ten)
X placed before L or C indicates ten less, so forty is XL (ten less than fifty) and ninety is XC (ten less than a hundred)
C placed before D or M indicates a hundred less, so four hundred is CD (a hundred less than five hundred) and nine hundred is CM (a hundred less than a thousand)
*/
class Solution {  
public: 
    int romanToInt(string s) {
        int ans = 0;
        for(int i = 0; i < s.size(); i++){
            if(s[i] == 'M') ans += 1000;
            else if(s[i] == 'D') ans += 500;
            else if(s[i] == 'C') {
                int sign = 1 - (i < s.size() - 1 && (s[i + 1] == 'D' || s[i + 1] == 'M')) * 2; // 判断是加还是减
                ans += sign * 100;   
            }
            else if(s[i] == 'L') ans += 50;
            else if(s[i] == 'X') {
                int sign = 1 - (i < s.size() - 1 && (s[i + 1] == 'L' || s[i + 1] == 'C')) * 2;
                ans += sign * 10; 
            } 
            else if(s[i] == 'V') ans += 5; 
            else {
                int sign = 1 - (i < s.size() - 1 && (s[i + 1] == 'V' || s[i + 1] == 'X')) * 2;
                ans += sign * 1;  
            } 
        } 

        return ans; 
    }
};

// Source : https://oj.leetcode.com/problems/roman-to-integer/
// Author : Hao Chen
// Date   : 2014-07-17

/********************************************************************************** 
* 
* Given a roman numeral, convert it to an integer.
* 
* Input is guaranteed to be within the range from 1 to 3999.
*               
**********************************************************************************/

#include <iostream>
#include <string>
using namespace std;

int romanCharToInt(char ch){
    int d = 0;
    switch(ch){
        case 'I':  
            d = 1;  
            break;  
        case 'V':  
            d = 5;  
            break;  
        case 'X':  
            d = 10;  
            break;  
        case 'L':  
            d = 50;  
            break;  
        case 'C':  
            d = 100;  
            break;  
        case 'D':  
            d = 500;  
            break;  
        case 'M':  
            d = 1000;  
            break;  
    }
    return d;
}
int romanToInt(string s) {
    if (s.size()<=0) return 0;
    int result = romanCharToInt(s[0]);
    for (int i=1; i<s.size(); i++){
        int prev = romanCharToInt(s[i-1]);
        int curr = romanCharToInt(s[i]);
        //if left<right such as : IV(4), XL(40), IX(9) ...
        if (prev < curr) {
            result = result - prev + (curr-prev);
        }else{
            result += curr;
        }
    }
    return result;
}

int main(int argc, char**argv)
{
    string s("XL");
    if (argc>1){
        s = argv[1];
    }
    cout << s << " : " << romanToInt(s) << endl;
    return 0;
}
