#include "main.h"


void func(int* p1, int p2[], int p3[10], int n1, int n2, int n3);

void testarray()
{
	int** p; //int**
	int a[3][2] = { 1,2,3,4,5,6 };//int(*)[2]  //两者类型不一样,虽然都是二级指针
	//p = a;
	int* a1;
	int a2[2] = {1,2};
	int a3[4] = { 4,3,2,1 };
	a1 = a3 + 3;
	func(a2, a1, a3,2,4,4);

}

void func(int* p1, int p2[], int p3[10],int n1,int n2,int n3)
{
	for (int i = 0; i < n1; i++)
	{
		cout << *(p1 + i) << " ";
	}
	cout << endl;
	for (int i = 0; i < n2; i++)
	{
		cout << *(p2--) << " ";
	}
	cout << endl;
	for (int i = 0; i < n3; i++)
	{
		cout << *(p3++) << " ";
	}
	cout << endl;
}