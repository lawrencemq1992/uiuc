# Implement strStr().
# Returns the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.

# KMP

class Solution(object):
    def strStr(self, haystack, needle):
        """
        :type haystack: str
        :type needle: str
        :rtype: int
        """
        m = len(haystack)
        n = len(needle)
        if n == 0:
            return 0
        if m < n:
            return -1
        kmp = [0] * n
        for i in range(1, n):
            prev = kmp[i - 1]
            while prev > 0 and needle[i] != needle[prev]:
                prev = kmp[prev - 1]
            kmp[i] = prev + (needle[i] == needle[prev])
        count = 0
        for i in range(m):
            while count > 0 and haystack[i] != needle[count]:
                count = kmp[count - 1]
            if haystack[i] == needle[count]:
                count += 1
            if count == n:
                return i - n + 1
        return -1
