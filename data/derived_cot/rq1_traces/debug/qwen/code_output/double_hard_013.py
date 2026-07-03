class Solution:
    def reverseKGroup(self, head: Optional[ListNode], k: int) -> Optional[ListNode]:
        if not head or k == 1:
            return head
        
        def getKth(node, k):
            while node and k:
                node = node.next
                k -= 1
            return node
        
        dummy = ListNode(0, head)
        prev = dummy
        
        while True:
            curr = prev.next
            kth = getKth(curr, k)
            if not kth:
                break
            nextGroup = kth.next
            
            prev_node = None
            curr_node = curr
            for _ in range(k):
                tmp = curr_node.next
                curr_node.next = prev_node
                prev_node = curr_node
                curr_node = tmp
            
            prev.next = prev_node
            prev = kth
        
        return dummy.next