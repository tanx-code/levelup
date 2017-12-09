class Solution {
public:
    // 跟chenhao的方法比起来，有点囧啊。赶紧学习一下！就是只比最低位，比完了就右移，再在下面写一下
    int hammingWeight(uint32_t n) {
        int count = 0;
        for(auto i =0;i< 32;i++)
        {
            uint32_t a = pow(2,i);
            if((n&a)==a)
                count++;
        }
        return count;
    }
    // 右移居然不行！？ 这uint32_t这不是没有符号位的吗！
    // 右移可以！- -！我底下的写法错了，应该是n>>=1
    int hammingWeight(uint32_t n) {
        int c = 0;
        //for(;n>0;n>>1){
        for(;n>0;n/=2)
            if(n&1) c++;
        }
        return c;
    }
};

// Source : https://leetcode.com/problems/number-of-1-bits/
// Author : Hao Chen
// Date   : 2015-03-30

/********************************************************************************** 
* 
* Write a function that takes an unsigned integer and returns the number of ’1' bits it has 
* (also known as the Hamming weight).
* 
* For example, the 32-bit integer ’11' has binary representation 00000000000000000000000000001011, 
* so the function should return 3.
* 
* Credits:Special thanks to @ts for adding this problem and creating all test cases.
*               
**********************************************************************************/

class Solution {
public:
    int hammingWeight(uint32_t n) {
        int cnt = 0;
        for(;n>0; n/=2){
            if (n & 0x1) cnt++;
        }
        return cnt;
    }
};
