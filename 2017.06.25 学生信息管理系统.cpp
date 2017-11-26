#ifndef STUDENT_H
#define STUDENT_H
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

typedef struct _node {
	struct _node *next, *prev;
	double student_id;
	char name[8];
	char gender[6];
	char address[15];
	char tel[12];
	double chinese_score;
	double math_score;
	double english_score;
	double average_score;
	int score_ranking;
	double classmates_score;
	double morality_score;
	double teacher_score;
	double total_score;
	int total_ranking;
}Node;
typedef struct _list {
	Node *head, *tile;
}List;

class System
{
private:
	List list;
public:
	System()
	{
		list.head = NULL;
		list.tile = NULL;
	}

	void Initialize()
	{
		Open();
		Average_sort();
		Total_sort();
		Id_sort();
	}
	//插入链表节点；
	void Add(double student_id, const char* name, const char* gender, const char* address,
		const char* tel, double chinese_score, double math_score, double english_score,
		double average_score, int score_ranking, double classmates_score,
		double morality_score, double teacher_score, double total_score, int total_ranking)
	{
		Node *p = (Node*)malloc(sizeof(Node));
		p->student_id = student_id;
		strcpy(p->name, name);
		strcpy(p->gender, gender);
		strcpy(p->address, address);
		strcpy(p->tel, tel);
		p->chinese_score = chinese_score;
		p->math_score = math_score;
		p->english_score = english_score;
		p->average_score = (chinese_score + math_score + english_score) / 3;
		p->score_ranking = score_ranking;
		p->classmates_score = classmates_score;
		p->morality_score = morality_score;
		p->teacher_score = teacher_score;
		p->total_score = 0.2*(chinese_score + math_score + english_score)
			+ 0.1*classmates_score + 0.1*morality_score + 0.2*teacher_score;
		p->total_ranking = total_ranking;
		p->next = NULL;
		p->prev = NULL;
		Node *last = list.head;
		if (last) {
			while (last->next) {
				last = last->next;
			}
			last->next = p;
			p->prev = last;
			list.tile = p;
		}
		else
		{
			list.head = p;
			list.tile = p;
		}
	}
	//打开数据文件，读取数据，创建链表；
	void Open()
	{
		string s1, s2, s3, s4;
		double student_id;
		double chinese_score;
		double math_score;
		double english_score;
		double average_score;
		int score_ranking;
		double classmates_score;
		double morality_score;
		double teacher_score;
		double total_score;
		int total_ranking;
		ifstream file("D:\\aaa.txt");
		while (!file.eof()) {
			file >> student_id;
			file >> s1;
			const char* name = s1.c_str();
			file >> s2;
			const char* gender = s2.c_str();
			file >> s3;
			const char* address = s3.c_str();
			file >> s4;
			const char* tel = s4.c_str();
			file >> chinese_score;
			file >> math_score;
			file >> english_score;
			file >> average_score;
			file >> score_ranking;
			file >> classmates_score;
			file >> morality_score;
			file >> teacher_score;
			file >> total_score;
			file >> total_ranking;
			if (file.eof())
				break;
			Add(student_id, name, gender, address,
				tel, chinese_score, math_score, english_score,
				average_score, score_ranking, classmates_score,
				morality_score, teacher_score, total_score, total_ranking);
		}
		file.close();
	}
	//按学号排序；
	void Id_sort() {
		Node *pEnd = NULL;
		Node *pTemp;
		Node *p1 = (Node*)malloc(sizeof(Node));
		p1->next = list.head;
		list.head->prev = p1;
		list.head = p1;
		Node *p3 = (Node*)malloc(sizeof(Node));
		p3->prev = list.tile;
		list.tile->next = p3;
		list.tile = p3;
		Node *p2;
		while (pEnd != list.head)
		{
			pTemp = list.head;
			for (p1 = list.head; p1->next->next != list.tile; p1 = p1->next) {
				if (p1->next->student_id > p1->next->next->student_id) {
					p2 = p1->next->next;
					p1->next->next = p2->next;
					p2->next->prev = p1->next;
					p2->next = p1->next;
					p1->next->prev = p2;
					p1->next = p2;
					p2->prev = p1;
					pTemp = p1->next->next;
				}
			}
			pEnd = pTemp;
		}
		p1 = list.head;
		list.head = list.head->next;
		list.head->prev = NULL;
		free(p1);
		p3 = list.tile;
		list.tile = list.tile->prev;
		list.tile->next = NULL;
		free(p3);
		p1 = NULL;
	}
	//按平均成绩排序；
	void Average_sort() {
		Node *pEnd = NULL;
		Node *pTemp;
		Node *p1 = (Node*)malloc(sizeof(Node));
		p1->next = list.head;
		list.head->prev = p1;
		list.head = p1;
		Node *p3 = (Node*)malloc(sizeof(Node));
		p3->prev = list.tile;
		list.tile->next = p3;
		list.tile = p3;
		Node *p2;
		while (pEnd != list.head)
		{
			pTemp = list.head;
			for (p1 = list.head; p1->next->next != list.tile; p1 = p1->next) {
				if (p1->next->average_score < p1->next->next->average_score) {
					p2 = p1->next->next;
					p1->next->next = p2->next;
					p2->next->prev = p1->next;
					p2->next = p1->next;
					p1->next->prev = p2;
					p1->next = p2;
					p2->prev = p1;
					pTemp = p1->next->next;
				}
			}
			pEnd = pTemp;
		}
		p1 = list.head;
		list.head = list.head->next;
		list.head->prev = NULL;
		free(p1);
		p3 = list.tile;
		list.tile = list.tile->prev;
		list.tile->next = NULL;
		free(p3);
		p1 = NULL;
		int i = 1;
		Node *p = NULL;
		for (p = list.head; p; p = p->next) {
			p->score_ranking = i;
			i++;
		}
	}
	//按综合成绩排序；
	void Total_sort() {
		Node *pEnd = NULL;
		Node *pTemp;
		Node *p1 = (Node*)malloc(sizeof(Node));
		p1->next = list.head;
		list.head->prev = p1;
		list.head = p1;
		Node *p3 = (Node*)malloc(sizeof(Node));
		p3->prev = list.tile;
		list.tile->next = p3;
		list.tile = p3;
		Node *p2;
		while (pEnd != list.head)
		{
			pTemp = list.head;
			for (p1 = list.head; p1->next->next != list.tile; p1 = p1->next) {
				if (p1->next->total_score < p1->next->next->total_score) {
					p2 = p1->next->next;
					p1->next->next = p2->next;
					p2->next->prev = p1->next;
					p2->next = p1->next;
					p1->next->prev = p2;
					p1->next = p2;
					p2->prev = p1;
					pTemp = p1->next->next;
				}
			}
			pEnd = pTemp;
		}
		p1 = list.head;
		list.head = list.head->next;
		list.head->prev = NULL;
		free(p1);
		p3 = list.tile;
		list.tile = list.tile->prev;
		list.tile->next = NULL;
		free(p3);
		p1 = NULL;
		int i = 1;
		Node *p = NULL;
		for (p = list.head; p; p = p->next) {
			p->total_ranking = i;
			i++;
		}
	}
	//将数据写入文本文件；
	void Close()
	{
		Id_sort();
		double student_id;
		char name[8];
		char gender[6];
		char address[15];
		char tel[12];
		double chinese_score;
		double math_score;
		double english_score;
		double average_score;
		int score_ranking;
		double classmates_score;
		double morality_score;
		double teacher_score;
		double total_score;
		int total_ranking;
		ofstream file("D:\\222.txt");
		Node *p = NULL;
		for (p = list.head; p; p = p->next) {
			file << p->student_id << " ";
			file << p->name << " ";
			file << p->gender << " ";
			file << p->address << " ";
			file << p->tel << " ";
			file << p->chinese_score << " ";
			file << p->math_score << " ";
			file << p->english_score << " ";
			file << p->average_score << " ";
			file << p->score_ranking << " ";
			file << p->classmates_score << " ";
			file << p->morality_score << " ";
			file << p->teacher_score << " ";
			file << p->total_score << " ";
			file << p->total_ranking << endl;
		}
		file.close();
	}
	//显示所有数据；
	void Print_all()
	{
		system("cls");
		Print_line();
		int i = 0, n;
		Node *p = NULL;
		for (p = list.head; p; p = p->next) {
			cout << "\t\t\t\t" << p->student_id << "\t" << left << setw(6) << p->name << "\t" << p->gender
				<< "\t" << p->address << " \t" << p->tel << "\t" << p->chinese_score << "\t" <<
				p->math_score << "\t" << p->english_score << "\t" << p->average_score << "     " <<
				p->score_ranking << "     " << p->classmates_score << "     " << p->morality_score
				<< "     " << p->teacher_score << "     " << p->total_score << "     " << p->total_ranking
				<< endl;
			i++;
			if (i >= 10) {
				cout << "\t\t\t\t------------------------------------------------------------------------";
				cout << "------------------------------------------------------" << endl;
				cout << "\t\t\t\t\t1.下一页\t\t\t\t\t\t\t\t\t\t\t2.返回" << endl;
				cin >> n;
				switch (n) {
				case 1:system("cls"); Print_line(); i = 0; break;
				case 2:Print_land6(); break;
				}

			}
		}
		cout << "\t\t\t\t------------------------------------------------------------------------";
		cout << "------------------------------------------------------" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t1.返回" << endl;
		cin >> n;
		if (n == 1)
			Print_land6();
	}
	//删除链表节点；
	void Del(Node *q)
	{
		if (q == list.head) {
			list.head = q->next;
			list.head->prev = NULL;
			free(q);
		}
		else if (q == list.tile) {
			list.tile = q->prev;
			list.tile->next = NULL;
			free(q);
		}
		else
		{
			q->next->prev = q->prev;
			q->prev->next = q->next;
			free(q);
		}
	}
	//显示表头（全部信息）；
	void Print_line()
	{
		cout << "\t\t\t\t学生" << "\t" << left << setw(6) << "学生" << "\t" << "学生"
			<< "\t" << "家庭" << "\t" << "   联系" << "\t" << "语文" << " " <<
			"数学" << " " << "英语" << " " << "平均" << " " <<
			"考试" << " " << "同学" << " " << "品德" << " " <<
			"教师" << " " << "综合" << " " << "综合" << endl;
		cout << "\t\t\t\t学号" << "\t" << left << setw(6) << "姓名" << "\t" << "性别"
			<< "\t" << "地址" << "\t" << "   电话" << "\t" << "成绩" << " " <<
			"成绩" << " " << "成绩" << " " << "成绩" << " " <<
			"名次" << " " << "评分" << " " << "成绩" << " " <<
			"评分" << " " << "总分" << " " << "排名 " << endl;
		cout << "\t\t\t\t------------------------------------------------------------------------";
		cout << "------------------------------------------------------" << endl;
	}
	//添加学生
	void Add_student()
	{
		system("cls");
		int m, n;
		cout << " " << endl;
		cout << "\t\t\t\t\t\t\t\t\t请输入要添加的学生数量：";
		cin >> m;
		cout << " " << endl;
		while (m--) {
			cout << "\t\t\t\t\t\t\t\t\t请按顺序输入要添加的学生的信息：" << endl;
			cout << " " << endl;
			cout << "\t\t\t\t\t学生" << "\t" << left << setw(6) << "学生" << "\t" << "学生"
				<< "\t" << "家庭" << "\t" << "   联系" << "\t" << "语文" << " " <<
				"数学" << " " << "英语" << " " << "同学" << " " << "品德" << " " <<
				"教师" << endl;
			cout << "\t\t\t\t\t学号" << "\t" << left << setw(6) << "姓名" << "\t" << "性别"
				<< "\t" << "地址" << "\t" << "   电话" << "\t" << "成绩" << " " <<
				"成绩" << " " << "成绩" << " " << "评分" << " " << "成绩" << " " <<
				"评分" << endl;
			cout << "\t\t\t\t\t-------------------------------------------------------------------------------------------------";
			cout << " " << endl;
			cout << "\t\t\t\t\t";
			string s1, s2, s3, s4;
			double student_id;
			double chinese_score;
			double math_score;
			double english_score;
			double classmates_score;
			double morality_score;
			double teacher_score;
			double average_score = 0;
			double score_ranking = 0;
			double total_score = 0;
			double total_ranking = 0;
			cin >> student_id;
			cin >> s1;
			const char* name = s1.c_str();
			cin >> s2;
			const char* gender = s2.c_str();
			cin >> s3;
			const char* address = s3.c_str();
			cin >> s4;
			const char* tel = s4.c_str();
			cin >> chinese_score;
			cin >> math_score;
			cin >> english_score;
			cin >> classmates_score;
			cin >> morality_score;
			cin >> teacher_score;
			Add(student_id, name, gender, address,
				tel, chinese_score, math_score, english_score,
				average_score, score_ranking, classmates_score,
				morality_score, teacher_score, total_score, total_ranking);
			cout << " " << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t\t添加成功！" << endl;
			cout << " " << endl;
			Average_sort();
			Total_sort();
			Id_sort();
		}
		cout << "\t\t\t\t\t\t\t\t\t请选择操作：1.继续添加    2.返回" << endl;
		cin >> n;
		if (n == 1) {
			system("cls");
			Add_student();
		}
		else if (n == 2)
			Print_land4();
	}
	//删除学生信息；
	void Delete_student()
	{
		system("cls");
		double m, n, i, k;
		cout << " " << endl;
		cout << "\t\t\t\t\t\t\t\t\t请输入要删除的学生数量：";
		cin >> m;
		while (m--) {
			cout << " " << endl;
			cout << "\t\t\t\t\t\t\t\t\t请输入要删除的学生的学号：";
			cin >> n;
			cout << " " << endl;
			Node *p = NULL;
			for (p = list.head, k = 0; p; p = p->next)
			{
				if (p->student_id == n) {
					cout << "\t\t\t\t\t\t\t\t\t确定要删除学号为" << n << "的学生的信息吗?" << endl;
					cout << " " << endl;
					cout << "\t\t\t\t\t\t\t\t\t\t1.确定                  2.取消" << endl;
					cin >> i;
					if (i == 1) {
						Del(p);
						cout << "\t\t\t\t\t\t\t\t\t\t\t删除完成！" << endl;
						k = 1;
						break;
					}
					else if (i == 2) {
						cout << "\t\t\t\t\t\t\t\t\t\t已取消！" << endl;
						k = 1;
					}
				}
			}
			if (k == 0)
				cout << "\t\t\t\t\t\t\t\t\t没有找到学号为" << n << "的学生！" << endl;
		}
		cout << " " << endl;
		cout << "\t\t\t\t\t\t\t\t\t请选择操作：1.继续删除    2.返回" << endl;
		cin >> n;
		if (n == 1) {
			system("cls");
			Delete_student();
		}
		else if (n == 2)
			Print_land4();
	}
	//查询学生信息；
	void Serch_student()
	{
		system("cls");
		double m = 1, n, i, k;
		while (m) {
			cout << " " << endl;
			cout << " " << endl;
			cout << "\t\t\t\t\t\t\t\t\t请输入要查询的学生的学号：";
			cin >> n;
			cout << " " << endl;
			Node *p = NULL;
			for (p = list.head, k = 0; p; p = p->next)
			{
				if (p->student_id == n) {
					Print_line();
					cout << "\t\t\t\t" << p->student_id << "\t" << left << setw(6) << p->name << "\t" << p->gender
						<< "\t" << p->address << " \t" << p->tel << "\t" << p->chinese_score << "\t" <<
						p->math_score << "\t" << p->english_score << "\t" << p->average_score << "     " <<
						p->score_ranking << "     " << p->classmates_score << "     " << p->morality_score
						<< "     " << p->teacher_score << "     " << p->total_score << "     " << p->total_ranking
						<< endl;
					k = 1;
				}
			}
			if (k == 0) {
				cout << " " << endl;
				cout << "\t\t\t\t\t\t\t\t\t 没有找到学号为" << n << "的学生！" << endl;
			}
			cout << " " << endl;
			cout << "\t\t\t\t\t\t\t\t  请选择后续操作： 1.继续查询   2.返回" << endl;
			cin >> i;
			if (i == 1) {
				Serch_student();
			}
			else  if (i == 2) {
				m = 0;
				Print_land4();
			}
		}
	}
	//修改学生信息；
	void Revise_student()
	{
		system("cls");
		double m, n, i, k, score;
		int a;
		string s;
		const char* massage;
		cout << " " << endl;
		cout << "\t\t\t\t\t\t\t\t请输入要修改的学生数量：";
		cin >> m;
		while (m--) {
			cout << " " << endl;
			cout << "\t\t\t\t\t\t\t\t请输入要修改的学生的学号：";
			cin >> n;
			Node *p = NULL;
			for (p = list.head, k = 0; p; p = p->next)
			{
				if (p->student_id == n) {
					cout << " " << endl;
					cout << "\t\t\t\t\t\t\t\t确定要修改学号为" << n << "的学生的信息吗?" << endl;
					cout << " " << endl;
					cout << "\t\t\t\t\t\t\t\t\t1.确定           2.取消" << endl;
					cin >> i;
					if (i == 1)
					{
						a = Print_rev();
						cout << "\t\t\t\t\t\t\t\t\t请输入更改后的内容：";
						if (a <= 4) {
							cin >> s;
							massage = s.c_str();
						}
						else
							cin >> score;
						switch (a) {
						case 1:strcpy(p->name, massage); break;
						case 2:strcpy(p->gender, massage); break;
						case 3:strcpy(p->address, massage); break;
						case 4:strcpy(p->tel, massage); break;
						case 5:p->chinese_score = score; break;
						case 6:p->math_score = score; break;
						case 7:p->english_score = score; break;
						case 8:p->classmates_score = score; break;
						case 9:p->morality_score = score; break;
						case 10:p->teacher_score = score; break;
						}
						cout << " " << endl;
						cout << "\t\t\t\t\t\t\t\t\t\t修改成功！" << endl;
						k = 1;
						break;
					}
					else if (i == 2) {
						cout << "\t\t\t\t\t\t\t\t\t\t已取消！" << endl;
						k = 1;
					}
				}
			}
			if (k == 0) {
				cout << " " << endl;
				cout << "\t\t\t\t\t\t\t\t没有找到学号为" << n << "的学生！" << endl;
			}
		}
		cout << " " << endl;
		cout << "\t\t\t\t\t\t\t\t请选择操作：1.继续修改    2.返回" << endl;
		cin >> n;
		if (n == 1) {
			system("cls");
			Revise_student();
		}
		else if (n == 2)
			Print_land4();
	}
	//用于修改的界面；
	int Print_rev()
	{
		int n;
		cout << "\t\t\t\t\t\t\t\t\t请输入要更改的选项：" << endl;
		cout << " " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t1. 学生姓名" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t2. 学生性别" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t3. 家庭住址" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t4. 联系电话" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t5. 语文成绩" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t6. 数学成绩" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t7. 英语成绩" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t8. 同学评分" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t9. 品德成绩" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t10. 教师评分" << endl;
		cout << " " << endl;
		cin >> n;
		switch (n) {
		case 1:return 1;
		case 2:return 2;
		case 3:return 3;
		case 4:return 4;
		case 5:return 5;
		case 6:return 6;
		case 7:return 7;
		case 8:return 8;
		case 9:return 9;
		case 10:return 10;
		}
	}
	//显示表头（个人信息）；
	void Print_massage()
	{
		cout << "\t\t\t\t\t\t\t\t学生" << "\t" << left << setw(6) << "学生" << "\t" << "学生"
			<< "\t" << "家庭" << "\t" << "   联系" << endl;
		cout << "\t\t\t\t\t\t\t\t学号" << "\t" << left << setw(6) << "姓名" << "\t" << "性别"
			<< "\t" << "地址" << "\t" << "   电话" << endl;
		cout << "\t\t\t\t\t\t\t\t----------------------------------------------------" << endl;
	}
	//显示表头（成绩信息）；
	void Print_score()
	{
		cout << "\t\t\t\t\t学生" << "\t" << left << setw(6) << "学生" << "\t"
			<< "语文" << " " << "数学" << " " << "英语" << " " << "平均" << " " <<
			"考试" << " " << "同学" << " " << "品德" << " " <<
			"教师" << " " << "综合" << " " << "综合" << endl;
		cout << "\t\t\t\t\t学号" << "\t" << left << setw(6) << "姓名" << "\t" <<
			"成绩" << " " << "成绩" << " " << "成绩" << " " << "成绩" << " " <<
			"名次" << " " << "评分" << " " << "成绩" << " " <<
			"评分" << " " << "总分" << " " << "排名 " << endl;
		cout << "\t\t\t\t\t-----------------------------------------------------";
		cout << "------------------------------------------" << endl;
	}
	//登录选项界面；
	void Print_land1()
	{
		system("cls");
		cout << " " << endl;
		cout << " " << endl;
		cout << " " << endl;
		cout << " " << endl;
		cout << "\t\t\t\t\t\t\t\t*************** 学生综合测评系统 **************" << endl;
		cout << " " << endl;
		cout << " " << endl;
		cout << " " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t请选择登录方式" << endl;
		cout << " " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t1. 学生帐号登录                                  " << endl;
		cout << " " << endl;
		cout << " " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t2. 管理员帐号登录                                 " << endl;
		cout << " " << endl;
		cout << " " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t3. 关闭" << endl;
		cout << " " << endl;
		int a;
		double b;
		cin >> a;
		switch (a) {
		case 1:b = Print_land5(); Print_land3(b); break;
		case 2:Print_land2(); Print_land4(); break;
		case 3:break;
		}
	}
	//管理员账号密码输入界面；
	void Print_land2()
	{
		double k = 0, c;
		string a, b;
		Node *p = NULL;
		while (k == 0) {
			Print_land7();
			cin >> a;
			if (a == "aaa")
				k = 1;
			if (k == 0) {
				cout << " " << endl;
				cout << "\t\t\t\t\t\t\t\t\t   账号不存在，请重新输入！" << endl;
				cout << " " << endl;
				cout << "\t\t\t\t\t\t\t\t\t   请按1重新输入" << endl;
				cin >> c;
			}
		}
		k = 0;
		while (k == 0) {
			Print_land7();
			cout << a << endl;
			cout << " " << endl;
			cout << "\t\t\t\t\t\t\t\t\t   密码：";
			cin >> b;
			if (b == "111")
				k = 1;
			if (k == 0) {
				cout << " " << endl;
				cout << "\t\t\t\t\t\t\t\t\t   密码不正确，请重新输入！" << endl;
				cout << " " << endl;
				cout << "\t\t\t\t\t\t\t\t\t   请按1重新输入" << endl;
				cin >> c;
			}
		}
	}
	//学生账号登录界面；
	void Print_land3(double b)
	{
		system("cls");
		cout << " " << endl;
		cout << " " << endl;
		cout << " " << endl;
		cout << "\t\t\t\t\t\t\t\t**********欢迎登陆学生综合测评系统**********" << endl;
		cout << " " << endl;
		cout << " " << endl;
		cout << " " << endl;
		cout << "\t\t\t\t\t\t\t\t\t 请根据下列编号选择相应操作                        " << endl;
		cout << "\t\t\t\t\t\t\t**********************************************************************" << endl;
		cout << " " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t1. 查看个人成绩信息" << endl;
		cout << " " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t2. 查看个人身份信息" << endl;
		cout << " " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t3. 查看个人全部信息" << endl;
		cout << " " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t4. 退出登录" << endl;
		cout << " " << endl;
		int a;
		cin >> a;
		switch (a) {
		case 1:Show_score(b); break;
		case 2:Show_massage(b); break;
		case 3:Show_all(b); break;
		case 4:Print_land1(); break;
		}
	}
	//管理员账号登录界面；
	void Print_land4()
	{
		system("cls");
		cout << " " << endl;
		cout << " " << endl;
		cout << " " << endl;
		cout << "\t\t\t\t\t\t\t\t  *********欢迎登陆学生综合测评系统*********" << endl;
		cout << " " << endl;
		cout << " " << endl;
		cout << " " << endl;
		cout << "\t\t\t\t\t\t\t\t\t  请根据下列编号选择相应操作" << endl;
		cout << "\t\t\t\t\t\t\t\t************************************************************" << endl;
		cout << " " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t1. 查看指定学生的信息" << endl;
		cout << " " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t2. 查看全部学生的信息" << endl;
		cout << " " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t3. 添加指定学生的信息" << endl;
		cout << " " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t4. 修改指定学生的信息" << endl;
		cout << " " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t5. 删除指定学生的信息" << endl;
		cout << " " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t6. 退出登录" << endl;
		cout << " " << endl;
		int a;
		cin >> a;
		switch (a)
		{
		case 1:Serch_student(); break;
		case 2:Print_land6(); break;
		case 3:Add_student(); break;
		case 4:Revise_student(); break;
		case 5:Delete_student(); break;
		case 6:Print_land1(); break;
		}

	}
	//学生账号密码输入界面；
	double Print_land5()
	{
		double a, b, c, k = 0;
		Node *p = NULL;
		while (k == 0) {
			Print_land7();
			cin >> a;
			for (p = list.head, k = 0; p; p = p->next) {
				if (p->student_id == a)
					k = 1;
			}
			if (k == 0) {
				cout << " " << endl;
				cout << "\t\t\t\t\t\t\t\t\t   账号不存在，请重新输入！" << endl;
				cout << " " << endl;
				cout << "\t\t\t\t\t\t\t\t\t   请按1重新输入" << endl;
				cin >> c;
			}
		}
		k = 0;
		while (k == 0) {
			Print_land7();
			cout << a << endl;
			cout << " " << endl;
			cout << "\t\t\t\t\t\t\t\t\t   密码：";
			cin >> b;
			for (p = list.head, k = 0; p; p = p->next) {
				if (p->student_id == b)
					k = 1;
			}
			if (k == 0) {
				cout << " " << endl;
				cout << "\t\t\t\t\t\t\t\t\t   密码不正确，请重新输入！" << endl;
				cout << " " << endl;
				cout << "\t\t\t\t\t\t\t\t\t   请按1重新输入" << endl;
				cin >> c;
			}
		}
		return a;
	}
	//账号密码输入界面；
	void Print_land7()
	{
		system("cls");
		cout << " " << endl;
		cout << " " << endl;
		cout << " " << endl;
		cout << " " << endl;
		cout << "\t\t\t\t\t\t\t\t***************学生综合测评系统**************" << endl;
		cout << " " << endl;
		cout << " " << endl;
		cout << " " << endl;
		cout << "\t\t\t\t\t\t\t\t\t   请输入账号及密码" << endl;
		cout << " " << endl;
		cout << "\t\t\t\t\t\t\t\t\t   账号：";
	}
	//管理员界面（成绩查询）；
	void Print_land6()
	{
		system("cls");
		cout << " " << endl;
		cout << "\t\t\t\t\t\t\t\t\t   请根据下列编号选择相应操作" << endl;
		cout << "\t\t\t\t\t\t\t\t ************************************************************" << endl;
		cout << " " << endl;
		cout << " " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t1. 查看全部学生信息" << endl;
		cout << " " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t2. 查看全部学生身份信息" << endl;
		cout << " " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t3. 全部成绩（按平均成绩降序）" << endl;
		cout << " " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t4. 全部成绩（按平均成绩升序）" << endl;
		cout << " " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t5. 全部成绩（按综合成绩降序）" << endl;
		cout << " " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t6. 全部成绩（按综合成绩升序）" << endl;
		cout << " " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t7. 返回" << endl;
		cout << " " << endl;
		int a;
		cin >> a;
		switch (a) {
		case 1:Print_all(); break;
		case 2:Show1(); break;
		case 3:Show2(); break;
		case 4:Show3(); break;
		case 5:Show4(); break;
		case 6:Show5(); break;
		case 7:Print_land4(); break;
		}
	}
	//展示学生个人成绩；
	void Show_score(double b)
	{
		system("cls");
		cout << " " << endl;
		Print_score();
		Node *p = NULL;
		for (p = list.head; p; p = p->next)
		{
			if (p->student_id == b) {
				cout << "\t\t\t\t\t" << p->student_id << "\t" << left << setw(6) << p->name << "\t"
					<< p->chinese_score << "\t" << p->math_score << "\t" << p->english_score << "     "
					<< p->average_score << "     " << p->score_ranking << "     " << p->classmates_score <<
					"     " << p->morality_score << "     " << p->teacher_score << "     " << p->total_score <<
					"     " << p->total_ranking << endl;
			}
		}
		cout << " " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t1.返回" << endl;
		int a;
		cin >> a;
		if (a == 1)
			Print_land3(b);
	}
	//展示学生个人信息；
	void Show_massage(double b)
	{
		system("cls");
		cout << " " << endl;
		Print_massage();
		Node *p = NULL;
		for (p = list.head; p; p = p->next)
		{
			if (p->student_id == b) {
				cout << "\t\t\t\t\t\t\t\t" << p->student_id << "\t" << left << setw(6) << p->name << "\t" << p->gender
					<< "\t" << p->address << " \t" << p->tel << endl;
			}
		}
		cout << " " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t1.返回" << endl;
		int a;
		cin >> a;
		if (a == 1)
			Print_land3(b);
	}
	//展示学生全部信息；
	void Show_all(double b)
	{
		system("cls");
		cout << " " << endl;
		Print_line();
		Node *p = NULL;
		for (p = list.head; p; p = p->next)
		{
			if (p->student_id == b) {
				cout << "\t\t\t\t" << p->student_id << "\t" << left << setw(6) << p->name << "\t" << p->gender
					<< "\t" << p->address << " \t" << p->tel << "\t" << p->chinese_score << "\t" <<
					p->math_score << "\t" << p->english_score << "\t" << p->average_score << "     " <<
					p->score_ranking << "     " << p->classmates_score << "     " << p->morality_score
					<< "     " << p->teacher_score << "     " << p->total_score << "     " << p->total_ranking
					<< endl;
			}
		}
		cout << " " << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t  1.返回" << endl;
		int a;
		cin >> a;
		if (a == 1)
			Print_land3(b);
	}
	//展示全部个人信息；
	void Show1()
	{
		system("cls");
		Print_massage();
		int i = 0, n;
		Node *p = NULL;
		for (p = list.head; p; p = p->next) {
			cout << "\t\t\t\t\t\t\t\t" << p->student_id << "\t" << left << setw(6) << p->name << "\t" << p->gender
				<< "\t" << p->address << " \t" << p->tel << endl;
			i++;
			if (i >= 10) {
				cout << "\t\t\t\t\t\t\t\t----------------------------------------------------" << endl;
				cout << "\t\t\t\t\t\t\t\t1.下一页\t\t\t\t 2.返回" << endl;
				cin >> n;
				switch (n) {
				case 1:system("cls"); Print_massage(); i = 0; break;
				case 2:Print_land6(); break;
				}

			}
		}
		cout << "\t\t\t\t\t\t\t\t----------------------------------------------------" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t1.返回" << endl;
		cin >> n;
		if (n == 1)
			Print_land6();
	}
	//展示全部成绩（按平均成绩升序）；
	void Show2()
	{
		system("cls");
		cout << " " << endl;
		Print_score();
		int i = 0, n;
		Average_sort();
		Node *p = NULL;
		for (p = list.tile; p; p = p->prev)
		{
			cout << "\t\t\t\t\t" << p->student_id << "\t" << left << setw(6) << p->name << "\t"
				<< p->chinese_score << "\t" << p->math_score << "\t" << p->english_score << "     "
				<< p->average_score << "     " << p->score_ranking << "     " << p->classmates_score <<
				"     " << p->morality_score << "     " << p->teacher_score << "     " << p->total_score <<
				"     " << p->total_ranking << endl;
			i++;
			if (i >= 10) {
				cout << "\t\t\t\t\t-----------------------------------------------------";
				cout << "------------------------------------------" << endl;
				cout << "\t\t\t\t\t\t\t1.下一页\t\t\t\t\t\t2.返回" << endl;
				cin >> n;
				switch (n) {
				case 1:system("cls"); Print_score(); i = 0; break;
				case 2:Print_land6(); break;
				}

			}
		}
		cout << "\t\t\t\t\t-----------------------------------------------------";
		cout << "------------------------------------------" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t1.返回" << endl;
		cin >> n;
		if (n == 1)
			Print_land6();
	}
	//展示全部成绩（按平均成绩降序）；
	void Show3()
	{
		system("cls");
		cout << " " << endl;
		Print_score();
		int i = 0, n;
		Average_sort();
		Node *p = NULL;
		for (p = list.head; p; p = p->next)
		{
			cout << "\t\t\t\t\t" << p->student_id << "\t" << left << setw(6) << p->name << "\t"
				<< p->chinese_score << "\t" << p->math_score << "\t" << p->english_score << "     "
				<< p->average_score << "     " << p->score_ranking << "     " << p->classmates_score <<
				"     " << p->morality_score << "     " << p->teacher_score << "     " << p->total_score <<
				"     " << p->total_ranking << endl;
			i++;
			if (i >= 10) {
				cout << "\t\t\t\t\t-----------------------------------------------------";
				cout << "------------------------------------------" << endl;
				cout << "\t\t\t\t\t\t\t1.下一页\t\t\t\t\t\t2.返回" << endl;
				cin >> n;
				switch (n) {
				case 1:system("cls"); Print_score(); i = 0; break;
				case 2:Print_land6(); break;
				}

			}
		}
		cout << "\t\t\t\t\t-----------------------------------------------------";
		cout << "------------------------------------------" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t1.返回" << endl;
		cin >> n;
		if (n == 1)
			Print_land6();;
	}
	//展示全部成绩（按综合成绩升序）；
	void Show4()
	{
		system("cls");
		cout << " " << endl;
		Print_score();
		int i = 0, n;
		Total_sort();
		Node *p = NULL;
		for (p = list.tile; p; p = p->prev)
		{
			cout << "\t\t\t\t\t" << p->student_id << "\t" << left << setw(6) << p->name << "\t"
				<< p->chinese_score << "\t" << p->math_score << "\t" << p->english_score << "     "
				<< p->average_score << "     " << p->score_ranking << "     " << p->classmates_score <<
				"     " << p->morality_score << "     " << p->teacher_score << "     " << p->total_score <<
				"     " << p->total_ranking << endl;
			i++;
			if (i >= 10) {
				cout << "\t\t\t\t\t-----------------------------------------------------";
				cout << "------------------------------------------" << endl;
				cout << "\t\t\t\t\t\t\t1.下一页\t\t\t\t\t\t2.返回" << endl;
				cin >> n;
				switch (n) {
				case 1:system("cls"); Print_score(); i = 0; break;
				case 2:Print_land6(); break;
				}

			}
		}
		cout << "\t\t\t\t\t-----------------------------------------------------";
		cout << "------------------------------------------" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t1.返回" << endl;
		cin >> n;
		if (n == 1)
			Print_land6();
	}
	//展示全部成绩（按综合成绩降序）；
	void Show5()
	{
		system("cls");
		cout << " " << endl;
		Print_score();
		int i = 0, n;
		Total_sort();
		Node *p = NULL;
		for (p = list.head; p; p = p->next)
		{
			cout << "\t\t\t\t\t" << p->student_id << "\t" << left << setw(6) << p->name << "\t"
				<< p->chinese_score << "\t" << p->math_score << "\t" << p->english_score << "     "
				<< p->average_score << "     " << p->score_ranking << "     " << p->classmates_score <<
				"     " << p->morality_score << "     " << p->teacher_score << "     " << p->total_score <<
				"     " << p->total_ranking << endl;
			i++;
			if (i >= 10) {
				cout << "\t\t\t\t\t-----------------------------------------------------";
				cout << "------------------------------------------" << endl;
				cout << "\t\t\t\t\t\t\t1.下一页\t\t\t\t\t\t2.返回" << endl;
				cin >> n;
				switch (n) {
				case 1:system("cls"); Print_score(); i = 0; break;
				case 2:Print_land6(); break;
				}

			}
		}
		cout << "\t\t\t\t\t-----------------------------------------------------";
		cout << "------------------------------------------" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t1.返回" << endl;
		cin >> n;
		if (n == 1)
			Print_land6();
	}
};
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////
#include "System.h"
using namespace std;

int main()
{
	System system;
	system.Initialize();
	system.Print_land1();
	system.Close();
}
