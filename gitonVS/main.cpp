#include <iostream>
#include <opencv.hpp>
#include <thread>
#include "windows.h"

using namespace cv;
using namespace std;

class threadtest
{
public:
	threadtest() {};
	threadtest(int& a, int& b, int& c);

	friend void threadCallback(threadtest* threadtestPtr);

	int a;
	int b;
private:
	int c = 100;
};

void threadCallback(threadtest* threadtestPtr)
{

	while (1)
	{
		puts("另外一个线程");
		Sleep(500);
		threadtestPtr->b++;
		cout << "threadtestPtr->b = " << threadtestPtr->b << endl;
	}
}

threadtest::threadtest(int& a, int& b,int& c)
{
	this->a = a;
	this->b = b;
	this->c = c;
}

int gittest();

int main()
{
	int a = 10;
	int b = 57;
	int c = 98;
	threadtest* ptr = new threadtest(a,b,c);
	thread another(threadCallback, ptr);
	another.detach();

	while (1)
	{
		puts("主线程------");
		Sleep(1000);
		gittest();
	}

	return 0;
}

int gittest()
{
	int* p;
	int a[10];
	for (int i = 0; i < 10; i++)
	{
		*(a + i) = i;
	}
	p = a;
	printf("%d,%d\n", *p, *a);
	printf("%p\n", (p + 1)); //把%x换成%p

	return 0;

}