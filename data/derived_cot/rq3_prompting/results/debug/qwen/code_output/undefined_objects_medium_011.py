# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def splitListToParts(self, head: Optional[ListNode], k: int) -> List[Optional[ListNode]]:
        length = 0
        ptr = head
        while ptr:
            length += 1
            ptr = ptr.next
        
        base = length // k
        remainder = length % k
        arrange = [base + 1] * remainder + [base] * (k - remainder)
        
        parts = []
        if length == 0:
            return [None] * k
        
        current = head
        for i in range(k):
            if arrange[i] == 0:
                parts.append(None)
                continue
            
            part_head = current
            for _ in range(arrange[i] - 1):
                current = current.next
            
            next_node = current.next
            current.next = None
            parts.append(part_head)
            current = next_node
        
        return parts