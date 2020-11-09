#include "main.h"

/*
从C++11开始，标准库里已经包含了对线程的支持，std::thread是C++11标准库中的多线程的支持库，
pthread.h是标准库没有添加多线程之前的在Linux上用的多线程库，而之前在windows上的多线程支持要包含wndows.h
应该thread库是最方便的
https://blog.csdn.net/u010029439/article/details/83749259
https://blog.csdn.net/sevenjoin/article/details/82187127
友元函数：https://www.runoob.com/cplusplus/cpp-friend-functions.html
*/

class testThreadClass
{
public:
	testThreadClass() {};
	testThreadClass(int& a, int& b, int& c);

	friend void threadCallback(testThreadClass* testThreadClassPtr);
	void threadCallback2();

	int a;
	int b;
private:
	int c = 100;
};

void threadCallback(testThreadClass* testThreadClassPtr)
{

	while (1)
	{
		puts("另外一个线程");
		Sleep(500);
		testThreadClassPtr->b++;
		cout << "testThreadClassPtr->b = " << testThreadClassPtr->b << endl;
	}
}

testThreadClass::testThreadClass(int& a, int& b, int& c)
{
	this->a = a;
	this->b = b;
	this->c = c;
}
void testThreadClass::threadCallback2()
{
	while (1)
	{
		puts("第二个线程");
		printf("%d,%d,%d\n", this->a, this->b, this->c);
		Sleep(300);
	}
}

int gittest();

/*
可以测试一下用malloc分配内存

*/

int maintest()
{
	int a = 10;
	int b = 57;
	int c = 98;
	testThreadClass* ptr = new testThreadClass(a, b, c);
	thread another(threadCallback, ptr);
	printf("第一个线程的id = %p\n", another.get_id()); //返回指针值
	another.detach();

	//testThreadClass* ptr2 = (testThreadClass*)malloc(sizeof(testThreadClass)); //之后怎么调用构造函数
	//testThreadClass* ptr2 = new testThreadClass;
	//ptr2->a = 20;
	//ptr2->b = 35;
	//testThreadClass thread2;
	//thread2.a = 678;
	//thread2.b = 467;
	//thread another2(testThreadClass::threadCallback2, thread2);//第二个参数好像必须是指针
	//printf("第二个线程的id = %p\n", another2.get_id());
	//another2.detach();
	//骗人的成员函数不能当回调函数

	while (1)
	{
		puts("主线程------");
		Sleep(1000);
		gittest();
	}


	delete ptr; //需不要我也不知道
	//delete ptr2;
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