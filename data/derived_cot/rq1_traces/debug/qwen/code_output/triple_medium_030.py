# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def splitListToParts(self, head: Optional[ListNode], k: int) -> List[Optional[ListNode]]:
        # Calculate the length of the linked list
        cur = head
        length = 0
        while cur:
            length += 1
            cur = cur.next
        
        # Calculate base and remainder
        base = length // k
        rem = length % k
        sizes = [base + 1] * rem + [base] * (k - rem)
        
        # If the list is empty, return k times None
        if head is None:
            return [None] * k
        
        parts = []
        current = head
        for size in sizes:
            if size == 0:
                parts.append(None)
                continue
            part_head = current
            # Move current to the last node of the part (size-1 steps)
            for _ in range(size - 1):
                if current is None:
                    break
                current = current.next
            # Cut the list at the last node
            if current:
                current.next = None
            parts.append(part_head)
            # Move to the next part's head
            if current is not None:
                current = current.next
            else:
                current = None
        
        return parts