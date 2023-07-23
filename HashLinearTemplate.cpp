#include <stdio.h>
#include <string.h>
#define SIZE 20
#define LEN 40

char table[SIZE][LEN] = {NULL};

int hash(char name[]){
	int res = 0;
	for(int i = 0;i<strlen(name);i++){
		res += name[i];
	}
	
	return res%SIZE;
}

void push(char name[]){
	int key = hash(name);
	int ind = key;
	
	while(strlen(table[ind]) != 0){
		ind = (ind +1) % SIZE;
		if(ind == key){
			printf ("Table is full\n");
			ind = -1;
			break;
		}
	}
	
	if (ind != -1){
		strcpy(table[ind],name);
	}
}

void pop(char name[]){
	int key = hash(name);
	int ind = key;
	
	while(strcmp (table[ind],name) != 0){
		ind = (ind +1) % SIZE;
		if(ind == key){
			printf ("Name not Found\n");
			ind = -1;
			break;
		}
	}
	
	if (ind != -1){
		table[ind][0] = '\0';
	}
}

void search(char name[]){
	int key = hash(name);
	int ind = key;
	
	while(strcmp (table[ind],name) != 0){
		ind = (ind +1) % SIZE;
		if(ind == key){
			printf ("Name not Found\n");
			ind = -1;
			break;
		}
	}
	
	if (ind != -1){
		printf ("Name found at index %d\n",ind);
	}
}

void display(){
	for (int i = 0;i<SIZE;i++){
		printf ("%d => %s\n", i,table[i]);
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
	search("BAC");
	search("ABC");
	
	return 0;
}

