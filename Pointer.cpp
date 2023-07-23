#include <stdio.h>

int main(){
	int a = 10;
	int *pa = &a;
	printf("a: %d\n",a);
	printf("&a: %d\n",&a);
	printf("pa: %d\n",pa);
	printf("&pa: %d\n",&pa);
	printf("*pa: %d\n",*pa);
	
	int arr[10] = {1,2,3,4,5};
	printf("\narr: %d\n",arr);
	printf("&arr[0]: %d\n",&arr[0]);
	for (int i=0;i<10;i++){
		printf ("arr[%d] : %d %d\n",i,arr[i],&arr[i]);
	}
	return 0;
}
