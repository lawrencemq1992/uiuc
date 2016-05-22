# Given an index k, return the kth row of the Pascal's triangle.
class Solution(object):
    def getRow(self, rowIndex):
        """
        :type rowIndex: int
        :rtype: List[int]
        """
        if rowIndex <= 0:
            return [1]
        prev_row = self.getRow(rowIndex - 1)
        curr_row = []
        curr_row.append(1)
        for i in range(0, rowIndex - 1):
            curr_row.append(prev_row[i] + prev_row[i + 1])
        curr_row.append(1)
        return curr_row
