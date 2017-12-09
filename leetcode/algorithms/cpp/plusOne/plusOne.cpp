class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int c = 1;
        vector<int> result;
        for(auto it = digits.rbegin(); it != digits.rend(); it++)
        {
            int r_tmp = c+(*it);
            if(r_tmp > 9)
            {
                c = 1;
                result.insert(result.begin(),r_tmp-10);
            }
            else
            {
                c = 0;
                result.insert(result.begin(),r_tmp);
            }
        }
        if(c == 1 && !result.empty())
            result.insert(result.begin(),1);
        return result;
    }
};

// Source : https://oj.leetcode.com/problems/plus-one/
// Author : Hao Chen
// Date   : 2014-06-21

/********************************************************************************** 
* 
* Given a non-negative number represented as an array of digits, plus one to the number.
* 
* The digits are stored such that the most significant digit is at the head of the list.
*               
**********************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

vector<int> plusOne(vector<int> &digits) {
    int carry=1;
    vector <int> v;
    while(digits.size()>0){
        int x = digits.back();
        digits.pop_back();
        x = x + carry;
        v.insert(v.begin(), x%10);
        carry = x/10;
    }
    if (carry>0){
        v.insert(v.begin(), carry);
    }
    return v;

}

void printVector(vector<int>& v)
{
    cout << "{ ";
    for(int i=0; i<v.size(); i++){
        cout << v[i] << " ";
    }
    cout << "} " << endl;
}


int main()
{
    int a[]={9,9,9};
    vector<int> d(&a[0], &a[0]+sizeof(a)/sizeof(int));
    vector<int> v = plusOne(d);
    printVector(v);
    return 0;
}
