
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100

void clrscr(){
    system("@cls||clear");
}

struct book{
	char id[10];
	char name[30];
	char genre[15];
	char auth[1000];
	char pub[30];
	long long int price;
	struct book *next;
};

char alpha[]={"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
char num[]={"0123456789"};
struct book *h[SIZE] = {NULL};

struct book *newNode(){
	srand(time(NULL));
	struct book *node = (struct book*)malloc(sizeof(struct book));
	for (int i = 0;i<=2;i++){
		int k = rand()%26;
		node->id[i] = alpha[k];
	}
	for (int i = 3;i<5;i++){
		int k = rand()%10;
		node->id[i] = num[k];
	}
	printf ("ID: %s\n",node->id);
	while(true){
		printf ("Input Book Name [5...20]: ");
		scanf ("%[^\n]",node->name);
		getchar();
		if (strlen(node->name)>4 && strlen(node->name)<21){
			break;
		}
	}
	
	while(true){
		printf ("Input Book Genre [Fantasy | Romance | Horror] (case sensitive): ");
		scanf ("%s",node->genre);
		getchar();
		if (strcmp (node->genre,"Romance") == 0 || strcmp (node->genre,"Fantasy") == 0 || strcmp (node->genre,"Horror") == 0){
			break;
		}
	}
	
	while(true){
		printf ("Input Book Author [minimum 1 character]: ");
		node->auth[0] = '\0';
		scanf ("%[^\n]",node->auth);
		getchar();
		if (strlen(node->auth) > 0){
			break;
		}
	}
	while(true){
		printf ("Input Book Publisher [3..10]: ");
		scanf ("%[^\n]",node->pub);
		getchar();
		if (strlen(node->pub)>=3 && strlen(node->pub)<=10){
			break;
		}
	}
	
	while(true){
		printf ("Input Book Price [cannot be zero]: ");
		scanf ("%lld",&node->price);
		getchar();
		if (node->price > 0){
			break;
		}
	}
	node->next = NULL;
	return node;
	
}

int hash(char id[]){
	int sum = 0;
	for (int i = 0;i<6;i++){
		sum += id[i];
	}
	return sum%SIZE;
}

void push(){
	struct book *node = newNode();
	int key = hash(node->id);
	
	if (h[key] == NULL){
		h[key] = node;
	}else{
		struct book *curr = h[key];
		while (curr->next != NULL){
			curr =  curr->next;
		}
		curr->next = node;
	}
	
	printf ("New book successfully inserted!\n");
}

int display(){
	long long int count = 0;
	int sign = 0;
	for (int i = 0;i<SIZE;i++){
		if (h[i] != NULL){
			sign = 1;
			break;
		}
	}
	if (sign == 0){
		printf ("List is Empty\n");
		return 0;
	}
	for (int i = 0;i<SIZE;i++){
		struct book *node = h[i];
		while (node!= NULL){
			count++;
			printf ("Book %d\n",count);
			printf ("ID: %s\n",node->id);
			printf ("Name: %s\n",node->name);
			printf ("Genre: %s\n",node->genre);
			printf ("Author: %s\n",node->auth);
			printf ("Price: %lld\n",node->price);
			printf ("=================\n");
			node=node->next;
		}
	}
	return 1;
}

void pop(){
	int sign = display();
	if (sign == 0){
		return;
	}
	printf ("\n");
	printf ("Enter Book ID to be deleted\n");
	printf ("ID: ");
	char id[10];
	scanf("%[^\n]",id);
	getchar();
	
	int key = hash(id);
	
	if (h[key] == NULL){
		printf ("Book not found\n");
		return;
	}
	
	struct book *node = h[key];
	
	if (node->next == NULL && strcmp (node->id,id) == 0){
		h[key] = NULL;
		free(node);
	}else{
		
		if (strcmp(node->id,id) == 0){
			h[key] = node->next;
			free(node);
			return;
		}
		
		while (node->next != NULL && strcmp (node->next->id,id) != 0){
			node = node->next;
		}	
		
		if (node->next == NULL && strcmp (node->id,id) != 0){
			printf ("Book not found\n");
			return;
		}else{
			struct book *temp = node->next;
			node->next = temp->next;
			free(temp);
		}
	}
	printf ("Book succesfully deleted\n");
}

int main(){
	int menu = 0;
	while (true){
		clrscr();
		printf ("Book Shop\n");
		printf ("=========\n");
		printf ("1. Add New Book\n");
		printf ("2. View Books\n");
		printf ("3. Delete Book\n");
		printf ("4. Exit\n");
		printf (">>");
		scanf ("%d",&menu);
		getchar();
		if (menu == 1){
			clrscr();
			push();
			getchar();
		}else if (menu == 2){
			clrscr();
			display();
			getchar();
		}else if (menu == 3){
			clrscr();
			pop();
			getchar();
		}else if (menu == 4){
			break;
		}
	}
	return 0;
}

