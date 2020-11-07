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
	printf("%x", p + 1);

	return 0;

}