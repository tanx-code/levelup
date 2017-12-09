class Solution {
public:
    // 这道题是动态规划吧，想起来就比较简单了。要么走一步要么走两步
    // 递归的做法
    unordered_map<int,int> m;
    int climbStairs(int n) {
        if(n<=2) //0,1,2阶的时候，各有0,1,2种方法，所以刚好返回n
            return n;
        if(m.find(n)!=m.end())
            return m[n];
        else
            return m[n] = climbStairs(n-1)+climbStairs(n-2);
    }
    
    // 自底向上的做法
    int climbStairs(int n) {
        int a[n+1];
        for(int i=0;i<=n;i++)
        {
            if(i<3)
                a[i] = i;
            else{
                a[i] = a[i-1]+a[i-2];
            }
        }
        return a[n];
    }
};

// Source : https://oj.leetcode.com/problems/climbing-stairs/
// Author : Hao Chen
// Date   : 2014-06-27

/********************************************************************************** 
* 
* You are climbing a stair case. It takes n steps to reach to the top.
* 
* Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
* 
*               
**********************************************************************************/

class Solution {
public:
    
    int climbStairs(int n) {
       if (n<=3) return n;
       int a[2]={2,3};
       for(int i=4; i<=n; i++){
           int t = a[0] + a[1];
           a[0] = a[1];
           a[1] = t;
       }
       return a[1];
    }
    //Time too long
    int climbStairs2(int n) {
        if (n<=3) return n;
        return climbStairs(n-1) + climbStairs(n-2);
    }
};
