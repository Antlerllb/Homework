// 李玲宝 计算机2101 20201303587 2022.4.12
#include<iostream>
#include<string.h>
#include<math.h>
#include<fstream>
using namespace std;
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSIZE 1000
typedef int Status;
typedef char Elemtype;
typedef struct QueueList {
	int front;
	int rear;
	int* base;
};
Status InitQueue(QueueList& Q)
{
	Q.base = new int[MAXSIZE];
	if (!Q.base)
	{
		return OVERFLOW;
	}
	Q.rear = 0;
	Q.front = Q.rear;
	return OK;
}
int Queue_length(QueueList& Q)
{
	if (!Q.base)
	{
		return ERROR;
	}
	return (Q.rear - Q.front + MAXSIZE) % MAXSIZE;
}
Status EnterQueue(QueueList& Q, int n)
{
	if ((Q.rear + 1) % MAXSIZE == Q.front)//判断队列已经满的情况
	{
		return ERROR;
	}
	Q.base[Q.rear] = n;
	Q.rear = (Q.rear + 1) % MAXSIZE;
	return OK;
}
Status DeleteQueue(QueueList& Q)
{
	if (Q.rear == Q.front)
	{
		return ERROR;
	}
	int num = Q.base[Q.front];
	Q.front = (Q.front + 1) % MAXSIZE;
	return num;
}
Status GetQueue(QueueList& Q)
{
	if (Q.rear == Q.front)
	{
		return ERROR;
	}
	int num = Q.base[Q.front];
	return num;
}
Status InPut_Num(int& num, QueueList& A, QueueList& B)
{
	cin >> num;
	for (int i = 0; i < num; i++)
	{
		int elem = 0;
		cin >> elem;
		if (elem % 2 == 0)
		{
			EnterQueue(B, elem);
		}
		if (elem % 2 != 0)
		{
			EnterQueue(A, elem);
		}
	}
	return OK;
}
Status InPut_File(QueueList& A, QueueList& B)
{
	fstream file;
	file.open("data.txt");
	if (!file)
	{
		cout << "未找到相关文件" << endl;
		return ERROR;
	}
	bool flag = 1;
	while (!file.eof())
	{
		int num = 0;
		if (flag)
		{
			file >> num;
			flag = 0;
			continue;
		}
		file >> num;
		if (num % 2)
		{
			EnterQueue(A, num);
		}
		else 
		{
			EnterQueue(B, num);
		}
	}
	cout << "输入成功！！！";
	return OK;
}
Status OutPut_file(QueueList& A, QueueList& B)
{
	ofstream out;
	int Queue_num = Queue_length(A)+Queue_length(B);
	out.open("the_out_put_data.txt");
	for (int i = 0; i < Queue_num; i++)
	{
		if (GetQueue(A))
		{
			out << DeleteQueue(A) << " ";
		}
		if (GetQueue(B))
		{
			out << DeleteQueue(B) << " ";
		}
	}
	cout << "存储完毕!!!";
	return OK;
}
int main()
{
	QueueList A, B;
	InitQueue(A);
	InitQueue(B);
	int num = 0;
	//InPut_Num(num, A, B);
	InPut_File(A, B);
	OutPut_file(A, B);
	int cou = 0;
	for (int i = 0; i < num; i++)
	{
		if (GetQueue(A))
		{
			cout << DeleteQueue(A);
			if (cou < num)
			{
				cout << " ";
			}
			cou++;
			cout << DeleteQueue(A);
			if (cou < num)
			{
				cout << " ";
			}
			cou++;
		}
		if (GetQueue(B))
		{
			cout << DeleteQueue(B);
			if (cou < num)
			{
				cout << " ";
			}
			cou++;

		}

	}
	return 0;

}
