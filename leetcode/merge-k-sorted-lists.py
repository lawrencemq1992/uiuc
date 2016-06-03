# Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.

# using heap queue(priority queue)
# O(Total of the node)

# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution(object):
    def mergeKLists(self, lists):
        """
        :type lists: List[ListNode]
        :rtype: ListNode
        """
        heap_node = []
        for node in lists:
            if node:
                heap_node.append((node.val, node))
        heapq.heapify(heap_node)
        head = ListNode(0)
        curr = head
        while heap_node:
            pop_tuple = heapq.heappop(heap_node)
            curr.next = ListNode(pop_tuple[0])
            curr = curr.next
            if pop_tuple[1].next:
                heapq.heappush(heap_node, (pop_tuple[1].next.val, pop_tuple[1].next))
        return head.next
        
            
