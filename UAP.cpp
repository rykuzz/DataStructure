#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct data{
	char id[10];
	char name[15];
	char brand[10];
	int price,qty,height;
	struct data *left, *right;
};

struct data *root = NULL;
int searchSign = -1;

struct data *newNode(char id[], char name[],char brand[],int price, int qty){
	struct data *node = (struct data*) malloc (sizeof(data));
	strcpy(node->id, id);
	strcpy(node->name, name);
	strcpy(node->brand, brand);
	node->price = price;
	node->qty = qty;
	node->height = 1;
	node->right = node->left = NULL;
	return node;
}

int getHeight(struct data *curr){
	if (curr == NULL) return 0;
	else return curr->height;
}

int getBF (struct data *curr){
	if (curr == NULL) return 0;
	else return (getHeight(curr->left) - getHeight(curr->right));
}

int max(int a, int b){
	return (a>b)?a:b;
}

struct data *findChild(struct data *curr){
	if(curr->right == NULL) return curr;
	
	findChild(curr->right);
}

struct data *leftRotate (struct data *node){
	struct data *child = node->right;
	struct data *gChild = child->left;
	
	child->left = node;
	node->right = gChild;
	
	node->height = 1 + max(getHeight(node->left), getHeight(node->right));
	child->height = 1 + max(getHeight(child->left), getHeight(child->right));
	return child;
}

struct data *rightRotate (struct data *node){
	struct data *child = node->left;
	struct data *gChild = child->right;
	
	child->right = node;
	node->left = gChild;
	
	node->height = 1 + max(getHeight(node->left), getHeight(node->right));
	child->height = 1 + max(getHeight(child->left), getHeight(child->right));
	return child;
}

struct data *push(struct data *node, char id[], char name[],char brand[],int price, int qty){
	if (node == NULL) return newNode(id,name,brand,price,qty);
	else if (strcmp(id, node->id) < 0) node->left = push(node->left,id,name,brand,price,qty);
	else if (strcmp(id, node->id) > 0) node->right = push(node->right,id,name,brand,price,qty);
	
	node->height = 1 + max(getHeight(node->left), getHeight(node->right));
	
	int bf = getBF(node);
	if(bf > 1){
		if (strcmp(id, node->left->id) < 0){
			return rightRotate(node);
		}else if (strcmp(id, node->left->id) > 0){
			node->left = leftRotate(node->left);
			return rightRotate(node);;
		}
	}else if (bf < -1){
		if (strcmp(id, node->right->id) > 0){
			return leftRotate(node);
		}else if (strcmp(id, node->right->id) < 0){
			node->right = rightRotate(node->right);
			return leftRotate(node);;
		}
	}else{
		return node;
	}
}

int search(struct data *node, char id[]){
	if (node == NULL){
		return 0;
	}
	
	if (strcmp(id, node->id) < 0){
		searchSign = search(node->left, id);
	}else if (strcmp(id, node->id) > 0){
		searchSign = search(node->right, id);
	}else{
		return 1;
	}
}

struct data *pop(struct data *node, char id[]){
	if (node == NULL){
		printf ("ID not found!");
		return NULL;
	}
	
	if (strcmp(id, node->id) < 0){
		node->left = pop(node->left, id);
	}else if (strcmp(id, node->id) < 0){
		node->right = pop(node->right, id);
	}else{
		if (node->left == NULL || node->right == NULL){
			struct data *temp = (node->left == NULL) ? node->right : node->left;
			
			if (temp == NULL){
				free(node);
				node = NULL;
			}else{
				*node = *temp;
				free(temp);
			}
			
			if(node == NULL){
				return NULL;
			}
		}else{
			struct data *temp = findChild(node->left);
			strcpy(node->id, temp->id);
			strcpy(node->name, temp->name);
			strcpy(node->brand, temp->brand);
			node->price = temp->price;
			node->qty = temp->qty;
			node->left = pop(node->left, temp->id);
		}
	}
	
	node->height = 1 + max(getHeight(node->left), getHeight(node->right));
	
	int bf = getBF(node);
	if(bf > 1){
		if (strcmp(id, node->left->id) < 0){
			return rightRotate(node);
		}else if (strcmp(id, node->left->id) > 0){
			node->left = leftRotate(node->left);
			return rightRotate(node);;
		}
	}else if (bf < -1){
		if (strcmp(id, node->right->id) > 0){
			return leftRotate(node);
		}else if (strcmp(id, node->right->id) < 0){
			node->right = rightRotate(node->right);
			return leftRotate(node);;
		}
	}else{
		return node;
	} 
}

void popAll(struct data *node){
	if (node == NULL) return;
	
	popAll(node->left);
	popAll(node->right);
	free(node);
}

int space(char string[]){
	return 11-strlen(string);
}

void inorder(struct data *node){
	if (node == NULL){
		return;
	}
	
	int spaceqty = 0;
	
	inorder(node->left);
	printf ("| %s\t",node->id);
	printf ("| %s",node->name);
	spaceqty = space(node->name);
	for (int i = 0; i<spaceqty;i++){
		printf (" ");
	}
	printf ("| %s",node->brand);
	spaceqty = space(node->brand);
	for (int i = 0; i<spaceqty;i++){
		printf (" ");
	}
	printf ("| %d",node->price);
	char temp[10];
	itoa (node->price, temp, 10);
	spaceqty = space(temp);
	for (int i = 0; i<spaceqty;i++){
		printf (" ");
	}
	printf ("| %d\t|\n",node->qty);
	inorder(node->right);
}

void preorder(struct data *node){
	if (node == NULL){
		return;
	}
	
	int spaceqty = 0;
	
	printf ("| %s\t",node->id);
	printf ("| %s",node->name);
	spaceqty = space(node->name);
	for (int i = 0; i<spaceqty;i++){
		printf (" ");
	}
	printf ("| %s",node->brand);
	spaceqty = space(node->brand);
	for (int i = 0; i<spaceqty;i++){
		printf (" ");
	}
	printf ("| %d",node->price);
	char temp[10];
	itoa (node->price, temp, 10);
	spaceqty = space(temp);
	for (int i = 0; i<spaceqty;i++){
		printf (" ");
	}
	printf ("| %d\t|\n",node->qty);
	preorder(node->left);
	preorder(node->right);
}

void postorder(struct data *node){
	if (node == NULL){
		return;
	}
	
	postorder(node->left);
	postorder(node->right);
	
	int spaceqty = 0;
	
	printf ("| %s\t",node->id);
	printf ("| %s",node->name);
	spaceqty = space(node->name);
	for (int i = 0; i<spaceqty;i++){
		printf (" ");
	}
	printf ("| %s",node->brand);
	spaceqty = space(node->brand);
	for (int i = 0; i<spaceqty;i++){
		printf (" ");
	}
	printf ("| %d",node->price);
	char temp[10];
	itoa (node->price, temp, 10);
	spaceqty = space(temp);
	for (int i = 0; i<spaceqty;i++){
		printf (" ");
	}
	printf ("| %d\t|\n",node->qty);
}

void seeding(){
	root = push(root, "MO005", "Apple 5", "Apple", 399000, 1);
	inorder(root);
	printf("\n");
	preorder(root);
	printf ("\n");
	postorder(root);
	printf ("\n\n");
	root = push(root, "MO001", "G1005", "Logitech", 150000, 2);
	inorder(root);
	printf("\n");
	preorder(root);
	printf ("\n");
	postorder(root);
	printf ("\n\n");
	root = push(root, "MO010", "Razer 2", "Razer", 249000, 4);
	inorder(root);
	printf("\n");
	preorder(root);
	printf ("\n");
	postorder(root);
	printf ("\n\n");
	root = pop(root, "MO005");
	inorder(root);
	printf("\n");
	preorder(root);
	printf ("\n");
	postorder(root);
	printf ("\n\n");
}

int main(){
//	seeding();
	int menu = 0;
	while (true){
		printf ("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		printf ("===============\n");
		printf ("|  Mouse Tech |\n");
		printf ("===============\n");
		puts("1. Insert Mouse");
		puts("2. Delete Mouse");
		puts("3. View Mouse");
		puts("4. Exit");
		printf (">> ");
		scanf ("%d",&menu);
		getchar();
		
		if (menu == 1){
			printf ("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
			char id[10];
			char name[15];
			char brand[10];
			int price,qty;
			int sign;
			//ID
			do{
				printf ("Insert Mouse ID [MOXXX | X must be number]: ");
				scanf ("%[^\n]",id);
				getchar();
				sign = 1;
				if (id[0] != 'M'){
//					printf ("JJ\n");
					sign = 0;
				}else if(id[1] != 'O'){
//					printf ("LL\n");
					sign = 0;
				}else{
					for (int i = 2; i<5;i++){
						if (id[i] < '0' || id[i] > '9'){
//							printf ("MM\n");
							sign = 0;
							break;
						}
					}
				}
				
				if (sign != 0){
					searchSign = search(root, id);
//					printf ("%d ",searchSign);
					if (searchSign != 0){
//						printf ("XX\n");
						sign = 0;
					}
				}
				
			}while(sign == 0);
			
			//Name
			do{
				printf ("Insert Mouse Name [5-10]: ");
				scanf ("%[^\n]",name);
				getchar();
				if (strlen(name) >= 5 && strlen(name) <= 10){
					break;
				}
				
			}while(true);
			
			//Brand
			do{
				printf ("Insert Mouse Brand [Logitech | HP | Razer | Apple] (Case Sensitive): ");
				scanf ("%[^\n]",brand);
				getchar();
				if ((strcmp(brand, "Logitech") == 0) || (strcmp(brand, "HP") == 0) || (strcmp(brand, "Razer") == 0) || (strcmp(brand, "Apple") == 0)){
					break;
				}
				
			}while(true);
			
			//Price
			do{
				printf ("Insert Mouse Price Rp.[10000 - 10000000]: ");
				scanf ("%d",&price);
				getchar();
				if (price >= 10000 && price <= 10000000){
					break;
				}
			}while(true); 
			
			//Quantity
			do{
				printf ("Insert Quantity [must be more than zero]: ");
				scanf ("%d",&qty);
				getchar();
				if (qty > 0){
					break;
				}
			}while(true);
			
			root = push(root, id, name, brand, price,qty);
			printf ("Order added!");
			getchar();
		}else if(menu == 2){
			printf ("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
			if (root == NULL){
				printf ("Data is empty!");
				getchar();
				continue;
			}else{
				printf ("=========================================================\n");
				printf ("| ID\t| Name       | Brand      | Price      | Qty\t|\n");
				printf ("=========================================================\n");
				inorder(root);
				printf ("=========================================================\n");
				printf ("\n\n\n");
				printf("Insert ID to be deleted: ");
				char id[10];
				scanf ("%[^\n]",id);
				getchar();
				searchSign = search(root, id);
				if (searchSign == 0){
					printf ("ID not found!\n");
					getchar();
					continue;
				}else{
					do{
						printf ("Are you sure ? [yes | no] : ");
						char sure[5];
						scanf ("%[^\n]",sure);
						getchar(); 
						if (strcmp(sure,"yes") == 0){
							root = pop(root, id);
							printf ("Item deleted!");
							getchar();
							break;
						}else if(strcmp(sure,"no") == 0){
							break;
						}
					}while(true);
				}
			}
		}else if (menu == 3){
			printf ("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
			if (root == NULL){
				printf ("Data is empty!");
				getchar();
				continue;
			}else{
				printf ("Insert View Type [Preorder | Inorder | Postorder] (Case Sensitive):");
				char view[20];
				scanf ("%[^\n]",view);
				getchar();
				
				if ((strcmp(view, "Preorder") == 0)){
					printf ("=========================================================\n");
					printf ("| ID\t| Name       | Brand      | Price      | Qty\t|\n");
					printf ("=========================================================\n");
					preorder(root);
					printf ("=========================================================\n");
				}else if((strcmp(view, "Inorder") == 0)){
					printf ("=========================================================\n");
					printf ("| ID\t| Name       | Brand      | Price      | Qty\t|\n");
					printf ("=========================================================\n");
					inorder(root);
					printf ("=========================================================\n");
				}else if((strcmp(view, "Postorder") == 0)){
					printf ("=========================================================\n");
					printf ("| ID\t| Name       | Brand      | Price      | Qty\t|\n");
					printf ("=========================================================\n");
					postorder(root);
					printf ("=========================================================\n");
				}
				
			}
			getchar();
		}else if (menu == 4){
			popAll(root);
			break;
		}
	}
	
	
	return 0;
}

