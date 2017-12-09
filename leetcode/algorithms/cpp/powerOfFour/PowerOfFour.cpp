// 感觉还是挺爽的，利用前面学到的，二的幂次方可以用减1后与自身相与来判断
// 而四的幂次方就是前者的特殊情况，这样去想，再去寻找规律，果不其然！
class Solution {
public:
    bool isPowerOfFour(int num) {
        return (num-1&num)==0 && (num%10==4||num%10==6||num==1); 
    }
};


// Source : https://leetcode.com/problems/power-of-four/
// Author : Hao Chen
// Date   : 2016-05-29

/*************************************************************************************** 
 *
 * Given an integer (signed 32 bits), write a function to check whether it is a power 
 * of 4.
 * 
 * Example:
 * Given num = 16, return true.
 * Given num = 5, return false.
 * 
 * Follow up: Could you solve it without loops/recursion?
 * 
 * Credits:Special thanks to @yukuairoy  for adding this problem and creating all test 
 * cases.
 ***************************************************************************************/


class Solution {
public:
    bool isPowerOfFour(int num) {
        static int mask = 0b01010101010101010101010101010101;
        
        //edge case
        if (num<=0) return false;
        
        // there are multiple bits are 1
        if ((num & num-1) != 0) return false;
        
        // check which one bit is zero, if the place is 1 or 3 or 5 or 7 or 9...,
        // then it is the power of 4
        if ((num & mask) != 0) return true;
        return false;
    }
};
