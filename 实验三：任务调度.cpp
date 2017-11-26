/*
某一个调度系统，具体描述如下：
（1）	调度任务存放在一个文本文件中，每一行一个调度任务。
（2）	每个调度任务包含任务名称、任务开始时间、以及执行任务需要的总时间。
（3）	假设每个任务每次可以得到的执行的时间为2分钟，当它执行时间完毕后，将它排到等待调度队列的尾部，等待新一轮的执行分配。
（4）	如果执行完毕，则写入日志文件：task_log.txt中，其格式为：
          任务名称  执行开始时间  执行结束时间 调度次数
提示：
  √ 开打任务所在的文本文件，将其任务按照时间先后顺序存放到调度一个队列中；
  √ 依次从调度队列中取出任务，修改其调度次数，并将其需要执行时间减去2分钟，如果大于0，则将其执行时间修改之后，插入队列尾。
  √ 如果小于等于0，则执行完毕，将其执行结果写入task_log.txt文件中。

*/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#define MaxSize 20

struct QueueRecord;
typedef struct QueueRecord *Queue;
struct Node
{
	char Name[20]; //An array to store schedule's name;
	double BeginTime; //A variable to store the beging time of each schedule in the file;
	double StartTime; // A variable to store the schedule's start time;
	double FinalTime; // A variable to store the schedule's finish time;
	double TotalTime; //A variable to store the total operation time of schedule;
	int OperatTime; //Keep the operation times of each schedule  during the operation;
	int Tag; //To mark whether the schedule is start operated;
};

struct QueueRecord
{
	int Front; //Points to the head of the queue;
	int Rear; // Points to the tile of the queue;
	Node Data[MaxSize]; //Creat an array to store the datas;
};

//Initialize the queue;
void MakeEmpty(Queue Q) 
{
	Q->Front = 0;
	Q->Rear = 0;
}

//Write datas into a queue;
int Enqueue(Queue Q, const char Name[], double BeginTime, double TotalTime,
	        double StartTime, double FinalTime ,int OperatTime ,int Tag)
{
	if ((Q->Rear + 1) % MaxSize == Q->Front) //Judge whether the queue is full;
		return -1;

	strcpy(Q->Data[Q->Rear].Name, Name);
	Q->Data[Q->Rear].BeginTime = BeginTime;
	Q->Data[Q->Rear].StartTime = StartTime;
	Q->Data[Q->Rear].FinalTime = FinalTime;
	Q->Data[Q->Rear].TotalTime = TotalTime;
	Q->Data[Q->Rear].OperatTime = OperatTime;
	Q->Data[Q->Rear].Tag = Tag;

	Q->Rear++;

	return 0;
}

int Dequeue(Queue Q, char Name[], double &BeginTime, double &StartTime,
	        double &TotalTime, double &FinalTime, int &OperatTime ,int &Tag)
{
	if (Q->Front == Q->Rear) //Judge whether the queue is empty;
		return -1;

	strcpy(Name, Q->Data[Q->Front].Name);
	BeginTime = Q->Data[Q->Front].BeginTime;
	StartTime = Q->Data[Q->Front].StartTime;
	FinalTime = Q->Data[Q->Front].FinalTime;
	TotalTime = Q->Data[Q->Front].TotalTime;
	OperatTime = Q->Data[Q->Front].OperatTime;
	Tag = Q->Data[Q->Front].Tag;

	Q->Front++;

	return 0;
}

//Write the datas into the file;
void WriteIntoFile(string Name, double StratTime, double FinalTime, int OperatTime)
{
	ofstream file("D:\\c_out.txt", ios::app);
	file << Name << " " << StratTime << " " << FinalTime << " " << OperatTime << endl;
}

double CurrentTime = 0; //A global variable to store the current time;

int main()
{
	Queue Q = (Queue)malloc(sizeof(QueueRecord)); //Creat a queue;
	MakeEmpty(Q);
	int n = 0; //A variable to keep the number of schedules;
	ifstream file("D:\\c.txt");
	while (!file.eof()) //Read datas to the queue;
	{
		string s1;
		double s2, s3;
		file >> s1 >> s2 >> s3;
		const char* Name = s1.c_str();
		Enqueue(Q, Name, s2, s3 ,0 ,0 ,0 ,0);
		n++;
	}
	file.close();

	while (Q->Front != Q->Rear) //The queue isn't empty;
	{
		double StartTime, TotalTime, FinalTime, BeginTime;
		char Name[20];
		int Tag, OperatTime;
		Dequeue(Q, Name ,BeginTime,StartTime, TotalTime, FinalTime, OperatTime, Tag); 
                //Take a schedule and get it's datas;
		if (BeginTime <= CurrentTime) //If begin time less than current time ,start operation
		{
			if (Tag == 0) //If hasn't start operation ,start it;
			{
				StartTime = CurrentTime; //Start time equals to the current time;
				Tag = 1; //Make tag equals to one;
			}
			TotalTime -= 2; 
			OperatTime++;
			if (TotalTime <= 0) //If total time less than zero,operation finished;
			{
				CurrentTime = CurrentTime + 2 + TotalTime; 
				FinalTime = CurrentTime;
				WriteIntoFile(Name, StartTime, FinalTime, OperatTime);  //Write the data into file;
			}
			else //If not finished ,enqueue;
			{
				CurrentTime += 2;
				Enqueue(Q, Name, BeginTime, TotalTime, StartTime, FinalTime, OperatTime,Tag);
			}
		}
		else //There is not the time to start the schedul ,enqueue;
			Enqueue(Q, Name, BeginTime, TotalTime, StartTime, FinalTime, OperatTime, Tag);
	}

}

