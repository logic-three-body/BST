#include<iostream>
#include<malloc.h>
#include<string>
typedef int ElementType;
typedef struct TreeNode *BinTree;



struct TreeNode {
	ElementType Data;
	BinTree Left;
	BinTree Right;
};

const char Nil = '#';//空
const int ERROR = 0;
const int OK = 1;

// 查找递归实现 
BinTree Find(ElementType KEY, BinTree BST) {
	if (!BST)  // 如果根结点为空，返回 nullptr 
		return nullptr;
	if (KEY < BST->Data) // 比根结点小，去左子树查找 
		return Find(KEY, BST->Left);
	else if (BST->Data < KEY)  // 比根结点大，去右子树查找 
		return Find(KEY, BST->Right);
	else if (BST->Data == KEY) // 找到了 
		return BST;
}

// 查找非递归实现
BinTree IterFind(ElementType KEY, BinTree BST) {
	while (BST) {
		if (KEY < BST->Data)
			BST = BST->Left;
		else if (BST->Data < KEY)  // 比根结点大，去右子树查找 
			BST = BST->Right;
		else if (BST->Data == KEY) // 找到了 
			return BST;
	}
	return nullptr;
}

// 查找最小值的递归实现
BinTree FindMin(BinTree BST) {
	if (!BST)    // 如果为空了，返回 nullptr 
		return nullptr;
	else if (BST->Left)   // 还存在左子树，沿左分支继续查找 
		return FindMin(BST->Left);
	else  // 找到了 
		return BST;
}

// 查找最大值的非递归实现
BinTree FindMax(BinTree BST) {
	if (BST)  // 如果不空 
		while (BST->Right)   // 只要右子树还存在 
			BST = BST->Right;
	return BST;
}

void CreateBiTree(BinTree &T)
{
	ElementType ch;


	std::cin >> ch;

	if (ch == Nil)
		T = nullptr;
	else
	{
		T = (BinTree)malloc(sizeof(TreeNode));
		T->Data = ch; /* 生成根结点 */
		CreateBiTree(T->Left); /* 构造左子树 */
		CreateBiTree(T->Right); /* 构造右子树 */
	}
}


// 插入
BinTree Insert(ElementType KEY, BinTree BST) {//BST中不允许相等元素
	if (!BST) {  // 如果为空，初始化该结点 
		BST = (BinTree)malloc(sizeof(struct TreeNode));
		if (KEY == Nil)
		{
			BST = nullptr;
		}
		else
		{
			BST->Data = KEY;
			BST->Left = nullptr;
			BST->Right = nullptr;
		}
	}
	else { // 不为空 
		if (KEY < BST->Data)  // 如果小，挂在左边 
			BST->Left = Insert(KEY, BST->Left);
		else if (BST->Data < KEY)  // 如果大，挂在右边 
			BST->Right = Insert(KEY, BST->Right);
		// 如果相等，什么都不用做 
	}
	return BST;
}

// 删除
BinTree Delete(ElementType KEY, BinTree BST) {
	BinTree tmp;
	if (!BST)
		std::cout << "要删除的元素未找到";
	else if (KEY < BST->Data)   // X 比当前结点值小，在左子树继续查找删除 
		BST->Left = Delete(KEY, BST->Left);
	else if (BST->Data < KEY)   // X 比当前结点值大，在右子树继续查找删除 
		BST->Right = Delete(KEY, BST->Right);
	else {  //  找到被删除结点 
		if (BST->Left && BST->Right) {  // 被删除结点有俩孩子结点 
			tmp = FindMin(BST->Right);   // 找到右子树中值最小的
			BST->Data = tmp->Data;     // 用找到的值覆盖当前结点 
			BST->Right = Delete(tmp->Data, BST->Right);    // 把前面找到的右子树最小值结点删除 
		}
		else {  // 被删除结点只有一个孩子结点或没有孩子结点 
			tmp = BST;
			if (!BST->Left && !BST->Right)  // 没有孩子结点 
				BST = nullptr;
			else if (BST->Left && !BST->Right)  // 只有左孩子结点 
				BST = BST->Left;
			else if (!BST->Left && BST->Right)  // 只有右孩子结点 
				BST = BST->Right;
			free(tmp);
		}
	}
	return BST;
}

// 中序遍历 
void  InOrderTraversal(BinTree BT) {
	if (BT) {
		InOrderTraversal(BT->Left);  // 进入左子树 
		std::cout << BT->Data;  // 打印根 
		InOrderTraversal(BT->Right);  // 进入右子树 
	}
}

BinTree Pre = nullptr;
//数据结构C习题P158
void JudBST(const BinTree&T, int &flag)//flag初值为OK
{
	if (T&&flag)
	{
		JudBST(T->Left, flag);//中序遍历左子树
		if (!Pre)//中序遍历第一个节点不必判断
		{
			Pre = T;
		}
		else if (Pre->Data < T->Data)
		{
			Pre = T;//前驱指针指向当前节点
		}
		else
		{
			flag = ERROR;//不是二叉排序树
		}
		JudBST(T->Right, flag);//中序遍历右子树
	}
}


//数据结构C习题P158
void Print(const BinTree&T)
{
	if (T)
	{
		Print(T->Left);
		std::cout << T->Data << " ";
		Print(T->Right);
	}
}

void PrintAllX(BinTree&T, ElementType&x)
{
	//BST 查找>=x 输出
	BinTree P = T;
	if (P)
	{
		while (P&&P->Data < x)//沿右分支向下，找到第一个 < x 
		{
			P = P->Right;
		}
		T = P; //T指向值为>=x的节点的根
		if (P)//找到第一个 < x 节点
		{
			BinTree F = P;
			P = P->Left;
			while (P&&P->Data >= x) //沿左向下 找到第一个 < x 节点
			{
				F = P;  //F是P双亲节点指针，指向第一个值>=x节点
				P = P->Left;
			}
			if (P)
			{
				F->Left = nullptr;//双亲与找到第一个<x节点断开 : 因为左边都是比它小的值，无需输出
			}
			Print(T);
		}
	}
}


int c[100] = {0};
int flag=0;
int k=0;
void PrintAllX_For_OJ(BinTree& T, int n, int key)
{
	if (T)
	{
		PrintAllX_For_OJ(T->Left, n, key);
		c[++k] = T->Data;
		if (c[k] >= key)
		{
			if (flag == 0)
			{
				std::cout << c[k];
				flag = 1;
			}
			else
				std::cout << " " << c[k];
		}
		PrintAllX_For_OJ(T->Right, n, key);
	}
}

int main() {
	while (true)
	{
		BinTree BST = nullptr;
		int size = 0;
		std::cin >> size;
		if (!size)
		{
			break;
		}
		ElementType *inp = new ElementType[size];
		for (size_t i = 0; i < size; i++)
		{
			std::cin >> inp[i];
		}
		for (int i = 0; i < size; i++)
		{
			BST = Insert(inp[i], BST);
		}
		int key = 0;
		std::cin >> key;
		flag = 0;
		PrintAllX_For_OJ(BST, size,key);
		std::cout << std::endl;
		delete inp;
	}
	return 0;
}