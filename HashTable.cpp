#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 10 //size hash table

struct data{
	char name[50];
	int age;
	struct data *next; //chaining
};

struct data *table[SIZE] = {NULL};

struct data *createNode(char name[],int age){
	struct data *node = (struct data*)malloc(sizeof(struct data));
	strcpy(node->name,name);
	node->age = age;
	node->next = NULL;
	
	return node;
}

int hash(char name[]){
	int ascii = 0;
	for (int i = 0;i<strlen(name);i++){
		ascii += name[i];
	}
//	printf ("%d\n",ascii);
	return ascii%SIZE;
}

void push(char name[],int age){
	struct data *node = createNode(name,age);
	
	//tentuin hash key
	int key = hash(name);
	
	if (table[key] == NULL){
		//Index masih kosong
		table[key] = node;
	}else{
		//Ud ad data dlm index ->collision
		struct data *curr = table[key];
		while (curr->next != NULL){
			curr =  curr->next;
		}
		curr->next = node;
	}
	
}

void display(){
	for (int i = 0;i<SIZE;i++){
		printf ("%d. ",i);//print index
		
		//looping isi dari index ke-i
		struct data *curr = table[i];
		while (curr != NULL){
			printf("(%s,%d)->",curr->name,curr->age);
			curr=curr->next;
		}
		printf ("NULL\n");
	}
}

void search(char name[]){
	int key = hash(name);
	
	if (table[key] == NULL){
		// ga ad isinya
		printf ("%s Not Found!\n",name);
		return;
	}else{
		struct data *curr = table[key];
		while (curr != NULL && strcmp (curr->name,name) != 0){
			curr = curr->next;
		}
		if (curr == NULL){
			printf ("%s Not Found!\n",name);
		}else{
			printf ("Found in index %d\n",key);
		}
	}
}

void pop(char name[]){
	int key = hash(name);
	
	if (table[key] == NULL){
		// ga ad isinya
		printf ("%s Not Found!\n",name);
		return;
	}
	
	struct data *curr = table[key];
	
	if (curr->next == NULL && strcmp (curr->name,name) == 0){
		//kalo cmn 1 data aj	
		table[key] = NULL;
		free(curr);
	}else{
		//jumlah data > 1
		if (strcmp(curr->name,name) == 0){
			table[key] = curr->next;
			free(curr);
			return;
		}
		while (curr->next != NULL && strcmp (curr->next->name,name) != 0){
			curr = curr->next;
		}	
		
		if (curr->next == NULL && strcmp (curr->name,name) != 0){
			printf ("%s Not Found!\n",name);
			return;
		}else{
			struct data *temp = curr->next;
			curr->next = temp->next;
			free(temp);
		}
	}
}

int main(){
	push("ABC",20);
	push ("BCA",15);
	push("Stuckony",40);
	push ("Apercy",30);
	push ("Malec",25);
	push("BAC",56);
	display();
	
	search("Malec");
	search ("CBA");
	search ("EDB");
	
	pop("BCA");
	pop ("XYZ");
	pop ("Malec");
	display();
	
	return 0;
}

