#include <stdio.h>
#include <malloc.h>
#define MaxSize 100
typedef char ElemType;
typedef struct node 
{	
	ElemType data;			//数据元素
	struct node *lchild;	//指向左孩子结点
	struct node *rchild;	//指向右孩子结点
} BTNode;
void CreateBTNode(BTNode * &b,char *str)
{
	BTNode *St[MaxSize],*p=NULL;
	int top=-1,k,j=0;  
	char ch;
	b=NULL;				//建立的二叉树初始时为空
	ch=str[j];
	while (ch!='\0')  	//str未扫描完时循环
	{
   	   	switch(ch) 
		{
		case '(':top++;St[top]=p;k=1; break;		//为左孩子结点
		case ')':top--;break;
		case ',':k=2; break;                      		//为孩子结点右结点
		default:p=(BTNode *)malloc(sizeof(BTNode));
				p->data=ch;p->lchild=p->rchild=NULL;
				if (b==NULL)                    	 	//*p为二叉树的根结点
					b=p;
				else  								//已建立二叉树根结点
				{	
					switch(k) 
					{
					case 1:St[top]->lchild=p;break;
					case 2:St[top]->rchild=p;break;
					}
				}
		}
		j++;
		ch=str[j];
	}
}
BTNode *FindNode(BTNode *b,ElemType x) //查找某一节点
{
	BTNode *p;
	if (b==NULL)
		return NULL;
	else if (b->data==x)
		return b;
	else  
	{
		p=FindNode(b->lchild,x);
		if (p!=NULL) 
			return p;
		else 
			return FindNode(b->rchild,x);
	}
}
BTNode *LchildNode(BTNode *p) //返回左孩子
{
    return p->lchild;
}
BTNode *RchildNode(BTNode *p) //返回右孩子
{
    return p->rchild;
}
int BTNodeHeight(BTNode *b) 
{
   	int lchildh,rchildh;
   	if (b==NULL) return(0); 				//空树的高度为0
   	else  
	{
		lchildh=BTNodeHeight(b->lchild);	//求左子树的高度为lchildh
		rchildh=BTNodeHeight(b->rchild);	//求右子树的高度为rchildh
		return (lchildh>rchildh)? (lchildh+1):(rchildh+1);
   	}
}
void DispBTNode(BTNode *b) 
{
	if (b!=NULL)
	{	printf("%c",b->data);
		if (b->lchild!=NULL || b->rchild!=NULL)
		{	printf("(");						//有孩子结点时才输出(
			DispBTNode(b->lchild);				//递归处理左子树
			if (b->rchild!=NULL) printf(",");	//有右孩子结点时才输出,
			DispBTNode(b->rchild);				//递归处理右子树
			printf(")");						//有孩子结点时才输出)
		}
	}
}

int NodeNum(BTNode *b) //计算树的节点个数
{
	if(b)
		return NodeNum(b->lchild) + NodeNum(b->rchild) + 1;
	else
		return 0;
}

void PreOrder(BTNode *b) //前序遍历
{
	if(b == NULL)
		return;
	printf("%c ",b->data);
	PreOrder(LchildNode(b));
	PreOrder(RchildNode(b));
}

void InOrder(BTNode *b) //中序遍历
{ 
	if(b == NULL)
		return;
	InOrder(LchildNode(b));
	printf("%c ",b->data);
    InOrder(RchildNode(b));
}

void PostOrder(BTNode *b)  //后序遍历
{
	if(b == NULL)
		return;
	PostOrder(LchildNode(b));
    PostOrder(RchildNode(b));
	printf("%c ",b->data);
}

void PrintNodeAtLevel(BTNode *b, int level) //打印当前层的节点
{
	// 空树或层级不合理
	if (b == NULL || level < 1)
		return;
	if (1 == level)
	{
		printf("%c ", b->data);
		return;
	}
	// 左子树的 level - 1 级
	PrintNodeAtLevel(b->lchild, level - 1);
	// 右子树的 level - 1 级
	PrintNodeAtLevel(b->rchild, level - 1);
}

void TravLevel(BTNode *b)  //逐层遍历二叉树
{
	if (b == NULL)
		return;
	int Height = BTNodeHeight(b);
	int i;
	for (i = 1; i <= Height; i++)
	{
		PrintNodeAtLevel(b, i);
		printf("\n");
	}
}


int main()
{
	BTNode *b;
	CreateBTNode(b,"A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))");
	printf("输出二叉树:");
	DispBTNode(b);
	printf("\n");
	BTNode *N = FindNode(b,'H');
    BTNode *p = LchildNode(N);
	printf("H的左孩子是：%c ,",p->data);
	p = RchildNode(N);
	printf("右孩子是： %c .\n",p->data);
	printf("二叉树b的深度: %d.\n",BTNodeHeight(b));
    printf("二叉树b的结点个数: %d.\n",NodeNum(b));
	printf(" 先序遍历序列:\n");
	printf("     递归算法:"); PreOrder(b); printf("\n");
	printf(" 中序遍历序列:\n");
	printf("     递归算法:"); InOrder(b); printf("\n");
	printf(" 后序遍历序列:\n");
	printf("     递归算法:"); PostOrder(b); printf("\n");
	printf(" 层次遍历序列:"); printf("\n");
	TravLevel(b); printf("\n");

	return 0;
}
