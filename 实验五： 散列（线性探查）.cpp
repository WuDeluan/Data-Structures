/*
【基本要求】
编写一个程序，实现哈希表的初始化、插入、查找、删除等相关运算，并在此基础上完成如下功能：
（1）	建立{16,74,60,43,54,90,46,31,29,88,77}哈希表A[0..12]，哈希函数为H(k)=key%p，（p取13），并采用线性探查法解决冲突。
（2）	在上述哈希表中查找关键字为29的记录。
（3）	在上述哈希表中删除关键字为77的记录，再将其插入。
【输出结果】
输出结果例子如下：
哈希表地址:       0   1   2   3   4   5   6   7   8   9  10  11  12
 哈希表关键字:    77      54  16  43  31  29  46  60  74  88      90
 搜索次数:         2       1   1   1   1   4   1   1   1   1       1
 平均搜索长度ASL(11)=1.36364
 ha[6].key=29
 删除关键字77
 哈希表地址:       0   1   2   3   4   5   6   7   8   9  10  11  12
 哈希表关键字:            54  16  43  31  29  46  60  74  88      90
 搜索次数:                 1   1   1   1   4   1   1   1   1       1
 平均搜索长度ASL(10)=1.3
 未找到77
 插入关键字77
 哈希表地址:       0   1   2   3   4   5   6   7   8   9  10  11  12
 哈希表关键字:    77      54  16  43  31  29  46  60  74  88      90
 搜索次数:         2       1   1   1   1   4   1   1   1   1       1
 平均搜索长度ASL(11)=1.36364
*/
 

#include <stdio.h>
#include <stdlib.h>

enum State
{
	EXIST,
	EMPTY,
	DELETE
};

typedef struct HashCell
{
	int Key;
	int Searchtime;
	State Info;
};

typedef struct HashTable
{
	int TableSize;
	HashCell *TheCells;
}*Hash;

void InitHash(Hash H)
{
	H->TheCells = (HashCell*)malloc(sizeof(HashCell) * H->TableSize);
	for (int i = 0; i < H->TableSize; i++)
		H->TheCells[i].Info = EMPTY;
}

int InsertHash(Hash H, int Key)
{
	int Index, i, j = 0, searchtime = 0;
	Index = Key % H->TableSize;
	for (i = Index; i < H->TableSize; i++)
	{
		j++;
		searchtime++;
		if (H->TheCells[i].Info != EXIST)
			break;
		if (i == H->TableSize - 1)
			i = -1;
		if (j == H->TableSize)
			return -1;
	}
	H->TheCells[i].Info = EXIST;
	H->TheCells[i].Key = Key;
	H->TheCells[i].Searchtime = searchtime;
	return 0;
}

int FindHash(Hash H, int Key)
{
	int Index, i, j = 0;
	Index = Key % H->TableSize;
	for (i = Index; i < H->TableSize; i++)
	{
		j++;
		if (H->TheCells[i].Key == Key && H->TheCells[i].Info == EXIST)
			return i;
		if (i == H->TableSize - 1)
			i = -1;
		if (j == H->TableSize)
			return -1;
	}
	return 0;
}

int DeleteHash(Hash H, int Key)
{
	int Index = FindHash(H, Key);
	if (Index == 0)
		H->TheCells[Index].Info = DELETE;
	else
		return -1;
	return 0;
}

double ASL(Hash H)
{
	double j = 0, asl = 0;
	for (int i = 0; i < H->TableSize; i++)
	{
		if (H->TheCells[i].Info != EXIST)
			asl += 0;
		else
		{
			j++;
			asl += H->TheCells[i].Searchtime;
		}
	}
	asl /= j;
	return asl;
}

void PrintHash(Hash H)
{
	int i;
	printf("哈希表地址:       ");
	for (i = 0; i < H->TableSize; i++)
		printf("%d  ", i);
	printf("\n哈希表关键字:     ");
	for (i = 0; i < H->TableSize; i++)
	{
		if (H->TheCells[i].Info != EXIST)
			printf("   ");
		else
			printf("%d ", H->TheCells[i].Key);
	}
	printf("\n搜索次数:          ");
	for (i = 0; i < H->TableSize; i++)
	{
		if (H->TheCells[i].Info != EXIST)
			printf("   ");
		else
			printf("%d  ", H->TheCells[i].Searchtime);
	}
	printf("\n平均搜索长度ASL(11)= %lf\n", ASL(H));
}

int main()
{
	Hash H;
	H = (Hash)malloc(sizeof(HashTable));
	H->TableSize = 13;
	InitHash(H);	
	int data[] = { 16,74,60,43,54,90,46,31,29,88,77 };
	for (int i = 0; i < 11; i++)
		InsertHash(H, data[i]);
	PrintHash(H);
	printf("ha[%d].key=29\n", FindHash(H,29));
	printf("删除关键字77\n");
	(DeleteHash(H, 77) == 0) ? PrintHash(H) : printf("删除失败!\n");
	(FindHash(H, 77) == 0) ? PrintHash(H) : printf("未找到77!\n");
	(InsertHash(H,77) == 0) ? PrintHash(H) : printf("插入失败！!\n");
}
