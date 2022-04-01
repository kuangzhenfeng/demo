#include <bits/stdc++.h>


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
 
class Solution {
public:
    ListNode* deleteNode(ListNode* head, int val) {
        ListNode *lastP = head;
        for(ListNode *p = head; p != NULL; p = p->next)
        {
            if(p == head)
            {
                if(p->val == val)
                {
                    head = head->next;
                }
                lastP = p->next;
                continue;
            }
            if(p->val == val)
            {
                lastP->next = p->next;
            }
            lastP = p;
        }
    }
};