#include <stdio.h>
#include <stdlib.h>

struct data{
	int val,height;
	struct data *left, *right;
};

struct data *root = NULL;

struct data *newNode(int val){
	struct data *node = (struct data*) malloc (sizeof(data));
	node->val = val;
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

struct data *push(struct data *node, int val){
	if (node == NULL) return newNode(val);
	else if (val < node->val) node->left = push(node->left,val);
	else if (val > node->val) node->right = push(node->right,val);
	
	node->height = 1 + max(getHeight(node->left), getHeight(node->right));
	
	int bf = getBF(node);
	if(bf > 1){
		if (val < node->left->val){
			return rightRotate(node);
		}else if (val > node->left->val){
			node->left = leftRotate(node->left);
			return rightRotate(node);;
		}
	}else if (bf < -1){
		if (val > node->right->val){
			return leftRotate(node);
		}else if (val < node->right->val){
			node->right = rightRotate(node->right);
			return leftRotate(node);;
		}
	}else{
		return node;
	}
}

struct data *pop(struct data *node, int val){
	if (node == NULL){
		printf ("Data not found!");
		return NULL;
	}
	
	if (val < node->val){
		node->left = pop(node->left, val);
	}else if (val > node->val){
		node->right = pop(node->right, val);
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
			node->val = temp->val;
			node->left = pop(node->left, temp->val);
		}
	}
	
	node->height = 1 + max(getHeight(node->left), getHeight(node->right));
	
	int bf = getBF(node);
	if(bf > 1){
		if (val < node->left->val){
			return rightRotate(node);
		}else if (val > node->left->val){
			node->left = leftRotate(node->left);
			return rightRotate(node);;
		}
	}else if (bf < -1){
		if (val > node->right->val){
			return leftRotate(node);
		}else if (val < node->right->val){
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

void inorder(struct data *node){
	if (node == NULL){
		return;
	}
	
	inorder(node->left);
	printf ("%d ",node->val);
	inorder(node->right);
}

void preorder(struct data *node){
	if (node == NULL){
		return;
	}
	
	printf ("%d ",node->val);
	preorder(node->left);
	preorder(node->right);
}

void postorder(struct data *node){
	if (node == NULL){
		return;
	}
	
	postorder(node->left);
	postorder(node->right);
	printf ("%d ",node->val);
}

int main(){
	root = push(root, 10);
	inorder(root);
	printf("\n");
	preorder(root);
	printf ("\n");
	postorder(root);
	printf ("\n\n");
	root = push(root, 20);
	inorder(root);
	printf("\n");
	preorder(root);
	printf ("\n");
	postorder(root);
	printf ("\n\n");
	root = push(root, 30);
	inorder(root);
	printf("\n");
	preorder(root);
	printf ("\n");
	postorder(root);
	printf ("\n\n");
	root = push(root, 40);
	inorder(root);
	printf("\n");
	preorder(root);
	printf ("\n");
	postorder(root);
	printf ("\n\n");
	root = push(root, 50);
	inorder(root);
	printf("\n");
	preorder(root);
	printf ("\n");
	postorder(root);
	printf ("\n\n");
	return 0;
}

