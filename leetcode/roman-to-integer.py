# Given a roman numeral, convert it to an integer.
# Input is guaranteed to be within the range from 1 to 3999.

class Solution(object):
    def romanToInt(self, s):
        """
        :type s: str
        :rtype: int
        """
        par_seq = [1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1]
        rom_dict = ["M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"]
        
        def parse_roman(s, pos):
            if len(s) == 0:
                return 0
            if s.startswith(rom_dict[pos]):
                return par_seq[pos] + parse_roman(s[len(rom_dict[pos]):], pos)
            else:
                return parse_roman(s, pos + 1)
        return parse_roman(s, 0)
