# Given a 2D board and a word, find if the word exists in the grid.
# The word can be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or # vertically neighboring. The same letter cell may not be used more than once.
# For example,
# Given board =
# [
#   ['A','B','C','E'],
#   ['S','F','C','S'],
#   ['A','D','E','E']
# ]
# word = "ABCCED", -> returns true,
# word = "SEE", -> returns true,
# word = "ABCB", -> returns false.

class Solution(object):
    def exist(self, board, word):
        """
        :type board: List[List[str]]
        :type word: str
        :rtype: bool
        """
        if word == []:
            return True
        m = len(board)
        if m == 0:
            return False
        n = len(board[0])
        if n == 0:
            return False
        visited = [[False for j in range(n)] for i in range(m)]
        for i in range(m):
            for j in range(n):
                if self.find_word(board, word, visited, i, j, 0):
                    return True
        return False

    def find_word(self, board, word, visited, x, y, pos):
        m, n = len(board), len(board[0])
        if pos == len(word):
            return True
        if x < 0 or x >= m or y < 0 or y >= n:
            return False
        if word[pos] != board[x][y] or visited[x][y]:
            return False
        visited[x][y] = True
        if self.find_word(board, word, visited, x + 1, y, pos + 1):
            return True
        if self.find_word(board, word, visited, x - 1, y, pos + 1):
            return True
        if self.find_word(board, word, visited, x, y + 1, pos + 1):
            return True
        if self.find_word(board, word, visited, x, y - 1, pos + 1):
            return True
        visited[x][y] = False
        return False
        
        
        
            
