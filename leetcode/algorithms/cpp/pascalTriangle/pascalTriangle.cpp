// discus里高效的做法，把边界条件都弄到循环里考虑了，厉害啊
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> ans;
        for(int i = 0;i < numRows; ++i){
            vector<int> tmp(i + 1, 1);
            for(int j = 1;j <= i - 1; ++j){
                tmp[j] = ans[i - 1][j] + ans[i - 1][j - 1];
            }
            ans.push_back(tmp);
        }
        return ans;
    }
};
// 我的做法，比上面长，显然没他优雅。不过道理是一样的
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int> > result;
        if(numRows < 1)
            return result;
        result.push_back(vector<int>{1});
        for(int i=1; i<numRows; i++)
        {
            result.push_back(vector<int>{1,1});
            auto it = result[i].end();
            it--;
            for(int j=0; j<result[i-1].size()-1; j++)
            {
                result[i].insert(it,result[i-1][j] + result[i-1][j+1]);
                it = result[i].end();
                it--;
            }
        }
        return result;
    }
};


// Source : https://oj.leetcode.com/problems/pascals-triangle/
// Author : Hao Chen
// Date   : 2014-06-18

/********************************************************************************** 
* 
* Given numRows, generate the first numRows of Pascal's triangle.
* 
* For example, given numRows = 5,
* Return
* 
* [
*      [1],
*     [1,1],
*    [1,2,1],
*   [1,3,3,1],
*  [1,4,6,4,1]
* ]
* 
*               
**********************************************************************************/

#include <stdlib.h>
#include <vector>
#include <iostream>
using namespace std;

vector<vector<int> > generate(int numRows) 
{
    vector<vector<int> > pascalTriangle;
    for (int i=0; i<numRows; i++){
        vector<int> v;
        if (i==0){
            v.push_back(1);
        } else {
            v.push_back(1);
            for(int j=0; j<pascalTriangle[i-1].size()-1; j++){
                v.push_back(pascalTriangle[i-1][j] + pascalTriangle[i-1][j+1]);
            }
            v.push_back(1);
        }
        pascalTriangle.push_back(v); 
    }
    return pascalTriangle;
}

void printTriangle(vector< vector<int> > pt)
{
	cout << "[" << endl;
    for(int i=0; i<pt.size(); i++){
    	for(int space=(pt.size()-i-1); space>=0; space--){
    		cout << " ";
    	}
        cout << "[";
        for(int j=0; j<pt[i].size(); j++){
            cout << pt[i][j];
            if(j<pt[i].size()-1){
            	cout << ",";
            }
        }
        cout << "]";
        if(i<pt.size()-1){
        	cout << ",";
        }
        cout << endl;
    }
    cout << "]" << endl;
}

int main(int argc, char** argv)
{
    int n = 3;
    if (argc>1) {
        n = atoi(argv[1]);
    }
    printTriangle(generate(n)); 
}
