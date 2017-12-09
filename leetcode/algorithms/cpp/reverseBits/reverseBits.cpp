class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
         uint32_t ret = 0;
         int c = 0;
         while(n!=0 || c!=32){
             ret = (ret<<1) + n%2;  // <<忘记加括号，居然犯了这种经典错误
             n>>=1;
             c++;
         }
         return ret;
    }
};

// discuss里神奇的merge方法，真的叼。。运行时间和我的做法是一样的
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        n = (n >> 16) | (n << 16);
        n = ((n & 0xff00ff00) >> 8) | ((n & 0x00ff00ff) << 8);
        n = ((n & 0xf0f0f0f0) >> 4) | ((n & 0x0f0f0f0f) << 4);
        n = ((n & 0xcccccccc) >> 2) | ((n & 0x33333333) << 2);
        n = ((n & 0xaaaaaaaa) >> 1) | ((n & 0x55555555) << 1);
        return n;
    }
};

// Source : https://leetcode.com/problems/reverse-bits/
// Author : Hao Chen
// Date   : 2015-03-30

/********************************************************************************** 
* 
* Reverse bits of a given 32 bits unsigned integer.
* 
* For example, given input 43261596 (represented in binary as 00000010100101000001111010011100), 
* return 964176192 (represented in binary as 00111001011110000010100101000000).
* 
* Follow up:
* If this function is called many times, how would you optimize it?
* 
* Related problem: Reverse Integer
* 
* Credits:Special thanks to @ts for adding this problem and creating all test cases.
*               
**********************************************************************************/



class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t ret=0;
        for(int i=0; i<32; i++) {
            ret = (ret*2) + (n & 0x1);
            n /=2 ;
        }
        return ret;
    }
};
