# Given an integer n, count the total number of digit 1 appearing in all non-negative integers less than or equal to n.
# For example:
# Given n = 13,
# Return 6, because digit 1 occurred in the following numbers: 1, 10, 11, 12, 13.

class Solution(object):
    def countDigitOne(self, n):
        """
        :type n: int
        :rtype: int
        """
        return self.count_one_helper(n, 0, 0)
        
    def count_one_helper(self, n, pos, rem):
        if n <= 0:
            return 0
        remain = n % 10
        division = int(n / 10)
        sum = 0
        if remain > 1:
            sum += 10 ** pos * (division + 1)
        elif remain == 1:
            sum += 10 ** pos * division + rem + 1
        else:
            sum += 10 ** pos * division
        return sum + self.count_one_helper(division, pos + 1, remain * 10 ** pos + rem)    
        
