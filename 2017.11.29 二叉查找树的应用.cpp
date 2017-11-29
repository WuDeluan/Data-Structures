#include <stdio.h>
#include <malloc.h>
typedef int KeyType;
typedef char InfoType[10];
typedef struct TreeNode           		//记录类型
{
	KeyType Key;              		//关键字项
	InfoType Data;             		//其他数据域
	struct TreeNode *Lchild, *Rchild;	//左右孩子指针
} *BSTree, *Position;
int InsertBST(BSTree &T, KeyType K)
{
	if (T == NULL)				//原树为空, 新插入的记录为根结点
	{
		T = (TreeNode*)malloc(sizeof(TreeNode));
		T->Key = K;
		T->Lchild = T->Rchild = NULL;
		return 0;
	}

	if (K < T->Key)
		return InsertBST(T->Lchild, K);	//插入到T的左子树中
	else if (K > T->Key)
		return InsertBST(T->Rchild, K);  //插入到T的右子树中
}


Position SearchBST(BSTree T, KeyType K)
{
	if (T == NULL)
		return T;
	if (K < T->Key)
		return SearchBST(T->Lchild, K);  //在左子树中递归查找
	else if (K > T->Key)
		return SearchBST(T->Rchild, K);  //在右子树中递归查找
	else
		return T;
}

int Judge(BSTree T, BSTree P)
{
	if (T == NULL && P == NULL)
		return 1;
	else if (T != NULL && P != NULL)
	{
		if (T->Key == P->Key)
			return Judge(T->Lchild, P->Lchild) && Judge(T->Rchild, P->Rchild);
		else
			return 0;
	}
	else
		return 0;
}

Position LchildNode(Position P) //返回左孩子
{
	return P->Lchild;
}

Position RchildNode(Position P) //返回右孩子
{
	return P->Rchild;
}

int BSTreeHeight(BSTree T)
{
	int LHeight, RHeight;
	if (T == NULL)
		return 0; 				//空树的高度为0
	else
	{
		LHeight = BSTreeHeight(T->Lchild);	//求左子树的高度为LHeight
		RHeight = BSTreeHeight(T->Rchild);	//求右子树的高度为RHeight
		return (LHeight > RHeight) ? (LHeight + 1) : (RHeight + 1);
	}
}
void PostOrder(BSTree T)  //后序遍历
{
	static BSTree P = T;
	if (T == NULL)
		return;
	PostOrder(LchildNode(T));
	PostOrder(RchildNode(T));
	if (T == P)
		printf("%d\n", T->Key);
	else
		printf("%d ", T->Key);
}

void PrintNodeAtLevel(BSTree T, int Level, int n) //打印当前层的节点
{
	static int k = 0;
	// 空树或层级不合理
	if (T == NULL || Level < 1)
		return;
	if (Level == 1 && n - 1 > k)
	{
		printf("%d ", T->Key);
		k++;
		return;
	}
	else if (Level == 1 && n - 1 == k)
	{
		printf("%d\n", T->Key);
		return;
	}
	// 左子树的 level - 1 级
	PrintNodeAtLevel(T->Lchild, Level - 1, n);
	// 右子树的 level - 1 级
	PrintNodeAtLevel(T->Rchild, Level - 1, n);
}

void TravLevel(BSTree T, int n)  //逐层遍历二叉树
{
	if (T == NULL)
		return;
	int Height = BSTreeHeight(T);
	int i;
	for (i = 1; i <= Height; i++)
	{
		PrintNodeAtLevel(T, i, n);
	}
}

int main()
{
	BSTree T, P;
	T = P = NULL;
	int n, m, k, l;
	scanf("%d%", &n);
	m = n;
	l = n;
	while (n--)
	{
		scanf("%d", &k);
		InsertBST(T, k);
	}
	while (m--)
	{
		scanf("%d", &k);
		InsertBST(P, k);
	}
	k = Judge(T, P);
	if (k == 0)
		printf("NO\n");
	else
		printf("YES\n");
		PostOrder(T);
		TravLevel(T, l);
}
