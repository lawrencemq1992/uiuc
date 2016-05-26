# Given a non-negative integer num, repeatedly add all its digits until the result has only one digit.
# For example:
# Given num = 38, the process is like: 3 + 8 = 11, 1 + 1 = 2. Since 2 has only one digit, return it.

# Solution:
# 0 = 0
# 9 = 9
# o.w. abcd... = 100...a + 10...b + 1...c + ..., which equals a + b + ... when mod 9

class Solution(object):
    def addDigits(self, num):
        """
        :type num: int
        :rtype: int
        """
        return 9 if num % 9 == 0 and num != 0 else 0 if num == 0 else num % 9
