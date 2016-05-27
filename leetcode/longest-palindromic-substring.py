# Given a string S, find the longest palindromic substring in S. You may assume that the maximum length of S is 1000, and there exists one unique longest palindromic substring.

class Solution(object):
    def longestPalindrome(self, s):
        """
        :type s: str
        :rtype: str
        """
        if len(s) == 0:
            return ""
        if len(s) == 1:
            return s
        
        start = -1
        end  = -2
        for i in range(len(s)):
            side = 1
            while i - side >= 0 and i + side < len(s) and s[i - side] == s[i + side]:
                side += 1
            if (side - 1) * 2 + 1 > end - start + 1:
                start = i - (side - 1)
                end = i + side
        out_string = s[start:end]
        start = -1
        end = -2
        for i in range(len(s) - 1):
            side = 0
            while i - side >= 0 and i + 1 + side < len(s) and s[i - side] == s[i + 1 + side]:
                side += 1
            if side * 2 > end - start + 1:
                start  = i - side + 1
                end = i + 1 + side
        return out_string if len(out_string) > end - start else s[start:end]
