class Solution {
public:
    // 做完看答案发现chenhao用的set，恩，是应该用集合的，虽然用map也没错。
    // 我一开始的想法是错的，以为用hash能解决。忘记了每个数组里的元素也可能重复，然后发现错了之后试图直接改，这是个坏习惯。
    // 总结。这一题关键在于，要仔细观察已知条件，然后才能选对数据结构！
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        vector<int> result;
        unordered_map<int, int> m1,m2;
        for(auto i: nums1)
        {
            if(m1.find(i) == m1.end())
            {
                m1[i] = 0;
            }
        }
        for(auto i: nums2)
        {
            if(m2.find(i) == m2.end())
            {
                m2[i] = 0;
            }
        }
        for(auto i: m1)
        {
            if(m2.find(i.first) != m2.end())
                result.push_back(i.first);
        }
        return result;
    }
    // 在这里，再写一遍用set的,（p.s.用时&排名和上面的方法居然是一样的，= = set的find是O(logn)，map的find是(O1)）
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        set<int> s1,s2;
        vector<int> result;
        for(auto i: nums1)
        {
            s1.insert(i);
        }
        for(auto i: nums2)
        {
            if(s1.find(i) != s1.end())
            {
                s2.insert(i); //集合里面不会有相同的元素
            }
        }
        for(auto i: s2)
        {
            result.push_back(i);
        }
        return result;
    }
};

// Source : https://leetcode.com/problems/intersection-of-two-arrays/
// Author : Calinescu Valentin
// Date   : 2016-05-20

/*************************************************************************************** 
 *
 * Given two arrays, write a function to compute their intersection.
 * 
 * Example:
 * Given nums1 = [1, 2, 2, 1], nums2 = [2, 2], return [2].
 * 
 * Note:
 * Each element in the result must be unique.
 * The result can be in any order.
 * 
 ***************************************************************************************/
class Solution {
public:
    set <int> inter1, inter2;//we use sets so as to avoid duplicates
    vector <int> solution;
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        for(int i = 0; i < nums1.size(); i++)
            inter1.insert(nums1[i]);//get all of the unique elements in nums1 sorted
        for(int i = 0; i < nums2.size(); i++)
            if(inter1.find(nums2[i]) != inter1.end())//search inter1 in O(logN)
                inter2.insert(nums2[i]);//populate the intersection set
        for(set<int>::iterator it = inter2.begin(); it != inter2.end(); ++it)
            solution.push_back(*it);//copy the set into a vector
        return solution;
    }
};
