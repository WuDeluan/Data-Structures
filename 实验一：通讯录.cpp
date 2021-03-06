/*
设计一个班级同学的通讯录，要求如下：
	通讯录中每个同学的信息包含以下内容：学号（id）、姓名（name）、电话号码（tel）。如果需要更多其他信息，请自行添加。
	程序主菜单包含以下几个功能：
（1）	添加记录：通过键盘输入信息，添加一条通讯录记录。
（2）	删除记录：通过键盘输入学号，删除该学号的记录。
（3）	输出记录：输出通讯录全部记录。
（4）	按姓名查找：通过键盘输入姓名，输出该同学的所有信息。
（5）	保存记录：把通讯录中所有的记录保存到文件中。
（6）	清空记录：删除通讯录中的全部记录，并删除文件。
（7）	退出
提示：
	程序启动时应判断是否存在记录文件，如果存在，则读取每条记录到链表中。
	用户选择并完成主菜单某功能后，除了退出程序，应该返回主菜单。
	添加一条记录时，插入到链表的尾部。
	查找、删除记录时，如果该记录不存在，则应该输出不存在的提示。
	添加记录、删除记录时不需要写文件。
	保存记录时，用覆盖写文件的方法。（或者先删除原文件，再保存全部记录信息）
	各个功能模块写成函数，由主函数调用。
*/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Node; //A storage to store students' Id,name and telephone numbers;
typedef struct Node *PtrToNode; //A pointer with type of Node;
typedef PtrToNode Position;
typedef PtrToNode List;

//Defination of Node struct;
typedef struct Node
{
	char Id[12]; //An array to store student ID;
	char Name[8]; // An array to store student name;
	char Tel[12]; //An array to store student telephone numbers;
	Position Next; //A pointer point to the next Node storage;
};

//Add student's informations into the list;
void Add(List L,const char Id[],const char Name[],const char Tel[])
{
	Position TmpCell, P; //Define a temporary pointer named TmpCell;
	TmpCell = (PtrToNode)malloc(sizeof(Node)); //Creat a storage for TmpCell;
	strcpy(TmpCell->Id, Id); //Copy datas
	strcpy(TmpCell->Name, Name);
	strcpy(TmpCell->Tel, Tel);
	TmpCell->Next = NULL;

	P = L->Next;
	if (P) //Judge whether the first Node of the list is exits;
	{
		while (P->Next)
			P = P->Next;
		P->Next = TmpCell;
	}
	else
		L->Next = TmpCell;
}

//Open the file and read the datas into the list;
//Each line of file is like “16401010101 张三 13600000000”
int Open(List &L)
{
	string s1, s2, s3;
	ifstream file("D:\\a.txt");
	while (!file.eof())
	{
		file >> s1 >> s2 >> s3;
		const char* Id = s1.c_str();
		const char* Name = s2.c_str();
		const char* Tel = s3.c_str();
		if (file.eof())
			break;
		Add(L, Id, Name, Tel);
	}
	file.close();
	return 0;
}

//Delete a student's information by his or her student ID;
int Delete(List L, char Id[])
{
	Position P = L,TmpCell;
	while (P->Next) //Judge whether the list is empty;
	{
		if (strcmp(P->Next->Id, Id) == 0)
		{
			TmpCell = P->Next;
			P->Next = P->Next->Next;
			free(TmpCell);
			return 0; //If successfully deleted ,return 0;
		}
		P = P->Next;
	}
	return -1; //If doesn't delete ,return -1;
}

//Search a student's information by name;
int Search(List L, char Name[])
{
	Position P = L->Next;
	while (P)
	{
		if (strcmp(P->Name, Name) == 0)
		{
			cout << P->Id << " " << P->Name << " " << P->Tel << endl;
			return 0; //If successfully found,return 0;
		}
		P = P->Next;
	}
	return -1; //If doesn't find,return -1;
}

//Print all the datas on the list;
void PrintAll(List L)
{
	Position P;
	for (P = L->Next; P; P = P->Next)
		cout << P->Id << " " << P->Name << " " << P->Tel << endl;
}

//Delete the whole list;
void DeleteAll(List L)
{
	Position P, TmpCell;
	for (P = L; P->Next; ) //Delete each node;
	{
		TmpCell = P->Next;
		P->Next = P->Next->Next;
		free(TmpCell);
	}
	free(L); //Delete the headof the list;
}

//Keep the datas into the file;
int Close(List L)
{
	string s1, s2, s3;
	ofstream file("D:\\a.txt");
	Position P;
	for (P = L->Next; P; P = P->Next) //Read each student's information into file;
	{
		file << P->Id << " " << P->Name << " " << P->Tel << endl;
	}
	file.close();
	rename("D:\\a.txt", "D:\\b.txt");
	return 0;
}

//The interface of the program;
void Menu()
{
	system("cls"); //Clean the interface;
	cout << "1.添加记录" << endl;
	cout << "2.删除记录" << endl;
	cout << "3.输出记录" << endl;
	cout << "4.按姓名查找" << endl;
	cout << "5.保存记录" << endl;
	cout << "6.清空记录" << endl;
	cout << "7.退出" << endl;
}

//The main founction;
int main()
{
	List L = (PtrToNode)malloc(sizeof(Node)); //Creat a storage for head of the list;
	L->Next = NULL; //Initialization of L;
	Open(L); //Read datas into the list;

	char Id[12], Name[8], Tel[12];
    Menu(); //Show the interface;
	while (1)
	{
		int a; //A variable to store the choose of users;
		int result; //A variable to store results of some founctions
		cin >> a; 
		switch (a)
		{
		case 1:cout << "请依次输入学号、姓名、电话号码："; //Add a information into the list;
			cin >> Id >> Name >> Tel;
			Add(L, Id, Name, Tel);
			break;
		case 2:cout << "请输入代删除学生学号："; //Delete a student's information;
			cin >> Id;
			result = Delete(L, Id);
			if (result == 0)
				cout << "删除成功！" << endl;
			else
				cout << "删除失败！" << endl;
			break;
		case 3:PrintAll(L); //Print the whole information;
			break;
		case 4:cout << "请输入代查询学生姓名："; //Search a student's information by name ,
			                                     //print all his or her information
			cin >> Name;
			result = Search(L, Name);
			if (result == -1)
				cout << "没有找到该学生！" << endl;
			break;
		case 5:Close(L); //Read all informations into the file;
			break;
		case 6:DeleteAll(L); //Delete the whole list;
			break;
		case 7:Menu(); //return back,show the interface;
			   break;
		}
	}
	return 0;
}
