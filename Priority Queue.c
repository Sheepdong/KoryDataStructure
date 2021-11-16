#include <stdio.h>
#define MAX_ELEMENTS 200
#define HEAP_FULL(n) (n == MAX_ELEMENTS-1)
#define HEAP_EMPTY(n) (!n)

typedef struct {
	int key;
	/* other fields*/
}element;

element heap[MAX_ELEMENTS];
int n = 0;

void push(element item, int* n) {
	/*element e;
	e.key = 14;
	no = 5;
	push(e,&no) 를 하면 */
	int i = 0;
	if (HEAP_FULL(*n)) {
		fprintf(stderr, "The heap is full. ");
		exit(EXIT_FAILURE);
	}
	i = ++(*n); /*no = 6*/
	while ((i != 1) && (item.key > heap[i / 2].key)) {
		heap[i] = heap[i / 2];
		i /= 2; /*i = 3*/
	}
	heap[i] = item;
}

element pop(int* n) {
	/*int no = 5;
	element e = pop(&no);*/
	int parent, child;
	element item, temp;
	if (HEAP_EMPTY(*n)){
		frpintf(stderr, "The heap is empty");
		exit(EXIT_FAILURE);	
	}
	item = heap[1];
	temp = heap[(*n)--];
	/* no = 4*/
	parent = 1;
	child = 2;
	while (child <= *n) /* child가 존재하는 동안*/ {
		if ((child < *n)/*child가 2개?*/ && heap[child].key < heap[child + 1].key) 
			/*leftchild rightchild 비교*/
			child++; /*child = 3*/
		if (temp.key >= heap[child].key) break;
		heap[parent] = heap[child];
		parent = child; /*parent = 3*/
		child *= 2; /*child = 6*/
	}
	heap[parent] = temp;
	return item;

}

