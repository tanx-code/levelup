// 这一题一定要看这个https://discuss.leetcode.com/topic/534/expected-output-of-abcde-4/2
// 不然根本搞不清它那个zigzag到底是什么意思好吗
class Solution {
public:
    string convert(string s, int numRows) {
        if(numRows<=1)
            return s;
        string ret;
        vector<string> vecbuf(numRows);
        int row = 0;
        int step = 1;
        for(auto i=0;i<s.size();i++){
            if(row == numRows-1) step = -1;
            if(row == 0) step = 1;
            vecbuf[row] += s[i];
            row+=step;
        }
        for(auto i:vecbuf){
            ret+=i;
        }
        return ret;
    }
};


// Source : https://oj.leetcode.com/problems/zigzag-conversion/
// Author : Hao Chen
// Date   : 2014-07-17

/********************************************************************************** 
* 
* The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: 
* (you may want to display this pattern in a fixed font for better legibility)
* 
* P   A   H   N
* A P L S I I G
* Y   I   R
* 
* And then read line by line: "PAHNAPLSIIGYIR"
* 
* Write the code that will take a string and make this conversion given a number of rows:
* 
* string convert(string text, int nRows);
* 
* convert("PAYPALISHIRING", 3) should return "PAHNAPLSIIGYIR".
* 
*               
**********************************************************************************/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

string convert(string s, int nRows) {
    //The cases no need to do anything
    if (nRows<=1 || nRows>=s.size()) return s;
     
    vector<string> r(nRows);
    int row = 0;
    int step = 1;
    for(int i=0; i<s.size(); i ++) {
        if (row == nRows-1) step = -1;
        if (row == 0) step = 1;
        //cout << row <<endl;
        r[row] += s[i];
        row += step;
    }
    
    string result;
    for (int i=0; i<nRows; i++){
        result += r[i];
    }
    return result;
}

int main(int argc, char**argv){

    string s;
    int r;

    s = "PAYPALISHIRING";
    r = 3;
    cout << s << " : " << convert(s, 3) << endl;

}
