class Solution {
public:

    // 看了提示，要用hash来减少查找次数，然后写的时候还是磕磕盼盼，思想也不复杂，应该要快速想出的T_T
    // 思路，把组成target的两个数当做key，然后遍历的时候把每个数的值作为key，然后把target-key作为key插进去，值为i。
    // 这样下次碰到已存在的key，就同时有前一个数的索引m[num[i]]，和当前数的索引i了。
    vector<int> twoSum(vector<int>& nums, int target) {
        int a,b;
        unordered_map<int, int>  m;
        for(int i = 0; i<nums.size(); i++)
        {
            if(m.find(nums[i]) == m.end())
            {
                m[target-nums[i]] = i;
            }
            else
            {
                a = m[nums[i]];
                b = i;
            }
        }
        return vector<int>{a,b};
    }


    // 错误：时间复杂度为O(n2)，超出运行时间了
    // vector<int> twoSum(vector<int>& nums, int target) {
    //     int a,b;
    //     for(int i = 0; i<nums.size(); i++)
    //     {
    //         if(nums[i]<target)
    //         {
    //             for(int j = 0; j<nums.size(); j++)
    //             {
    //                 if(i != j && (nums[i]+nums[j]==target))
    //                 {
    //                     a = i>j?j:i;
    //                     b = i>j?i:j;
    //                     break;
    //                 }
    //             }
    //         }
    //     }
    //     return vector<int>{a,b};
    // }
};

// Source : https://oj.leetcode.com/problems/two-sum/
// Author : Hao Chen
// Date   : 2014-06-17

/********************************************************************************** 
* 
* Given an array of integers, find two numbers such that they add up to a specific target number.
* 
* The function twoSum should return indices of the two numbers such that they add up to the target, 
* where index1 must be less than index2. Please note that your returned answers (both index1 and index2) 
* are not zero-based.
* 
* You may assume that each input would have exactly one solution.
* 
* Input: numbers={2, 7, 11, 15}, target=9
* Output: index1=1, index2=2
* 
*               
**********************************************************************************/

class Solution {
public:
    /*
     *   The easy solution is O(n^2) run-time complexity.
     *   ```
     *       foreach(item1 in array) {
     *           foreach(item2 in array){
     *               if (item1 + item2 == target) {
     *                   return result
     *               }
     *           }
     *   ```
     *   
     *   We can see the nested loop just for searching, 
     *   So, we can use a hashmap to reduce the searching time complexity from O(n) to O(1)
     *   (the map's `key` is the number, the `value` is the position)
     *   
     *   But be careful, if there are duplication numbers in array, 
     *   how the map store the positions for all of same numbers?
     *
     */


    //
    // The implementation as below is bit tricky. but not difficult to understand
    //
    //  1) Traverse the array one by one
    //  2) just put the `target - num[i]`(not `num[i]`) into the map
    //     so, when we checking the next num[i], if we found it is exisited in the map.
    //     which means we found the second one.
    //      
    vector<int> twoSum(vector<int> &numbers, int target) {
        unordered_map<int, int> m;
        vector<int> result;
        for(int i=0; i<numbers.size(); i++){
            // not found the second one
            if (m.find(numbers[i])==m.end() ) { 
                // store the first one poisition into the second one's key
                m[target - numbers[i]] = i; 
            }else { 
                // found the second one
                result.push_back(m[numbers[i]]+1);
                result.push_back(i+1);
                break;
            }
        }
        return result;
    }
};
