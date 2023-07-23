#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 20


struct data{
	char name[40];
	struct data *next;
};

struct data *table[SIZE] = {NULL};
struct data *curr = NULL;
struct data *node = NULL;

struct data *newNode(char name[]){
	node = (struct data*) malloc (sizeof(data));
	strcpy(node->name,name);
	node->next = NULL;
	return node;
}

int hash(char name[]){
	int res = 0;
	for(int i = 0;i<strlen(name);i++){
		res += name[i];
	}
	
	return res%SIZE;
}

void push(char name[]){
	node = newNode (name);
	int key = hash(name);
	
	if(table[key] == NULL){
		table[key] = node;
	}else{
		curr = table[key];
		while(curr->next != NULL){
			curr = curr->next;
		}
		curr->next = node;
	}
}

void pop(char name[]){
	int key = hash(name);
	
	if(table[key] == NULL){
		printf ("Name not found\n");
		return;
	}
	
	curr = table[key];
	
	if (curr->next == NULL && strcmp (curr->name, name) == 0){
		table[key] = NULL;
		free(curr);
	}else{
		if(strcmp(curr->name,name) == 0){
			table[key] = curr->next;
			free(curr);
			return;
		}
		
		while(curr->next != NULL && strcmp(curr->next->name,name) != 0){
			curr=curr->next;
		}
		
		if (curr->next == NULL && strcmp(curr->name,name) != 0){
			printf ("Name not found!\n");
			return;
		}else{
			node = curr->next;
			curr->next = node->next;
			free(node);
		}
	}
}

void search(char name[]){
	int key = hash(name);
	
	if (table[key] == NULL){
		printf ("Name not found\n");
		return;
	}else{
		curr = table[key];
		while (curr != NULL && strcmp(curr->name,name) != 0){
			curr = curr->next;
		}
		
		if (curr == NULL){
			printf ("Name not found\n");
		}else{
			printf ("Name found at index %d\n",key);
		}
	}
}

void display(){
	for (int i = 0; i<SIZE;i++){
		printf ("%d. ",i);
		
		curr = table[i];
		while(curr != NULL){
			printf ("%s => ",curr->name);
			curr = curr->next;
		}
		
		printf ("NULL\n");
	}
}

int main(){
	
	push("ABC");
	push("BAC");
	push("CBA");
	push("PLAY");
	display();
	printf ("\n\n");
	
	pop("ABC");
	pop("CBS");
	display();
	printf ("\n\n");
	
	push ("BCA");
	display();
	printf ("\n\n");
	
	pop("BCA");
	display();
	printf ("\n\n");
	
	push("ACB");
	display();
	printf ("\n\n");
	
	pop("CBA");
	display();
	printf ("\n\n");
	
	search("BAC");
	search("ABC");
	
	return 0;
}

