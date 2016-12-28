class Solution(object):
    def solveSudoku(self, board):
        """
        :type board: List[List[str]]
        :rtype: void Do not return anything, modify board in-place instead.
        """
        def is_valid(row, col, value):
            for i in range(0, 9): # check row
                if i != row:
                    if board[i][col] == value:
                        return False
                if i != col:
                    if board[row][i] == value:
                        return False
            row_mod = row % 3
            col_mod = col % 3
            for i in range(0, 3):
                for j in range(0, 3):
                    if i != row_mod and j != col_mod:
                        if board[row - row_mod + i][col - col_mod + j] == value:
                            return False
            return True
        
        def process(row, col):
            if row >= 9:
                return True
            if col >= 9:
                return process(row + 1, 0)
            if board[row][col] != '.':
                return process(row, col + 1)
            for i in range(1, 10):
                if is_valid(row, col, str(i)):
                    board[row][col] = str(i)
                    if process(row, col + 1):
                        return True
            board[row][col] = '.'
            return False
            
        if len(board) != 9:
            return
        if len(board[0]) != 9:
            return
        process(0,0)
        return
