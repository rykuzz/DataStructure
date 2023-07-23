#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct student{
	char name[100];
	int age;
};

int main(){
//	struct student std1;
//	strcpy(std1.name, "Galaxy");
//	std1.age = 20;
//	printf ("std1.name: %s\n",std1.name);
//	printf ("std1.age: %d\n",std1.age);
//	
//	struct student *pstd1 = &std1;
//	printf ("\n&std1: %d\n",&std1);
//	printf ("pstd1: %d\n",pstd1);
//	printf ("pstd1->name: %s\n",pstd1->name);
//	printf ("pstd1->age: %d\n",pstd1->age);
//	
//	struct student std[10];
//	int stdcnt = 0;
//	std[0] = std1;
//	printf ("\nstd[0].name: %s\n",std[0].name);
//	printf ("std[0].age: %d\n",std[0].age);
//	stdcnt++;
//	
//	for (int i = 1;i<10;i++){
//		printf ("\nInput Name: ");
//		scanf ("%s",std[stdcnt].name);
//		getchar();
//		printf ("Input Age: ");
//		scanf ("%d",&std[stdcnt].age);
//		getchar();
//		stdcnt++;
//		
//		printf ("\n");
//		for (int j = 0;j<stdcnt;j++){
//			printf ("std[%d].name: %s\n",j,std[j].name);
//			printf ("std[%d].age: %d\n",j,std[j].age);
//		}
//	}
	
	//STRUCT WITH POINTER
	struct student *pstd1 = (struct student*) malloc(sizeof(struct student));
	strcpy (pstd1->name,"Holly");
	pstd1->age = 20;
	printf ("pstd1->name: %s\n",pstd1->name);
	printf ("pstd1->age: %d\n",pstd1->age);
	
	/*
	Union VS Struct
	
	struct student{
	char name[100];//100 byte
	int age;//4 byte
	};
	Struct student 104 byte
	Union student 100 byte
	*/
	
	return 0;
}

