class Solution(object):
    def isValidSudoku(self, board):
        """
        :type board: List[List[str]]
        :rtype: bool
        """
        def is_valid(row, col):
            if board[row][col] == '.':
                return True
            for i in range(row + 1, 9): # check row
                if board[i][col] == board[row][col]:
                    return False
            for i in range(col + 1, 9): # check row
                if board[row][i] == board[row][col]:
                    return False
            row_mod = row % 3
            col_mod = col % 3
            for i in range(0, 3):
                for j in range(0, 3):
                    if i != row_mod and j != col_mod:
                        if board[row - row_mod + i][col - col_mod + j] == board[row][col]:
                            return False
            return True
        
        if len(board) != 9:
            return False
        if len(board[0]) != 9:
            return False
        for i in range(9):
            for j in range(9):
                if not is_valid(i, j):
                    return False
        return True
