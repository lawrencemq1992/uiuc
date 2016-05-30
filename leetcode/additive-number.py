# Additive number is a string whose digits can form additive sequence.
# A valid additive sequence should contain at least three numbers. Except for the first two numbers, each subsequent 3 number in the sequence must be the sum of the preceding two.
# For example:
# "112358" is an additive number because the digits can form an additive sequence: 1, 1, 2, 3, 5, 8.
# 1 + 1 = 2, 1 + 2 = 3, 2 + 3 = 5, 3 + 5 = 8
# "199100199" is also an additive number, the additive sequence is: 1, 99, 100, 199.
# 1 + 99 = 100, 99 + 100 = 199
# Note: Numbers in the additive sequence cannot have leading zeros, so sequence 1, 2, 03 or 1, 02, 3 is invalid.
# Given a string containing only digits '0'-'9', write a function to determine if it's an additive number.

class Solution(object):
    def isAdditiveNumber(self, num):
        """
        :type num: str
        :rtype: bool
        """
        
        def is_valid(num):
            return len(num) == 1 or num[0] != '0'
            
        def search_num(num, int_1, int_2):
            new_sum = str(int_1 + int_2);
            if not is_valid(new_sum) or not num.startswith(new_sum):
                return False
            elif new_sum == num:
                return True
            else:
                return search_num(num[len(new_sum):], int_2, int(new_sum))
        
        lenn = len(num)
        for i in range(1, lenn / 2 + 1):
            num_1 = num[0: i]
            for j in range(i + 1, lenn):
                num_2 = num[i: j]
                if (is_valid(num_1) and is_valid(num_2)):
                    if search_num(num[j:], int(num_1), int(num_2)):
                        return True
        return False
        
        
                
