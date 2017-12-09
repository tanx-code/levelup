class Solution {
public:
    //　没想出来。看了答案。
    //  1 0; 1 1 0; 1 2 1 0;1 3 3 1 0;
    //  不断地用最后一个1加0得到每一行的最后一个1，然后用1前面的数加1得到新的1前面的数，依次加到开头的数
    //  这种预先弄一个数来实现操作的可循环性，是比较巧妙地技巧。
    vector<int> getRow(int rowIndex) {
        if(rowIndex==0)
            return vector<int> {1};
        vector<int> result(rowIndex+1,0);
        result[0] = 1;
        for(int i=0;i<rowIndex;i++)
        {
            for(int j=i+1;j>0;j--)
                result[j]+=result[j-1];
        }
        return result;
    }
};

// Source : https://oj.leetcode.com/problems/pascals-triangle-ii/
// Author : Hao Chen
// Date   : 2014-06-18

/********************************************************************************** 
* 
* Given an index k, return the kth row of the Pascal's triangle.
* 
* For example, given k = 3,
* Return [1,3,3,1].
* 
* Note:
* Could you optimize your algorithm to use only O(k) extra space?
* 
*               
**********************************************************************************/

#include <stdlib.h>
#include <vector>
#include <iostream>
using namespace std;

vector<int> getRow(int rowIndex) {
    vector<int> v(rowIndex+1, 0);
    v[0]=1;

    for (int i=0; i<rowIndex; i++){
        for(int j=i+1; j>0; j--){
           v[j] += v[j-1];
        } 
    }
    return v;
    
}

void printVector( vector<int>  pt)
{
    cout << "{ ";
    for(int j=0; j<pt.size(); j++){
        cout << pt[j] << ", ";
    }
    cout << "} " << endl;
}

int main(int argc, char** argv)
{
    int n = 3;
    if (argc>1) {  
        n = atoi(argv[1]);
    }
    printVector(getRow(n)); 
}
