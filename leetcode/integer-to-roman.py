# Given an integer, convert it to a roman numeral.
# Input is guaranteed to be within the range from 1 to 3999.

class Solution(object):
    def intToRoman(self, num):
        """
        :type num: int
        :rtype: str
        """
        par_seq = [1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1]
        rom_dict = ["M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"]
        
        def parse_to_roman(num, par):
            if num == 0:
                return ""
            if num >= par_seq[par]:
                times = num / par_seq[par]
                return rom_dict[par] * times + parse_to_roman(num - par_seq[par] * times, par)
            else:
                return parse_to_roman(num, par + 1)

        return_s = parse_to_roman(num, 0)
        return return_s
        
