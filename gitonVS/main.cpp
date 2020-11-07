#include <iostream>

int main()
{
	int* p;
	int a[10];
	for (int i = 0; i < 10; i++)
	{
		*(a + i) = i;
	}
	p = a;
	printf("%d,%d\n", *p, *a);

	return 0;

}