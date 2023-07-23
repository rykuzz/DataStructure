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

void upHeapMin(int idx){
	if(idx <= 1) return;
	
	int parIdx = getParent(idx);
	if (heap[idx] < heap[parIdx]){
		swap(&heap[idx],&heap[parIdx]);
		upHeapMin(parIdx);
	}
}

void push(int val){
	count++;
	heap[count] = val;
	upHeapMin(count);
}

void downHeapMin(int idx){
	if(idx >= count) return;
	
	int leftIdx = getLeftC(idx);
	if (leftIdx > count) return;
	
	int smallIdx = idx;
	if (heap[leftIdx] < heap[smallIdx]){
		smallIdx = leftIdx;
	}
	int rightIdx = getRightC(idx);
	if (rightIdx <= count){
		if(heap[rightIdx] < heap[smallIdx]){
			smallIdx = rightIdx;
		}
	}
	
	if(smallIdx == idx) return;
	
	swap(&heap[idx],&heap[smallIdx]);
	downHeapMin(smallIdx);
}

void pop(){
	if(count <= 0){
		return;
	}
	heap[1] = heap[count];
	count--;
	downHeapMin(1);
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

