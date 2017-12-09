class Solution {
public:
    // 改了好几下，最后查看发现效率不高
    int removeDuplicates(vector<int>& nums) {
        auto p = nums.begin();
        auto it = nums.begin();
        for( ;it!=nums.end(); )
        {
            it++;
            while(*it == *p && it!=nums.end())
            {
                it = nums.erase(it);
            }
            p = it;
        }
        return nums.size();
    }
    // 用chenhao的方法再写一遍，我才发现题目允许你在数组最后留东西，显然我的方法就没利用到这一条件。
    // 他的方法的原理，在于用pos滞后来将不重复的元素一个一个往前复制。
    int removeDuplicates(vector<int>& nums) {
        if(nums.size()<=1)
            return nums.size();
        int pos = 0;
        for(int i = 0; i<nums.size()-1; i++)
        {
            if(nums[i] != nums[i+1])
            {
                nums[++pos] = nums[i+1];
            }
        }
        return pos+1;
    }
};

// Source : https://oj.leetcode.com/problems/remove-duplicates-from-sorted-array/
// Author : Hao Chen
// Date   : 2014-06-22

/********************************************************************************** 
* 
* Given a sorted array, remove the duplicates in place such that each element appear 
* only once and return the new length.
* 
* Do not allocate extra space for another array, you must do this in place with constant memory.
* 
* For example,
* Given input array A = [1,1,2],
* 
* Your function should return length = 2, and A is now [1,2].
* 
*               
**********************************************************************************/

class Solution {
public:
    int removeDuplicates(int A[], int n) {
        
        if (n<=1) return n;
        
        int pos=0;
        for(int i=0; i<n-1; i++){
            if (A[i]!=A[i+1]){
                A[++pos] = A[i+1];
            }
        }
        return pos+1;
    }
};
