# Given a linked list, remove the nth node from the end of list and return its head.
# For example,
#   Given linked list: 1->2->3->4->5, and n = 2.
#    After removing the second node from the end, the linked list becomes 1->2->3->5.
# Note:
# Given n will always be valid.
# Try to do this in one pass.

# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution(object):
    def removeNthFromEnd(self, head, n):
        """
        :type head: ListNode
        :type n: int
        :rtype: ListNode
        """
        if head is None or n == 0:
            return None
        nodes = []
        start = head
        while start != None:
            nodes.append(start)
            start = start.next
        m = len(nodes)
        if m < n:
            return None
        if m == n:
            return head.next
        nodes[m - n - 1].next = nodes[m - n].next
        return head
