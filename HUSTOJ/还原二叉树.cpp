/×
题目描述

给一棵二叉树的层序遍历序列和中序遍历序列，求这棵二叉树的先序遍历序列和后序遍历序列。

输入

每个输入文件中一组数据。

第一行一个正整数N（1<=N<=30），代表二叉树的结点个数（结点编号为1~N）。接下来两行，每行N个正整数，分别代表二叉树的层序遍历序列和中序遍历序列。数据保证序列中1~N的每个数出现且只出现一次。

输出

输出两行，每行N个正整数，分别代表二叉树的先序遍历序列和后序遍历序列。每行末尾不输出额外的空格。

样例输入

7
3 5 4 2 6 7 1
2 5 3 6 4 7 1
样例输出

3 5 2 4 6 7 1
2 5 6 1 7 4 3
×/
#include <stdio.h>
#include <stdlib.h>
int *level;
int *in;

typedef struct BiTNode
{
    int data;
    BiTNode *lchild;
    BiTNode *rchild; // 左右孩子指针
} BiTNode,*BiTree;

typedef struct QElemNode
{
    int data;
    int l,h; //中序序列的下界和上界
    BiTree parent; //双亲结点指针
    int lr; //lr==1->双亲的左子树；lr==2->双亲的右子树；lr==0->根结点
} QElemNode;

typedef QElemNode QElemType;

typedef struct QNode
{
    QElemType data;
    struct QNode *next;
} QNode,*Queueptr;

typedef struct
{
    Queueptr front;
    Queueptr rear;
} LinkQueue;

BiTree T;

void InitQueue(LinkQueue &Q)
{
    Q.front=Q.rear=(Queueptr)malloc(sizeof(QNode));
    if(!Q.front) exit(0);
    Q.front->next=NULL;
}

void EnQueue(LinkQueue &Q,QElemType e)
{
    Queueptr p;
    p=(Queueptr)malloc(sizeof(QNode));
    if(!p) exit(0);
    p->data=e;
    p->next=NULL;
    Q.rear->next=p;
    Q.rear=p;
}

void DeQueue(LinkQueue &Q,QElemType &e)
{
    Queueptr p;
    if(Q.front==Q.rear)
        exit(0);
    p=Q.front->next;
    e=p->data;
    Q.front->next=p->next;
    if(Q.rear==p)
        Q.rear=Q.front;
    free(p);
}

int QueueEmpty(LinkQueue Q)
{
    if(Q.front==Q.rear)
        return 1;
    else
        return 0;
}

void InitBiTree(BiTree &T)
{
    T=NULL;
}

void DestroyBiTree(BiTree &T)
{
    if(T) // 非空树
    {
        if(T->lchild) // 有左孩子
            DestroyBiTree(T->lchild); // 销毁左孩子子树
        if(T->rchild) // 有右孩子
            DestroyBiTree(T->rchild); // 销毁右孩子子树
        free(T); // 释放根结点
        T=NULL; // 空指针赋0
    }
}

void PostOrderTraverse(BiTree T,int n)
{
	static int i = 0;
    if(T!=NULL)
    {
        PostOrderTraverse(T->lchild,n);
        PostOrderTraverse(T->rchild,n);
        (i < n - 1) ? printf("%d ",T->data) : printf("%d\n",T->data);
		i++;
    }
}

void PreOrderTraverse(BiTree T,int n)
{
	static int i = 0;
    if(T!=NULL)
    {
       (i < n - 1) ? printf("%d ",T->data) : printf("%d\n",T->data);
		i++;
        PreOrderTraverse(T->lchild,n);
        PreOrderTraverse(T->rchild,n);
    }
}


BiTree CreateBiTreeFromLevelInOrder(int  *level, int  *in, int n)
{
    int r=-1, low, high, lr, i, j;
    BiTree root = NULL, p, f;
    int ch;
    QElemType s;
    LinkQueue Q;
    InitQueue(Q);
    s.data = level[++r];
    s.l = 0;
    s.h = n-1;
    s.parent = NULL;
    s.lr = 0;
    EnQueue(Q,s);
    while(!QueueEmpty(Q))
    {
        DeQueue(Q, s);
        ch = s.data;
        low = s.l;
        high = s.h;
        f = s.parent;
        lr = s.lr;
        for (j=low; j<=high; j++)
            if (in[j]==ch)
            {
                i = j;
                break;
            }
        p = (BiTree)malloc(sizeof(BiTNode));
        p->data = ch;
        p->lchild = p->rchild = NULL;
        if (lr==0) root = p;
        else if (lr==1) f->lchild = p;
        else f->rchild = p;
        if (low==high) continue;
        if (i==low)//结点无左孩子
        {
            s.l = low+1;
            s.lr = 2;
            s.data = level[++r];
            s.parent = p;
            EnQueue(Q, s);
        }
        else if(i==high)//结点无右孩子
        {
            s.h = high-1;
            s.lr = 1;
            s.data = level[++r];
            s.parent = p;
            EnQueue(Q, s);
        }
        else//结点有左右孩子
        {
            s.h = i-1;
            s.l = low;
            s.lr = 1;
            s.data = level[++r];
            s.parent = p;
            EnQueue(Q, s);
            s.l = i+1;
            s.h = high;
            s.lr = 2;
            s.data = level[++r];
            s.parent = p;
            EnQueue(Q, s);
        }
    }
    return root;
}


int main()
{
    InitBiTree(T);
    int n;
    int i;
    scanf("%d",&n);
    level=(int *)malloc(sizeof(int)*n);
    in=(int *)malloc(sizeof(int)*n);
    for(i=0; i<n; i++)
    {
        scanf("%d",level+i);
    }
    for(i=0; i<n; i++)
    {
        scanf("%d",in+i);
    }
    T = CreateBiTreeFromLevelInOrder(level, in, n);
    PreOrderTraverse(T,n);
    PostOrderTraverse(T,n);
    return 0;
}               
