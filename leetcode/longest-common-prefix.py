# Write a function to find the longest common prefix string amongst an array of strings.

class Solution(object):
    def longestCommonPrefix(self, strs):
        """
        :type strs: List[str]
        :rtype: str
        """
        if len(strs) == 0:
            return ""
        return_s = ""
        for i in range(len(strs[0])):
            for j in strs:
                if i >= len(j) or strs[0][i] != j[i]:
                    return return_s
            return_s += strs[0][i]
        return return_s
