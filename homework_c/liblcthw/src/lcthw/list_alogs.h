#ifndef lcthw_List_alogs_h
#define lcthw_List_alogs_h

#include<lcthw/list.h>
typedef int (*List_compare)(const void *a,const void *b);

int List_bubble_sort(List *words, List_compare cmp);

void ListNode_swap(ListNode *a, ListNode *b);

List *List_merge(List *left, List *right, List_compare cmp);

List *List_merge_sort_down(List *list, List_compare cmp);

List *List_merge_sort_up(List *list,List_compare cmp);

void List_split(List *list,List *left,List *right,int count);

List *List_join(List *left,List *right, List_compare cmp);

void List_insert_sorted(List *list, void *value, List_compare cmp);

void List_insert(List *list, ListNode *cur, ListNode *new_node);

ListNode *ListNode_create(void *value);

#endif

