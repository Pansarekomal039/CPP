class Solution {
public:
    bool isSubsequence(string s, string t) {
       int i = 0, flag = 1;  
       for (int j = 0; j < t.size(); j++) {
           if (i < s.size() && s[i] == t[j]) {
               i++;  
           }
       }

       if (i < s.size()) {
           flag = 0;  
       }

       return flag;
    }
};
