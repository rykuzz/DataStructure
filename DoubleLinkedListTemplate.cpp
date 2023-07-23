#include <stdio.h>
#include <stdlib.h>

struct data{
	int val;
	struct data *next,*prev;
};

struct data *head = NULL;
struct data *tail = NULL;
struct data *node = NULL;
struct data *curr = NULL;

struct data *newNode(int val){
	node = (struct data*) malloc (sizeof(data));
	node->val = val;
	node->next = NULL;
	node->prev = NULL;
	
	return node;
}

void pushHead (int val){
	node = newNode(val);
	
	if (head == NULL){
		head = node;
		tail = node;
	}else{
		node->next = head;
		head->prev = node;
		head = node;
	}
}

void pushTail(int val){
	node = newNode(val);
	
	if (head == NULL){
		head = node;
		tail = node;
	}else{
		node->prev = tail;
		tail->next = node;
		tail = node;
	}
}

//Insert in ascending order
void push(int val){
	if (head == NULL || val < head->val){
		pushHead(val);
	}else if(val > tail->val){
		pushTail(val);
	}else{
		node = newNode(val);
		curr = head;

		while ((curr->val < node->val) && (curr->next != NULL)){
			curr = curr->next;
		}
		
		node->next = curr;
		node->prev = curr->prev;
		curr->prev->next = node;
		curr->prev = node;
	}
}

void popHead(){
	if (head == NULL){
		printf ("No data\n");
		return;
	}else{
		if (head == tail){
			head = tail = NULL;
			free(head);
		}else{
			curr = head;
			head = curr->next;
			head->prev = NULL;
			free(curr);
		}
	}
}

void popTail(){
	if (head == NULL){
		printf ("No data\n");
		return;
	}else{
		if (head == tail){
			head = tail = NULL;
			free(head);
		}else{
			curr = tail;
			tail = curr->prev;
			tail->next = NULL;
			free(curr);
		}
	}
}

void pop(int val){
	if (head == NULL){
		printf ("No data\n");
		return;
	}else{
		curr = head;
		while(curr != NULL && curr->val != val){
			curr = curr->next;
		}
		
		if (curr == NULL){
			printf ("Not found\n");
			return;
		}
		
		if(curr == head){
			popHead();
			return;
		}else if (curr== tail){
			popTail();
			return;
		}else{
			curr->prev->next = curr->next;
			curr->next->prev = curr->prev;
			free(curr);
		}
	}
}

void display(){
	if(head == NULL){
		printf ("No data\n");
		return;
	}
	curr = head;
	while (curr != NULL){
		printf ("%d => ", curr->val);
		curr = curr->next;
	}
	printf ("\n");
}

int main(){
	
	display();
	push(5);
	push(10);
	push(7);
	push(3);
	push(15);
	display();
	
	pop(7);
	display();
	pop(10);
	pop(5);
	pop(10);
	pop(7);
	pop(3);
	pop(15);
	display();
	
	return 0;
}

