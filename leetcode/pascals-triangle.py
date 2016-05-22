class Solution(object):
    def generate(self, numRows):
        """
        :type numRows: int
        :rtype: List[List[int]]
        """
        if numRows < 1:
            return []
        if numRows == 1:
            return [[1]]
        prev_rows = self.generate(numRows - 1)
        new_row = []
        new_row.append(1)
        for i in range(0, numRows - 2):
            new_row.append(prev_rows[numRows - 2][i] + prev_rows[numRows - 2][i + 1])
        new_row.append(1)
        prev_rows.append(new_row)
        return prev_rows
