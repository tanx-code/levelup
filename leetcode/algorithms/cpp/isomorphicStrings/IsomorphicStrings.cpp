// map的思想，两个字符串里的字母要严格对应。
// 第一次提交少了第八行那段for，所以错了。
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        unordered_map<char,char> m;
        for(auto i = s.begin(),j=t.begin();i!=s.end();i++,j++){
            if(m.find(*i)==m.end()){
                for(auto itm : m){
                    if(itm.second==*j)
                        return false;
                }
                m[*i] = *j;
            }else if(*j!=m[*i]){
                    return false;
            }
        }
        return true;
    }
};


// Source : https://leetcode.com/problems/isomorphic-strings/
// Author : Hao Chen
// Date   : 2015-06-09

/********************************************************************************** 
 * 
 * Given two strings s and t, determine if they are isomorphic.
 * 
 * Two strings are isomorphic if the characters in s can be replaced to get t.
 * 
 * All occurrences of a character must be replaced with another character while preserving 
 * the order of characters. No two characters may map to the same character but a character
 *  may map to itself.
 * 
 * For example,
 *
 *     Given "egg", "add", return true.
 *     
 *     Given "foo", "bar", return false.
 *     
 *     Given "paper", "title", return true.
 * 
 * Note:
 * You may assume both s and t have the same length.
 *               
 **********************************************************************************/


class Solution {
public:
    bool isIsomorphic(string s, string t) {
        if (s.size()!=t.size()) return false;
        
        const int MAXCHAR = 256;
        char maps[MAXCHAR]={0}, mapt[MAXCHAR]={0};
        //memset(maps, 0, sizeof(maps));
        //memset(mapt, 0, sizeof(mapt));
        
        for(int i=0; i<s.size(); i++){
            if(maps[s[i]] == 0 && mapt[t[i]] == 0){
                maps[s[i]] = t[i];
                mapt[t[i]] = s[i];
                continue;
            }
            if(maps[s[i]] == t[i] && mapt[t[i]] == s[i]) {
                continue;
            }
            return false;
        }
        return true;
    }
};
