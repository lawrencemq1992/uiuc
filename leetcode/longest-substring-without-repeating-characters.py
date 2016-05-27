# Given a string, find the length of the longest substring without repeating characters.
# Examples:
# Given "abcabcbb", the answer is "abc", which the length is 3.
# Given "bbbbb", the answer is "b", with the length of 1.
# Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer must be a substring, "pwke" is a subsequence and not a substring.

class Solution(object):
    def lengthOfLongestSubstring(self, s):
        """
        :type s: str
        :rtype: int
        """
        if len(s) == 0:
            return 0
        if len(s) == 1:
            return 1
        char_list = []
        for i in range(0, 255):
            char_list.append(-1)
        max_len = 0
        start = 0
        end = 1
        char_list[ord(s[0])] = 0
        while end < len(s):
            if char_list[ord(s[end])] < start:
                char_list[ord(s[end])] = -1
            if char_list[ord(s[end])] < 0:
                char_list[ord(s[end])] = end
                max_len = max(max_len, end - start + 1)
                end += 1
            else:
                start += 1
        return max_len
