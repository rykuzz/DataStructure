#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct node{
	int id;
	char name[100];
	struct node *left, *right;
	int height;
};

//utility function
int max (int a, int b){
	if (a>b){
		return a;
	}else{
		return b;
	}
}

int getHeight(struct node *n){
	if (n == NULL){
		return 0;
	}else{
		return n->height;
	}
}

int getBalance(struct node *n){
	if (n == NULL){
		return 0;
	}else {
		return getHeight(n->left) - getHeight(n->right);
	}
}

struct node *createNode(int id, char name[]){
	struct node *curr = (struct node*) malloc (sizeof(struct node));
	curr->id = id;
	strcpy(curr->name,name);
	curr->left = curr->right = NULL;
	curr->height = 1;
	return curr;
}

struct node *leftRotate (struct node *a){
	struct node *b = a->right;
	struct node *t1 = b->left;
	
	b->left = a;
	a->right = t1;
	
	a->height = 1 + max(getHeight(a->left),getHeight(a->right));
	b->height = 1 + max(getHeight(b->left),getHeight(b->right));
	
	return b;
}

struct node *rightRotate(struct node *a){
	struct node *b = a->left;
	struct node *t1 = b->right;
	
	b->right = a;
	a->left = t1;
	
	a->height = 1 + max(getHeight(a->left),getHeight(a->right));
	b->height = 1 + max(getHeight(b->left),getHeight(b->right));
	
	return b;
}

struct node *push(struct node *curr, int id, char name[]){
	//1. Insert BST biasa
	if (curr == NULL) return createNode(id,name);
	
	if(id < curr->id)
		curr->left = push(curr->left,id,name);
	else if (id > curr->id)
		curr->right = push(curr->right,id,name);
	else //if not unique, return
		return curr;
		
	//2. Update height
	curr->height = 1 + max(getHeight(curr->left),getHeight(curr->right));
	
	//3. Rotate (if needed)
	int bf = getBalance(curr); // bf = balance factor
	if (bf > 1){ //berat kiri
		if (id < curr->left->id){ //left left case
			//right rotate
			return rightRotate(curr);
		}else if(id > curr->left->id){ //left right case
			//left rotate
			curr->left = leftRotate (curr->left);
			//then right rotate
			return rightRotate(curr);
		}
	}else if(bf < -1){ // berat kanan
		if (id > curr->right->id){ //right right case
			//left rotate
			return leftRotate(curr);
		}else if(id < curr->right->id){ //right left case
			//right rotate
			curr->right = rightRotate(curr->right);
			//then left rotate
			return leftRotate(curr);
		}
	}else{
		return curr;
	}
	
}

void search(struct node *curr, int id){
	if (curr == NULL){
		printf ("Not Found\n");
		return;
	}

	if(id < curr->id)
		search (curr->left,id);
	else if (id > curr->id)
		search(curr->right,id);
	else //if found
		printf("Student name: %s\n", curr->name);
}

struct node *leftRightChild(struct node *curr){
	if(curr->right == NULL){
		return curr;
	}
	
	leftRightChild(curr->right);
}

struct node *del(struct node *curr, int id){
	//1. delete BST
	if(curr == NULL){
		printf ("Student ID Not Found!\n");
		return NULL;
	}
	
	if (id < curr->id){
		//cari ke kiri
		curr->left = del(curr->left, id);
	}else if (id > curr->id){
		//cari ke kanan
		curr->right = del(curr->right, id);
	}else{
		//yang mau di delete ud ketemu
		//delete BST -> ga punya child/1 child/ 2 child
		// node ga punya child/ 1 child
		if (curr->left == NULL || curr->right == NULL){
			struct node *temp = curr->left != NULL ? curr->left : curr->right; // nampung anaknya
			
			if (temp == NULL){
				//ga punya child
				free(curr);
				curr = NULL;
			}else{
				// punya 1 child
				*curr = *temp;
				free(temp);
			}
			
			if (curr == NULL){
				return NULL;
			}
		}
		//node punya 2 child
		else{
			struct node *temp = leftRightChild(curr->left);//nampung child
			curr->id = temp->id;
			strcpy (curr->name, temp->name);
			curr->left = del(curr->left, temp->id);
		}
	}
	
	//2. update height
	curr->height = 1 + max(getHeight(curr->left),getHeight(curr->right));
	
	//3. balance
	int bf = getBalance(curr); // bf = balance factor
	if (bf > 1){ //berat kiri
		if (getBalance(curr->left) >= 0){ //left left case
			//right rotate
			return rightRotate(curr);
		}else if(getBalance(curr->left) < 0){ //left right case
			//left rotate
			curr->left = leftRotate (curr->left);
			//then right rotate
			return rightRotate(curr);
		}
	}else if(bf < -1){ // berat kanan
		if (getBalance(curr->right) <= 0){ //right right case
			//left rotate
			return leftRotate(curr);
		}else if(getBalance(curr->right) > 0){ //right left case
			//right rotate
			curr->right = rightRotate(curr->right);
			//then left rotate
			return leftRotate(curr);
		}
	}
	
	return curr;
}

void update(struct node *curr, int id, int newId, char newName[]){
	del(curr, id); //delete student id yg lama
	push(curr, newId, newName); //insert data yg baru
}

void delAll(struct node *curr){
	if (curr == NULL){
		return;
	}
	//post order traversal
	delAll(curr->left);
	delAll(curr->right);
	free(curr);
}

void display(struct node *curr, int space){
	if (curr == NULL){
		return;
	}
	space++;
	display(curr->right, space);
	for (int i = 0; i<space;i++) printf ("     ");
	printf ("%d\n",curr->id);
	for (int i = 0; i<space;i++) printf ("     ");
	printf ("%s\n",curr->name);
	display(curr->left, space);
}

struct node *seeding (struct node *root){
	display(root, 0);
	printf ("\n\n");
	root = push(root, 10, "Anita");
	display(root, 0);
	printf ("\n\n");
	root = push(root, 20, "Budi");
	display(root, 0);
	printf ("\n\n");
	root = push(root, 30, "Charlie");
	display(root, 0);
	printf ("\n\n");
	root = push(root, 40, "Dodi");
	display(root, 0);
	printf ("\n\n");
	root = push(root, 50, "Eko");
	display(root, 0);
	printf ("\n\n");
	return root;
}

int main(){
	struct node *root = NULL;
	
	root = seeding(root);
	int menu = 0;
	
	do{
		display(root,0);
		printf ("\n\n");
		puts("Student AVL Tree");
		puts("1. Insert");
		puts("2. Search");	
		puts("3. Delete Node");
		puts("4. Update");
		puts("5. Delete All");
		puts("0. Quit");	
		printf ("Choose: ");
		scanf ("%d", &menu);
		getchar();
		
		if (menu == 0){
			break;
		}else if (menu == 1){
			int id; 
			printf("input student id: ");
			scanf ("%d", &id);
			getchar();
			
			char name[100];
			printf ("input student name: ");
			scanf ("%s", name);
			getchar();
			
			root = push(root, id, name);
		}else if(menu == 2){
			int id; 
			printf("input student id: ");
			scanf ("%d", &id);
			getchar();
			
			search(root, id);
			puts ("press any key to continue");
			getchar();
		}else if(menu == 3){
			int id; 
			printf("input student id: ");
			scanf ("%d", &id);
			getchar();
			
			root = del(root, id);
			puts ("Delete Success!");
			puts ("press any key to continue");
			getchar();
		}else if(menu == 4){
			int id; 
			printf("input student id: ");
			scanf ("%d", &id);
			getchar();
			
			int newId; 
			printf("input new student id: ");
			scanf ("%d", &newId);
			getchar();
			
			char name[100];
			printf ("input new student name: ");
			scanf ("%s", name);
			getchar();
			
			update(root, id, newId, name);
		}else if (menu == 5){
			delAll(root);
			root = NULL;
			puts ("Delete Success!");
		}
		for (int i = 0; i<20;i++) printf ("\n");
	}while (true);
	
	return 0;
}

