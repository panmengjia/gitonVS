#include "main.h"

/*
��C++11��ʼ����׼�����Ѿ������˶��̵߳�֧�֣�std::thread��C++11��׼���еĶ��̵߳�֧�ֿ⣬
pthread.h�Ǳ�׼��û����Ӷ��߳�֮ǰ����Linux���õĶ��߳̿⣬��֮ǰ��windows�ϵĶ��߳�֧��Ҫ����wndows.h
Ӧ��thread��������
https://blog.csdn.net/u010029439/article/details/83749259
https://blog.csdn.net/sevenjoin/article/details/82187127
��Ԫ������https://www.runoob.com/cplusplus/cpp-friend-functions.html
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
		puts("����һ���߳�");
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
		puts("�ڶ����߳�");
		printf("%d,%d,%d\n", this->a, this->b, this->c);
		Sleep(300);
	}
}

int gittest();

/*
���Բ���һ����malloc�����ڴ�

*/

int maintest()
{
	int a = 10;
	int b = 57;
	int c = 98;
	testThreadClass* ptr = new testThreadClass(a, b, c);
	thread another(threadCallback, ptr);
	printf("��һ���̵߳�id = %p\n", another.get_id()); //����ָ��ֵ
	another.detach();

	//testThreadClass* ptr2 = (testThreadClass*)malloc(sizeof(testThreadClass)); //֮����ô���ù��캯��
	//testThreadClass* ptr2 = new testThreadClass;
	//ptr2->a = 20;
	//ptr2->b = 35;
	//testThreadClass thread2;
	//thread2.a = 678;
	//thread2.b = 467;
	//thread another2(testThreadClass::threadCallback2, thread2);//�ڶ����������������ָ��
	//printf("�ڶ����̵߳�id = %p\n", another2.get_id());
	//another2.detach();
	//ƭ�˵ĳ�Ա�������ܵ��ص�����

	while (1)
	{
		puts("���߳�------");
		Sleep(1000);
		gittest();
	}


	delete ptr; //�費Ҫ��Ҳ��֪��
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
	printf("%p\n", (p + 1)); //��%x����%p

	return 0;

}