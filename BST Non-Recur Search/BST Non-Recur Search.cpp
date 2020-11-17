#include<iostream>
#include<malloc.h>
#include<string>
typedef int ElementType;
typedef struct TreeNode *BinTree;
constexpr int inf = 65533;


struct TreeNode {
	ElementType Data;
	BinTree Left;
	BinTree Right;
	int Count;//计数
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
bool IterFind(ElementType KEY, BinTree BST) {
	if (!BST)
	{
		return ERROR;
	}
	BinTree root = BST;
	while (root) {
		if (KEY < root->Data)
			root = root->Left;
		else if (root->Data < KEY)  // 比根结点大，去右子树查找 
			root = root->Right;
		else if (root->Data == KEY) // 找到了 
		{
			++root->Count;//找到则计数加1
			return OK;
		}			
	}
	return ERROR;
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
		T->Count = 0;
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
			BST->Count = 0;
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

// 插入
BinTree Insert2(BinTree& KEY, BinTree BST) {//BST中不允许相等元素
	if (!BST) {  // 如果为空，初始化该结点 
		BST = (BinTree)malloc(sizeof(struct TreeNode));
		if (KEY == nullptr)
		{
			BST = nullptr;
		}
		else
		{
			BST = KEY;
		}
	}
	else { // 不为空 
		if (KEY->Data < BST->Data)  // 如果小，挂在左边 
			BST->Left = Insert2(KEY, BST->Left);
		else if (BST->Data < KEY->Data)  // 如果大，挂在右边 
			BST->Right = Insert2(KEY, BST->Right);
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

int size = 0;//为节点个数，同时也为满足OJ输出判断
void  InOrderTraversal_For_OJ(BinTree BT) {
	static int count = 0;//计数器
	if (BT) {
		InOrderTraversal_For_OJ(BT->Left);  // 进入左子树 

		if (count==size)
		{
			std::cout << BT->Data<<std::endl;
		}
		else
		{
			std::cout << BT->Data<<" ";  // 打印根 
			++count;
		}
		
		InOrderTraversal_For_OJ(BT->Right);  // 进入右子树 
	}
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

int COUNT = 0;
ElementType Vector[100] = {0};
//数据结构C习题P158
void PrintElem(const BinTree&T)
{
	if (T)
	{
		PrintElem(T->Left);
		//std::cout << T->Data << " ";
		Vector[COUNT++] = T->Data;
		PrintElem(T->Right);
	}
}

int COUNT2 = 0;//计数器
ElementType Vector2[100] = { 0 };
//数据结构C习题P158
void PrintCount(const BinTree&T)
{
	if (T)
	{
		PrintCount(T->Left);
		//std::cout << T->Data << " ";
		Vector[COUNT++] = T->Count;
		PrintCount(T->Right);
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
			PrintElem(T);
			//InOrderTraversal_For_OJ(T);
		}
	}
}

bool ListInsert(BinTree* L, int i, BinTree e)//i为线性表位置
{


	if (i <= size)        /* 若插入数据位置不在表尾 */
	{
		for (int k = size - 1; k >= i - 1; k--)  /* 将要插入位置之后的数据元素向后移动一位 */ //此时k对应的是数组下标
			L[k + 1] = L[k];
	}
	L[i - 1] = e;          /* 将新元素插入 */
	size++;

	return OK;
}


int main() {
	while (true)
	{
		BinTree RVector[100] ;
		for (int i = 0; i < 100; i++)
		{
			RVector[i] = nullptr;
		}
		COUNT = 0;
		
		for (int i = 0; i < 100; i++)
		{
			Vector[i] = inf;
		}
		BinTree BST = nullptr;	
		std::cin >> size;
		if (!size)
		{
			break;
		}
		ElementType *inp = new ElementType[size];
		for (int i = 0; i < size; i++)
		{
			std::cin >> inp[i];
		}
		for (int i = 0; i < size; i++)
		{
			RVector[i] = new TreeNode;
			RVector[i]->Data = inp[i];
			RVector[i]->Count = 0;
			RVector[i]->Left = nullptr;
			RVector[i]->Right = nullptr;
			BST = Insert2(RVector[i], BST);			
		}
		int num = 0;
		std::cin >> num;
		if (!IterFind(num, BST))
		{
			BinTree tmp = new TreeNode;
			tmp->Count = 0;
			tmp->Data = num;
			tmp->Left = tmp->Right = nullptr;
			ListInsert(RVector, num, tmp);
			//Insert(num, BST);
		}
		
		for (int i = 0; i < size; i++)
		{
			if (i==size-1)
			{
				std::cout << RVector[i]->Data<<std::endl;
			}
			else
			{
				std::cout << RVector[i]->Data << " ";
			}
		}
		
		for (int i = 0; i < size; i++)
		{
			if (i == size - 1)
			{
				std::cout << RVector[i]->Count << std::endl;
			}
			else
			{
				std::cout << RVector[i]->Count << " ";
			}
		}
		delete inp;
		for (int i = 0; i < size; i++)
		{
			delete RVector[i];
		}

	}
	return 0;
}