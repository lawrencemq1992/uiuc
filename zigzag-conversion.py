# The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)
# P   A   H   N
# A P L S I I G
# Y   I   R
# And then read line by line: "PAHNAPLSIIGYIR"
# Write the code that will take a string and make this conversion given a number of rows:
# string convert(string text, int nRows);
# convert("PAYPALISHIRING", 3) should return "PAHNAPLSIIGYIR".

# Qing Ma's Note:
# FUCKING HARD TO CALCULATE THE POSITION AND RUN WITH LIMITED TIME

class Solution(object):
    def convert(self, s, numRows):
        """
        :type s: str
        :type numRows: int
        :rtype: str
        """
        lens = len(s)
        if numRows >= lens or numRows <= 1:
            return s
        return_s = ""
        for i in range(numRows):
            jump1 = 2 * numRows - 2 - 2 * i
            jump2 = 2 * numRows - 2 - jump1
            pos = i
            while True:
                if pos == i:
                    return_s += s[pos]
                if pos + jump1 >= lens:
                    break
                if jump1 != 0:
                    return_s += s[pos + jump1]
                    pos += jump1
                if pos + jump2 >= lens:
                    break
                if jump2 != 0:
                    return_s += s[pos + jump2]
                    pos += jump2
        return return_s
        
