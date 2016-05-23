# Given an array where elements are sorted in ascending order, convert it to a height balanced BST.

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution(object):
    def sortedArrayToBST(self, nums):
        """
        :type nums: List[int]
        :rtype: TreeNode
        """
        if nums is None:
            return None
        head_node = self.convert_to_bst(nums, 0, len(nums) - 1)
        return head_node
    
    def convert_to_bst(self, nums, left, right):
        if left > right:
            return
        mid = int((left + right) / 2)
        this_node = TreeNode(nums[mid])
        this_node.left = self.convert_to_bst(nums, left, mid - 1)
        this_node.right = self.convert_to_bst(nums, mid + 1, right)
        return this_node

    
