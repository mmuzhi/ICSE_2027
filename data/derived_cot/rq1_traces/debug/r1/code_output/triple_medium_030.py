# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def splitListToParts(self, head: Optional[ListNode], k: int) -> List[Optional[ListNode]]:
        parts = []
        length = 0
        ptr = head
        while ptr:
            length += 1
            ptr = ptr.next
        
        part_size = length // k
        remainder = length % k
        
        arrange = []
        for i in range(k):
            if remainder > 0:
                arrange.append(part_size + 1)
                remainder -= 1
            else:
                arrange.append(part_size)
        
        current = head
        part_index = 0
        count = 0
        prev = None
        while current and part_index < k:
            if count == 0:
                parts.append(current)
            
            count += 1
            prev = current
            current = current.next
            
            if count == arrange[part_index]:
                prev.next = None
                part_index += 1
                count = 0
        
        while len(parts) < k:
            parts.append(None)
        
        return parts