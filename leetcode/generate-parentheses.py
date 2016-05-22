# Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.
# For example, given n = 3, a solution set is:
# "((()))", "(()())", "(())()", "()(())", "()()()"
class Solution(object):
    def generateParenthesis(self, n):
        """
        :type n: int
        :rtype: List[str]
        """
        if n == 0:
            return []
        result = []
        self.generate_helper(n, n, '', result)
        return result
    
    def generate_helper(self, left, right, item, result):
        if left > right:
            return
        if left == 0 and right == 0:
            result.append(item)
        if left > 0:
            self.generate_helper(left - 1, right, item + '(', result)
        if right > 0:
            self.generate_helper(left, right - 1, item + ')', result)
