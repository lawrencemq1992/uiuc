# Given a complete binary tree, count the number of nodes.
# Definition of a complete binary tree from Wikipedia:
# In a complete binary tree every level, except possibly the last, is completely filled, and all nodes in the last level are as far left as possible. It can have between 1 and 2h nodes inclusive at the last level h.

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution(object):
    def countNodes(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        if root is None:
            return 0
        left_count = right_count = 0
        left = right = root
        while left:
            left_count += 1
            left = left.left
        while right:
            right_count += 1
            right = right.right
        if left_count == right_count:
            return 2 ** left_count - 1
        return 1 + self.countNodes(root.left) + self.countNodes(root.right)
