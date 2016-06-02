# Given a digit string, return all possible letter combinations that the number could represent.
# A mapping of digit to letters (just like on the telephone buttons) is given below.
# Input:Digit string "23"
# Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].

class Solution(object):
    def letterCombinations(self, digits):
        """
        :type digits: str
        :rtype: List[str]
        """
        dict = [" ", "*", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"]
        
        def translate(strs, nums):
            if len(nums) == 0:
                return strs
            new_strs = []
            for i in strs:
                for j in dict[int(nums[0])]:
                    new_strs.append(i + j)
            return translate(new_strs, nums[1:])
        
        if len(digits) == 0:
            return []
        return translate([""], digits)
