# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def splitListToParts(self, head: Optional[ListNode], k: int) -> List[Optional[ListNode]]:

        # Calculate the length of the linked list
        length = 0
        ptr = head
        while ptr:
            length += 1
            ptr = ptr.next

        # Calculate the base length and remainder
        maxi = length // k
        remain = length % k
        
        # Build the arrangement of part lengths
        arrange = []
        for i in range(k):
            if i < remain:
                arrange.append(maxi + 1)
            else:
                arrange.append(maxi)
        
        # Initialize the result list and pointers
        l = []
        ptr = head
        j = 0
        i = 0
        
        while ptr and j < k:
            part_length = arrange[j]
            if part_length == 0:
                j += 1
                continue
            
            q = ptr
            ptr = ptr.next
            i += 1
            if i == part_length:
                q.next = None
                l.append(head)
                head = ptr
                i = 0
                j += 1
        
        # Append None for any remaining parts
        for _ in range(j, k):
            l.append(None)
        
        return l