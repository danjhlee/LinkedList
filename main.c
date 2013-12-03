#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE	5

/*
 * Data Structure of Linked List
 */
typedef struct list 
{
	int value;
	struct list *next;
} list;


void list_insert(int value, list *start);
void list_delete(int value, list *start);
void list_print(list *start);

/*
 * Creating a sorted Linked List
 */
void list_insert(int value, list *start)
{
	list *previous, *node, *new_node;
	

	previous = start;
	node = start->next;

	while (node != NULL && node->value < value) {
		previous = node;
		node = node->next;
	}
	new_node = (list *)calloc(1, sizeof(list));
	new_node->value = value;
	new_node->next = node;
	previous->next = new_node;
}

/*
 * Removing a node from the Linked List
 */
void list_delete(int value, list *start)
{
	list *previous, *node;
	
	previous = start;
	node = start->next;

	while (node != NULL && node->value != value) {
		previous = node;
		node = node->next;
	}	
	if (node) {
		previous->next = node->next;
		free(node);
	}
}

/*
 * Printing items of the Linked List
 */
void list_print(list *start)
{
	list *node;

	for (node=start->next; node; node=node->next) {
		printf("%d->", node->value);
	}
	printf("\n");
}

/*
 * Freeing Linked List
 */
void list_free(list *start)
{
	list *node, *next;

	for (node=start; node; node=next) {
		next = node->next;
		free(node);
	}
}

/*
 * Finding median node in the Linked List
 */
list *list_median(list *start)
{
	list *node, *fast;
	
	node = fast = start->next;

	while (fast != NULL && fast->next != NULL) {
		node = node->next;
		fast = fast->next->next;
	}
	return node;
}
	

/*
 * Reversing the Linked List
 */
list *list_reverse(list *start)
{
	list *previous, *current, *next;
	list *reverse;

	previous = NULL;
	current = start;

	while (current != NULL) {
		next = current->next;
		current->next = previous;
		previous = current;
		current = next;
	}
	reverse = (list *)calloc(1, sizeof(list));
	reverse->next = previous;

	return reverse;
}

/*
 * Merging two Linked Lists
 */
list *mergeLinkedList(list *a, list *b)
{
	list *merge;

	if (a == NULL)
		return b;
	if (b == NULL)
		return a;

	if (a->value < b->value) {
		merge = a;
		merge->next = mergeLinkedList(a->next, b);
	} else {
		merge = b;
		merge->next = mergeLinkedList(a, b->next);
	}
	return merge;
}


int main()
{
	list *start, *reverse, *median;
	int value[ARRAY_SIZE] = {1, 5, 2, 4, 3};
	int value_a[ARRAY_SIZE] = {3, 7, 2, 8, 5};
	int value_b[ARRAY_SIZE] = {10, 6, 4, 9, 1};
	list *list_a, *list_b, *merge;
	int i;

	start = (list *)calloc(1, sizeof(list));
	for (i=0; i<ARRAY_SIZE; i++) {
		list_insert(value[i], start);
	}
	printf("print LinkedList: ");
	list_print(start);	

	median = list_median(start);
	printf("The value of median node is %d\n", median->value);	

	reverse = list_reverse(start);
	printf("reversed LinkedList: ");
	list_print(reverse);

	printf("removing LinkedList items\n");
	for (i=0; i<ARRAY_SIZE; i++) {
		printf("removing %d from the LinkedList\n", value[i]);
		list_delete(value[i], reverse);
		list_print(reverse);
	}
	list_free(reverse);

	
	list_a = (list *)calloc(1, sizeof(list));
	for (i=0; i<ARRAY_SIZE; i++) {
		list_insert(value_a[i], list_a);
	}
	printf("print LinkedList a\n");
	list_print(list_a);

	list_b = (list *)calloc(1, sizeof(list));
	for (i=0; i<ARRAY_SIZE; i++) {
		list_insert(value_b[i], list_b);
	}
	printf("print LinkedList b\n");
	list_print(list_b);

	merge = mergeLinkedList(list_a, list_b);
	printf("print merged LinkedList a and LinkedList b\n");
	list_print(merge->next);

	return 0;
}
