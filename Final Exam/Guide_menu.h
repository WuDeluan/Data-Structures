#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <stdlib.h>
#include "Guide_class.h"

using namespace std;

void Menu(Guide G);
void SchoolIntroduction(Guide G);
void ShowAPoint(MGraph Graph, int i);
void SpotsList(Guide G);
void Search(Guide G);
void PathSearch(Guide G);
void MenageInfomation(Guide G);
void MenageInfomation2(Guide G);
//主菜单
void Menu(Guide G)
{
	system("Cls");
	cout << "***************************************************************************" << endl;
	cout << "*                                                                         *" << endl;
	cout << "*                    欢迎来到宁波工程学院校园导游系统                     *" << endl;
	cout << "*                                                                         *" << endl;
	cout << "*                                                                         *" << endl;
	cout << "*                              1.宁工简介                                 *" << endl;
	cout << "*                                                                         *" << endl;
	cout << "*                              2.景点展示                                 *" << endl;
	cout << "*                                                                         *" << endl;
	cout << "*                              3.景点查询                                 *" << endl;
	cout << "*                                                                         *" << endl;
	cout << "*                              4.线路查询                                 *" << endl;
	cout << "*                                                                         *" << endl;
	cout << "*                              5.景点管理                                 *" << endl;
	cout << "*                                                                         *" << endl;
	cout << "*                                                                         *" << endl;
	cout << "*                                                                         *" << endl;
	cout << "***************************************************************************" << endl;
	int a;
	while (cin >> a)
		switch (a)
		{
		case 1:SchoolIntroduction(G); break;
		case 2:SpotsList(G); break;
		case 3:Search(G); break;
		case 4:PathSearch(G); break;
		case 5:MenageInfomation(G); break;
		default:cout << "请输入正确指令！" << endl;
		}
}
//学校简介
void SchoolIntroduction(Guide G)
{
	system("Cls");
	cout << "***************************************************************************" << endl;
	cout << "*                                                                         *" << endl;
	cout << "*                           宁波工程学院简介                              *" << endl;
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
			Menu(G);
			break;
		}
		else
			cout << "请输入正确指令!" << endl;
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
//展示某一景点
void ShowAPoint(MGraph Graph, int i)
{
	char *p;
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
}
//展示所有景点
void SpotsList(Guide G)
{
	Tital1();
	int i, j = 0, a; char *p;
	MGraph Graph = G.getGraph();
	for (i = 0; i < Graph->Nv; i++)
	{
		if (strcmp(Graph->Data[i].Name, "Delete") == 0)
			continue;
		j++;
		ShowAPoint(Graph, i);
		if (j % 3 == 0 || i == Graph->Nv - 1)
		{
			cout << "\t\t1.上一页\t\t2.下一页\t\t3.退出" << endl;
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
				else if (a == 3)
				{
					Menu(G);
					break;
				}
				else
					cout << "请输入正确指令!" << endl;
			}
			j = 0;
		}
	}
}
//查找景点
void Search(Guide G)
{
	system("Cls");
	cout << "***************************************************************************" << endl;
	cout << "                                                                           " << endl;
	cout << "                       宁波工程学院校园景点查询                            " << endl;
	cout << endl;
	cout << "\t\t\t请输入查询景点名称：";
	char Name[200];
	Vertex V;
	MGraph Graph = G.getGraph();
	cin >> Name;
	cout << endl;
	V = G.Search(Name);
	if (V == -1)
		cout << "\t\t\t  该景点不存在！" << "\n" << endl;
	else
		ShowAPoint(Graph, V);
	cout << "\t\t\t 1.继续查询\t\t2.退出查询" << endl;

	int a;
	while (cin >> a)
	{
		if (a == 2)
			Menu(G);
		else if (a == 1)
			Search(G);
		else
			cout << "\t\t\t请输入正确指令！" << endl;
	}
}
//线路查询
void PathSearch(Guide G)
{
	Vertex Start, End, Mark;
	MGraph Graph = G.getGraph();
	char Name[200]; int a;
	system("Cls");
	cout << "******************************************************************************" << endl;
	cout << endl;
	cout << "\t\t\t  宁波工程学院景点线路查询" << endl;
	cout << endl;
	cout << "\t\t\t请输入您的当前位置：";
	cin >> Name;
	Start = G.Search(Name);
	cout << "\t\t\t请输入您想要到达的景点：";
	cin >> Name;
	End = G.Search(Name);
	if (Start != -1 && End != -1)
	{
		cout << "\n\t\t\t请选择线路模式：" << endl;
		cout << "\t\t\t1.最短线路\n\t\t\t2.包含某一景点的路径\n\t\t\t3.所有路径" << endl;
		while (cin >> a)
		{
			if (a == 1)
			{
				G.MinDist(Start, End);
				break;
			}
			else if (a == 2)
			{
				cout << "\t\t\t请输入需要经过的景点：";
				cin >> Name;
				Mark = G.Search(Name);
				G.AllRoad(Start, Graph, End, Mark);
				break;
			}
			else if (a == 3)
			{
				G.AllRoad(Start, Graph, End, -1);
				break;
			}
			else
				cout << "请输入正确的指令！" << endl;
		}
	}
	else
		cout << "\t\t\t请输入正确地址！" << endl;
	cout << "\n\t\t\t1.继续查询\t\t2.退出" << endl;
	while (cin >> a)
	{
		if (a == 1)
			PathSearch(G);
		else if (a == 2)
			Menu(G);
		else
			cout << "请输入正确的指令！" << endl;
	}
}
//管理景点信息
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
			Menu(G);
		else if (a == 1)
		{
			cout << "\t\t\t  请输入密码：";
			while (cin >> a)
			{
				if (a == 321)
					break;
				if (a == 1)
					Menu(G);
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
	cout << "\n\n\t\t\t请选择以下功能:" << "\n" << endl;
	cout << "\t\t1.增加景点\t\t2.删除景点" << "\n" << endl;
	cout << "\t\t3.增加道路\t\t4.删除道路" << "\n" << endl;
	cout << "\t\t5.更新信息\t\t6.退出管理" << endl;
	int a;
	while (cin >> a)
	{
		if (a == 1)
		{
			if (G.AddPoint() == -1)
				cout << "\t\t\t添加失败！" << "\n" << endl;
			else
			{
				G.SaveFile();
				cout << "\t\t\t添加成功！" << "\n" << endl;
			}
			break;
		}
		else if (a == 2)
		{
			if (G.DeletePoint() == -1)
				cout << "\t\t\t该景点不存在！" << "\n" << endl;
			else
			{
				G.SaveFile();
				cout << "\t\t\t删除成功！" << "\n" << endl;
			}
			break;
		}
		else if (a == 3)
		{
			if (G.AddLoad() == -1)
				cout << "\t\t\t该道路不存在！" << "\n" << endl;
			else
			{
				G.SaveFile();
				cout << "\t\t\t删除成功！" << "\n" << endl;
			}
			break;
		}
		else if (a == 4)
		{
			if (G.DeleteLoad() == -1)
				cout << "\t\t\t该道路不存在！" << "\n" << endl;
			else
			{
				G.SaveFile();
				cout << "\t\t\t删除成功！" << "\n" << endl;
			}
			break;
		}
		else if (a == 5)
		{
			G.BuildMGraph();
			cout << "\t\t\t信息已更新！" << "\n" << endl;
			break;
		}
		else if (a == 6)
			Menu(G);
		else
			cout << "\t\t\t 请输入正确指令！" << endl;
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
	Menu(G);
}

#endif 
