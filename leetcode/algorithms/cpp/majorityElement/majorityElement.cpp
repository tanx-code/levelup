class Solution {
public:
    int majorityElement(vector<int>& nums) {
        // 用两个map，来按值排序，因为这个majority element 肯定是值最大的，而且唯一。
        map<int, int> m1,m2;
        for(auto i:nums)
        {
            if(m1.find(i)==m1.end())
                m1[i]=1;
            else
                m1[i]++;
        }
        for(auto i:m1)
        {
            m2[i.second] = i.first;
        }
        auto end = m2.end();
        return (--end)->second;
    }
};

// Source : https://oj.leetcode.com/problems/majority-element/
// Author : Hao Chen
// Date   : 2014-12-25

/********************************************************************************** 
 * 
 * Given an array of size n, find the majority element. The majority element is the element that appears more than ⌊ n/2 ⌋ times.
 * 
 * You may assume that the array is non-empty and the majority element always exist in the array.
 * 
 * Credits:Special thanks to @ts for adding this problem and creating all test cases.
 *               
 **********************************************************************************/

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;


// Moore Voting Algorithm
// Refer to: 
// http://www.cs.utexas.edu/~moore/best-ideas/mjrty/index.html
int majorityElement(vector<int> &num) {
    int majority;
    int cnt = 0;
    for(int i=0; i<num.size(); i++){
        if ( cnt ==0 ){
            majority = num[i];
            cnt++;
        }else{
            majority == num[i] ? cnt++ : cnt --;
            if (cnt >= num.size()/2) return majority;
        }
    }
    return majority;

}


vector<int> &split(const string &s, char delim, vector<int> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(atoi(item.c_str()));
    }
    return elems;
}


vector<int> split(const string &s, char delim) {
    vector<int> elems;
    split(s, delim, elems);
    return elems;
}


int main(int argc, char** argv)
{
    string array = "1,2,1,2,1,2,1,2,1,2,1";
    if (argc > 1){
        array = argv[1];
    }

    cout << "[" << array << "]" << endl;
    vector<int> num = split(array, ',');
    cout << majorityElement(num) <<endl;

    return 0;
}
