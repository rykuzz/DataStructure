#include <stdio.h>
#include <stdlib.h>

struct data{
	int val;
	struct data *next;
};

struct data *head = NULL;
struct data *tail = NULL;
struct data *curr = NULL;
struct data *node = NULL;

struct data *newNode(int val){
	node = (struct data*) malloc (sizeof(data));
	node->val = val;
	node->next = NULL;
	
	return node;
};

void pushHead(int val){
	node = newNode(val);
	if (head == NULL){
		head = node;
		tail = node;
	}else{
		node->next = head;
		head = node;
	}
}

void pushTail(int val){
	node = newNode(val);
	if (head == NULL){
		head = node;
		tail = node;
	}else{
		tail->next = node;
		tail = node;
	}
}

void push(int val){
	if (head == NULL || val < head->val){
		pushHead(val);
	}else if(val > tail->val){
		pushTail(val);
	}else{
		node = newNode(val);
		curr = head;

		while ((curr->next->val < val) && (curr->next != NULL)){
			curr = curr->next;
		}
		
		node->next = curr->next;
		curr->next = node;
	}
}

void popHead(){
	curr = head;
	if (head == tail){
		head = tail = NULL;
		free(curr);
	}else{
		head = curr->next;
		free(curr);
	}
}

void popTail(){
	curr = head;
	if (head == tail){
		head = tail = NULL;
		free(curr);
	}else{
		while (curr->next != tail){
			curr = curr->next;
		}
		curr->next = NULL;
		free(tail);
		tail = curr;
	}
	
}

void pop (int val){
	if (head == NULL){
		printf ("No data\n");
		return;
	}
	
	if (head->val == val){
		popHead();
	}else{
		curr = head;
		while(curr->next != NULL && curr->next->val != val){
			curr = curr->next;
		}
		
		if (curr == tail && curr->val != val){
			printf ("Value not found!\n");
			return;
		}
		
		if (curr->next == tail){
			curr->next = NULL;
			free(tail);
			tail = curr;
		}else{
			node = curr->next;
			curr->next = node->next;
			free(node);
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
	
//	popHead();
//	display();
	
//	popTail();
//	display();
	
	pop(15);
	display();
	pop(3);
	pop(5);
	pop(12);
	pop(10);
	pop(7);
	pop(3);
	pop(15);
	display();
	
	return 0;
}

