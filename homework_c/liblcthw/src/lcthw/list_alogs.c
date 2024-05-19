#include<lcthw/list_alogs.h>
#include<lcthw/dbg.h>

void ListNode_swap(ListNode *a, ListNode *b)
{
	void *temp = a->value;
	a->value = b->value;
	b->value = temp;
}

int List_bubble_sort(List *list, List_compare cmp)
{
	int sorted = 1;

	if(List_count(list) <= 1)
	{
		return 0;
	}

	do
	{
		sorted = 1;
		LIST_FOREACH(list, first, next, cur)
		{
			if(cur->next)
			{
				if(cmp(cur->value, cur->next->value) > 0)
				{
					ListNode_swap(cur, cur->next);
					sorted = 0;
				}
			}
		}
	} while(!sorted);

	return 0;
}

List *List_merge(List *left, List *right, List_compare cmp)
{
	List *result = List_create();
	void *val = NULL;

	while(List_count(left) > 0 || List_count(right) > 0)
	{
		if(List_count(left) > 0 && List_count(right) > 0)
		{
			if(cmp(List_first(left), List_first(right)) <= 0)
			{
				val = List_shift(left);
			}
			else
			{
				val = List_shift(right);
			}

			List_push(result, val);
		}
		else if(List_count(left) > 0)
		{
			val = List_shift(left);
			List_push(result, val);
		}
		else if(List_count(right) > 0)
		{
			val = List_shift(right);
			List_push(result, val);
		}
	}

	return result;
}

void List_split(List *list, List *left, List *right,int middle)
{

	LIST_FOREACH(list, first, next, cur)
	{
		if(middle > 0)
		{
			List_push(left, cur->value);
		}
		else
		{
			List_push(right, cur->value);
		}

		middle--;
	}
}

ListNode *ListNode_create(void *value)
{
	ListNode *_node = malloc(sizeof(ListNode));

	_node->value = value;

	return _node;
}

List *List_join(List *left,List *right, List_compare cmp)
{
	return List_merge(left, right, cmp);
}

void List_insert_sorted(List *list, void *value, List_compare cmp)
{
	ListNode *new_node = ListNode_create(value);

	LIST_FOREACH(list,first,next,cur)
	{
		if(cmp(value, cur->value) < 0)
		{
			List_insert(list, cur, new_node);
			return;
		}
	}

	List_push(list, value);
}

void List_insert(List *list,ListNode *cur, ListNode *new_node)
{
	if(!cur)
	{
		List_unshift(list, new_node->value);
	}
	else if(cur == list->first)
	{
		List_push(list,new_node->value);
	}
	else
	{
		new_node->next = cur;
		new_node->prev = cur->prev;
		cur->prev->next = new_node;
		cur->prev = new_node;
		list->count++;
	}
}

List *List_merge_sort_down(List *list, List_compare cmp)
{
	if(List_count(list) <= 1)
	{
		return list;
	}

	List *left = List_create();
	List *right = List_create();

	int middle = List_count(list) / 2;
	
	List_split(list, left, right,middle);

	List *sort_left = List_merge_sort_down(left, cmp);
	List *sort_right = List_merge_sort_down(right, cmp);

	if(sort_left != left) List_destroy(left);
	if(sort_right != right) List_destroy(right);

	return List_join(sort_left, sort_right, cmp);
}

List *List_merge_sort_up(List *list, List_compare cmp)
{
	int n = List_count(list);
	List *sorted = List_create();

	for(int curr_size = 1; curr_size < n; curr_size *= 2)
	{
		for(int left_start = 0; left_start < n - 1; left_start += 2 * curr_size)
		{
			int middle = left_start + curr_size - 1;
			int right_end = (left_start + 2*curr_size - 1 < n-1) ? left_start + 2*curr_size - 1 : n-1;

			List *left = List_create();
			List *right = List_create();

			List_split(list, left, right, middle);

			List *sort_left = List_merge(left, right, cmp);
			List *sort_right = List_merge(right, left, cmp);

			if(sort_left != left) List_destroy(left);
			if(sort_right != right) List_destroy(right);

			List *merged = List_merge(sort_left,sort_right, cmp);

			List_join(sorted, merged, cmp);
		}
	}

	return sorted;
}

