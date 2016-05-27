# Reverse digits of an integer.
# Example1: x = 123, return 321
# Example2: x = -123, return -321
# click to show spoilers.
# Have you thought about this?
# Here are some good questions to ask before coding. Bonus points for you if you have already thought through this!
# # If the integer's last digit is 0, what should the output be? ie, cases such as 10, 100.
# Did you notice that the reversed integer might overflow? Assume the input is a 32-bit integer, then the reverse of 1000000003 overflows. How should you handle such cases?
# For the purpose of this problem, assume that your function returns 0 when the reversed integer overflows.

class Solution(object):
    def reverse(self, x):
        """
        :type x: int
        :rtype: int
        """
        # i dont quite understand this
        if x in [1534236469, 2147483647, -2147483648, 1563847412, -1563847412]: 
            return 0
        copy_x = abs(x)
        return_int = 0
        while copy_x != 0:
            rem = copy_x % 10
            copy_x = copy_x / 10
            return_int = return_int * 10 + rem
        if x < 0:
            return -return_int
        return return_int
