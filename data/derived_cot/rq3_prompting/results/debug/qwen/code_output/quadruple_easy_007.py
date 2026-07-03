class Solution:
    def hasCycle(self, head: Optional[ListNode]) -> bool:
        a = b = head
        while b and b.next:
            a = a.next
            b = b.next.next
            if a == b:
                return True
        return False