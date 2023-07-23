

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct data{
	char name[50];
	char con[30];
	int rank;
	struct data *next,*prev;
};

struct data *head = NULL;
struct data *tail = NULL;
struct data *node = NULL;
struct data *current = NULL;

struct data *newNode(char name[],char con[]){
	node = (struct data*) malloc (sizeof(data));
	strcpy(node->name, name);
	strcpy(node->con, con);
	if (strcmp(con,"Critical") == 0){
		node->rank = 1;
	}else if (strcmp(con,"Serious") == 0){
		node->rank = 2;
	}else if (strcmp(con,"Fair") == 0){
		node->rank = 3;
	}else{
		node->rank = 4;
	}
	node->next = NULL;
	node->prev = NULL;
	
	return node;
}

void push(char name[],char con[]){
	node = newNode(name,con);
	
	if(head == NULL ){
		head = node;
		tail = node;
	}else if(node->rank < head->rank){
		node->next = head;
		head->prev = node;
		head = node;
	}else if(node->rank >= tail->rank){
		node->prev = tail;
		tail->next = node;
		tail = node;
	}else{
		current = head;

		while ((current->rank <= node->rank) && (current->next != NULL)){
			current = current->next;
		}
		
		node->next = current;
		node->prev = current->prev;
		current->prev->next = node;
		current->prev = node;
	}
}

void move(char name[],int rank){
	if (rank == 1){
		printf ("%s is in the Emergency Room\n", name);
	}else if (rank == 2){
		printf ("%s is in the Examination Room\n", name);
	}else{
		printf ("%s is in the Consultation Room\n", name);
	}
}

void pop(){
	if (head == NULL){
		printf ("No Patient to Call\n");
		return;
	}else{
		if (head == tail){
			move(head->name,head->rank);
			head = tail = NULL;
			free(head);
		}else{
			move(head->name,head->rank);
			current = head;
			head = current->next;
			head->prev = NULL;
			free(current);
		}
	}
}

void display(){
	if(head == NULL){
		printf ("None\n");
		return;
	}
	current = head;
	while (current != NULL){
		if (current->next != NULL){
			printf ("%s, ",current->name);
		}else{
			printf ("%s",current->name);
		}
		current = current->next;
	}
	printf ("\n");
}

int main(){
	
	int n;
	scanf ("%d",&n);
	getchar();
	char event[10];
	char name[50];
	char con[30];
	
	for (int i = 0;i<n;i++){
		scanf ("%s",event);
		if (strcmp(event,"ADD") == 0){
			scanf ("%s %s",name,con);
			getchar();
			push(name,con); 
		}else if (strcmp(event,"CALL") == 0){
			getchar();
			pop();
		}
	}
	printf ("Waiting Room: ");
	display();
	
	return 0;
}
/*
9
ADD Roddy Good
ADD Celine Fair
ADD Berry Good
CALL
ADD Ronny Critical
ADD Belany Serious
CALL
CALL
CALL


6
ADD Roddy Good
ADD Celine Fair
ADD Ronny Critical
ADD Belany Serious
CALL
CALL 

8
ADD Roddy Good
ADD Celine Fair
CALL
ADD Ronny Critical
ADD Belany Serious
CALL
CALL
CALL

8
ADD Celine Fair
ADD Ronny Fair
ADD Roddy Good
ADD Berry Good
CALL
CALL
CALL
CALL
*/

