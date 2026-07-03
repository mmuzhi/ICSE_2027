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
        
        # Calculate the base size and remaining nodes
        maxi = length // k
        remain = length % k
        
        # Create a list to store the size of each part
        arrange = []
        for i in range(k):
            if i < remain:
                arrange.append(maxi + 1)
            else:
                arrange.append(maxi)
        
        # Split the linked list into k parts
        parts = []
        current = head
        for size in arrange:
            parts.append(current)
            if size == 0:
                continue
            for _ in range(size - 1):
                current = current.next
            if current:
                temp = current.next
                current.next = None
                current = temp
        
        return parts