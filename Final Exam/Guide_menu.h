#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <stdlib.h>
#include "Guide_class.h"

using namespace std;

void MenuC(Guide G);
void MenuE(Guide G);
void SchoolIntroductionC(Guide G);
void SchoolIntroductionE(Guide G);
void SpotsListC(Guide G);
void MenageInfomation(Guide G);
void MenageInfomation2(Guide G);

void MenuC(Guide G)
{
	system("Cls");
	cout << "***************************************************************************" << endl;
	cout << "*                                                                         *" << endl;
	cout << "*                    欢迎来到宁波工程学院校园导游系统                     *" << endl;
	cout << "*                                                                         *" << endl;
	cout << "*                              1.宁工简介                                 *" << endl;
	cout << "*                                                                         *" << endl;
	cout << "*                              2.景点展示                                 *" << endl;
	cout << "*                                                                         *" << endl;
	cout << "*                              3.景点查询                                 *" << endl;
	cout << "*                                                                         *" << endl;
	cout << "*                              4.路径查询                                 *" << endl;
	cout << "*                                                                         *" << endl;
	cout << "*                              5.景点管理                                 *" << endl;
	cout << "*                                                                         *" << endl;
	cout << "*                                                                         *" << endl;
	cout << "*                                                                         *" << endl;
	cout << "*                                                            6.语言切换   *" << endl;
	cout << "***************************************************************************" << endl;
	int a;
	cin >> a;
	switch (a)
	{
	case 1:SchoolIntroductionC(G); break;
	case 2:SpotsListC(G); break;
	case 5:MenageInfomation(G); break;
	case 6:MenuE(G); break;
	}
}

void MenuE(Guide G)
{
	system("Cls");
	cout << "***************************************************************************" << endl;
	cout << "*                                                                         *" << endl;
	cout << "*   Welcome to NingBo University Of Technology School Tour Guide System   *" << endl;
	cout << "*                                                                         *" << endl;
	cout << "*                         1.School Introduction                           *" << endl;
	cout << "*                                                                         *" << endl;
	cout << "*                         2.Feature Spots List                            *" << endl;
	cout << "*                                                                         *" << endl;
	cout << "*                         3.Feature Spots Searching                       *" << endl;
	cout << "*                                                                         *" << endl;
	cout << "*                         4.Route Searching                               *" << endl;
	cout << "*                                                                         *" << endl;
	cout << "*                         5.Fearure Spots menagement                      *" << endl;
	cout << "*                                                                         *" << endl;
	cout << "*                                                                         *" << endl;
	cout << "*                                                                         *" << endl;
	cout << "*                                                   6.Language Changing   *" << endl;
	cout << "***************************************************************************" << endl;
	int a;
	cin >> a;
	switch (a)
	{
	case 1:SchoolIntroductionE(G); break;

	case 6:MenuC(G); break;
	}
}

void SchoolIntroductionC(Guide G)
{
	system("Cls");
	cout << "***************************************************************************" << endl;
	cout << "*                                                                         *" << endl;
	cout << "*                         宁波工程学院简介                                *" << endl;
	cout << "*                                                                         *" << endl;
	cout << "*                                                                         *" << endl;
	cout << "*       宁波工程学院是由宁波市政府创办的全日制普通本科院校，创建于1983年。*" << endl;
	cout << "*     2004养年5月由专科升格更名为宁波工程学院。2010年被教育部列入卓越工   *" << endl;
	cout << "*     程师教育培计划首批61所实施高校。官网2017年11月显示， 学校占地面积   *" << endl;
	cout << "*     1800亩，分为风华校区、翠柏校区和杭州湾校区。现有12个二级学院，40个  *" << endl;
	cout << "*     本科专业；专任教师769人，其中具有正高职称67人，副高职称226人，具有  *" << endl;
	cout << "*     博士学位275人；在校全日制本科学生13296人。                          *" << endl;
	cout << "*                                                                         *" << endl;
	cout << "*                                                                         *" << endl;
	cout << "*                                                                1.返回   *" << endl;
	cout << "***************************************************************************" << endl;
	int a;
	while (cin >> a)
	{
		if (a == 1)
		{
			MenuC(G);
			break;
		}
		else
			cout << "请输入正确指令!" << endl;
	}
}

void SchoolIntroductionE(Guide G)
{
	system("Cls");
	cout << "***************************************************************************" << endl;
	cout << "*                                                                         *" << endl;
	cout << "*            NingBo University Of Technology Introduction                 *" << endl;
	cout << "*                                                                         *" << endl;
	cout << "*                                                                         *" << endl;
	cout << "*        Ningbo Institute of Technology is a full-time general under-     *" << endl;
	cout << "*     graduate college founded. By the Ningbo Municipal Government,       *" << endl;
	cout << "*     founded in 1983. May 2004 by the college upgraded its name to       *" << endl;
	cout << "*     Ningbo Institute of Technology. In 2010, the Ministry of Education  *" << endl;
	cout << "*     was included in the first batch of 61 implementing colleges and     *" << endl;
	cout << "*     universities in the Excellent Engineer Education and Training       *" << endl;
	cout << "*     Program.                                                            *" << endl;
	cout << "*                                                                         *" << endl;
	cout << "*                                                          1.return back  *" << endl;
	cout << "***************************************************************************" << endl;
	int a;
	while (cin >> a)
	{
		if (a == 1)
		{
			MenuE(G);
			break;
		}
		else
			cout << "Please enter correct order " << endl;
	}
}

void Tital1()
{
	system("Cls");
	cout << "******************************************************************************" << endl;
	cout << endl;
	cout << "\t\t\t\t宁波工程学院景点展示" << endl;
	cout << endl;
}

void SpotsListC(Guide G)
{
	Tital1();
	int i, j = 0, a; char *p;
	MGraph Graph = G.getGraph();
	for (i = 0; i < Graph->Nv; i++)
	{
		if (strcmp(Graph->Data[i].Name, "Delete") == 0)
			continue;
		j++;
		cout << "\t\t*" << Graph->Data[i].Name << ":\n" << endl;
		cout << "\t\t";
		for (p = Graph->Data[i].Introduction; *p != '\0'; p++)
		{
			if (*p == '#')
			{
				cout << endl;
				cout << "\t\t";
				p++;
			}
			cout << *p;
		}
		cout << "\n\t\t----------------------------------------------------" << endl;
		cout << endl;

		if (j % 3 == 0 || i == Graph->Nv - 1)
		{
			cout << "\t\t1.上一页\t\t\t\t   2.下一页" << endl;
			cout << "******************************************************************************" << endl;
			while (cin >> a)
			{
				if (a == 2)
				{
					if (i == Graph->Nv - 1)
						cout << "已经是最后一页！" << endl;
					else
					{
						Tital1();
						break;
					}
				}
				else if (a == 1)
				{
					if (i == 2)
						cout << "已经是第一页！" << endl;
					else
					{
						i = i - j - 3;
						Tital1();
						break;
					}
				}
				else
					cout << "请输入正确指令!" << endl;
			}
			j = 0;
		}
	}
}

void MenageInfomation(Guide G)
{
	system("Cls");
	cout << "***************************************************************************" << endl;
	cout << "                                                                           " << endl;
	cout << "                     宁波工程学院校园导游系统景点管理                      " << endl;
	cout << endl;
	cout << "\t\t\t  此功能需要管理员权限！" << "\n" << endl;
	cout << "\t\t\t 请问是否具有管理员权限" << "\n" << endl;
	cout << "\t\t\t  1.是\t\t 2.否" << endl;
	int a;
	while (cin >> a)
	{
		if (a == 2)
			MenuC(G);
		else if (a == 1)
		{
			cout << "\t\t\t  请输入密码：";
			while (cin >> a)
			{
				if (a == 321)
					break;
				if (a == 1)
					MenuC(G);
				cout << "\t\t\t密码错误，请重试！" << endl;
				cout << "\t\t\t请输入密码：";
			}
			MenageInfomation2(G);
		}
		else
			cout << "\t\t\t请输入正确指令！" << endl;
	}
}

void MenageInfomation2(Guide G)
{
	system("Cls");
	cout << "\n\n\n\t\t\t请选择以下功能:" << "\n" << endl;
	cout << "\t\t\t1.增加景点" << "\n" << endl;
	cout << "\t\t\t2.删除景点" << "\n" << endl;
	cout << "\t\t\t3.更新信息" << endl;
	int a;
	while (cin >> a)
	{
		if (a == 1)
		{
			if (G.Add() == -1)
				cout << "\t\t\t添加失败！" << "\n" << endl;
			else
				cout << "\t\t\t添加成功！" << "\n" << endl;
			break;
		}
		else if (a == 2)
		{
			if (G.Delete() == -1)
				cout << "\t\t\t该景点不存在！" << "\n" << endl;
			else
				cout << "\t\t\t删除成功！" << "\n" << endl;
			break;
		}
		else if (a == 3)
		{
			G.SaveFile();
			cout << "\t\t\t信息已更新！" << "\n" << endl;
			break;
		}
		else
			cout << "\t\t\t 请输入正确指令！" << endl;;
	}
	cout << "\t\t\t1.继续管理\t\t2.退出" << endl;
	while (cin >> a)
	{
		if (a == 1)
			MenageInfomation2(G);
		else if (a == 2)
			break;
		else
			cout << "请输入正确的指令！" << endl;
	}
	MenuC(G);
}
#endif
