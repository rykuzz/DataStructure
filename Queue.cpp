#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct order{
	char name[100];
	int rank;
	struct order *next;
	struct order *prev;
};

struct order *head = NULL;
struct order *tail = NULL;

struct order *createNode(char name[], int rank){
	struct order *node = (struct order*) malloc (sizeof(struct order));
	strcpy (node->name,name);
	node->rank = rank;
	node->next = NULL;
	node->prev = NULL;
	return node;
}

void pushHead (char name[], int rank){
	struct order *node = createNode(name,rank);
	if(head == NULL){
		head = tail = node;
	}else{
		head->prev = node;
		node->next = head;
		head = node;
	}
}

void pushTail(char name[], int rank){
	if(head == NULL){
		pushHead(name,rank);
	}else{
		struct order *node = createNode(name,rank);
		tail->next = node;
		node->prev = tail;
		tail = node;
	}
}

void pushMid(char name[], int rank){
	if(head == NULL){
		pushHead(name,rank);
	}else if (rank > head->rank){
		pushHead(name,rank);
	}else if (tail->rank > rank){
		pushTail(name,rank);
	}else{
		struct order *node = createNode(name,rank);
		struct order *curr = head;
		while (curr->rank > node->rank && curr->next != NULL){
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
		printf ("No data!\n\n");
		return;
	}else{
		struct order *node = head;
		if (head == tail){
			head = tail = NULL;
			free(node);
		}else{
			head = node->next;
			head->prev = NULL;
			free(node);
		}
	}
}

void popTail(){
	if (head == NULL){
		printf ("No data!\n\n");
		return;
	}else{
		struct order *node = tail;
		if (head == tail){
			popHead();
		}else{
			tail = node->prev;
			tail->next = NULL;
			free(node);
		}
	}
}

void popMid(char name[]){
	if (head == NULL){
		printf ("No data!\n\n");
		return;
	}else{
		struct order *node = head;
		while (node != NULL && strcmp(name,node->name) != 0){
			node = node->next;
		}
		if (node == NULL){
			printf ("Data not found\n\n");
			return;
		}
		if(node == head){
			popHead();
			return;
		}else if (node == tail){
			popTail();
			return;
		}else{
			node->prev->next = node->next;
			node->next->prev = node->prev;
			free(node);
		}
	}
}

int search(char name[]){
	if (head == NULL){
		printf ("No data!\n");
		return -1;
	}else{
		struct order *node = head;
		int ind = 0;
		while (node != NULL && strcmpi(name,node->name) != 0){
			node = node->next;
			ind++;
		}
		if (node == NULL){
			printf ("Data not found\n");
			return -1;
		}else{
			return ind + 1;
		}
		
	}
}

void display(){
	if (head == NULL){
		printf ("No data!\n\n");
		return;
	}
	struct order *curr = head;
	while(curr != NULL){
		if (curr == head && curr == tail ){
			printf ("%s - %d (h) (t)\n",curr->name, curr->rank);
		}else if (curr == head){
			printf ("%s - %d (h)\n",curr->name, curr->rank);
		}else if (curr == tail){
			printf ("%s - %d (t)\n",curr->name, curr->rank);
		}else{
			printf ("%s - %d\n",curr->name, curr->rank);
		}
		curr = curr->next;
	}
	printf ("\n");
}

void testing(){
	//Test pushHead
//	display();
//	pushHead("Troy",5);
//	display();
//	pushHead("Alec",5);
//	display();
//	pushHead("Magnus",5);
//	display();
	
	//Test pushTail
//	pushTail ("Jace", 10);
//	pushTail ("Simon",15);
//	display();
	
	//Test pushMid
//	pushMid ("Clary",3);
//	display();
//	pushMid ("Jace",5);
//	display();
//	pushMid ("Izzy",4);
//	display();
//	pushMid ("Simon",3);
//	display();
//	popHead();
//	display();
//	popHead();
//	display();
//	popHead();
//	display();
//	popHead();
//	display();

//	pushMid ("Clary",3);
//	display();
//	pushMid ("Jace",5);
//	display();
//	pushMid ("Izzy",4);
//	display();
//	pushMid ("Simon",3);
//	display();
//	popTail();
//	display();
//	popTail();
//	display();
//	popTail();
//	display();
//	popTail();
//	display();

//	pushMid ("Clary",3);
//	display();
//	pushMid ("Jace",5);
//	display();
//	pushMid ("Izzy",4);
//	display();
//	pushMid ("Simon",3);
//	display();
//	popMid("Jace");
//	display();
//	popMid("Simon");
//	display();
//	popMid("Siton");
//	display();
//	popMid("Clary");
//	display();
//	popMid("Izzy");
//	display();
//	popMid("Simon");
//	display();

	pushMid ("Clary",3);
	display();
	pushMid ("Jace",5);
	display();
	pushMid ("Izzy",4);
	display();
	pushMid ("Simon",3);
	display();
	printf ("%d\n",search("Simon"));
	printf ("%d\n",search("Siton"));
	printf ("%d\n",search("izzy"));
	popMid("Jace");
	popMid("Simon");
	popMid("Clary");
	popMid("Izzy");
	display();
	printf ("%d\n",search("izzy"));
}

void seeding(){
	pushMid ("Clary",3);
	pushMid ("Jace",5);
	pushMid ("Izzy",4);
	pushMid ("Simon",3);
}

int main(){
	seeding();
	int menu = 0;
//	while(true){
//		display();
//		puts("1. New Order");
//		puts("2. Serve Order");
//		puts("3. Search Order");
//		puts ("4. Quit")
//	}
//	
	return 0;
}

