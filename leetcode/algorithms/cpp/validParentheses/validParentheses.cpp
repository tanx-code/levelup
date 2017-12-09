class Solution {
public:
    bool isValid(string s) {
        if(!s.size() || s.size()%2==1)
            return false;
        stack<char> mstk;
        mstk.push(s[0]);
        map<char,char> mm = {{'(',')'},{'[',']'},{'{','}'}
                            ,{')','0'},{']','0'},{'}','0'}};;
        int i = 1;
        while(!mstk.empty()){
            if(mm.find(s[i]) == mm.end())
                return false;
            if(mm[s[i]] == '0'){
                if(mm[mstk.top()]!=s[i]){
                    return false;
                }else{
                    mstk.pop();
                }
            }else{
                mstk.push(s[i]);
            }
            if(++i > s.size()-1 && !mstk.empty())
                return false;
        }
        return true;
    }
};


// Source : https://oj.leetcode.com/problems/valid-parentheses/
// Author : Hao Chen
// Date   : 2014-06-30

/********************************************************************************** 
* 
* Given a string containing just the characters '(', ')', '{', '}', '[' and ']', 
* determine if the input string is valid.
* 
* The brackets must close in the correct order, "()" and "()[]{}" are all valid 
* but "(]" and "([)]" are not.
* 
*               
**********************************************************************************/

#include <iostream>
#include <string>
#include <stack>
using namespace std;

bool isValid(string s) {
    stack<char> st;
    for(auto ch : s) {
        if (ch=='{' || ch =='[' || ch=='(' ) {
            st.push(ch);
        }else if (ch=='}' || ch ==']' || ch == ')' ){
            if (st.empty()) return false;
            char sch = st.top();
            if ( (sch=='{' && ch =='}') || (sch=='[' && ch==']') || (sch=='(' && ch==')' ) ){
                st.pop();
            }else {
                return false;
            }
        }else{
            return false;
        }
    }
    return st.empty();
}

int main(int argc, char**argv)
{
    string s = "{{}{[]()}}";
    if (argc>1){
        s = argv[1];
    }
    cout << "str = \"" << (s) << "\"" << endl;
    cout << isValid(s) << endl;
}
