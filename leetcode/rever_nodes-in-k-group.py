# Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.
# If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.
# You may not alter the values in the nodes, only nodes itself may be changed.
# Only constant memory is allowed.
# For example,
# Given this linked list: 1->2->3->4->5
# For k = 2, you should return: 2->1->4->3->5
# For k = 3, you should return: 3->2->1->4->5

# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution(object):
    def reverseKGroup(self, head, k):
        """
        :type head: ListNode
        :type k: int
        :rtype: ListNode
        """
        if k <= 1:
            return head
        nodes = []
        curr = head
        while curr != None:
            nodes.append(curr)
            curr = curr.next
        if len(nodes) < k:
            return head
        count = 0
        new_head = ListNode(0)
        new_curr = new_head
        while len(nodes) - count >= k:
            for i in reversed(range(k)):
                new_curr.next = nodes[count + i]
                new_curr = new_curr.next
            count += k
        if count < len(nodes):
            new_curr.next = nodes[count]
        else:
            new_curr.next = None
        return new_head.next
                
        
