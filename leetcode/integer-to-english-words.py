# Convert a non-negative integer to its english words representation. Given input is guaranteed to be less than 231 - 1.
# For example,
# 123 -> "One Hundred Twenty Three"
# 12345 -> "Twelve Thousand Three Hundred Forty Five"
# 1234567 -> "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"

class Solution(object):
    def numberToWords(self, num):
        """
        :type num: int
        :rtype: str
        """
        lv1 = "Zero One Two Three Four Five Six Seven Eight Nine Ten Eleven Twelve Thirteen Fourteen Fifteen Sixteen Seventeen Eighteen Nineteen".split()
        lv2 = "Twenty Thirty Forty Fifty Sixty Seventy Eighty Ninety".split()
        lv3 = "Hundred"
        lv4 = "Thousand Million Billion".split()
        if num == 0:
            return lv1[0]
        return_s = ""
        thousand = 0
        copy_num = abs(num)
        rem_100 = rem_100 = rem_10 = 0
        div_100 = div_10 = 0
        while copy_num > 0:
            temp_s = ""
            rem_1000 = copy_num % 1000
            if rem_1000 != 0:
                if rem_1000 >= 100:
                    div_100 = rem_1000 / 100
                    rem_100 = rem_1000 % 100
                    temp_s += lv1[div_100] + " " + lv3 + " "
                    if rem_100 >= 20:
                        div_10 = rem_100 / 10
                        rem_10 = rem_100 % 10
                        temp_s += lv2[div_10 - 2] + ((" " + lv1[rem_10] + " ") if rem_10 > 0 else " ")
                    else:
                        temp_s += lv1[rem_100] + " " if rem_100 > 0 else ""
                else:
                    if rem_1000 >= 20:
                        div_10 = rem_1000 / 10
                        rem_10 = rem_1000 % 10
                        temp_s += lv2[div_10 - 2] + ((" " + lv1[rem_10] + " ") if rem_10 > 0 else " ")
                    else:
                        temp_s += (lv1[rem_1000] + " " if rem_1000 > 0 else "")
                return_s = temp_s + ((lv4[thousand - 1] + " ") if thousand > 0 else " ") + return_s
            thousand += 1
            copy_num = copy_num / 1000
        return_s = return_s.rstrip()
        return ("Negative " + return_s) if num < 0 else return_s
