#include <stdio.h>
#include <string.h>

struct patient{
	int priority;
	char name[100];
};

struct patient heap[100]; //1-99
int count = 0;

int getParent(int idx){
	return idx / 2;
}

int getLeftC(int idx){
	return idx * 2;
}

int getRightC(int idx){
	return (idx * 2) + 1;
}

void swap(struct patient *a, struct patient *b){
	struct patient temp = *a;
	*a = *b;
	*b = temp;
}

void upHeapMax(int idx){
	if(idx <= 1) return;
	
	int parIdx = getParent(idx);
	if (heap[idx].priority > heap[parIdx].priority){
		swap(&heap[idx],&heap[parIdx]);
		upHeapMax(parIdx);
	}
}

void push(struct patient val){
	count++;
	heap[count] = val;
	upHeapMax(count);
}

void downHeapMax(int idx){
	if(idx >= count) return;
	
	int leftIdx = getLeftC(idx);
	if (leftIdx > count) return;
	
	int largeIdx = idx;
	if (heap[leftIdx].priority > heap[largeIdx].priority){
		largeIdx = leftIdx;
	}
	int rightIdx = getRightC(idx);
	if (rightIdx <= count){
		if(heap[rightIdx].priority > heap[largeIdx].priority){
			largeIdx = rightIdx;
		}
	}
	
	if(largeIdx == idx) return;
	
	swap(&heap[idx],&heap[largeIdx]);
	downHeapMax(largeIdx);
}

void pop(){
	if(count <= 0){
		return;
	}
	heap[1] = heap[count];
	count--;
	downHeapMax(1);
}

void display(){
	for(int i = 1; i <= count;i++){
		printf ("%d %s\n",heap[i].priority,heap[i].name);
	}
	printf ("\n");
}

int main(){
	int menu = 0;
	while (true){
		printf ("\n\n");
		display();
		menu = 0;
		puts ("1. Insert");
		puts ("2. Delete");
		puts ("3. Exit");
		printf ("Choose: ");
		scanf("%d", &menu);
		getchar();
		
		if (menu == 1){
			int priority;
			printf ("Input patient's priority: ");
			scanf ("%d", &priority);
			getchar();
			
			char name[100];
			printf ("Input patient's name: ");
			scanf ("%[^\n]", name);
			getchar();
			
			struct patient newPatient;
			newPatient.priority = priority;
			strcpy(newPatient.name, name);
			
			push(newPatient);
		}else if(menu == 2){
			pop();
		}else if(menu == 3){
			break;
		}
	}
		
	return 0;
}

