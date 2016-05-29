# Implement regular expression matching with support for '.' and '*'.
# '.' Matches any single character.
# '*' Matches zero or more of the preceding element.
# The matching should cover the entire input string (not partial).
# The function prototype should be:
# bool isMatch(const char *s, const char *p)
# Some examples:
# isMatch("aa","a") → false
# isMatch("aa","aa") → true
# isMatch("aaa","aa") → false
# isMatch("aa", "a*") → true
# isMatch("aa", ".*") → true
# isMatch("ab", ".*") → true
# isMatch("aab", "c*a*b") → true

class Solution(object):
    def isMatch(self, s, p):
        """
        :type s: str
        :type p: str
        :rtype: bool
        """
        if len(p) == 0:
            return len(s) == 0
        m = len(s)
        n = len(p)
        dp = []
        for i in range(m + 1):
            dp.append([])
            for j in range(n + 1):
                dp[i].append(False)
        dp[0][0] = True
        for i in range(m + 1):
            for j in range(1, n + 1):
                if p[j - 1] != '.' and p[j - 1] != '*':
                    if i > 0 and s[i - 1] == p[j - 1] and dp[i - 1][j - 1]:
                        dp[i][j] = True
                elif p[j - 1] == '.':
                    if i > 0 and dp[i - 1][j - 1]:
                        dp[i][j] = True
                elif j > 1: # p[i - 1] == '*'
                    if dp[i][j - 1] or dp[i][j - 2]:
                        dp[i][j] = True
                    elif i > 0 and (p[j - 2] == s[i - 1] or p[j - 2] == '.') and dp[i - 1][j]:
                        dp[i][j] = True
        return dp[m][n]
                        
        
