#include <stdio.h>

//searching heap, looping satu2, linear search

int heap[100]; //1-99
//kalo mulai dari 0, semua - 1
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

void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

void upHeapMax(int idx){
	if(idx <= 1) return;
	
	int parIdx = getParent(idx);
	if (heap[idx] > heap[parIdx]){
		swap(&heap[idx],&heap[parIdx]);
		upHeapMax(parIdx);
	}
}

void push(int val){
	count++;
	heap[count] = val;
	upHeapMax(count);
}

void downHeapMax(int idx){
	if(idx >= count) return;
	
	int leftIdx = getLeftC(idx);
	if (leftIdx > count) return;
	
	int largeIdx = idx;
	if (heap[leftIdx] > heap[largeIdx]){
		largeIdx = leftIdx;
	}
	int rightIdx = getRightC(idx);
	if (rightIdx <= count){
		if(heap[rightIdx] > heap[largeIdx]){
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
		printf ("%d ",heap[i]);
	}
	printf ("\n");
}

int main(){
	push(50);
	push(30);
	push(40);
	push(55);
	push(20);
	push(25);
	display();
	pop();
	display();
		
	return 0;
}

