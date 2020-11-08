#include <iostream>

void putmessage()
{
	puts("给mainlocal再开一个节点,工作区再增加一个mainlocaltest.txt文件");
}

int main()
{
	int* p;
	int a[10];
	for (int i = 0; i < 10; i++)
	{
		*(a + i) = i;
	}
	p = a;
	putmessage();
	printf("%d,%d\n", *p, *a);


	return 0;

}