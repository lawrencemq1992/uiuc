# Given a string S, you are allowed to convert it to a palindrome by adding characters in front of it. Find and return the shortest palindrome you can find by performing this transformation.
# For example:
# Given "aacecaaa", return "aaacecaaa".
# Given "abcd", return "dcbabcd".

# build s + # + reverse(s), use kmp to find where to start if there's a mismatch at the end of reverse(s), then concatonate the rest to the s
# KMP: https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm

class Solution(object):
    def shortestPalindrome(self, s):
        """
        :type s: str
        :rtype: str
        """
        rev_s = s[::-1] # [begin:end:step]
        new_s = s + '#' + rev_s # '#' is to avoid empty string
        kmp = [0] * len(new_s)
        for i in range(1, len(new_s)):
            prev = kmp[i - 1]
            while prev > 0 and new_s[i] != new_s[prev]:
                prev = kmp[prev - 1]
            kmp[i] = prev + (new_s[i] == new_s[prev])
        return rev_s[:len(s) - kmp[-1]] + s
