#include <iostream>

void putmessage()
{
	puts("��mainlocal�ٿ�һ���ڵ�,������������һ��mainlocaltest.txt�ļ�");
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