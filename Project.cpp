
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct data{
	char word[55];
	int height;
	struct data *left, *right;
};


struct lang{
	char language[35];
	long long int total;
	int height;
	struct data *langRoot;
	struct lang *left, *right;
};


struct lang *root = NULL;

struct lang *point = NULL;

struct data *WnewNode(char word[]){
	struct data *node = (struct data*) malloc (sizeof(data));
	strcpy (node->word, word);
	node->height = 1;
	node->right = node->left = NULL;
	return node;
}

struct lang *LnewNode(char language[]){
	struct lang *node = (struct lang*) malloc (sizeof(lang));
	strcpy (node->language, language);
	node->total = 0;
	node->langRoot = NULL;
	node->height = 1;
	node->right = node->left = NULL;
	return node;
}

int WgetHeight(struct data *curr){
	if (curr == NULL) return 0;
	else return curr->height;
}

int WgetBF (struct data *curr){
	if (curr == NULL) return 0;
	else return (WgetHeight(curr->left) - WgetHeight(curr->right));
}

int LgetHeight(struct lang *curr){
	if (curr == NULL) return 0;
	else return curr->height;
}

int LgetBF (struct lang *curr){
	if (curr == NULL) return 0;
	else return (LgetHeight(curr->left) - LgetHeight(curr->right));
}

int max(int a, int b){
	return (a>b)?a:b;
}

struct data *WfindChild(struct data *curr){
	if(curr->right == NULL) return curr;
	
	WfindChild(curr->right);
}

struct data *WleftRotate (struct data *node){
	struct data *child = node->right;
	struct data *gChild = child->left;
	
	child->left = node;
	node->right = gChild;
	
	node->height = 1 + max(WgetHeight(node->left), WgetHeight(node->right));
	child->height = 1 + max(WgetHeight(child->left), WgetHeight(child->right));
	return child;
}

struct data *WrightRotate (struct data *node){
	struct data *child = node->left;
	struct data *gChild = child->right;
	
	child->right = node;
	node->left = gChild;
	
	node->height = 1 + max(WgetHeight(node->left), WgetHeight(node->right));
	child->height = 1 + max(WgetHeight(child->left), WgetHeight(child->right));
	return child;
}

struct lang *LfindChild(struct lang *curr){
	if(curr->right == NULL) return curr;
	
	LfindChild(curr->right);
}

struct lang *LleftRotate (struct lang *node){
	struct lang *child = node->right;
	struct lang *gChild = child->left;
	
	child->left = node;
	node->right = gChild;
	
	node->height = 1 + max(LgetHeight(node->left), LgetHeight(node->right));
	child->height = 1 + max(LgetHeight(child->left), LgetHeight(child->right));
	return child;
}

struct lang *LrightRotate (struct lang *node){
	struct lang *child = node->left;
	struct lang *gChild = child->right;
	
	child->right = node;
	node->left = gChild;
	
	node->height = 1 + max(LgetHeight(node->left), LgetHeight(node->right));
	child->height = 1 + max(LgetHeight(child->left), LgetHeight(child->right));
	return child;
}

struct data *Wpush(struct data *node, char word[]){
	if (node == NULL) return WnewNode(word);
	else if (strcmp (word, node->word) < 0) node->left = Wpush(node->left,word);
	else if (strcmp (word, node->word) > 0) node->right = Wpush(node->right,word);
	
	node->height = 1 + max(WgetHeight(node->left), WgetHeight(node->right));
	
	int bf = WgetBF(node);
	if(bf > 1){
		if (strcmp (word, node->left->word) < 0){
			return WrightRotate(node);
		}else if (strcmp (word, node->left->word) > 0){
			node->left = WleftRotate(node->left);
			return WrightRotate(node);;
		}
	}else if (bf < -1){
		if (strcmp(word, node->right->word) > 0){
			return WleftRotate(node);
		}else if (strcmp(word, node->right->word) < 0){
			node->right = WrightRotate(node->right);
			return WleftRotate(node);;
		}
	}else{
		return node;
	}
}

struct lang *Lpush(struct lang *node, char language[]){
	if (node == NULL) return LnewNode(language);
//	else if(strcmp (language, node->language) == 0){
////		point = node->langRoot;
//		node->langRoot = Wpush(node->langRoot, word);
//		node->total++;
//		printf ("Successfully Added");
//		return node;
//	} 
	else if (strcmp (language, node->language) < 0) node->left = Lpush(node->left,language);
	else if (strcmp (language, node->language) > 0) node->right = Lpush(node->right,language);
	
//	node->langRoot = Wpush(node->langRoot, word);
//	node->total++;
//	printf ("Successfully Added");
	node->height = 1 + max(LgetHeight(node->left), LgetHeight(node->right));
	
	int bf = LgetBF(node);
	if(bf > 1){
		if (strcmp (language, node->left->language) < 0){
			return LrightRotate(node);
		}else if (strcmp (language, node->left->language) > 0){
			node->left = LleftRotate(node->left);
			return LrightRotate(node);;
		}
	}else if (bf < -1){
		if (strcmp(language, node->right->language) > 0){
			return LleftRotate(node);
		}else if (strcmp(language, node->right->language) < 0){
			node->right = LrightRotate(node->right);
			return LleftRotate(node);;
		}
	}else{
		return node;
	}
}

int Wsearch (struct data *node, char word[]){
	if (node == NULL){
		printf ("Word (%s) not found\n", word);
		return 0;
	}
	
	int sign = -1;
	if (strcmp (word, node->word) < 0){
		sign = Wsearch(node->left, word);
	}else if (strcmp (word, node->word) > 0){
		sign = Wsearch(node->right, word);
	}else{
		return 1;
	}
}

int Lsearch (struct lang *node, char language[]){
	if (node == NULL){
		printf ("%s language not found\n", language);
		return 0;
	}
	
	int sign = -1;
	if (strcmp (language, node->language) < 0){
		sign = Lsearch(node->left, language);
	}else if (strcmp (language, node->language) > 0){
		sign = Lsearch(node->right, language);
	}else{
		point = node;
		return 1;
	}
}

struct lang *push (struct lang *node, char language[], char word[]){
	if (node == NULL){
		node = Lpush(root,language);
		node->langRoot = Wpush(node->langRoot, word);
		node->total++;
		printf ("Successfully Added\n");
		return node;
	}
	
	if (strcmp (language, node->language) < 0){
		node->left = push(node->left, language, word);
	}else if (strcmp (language, node->language) > 0){
		node->right = push(node->right, language, word);
	}else{
		node->langRoot = Wpush(node->langRoot, word);
		node->total++;
		printf ("Successfully Added\n");
		return node;
	}
}

void WpopAll(struct data *node){
	if (node == NULL) return;
	
	WpopAll(node->left);
	WpopAll(node->right);
	free(node);
}

struct lang *LpopAll(struct lang *node, char language[]){
	if (node == NULL){
		printf ("%s language not found\n", language);
		return NULL;
	}
	
	if (strcmp (language, node->language) < 0) node->left = LpopAll(node->left,language);
	else if (strcmp (language, node->language) > 0) node->right = LpopAll(node->right,language);
	else{
		if (node->left == NULL || node->right == NULL){
			struct lang *temp = (node->left == NULL) ? node->right : node->left;
			
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
			struct lang *temp = LfindChild(node->left);
			strcpy (node->language, temp->language);
			node->langRoot = temp->langRoot;
			node->total = temp->total;
			node->left = LpopAll(node->left, temp->language);
		}
		
		node->height = 1 + max(LgetHeight(node->left), LgetHeight(node->right));
	
		int bf = LgetBF(node);
		if(bf > 1){
			if (strcmp (language, node->left->language) < 0){
				return LrightRotate(node);
			}else if (strcmp (language, node->left->language) > 0){
				node->left = LleftRotate(node->left);
				return LrightRotate(node);;
			}
		}else if (bf < -1){
			if (strcmp(language, node->right->language) > 0){
				return LleftRotate(node);
			}else if (strcmp(language, node->right->language) < 0){
				node->right = LrightRotate(node->right);
				return LleftRotate(node);
			}
		}else{
			return node;
		}
	}
}

struct data *Wpop(struct data *node, char word[]){
	if (node == NULL){
		printf ("Word (%s) not found\n", word);
		return NULL;
	}
	
	if (strcmp (word, node->word) < 0){
		node->left = Wpop(node->left, word);
	}else if (strcmp (word, node->word) > 0){
		node->right = Wpop(node->right, word);
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
			struct data *temp = WfindChild(node->left);
			strcpy (node->word, temp->word);
			node->left = Wpop(node->left, temp->word);
		}
	}
	
	node->height = 1 + max(WgetHeight(node->left), WgetHeight(node->right));
	
	int bf = WgetBF(node);
	if(bf > 1){
		if (strcmp (word, node->left->word) < 0){
			return WrightRotate(node);
		}else if (strcmp (word, node->left->word) > 0){
			node->left = WleftRotate(node->left);
			return WrightRotate(node);;
		}
	}else if (bf < -1){
		if (strcmp(word, node->right->word) > 0){
			return WleftRotate(node);
		}else if (strcmp(word, node->right->word) < 0){
			node->right = WrightRotate(node->right);
			return WleftRotate(node);;
		}
	}else{
		return node;
	}
}

struct lang *Lpop(struct lang *node, char language[], char word[]){
	if (node == NULL){
		printf ("%s language not found\n", language);
		return NULL;
	}
	else if(strcmp (language, node->language) == 0){
//		point = node->langRoot;
		int sign = -1;
		sign = Wsearch (node->langRoot, word);
		if (sign == 1){
			node->langRoot = Wpop(node->langRoot, word);
			node->total--;
			printf ("Successfully Deleted\n");
		}else{
			return node;
		}
		
	} 
	else if (strcmp (language, node->language) < 0) node->left = Lpop(node->left,language, word);
	else if (strcmp (language, node->language) > 0) node->right = Lpop(node->right,language, word);
	
	if (node->total == 0){
		if (node->left == NULL || node->right == NULL){
			struct lang *temp = (node->left == NULL) ? node->right : node->left;
			
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
			struct lang *temp = LfindChild(node->left);
			strcpy (node->language, temp->language);
			node->langRoot = temp->langRoot;
			node->total = temp->total;
			node->left = LpopAll(node->left, temp->language);
		}
		
		node->height = 1 + max(LgetHeight(node->left), LgetHeight(node->right));
	
		int bf = LgetBF(node);
		if(bf > 1){
			if (strcmp (language, node->left->language) < 0){
				return LrightRotate(node);
			}else if (strcmp (language, node->left->language) > 0){
				node->left = LleftRotate(node->left);
				return LrightRotate(node);;
			}
		}else if (bf < -1){
			if (strcmp(language, node->right->language) > 0){
				return LleftRotate(node);
			}else if (strcmp(language, node->right->language) < 0){
				node->right = LrightRotate(node->right);
				return LleftRotate(node);
			}
		}else{
			return node;
		}
	}else {
		return node;
	}
	
}

void Winorder(struct data *node){
	if (node == NULL){
		return;
	}
	
	Winorder(node->left);
	printf ("- %s\n",node->word);
	Winorder(node->right);
}

void LAllinorder (struct lang *node){
	if (node == NULL){
		return;
	}
	
	LAllinorder(node->left);
	printf ("%s (%d):\n",node->language, node->total);
	Winorder(node->langRoot);
	LAllinorder(node->right);
}

void Linorder (struct lang *node, char language[]){
	if (node == NULL){
		printf ("%s language not found\n", language);
		return;
	}
	
	if (strcmp (language, node->language) < 0){
		Linorder(node->left, language);
	}else if (strcmp (language, node->language) > 0){
		Linorder (node->right, language);
	}else{
		printf ("%s (%d):\n",node->language, node->total);
		Winorder (node->langRoot);
		return;
	}
}

int main(){
	
	long long int t,k;
	scanf ("%d", &t);
	getchar();
	
	for (k = 1; k<=t;k++){
		printf ("Case %d:\n", k);
		
		char op[20];
		scanf ("%s", op);
		getchar();
		
		if(strcmp("ADD", op) == 0){
			char language[35];
			char word[55];
			scanf ("%s %s", language, word);
			getchar();
			
			root = push (root, language, word);
		}else if (strcmp("SHOW-ALL", op) == 0){
			if (root == NULL){
				printf ("Dictionary empty\n");
			}else{
				LAllinorder(root);
			}
		}else if (strcmp("SHOW-LANG", op) == 0){
			char language[35];
			scanf ("%s", language);
			getchar();
			
			Linorder (root, language);
		}else if (strcmp("DEL-LANG", op) == 0){
			char language[35];
			scanf ("%s", language);
			getchar();
			
			int sign = Lsearch(root, language);
			
			if (sign == 1){
				WpopAll(point->langRoot);
				root = LpopAll(root, language);
				printf ("Successfully Deleted\n");
			}
		}else if (strcmp("DEL-WORD", op) == 0){
			char language[35];
			char word[55];
			scanf ("%s %s", language, word);
			getchar();
			
			int sign = Lsearch(root, language);
			
			if (sign == 1){
				root = Lpop(root, language, word);
				printf ("Successfully Deleted\n");
			}
		}
	}
	
	return 0;
}

/*
19
ADD English Park
ADD English Choose
ADD Indonesia Duduk
ADD Indonesia Makan
ADD Spanish Medico
ADD English Chalk
ADD Indonesia Minum
ADD French Cuisinier
SHOW-ALL
SHOW-LANG Indonesia
DEL-LANG Indonesia
SHOW-ALL
ADD Indonesia Masak
SHOW-ALL
DEL-WORD English Choose
DEL-WORD English Park
DEL-WORD English Eat
SHOW-ALL
SHOW-LANG JAPAN
*/

