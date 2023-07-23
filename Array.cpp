#include <stdio.h>

int main(){
	int arr[10];
	arr[0] = 5;
	printf ("arr[0]: %d\n\n",arr[0]);
	
	int array[10] = {1,2,3,4,5};
	for (int i=0;i<10;i++){
		printf ("array[%d] : %d\n",i,array[i]);
	}
	
	char str[5] = "Home";
	printf ("\nstr: %s\n\n",str);
	
	int arr2d[3][2] = {{1,2},{3,4},{4,5}};
	for (int i = 0;i<3;i++){
		for(int j =0;j<2;j++){
			printf("arr2d[%d][%d]: %d  ",i,j,arr2d[i][j]);
		}
		printf ("\n");
	}
	
	int arr3d[3][2][5] = {
		{{1,2,3,4,5},{6,7,8,9,0}},
		{{1,2,3,4,5},{6,7,8,9,0}},
		{{1,2,3,4,5},{6,7,8,9,0}},
	};
	
	printf("\n");
	for (int i = 0;i<3;i++){
		for(int j =0;j<2;j++){
			for (int k=0;k<5;k++){
				printf("arr3d[%d][%d][%d]: %d  ",i,j,k,arr3d[i][j][k]);
			}
			printf ("\n");
		}
		printf ("\n");
	}
	return 0;
}

