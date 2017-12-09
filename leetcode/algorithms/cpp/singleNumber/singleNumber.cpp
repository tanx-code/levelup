// 题目要求是O(1)space，我没想出来
// 其实我想到异或了，但是没想到，异或具有结合律 a ^ b ^ c = a ^ (b ^ c)
// 想到这一点的话，所有相同的数加起来都是0，剩下的那个就是特殊的了。
int singleNumber(int A[], int n) {
    int s = 0;
    for(int i=0; i<n; i++){
        s = s^A[i];
    }
    return s;
}



// O(n) space
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        map<int,int> m;
        for(auto i : nums){
            if(m.find(i) == m.end()){
                m[i] = 0;
            }else{
                m[i]++;
            }
        }
        
        for(auto i : m){
            if(i.second == 0)
                return i.first;
        }
        
        return 0;
    }
};



// Source : https://oj.leetcode.com/problems/single-number/
// Author : Hao Chen
// Date   : 2014-06-17

/********************************************************************************** 
* 
* Given an array of integers, every element appears twice except for one. Find that single one.
* 
* Note:
* Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?
* 
*               
**********************************************************************************/

#include <stdio.h>
// This is classical interview question
// As we know, the same number XOR together will be 0,
// So, XOR all of numbers, the result is the number which only appears once. 
int singleNumber(int A[], int n) {
    int s = 0;
    for(int i=0; i<n; i++){
        s = s^A[i];
    }
    return s;
}

int main()
{
    int a[]={1,1,2,2,3};
    printf("%d\n", singleNumber(a,5));
    return 0;
}
