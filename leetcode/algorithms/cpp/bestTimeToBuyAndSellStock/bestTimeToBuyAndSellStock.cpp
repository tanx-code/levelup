class Solution {
public:
    // 我没做出来。discus里面的一目了然的方法：每一次用当前价格去减，前面一段的最低价格，就能减少判断次数了。
    // 看了下chenhao的做法。跟上面实质一样，只是想法有点不同，用begin去记录最低价格，当价格差为负数的时候，移动begin到当前位置。
    int maxProfit(vector<int>& prices) {
        if(prices.size()<=1)
            return 0;
        int max_profit = 0;
        int low_price = prices[0];
        for(auto i=0;i<prices.size();i++) 
        {
            low_price = min(low_price,prices[i]);
            max_profit = max(max_profit,prices[i]-low_price);
        }
        return max_profit;
    }
};

// Source : https://oj.leetcode.com/problems/best-time-to-buy-and-sell-stock/
// Author : Hao Chen
// Date   : 2014-06-18

/********************************************************************************** 
* 
* Say you have an array for which the ith element is the price of a given stock on day i.
* 
* If you were only permitted to complete at most one transaction (ie, buy one and sell one share of the stock), 
* design an algorithm to find the maximum profit.
*               
**********************************************************************************/

class Solution {
public:
    //
    // This solution is O(1) space dynamic programming 
    //
    // We can make sure the max profit at least be ZERO. So,
    //    1) we have two pointers (begin & end ) 
    //    2) if prices[end] - prices[begin] >  0, then move the "end" pointer to next
    //    3) if prices[end] - prices[begin] <= 0, then move the "begin" pointer to current posstion.
    //    4) tracking the max profit
    //
    // Notes:
    //    Some people think find the highest-price & lowest-price, this is wrong. 
    //    Because the highest-price must be after lowest-price
    //
    int maxProfit(vector<int> &prices) {
        
        int max=0, begin=0, end=0, delta=0;
        
        for (int i=0; i<prices.size(); i++) {
            
            end = i;
            
            delta = prices[end] - prices[begin];
            
            if (delta <= 0){
                begin = i;
            }
            
            if ( delta > max ){
                max = delta;
            }
            
        }
        
        return max;
        
    }
};
