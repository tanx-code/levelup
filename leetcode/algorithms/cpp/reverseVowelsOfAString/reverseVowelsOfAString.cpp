class Solution {
public:
    string reverseVowels(string s) {
        map<int,char> m;
        for(int i = 0;i<s.size();i++)
        {
            if( s[i]=='a'||s[i]=='A'||
                s[i]=='e'||s[i]=='E'||
                s[i]=='o'||s[i]=='O'||
                s[i]=='i'||s[i]=='I'||
                s[i]=='u'||s[i]=='U')
                {
                    m[i] = s[i];
                }
        }
        if(m.size()<2)
            return s;
        auto it1 = m.begin();
        auto it2 = m.rbegin();
        for(;it1->first!=it2->first;)
        {
            s[it1->first] = it2->second;
            s[it2->first] = it1->second;
            it1++;
            if(it1->first ==it2->first)
                break;
            else
                it2++;
        }
        return s;
    }
};

// Source : https://leetcode.com/problems/reverse-vowels-of-a-string/
// Author : Calinescu Valentin
// Date   : 2016-04-30

/*************************************************************************************** 
 *
 * Write a function that takes a string as input and reverse only the vowels of a 
 * string.
 * 
 * Example 1:
 * Given s = "hello", return "holle".
 * 
 * Example 2:
 * Given s = "leetcode", return "leotcede".
 * 
 ***************************************************************************************/
class Solution {
public:
    string reverseVowels(string s) {
        list <char> vowels;
        set <char> vows;
        vows.insert('a');
        vows.insert('A');
        vows.insert('e');
        vows.insert('E');
        vows.insert('i');
        vows.insert('I');
        vows.insert('o');
        vows.insert('O');
        vows.insert('u');
        vows.insert('U');
        string result;
        for(int i = 0; i < s.size(); i++)
        {
            if(vows.find(s[i]) != vows.end())
                vowels.push_back(s[i]);
        }
        for(int i = 0; i < s.size(); i++)
        {
            if(vows.find(s[i]) != vows.end())
            {
                result.push_back(vowels.back());
                vowels.pop_back();
            }
            else
                result.push_back(s[i]);
        }
        return result;
    }
};
