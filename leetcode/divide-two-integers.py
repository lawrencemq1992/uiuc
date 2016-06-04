# Divide two integers without using multiplication, division and mod operator.
# If it is overflow, return MAX_INT.

class Solution(object):
    def divide(self, dividend, divisor):
        """
        :type dividend: int
        :type divisor: int
        :rtype: int
        """
        neg = (dividend < 0 and divisor > 0) or (dividend > 0 and divisor < 0)
        a = abs(dividend)
        b = abs(divisor)
        if neg and a < b:
            return 0
        add_b = 0
        count = 0
        res = 0
        while a >= b:
            add_b = b
            count = 1
            while add_b + add_b <= a:
                add_b += add_b
                count += count
            a -= add_b
            res += count
        if neg:
            res = 0 - res
        if res > 2147483647:
            return 2147483647
        return res
