#include<iostream>
using namespace std;
typedef struct BiTNode
{
	char data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;
void CreateBiTree(BiTree &T, char S[], int &i)
{
	if (S[i] == '#')
		T = NULL;
	else
	{
		T = new BiTNode;
		T->data = S[i];
		CreateBiTree(T->lchild, S, ++i);
		CreateBiTree(T->rchild, S, ++i);
	}
}
int Depth(BiTree T)
{
	if (!T)
		return 0;
	else if (!T->lchild && !T->rchild)
		return 1;
	return Depth(T->lchild) >= Depth(T->rchild) ? Depth(T->lchild) + 1 : Depth(T->rchild) + 1;
}
int main()
{
	char S[200];
	while (cin >> S && S[0] != '#')
	{
		int i = -1;
		BiTree T;
		CreateBiTree(T, S, ++i);
		cout << Depth(T) << endl;
	}
	return 0;
}
// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
