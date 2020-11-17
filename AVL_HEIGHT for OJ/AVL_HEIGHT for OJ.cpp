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
		T = nullptr;
	else
	{
		T = new BiTNode;
		T->data = S[i];
		CreateBiTree(T->lchild, S, ++i);
		CreateBiTree(T->rchild, S, ++i);
	}
}
int Height(BiTree T)
{
	if (!T)
		return 0;
	else if (!T->lchild && !T->rchild)
		return 1;
	return Height(T->lchild) >= Height(T->rchild) ? Height(T->lchild) + 1 : Height(T->rchild) + 1;
}
int main()
{
	char inp[200];
	while (cin >> inp && inp[0] != '#')
	{
		int i = -1;
		BiTree T;
		CreateBiTree(T, inp, ++i);
		cout << Height(T) << endl;
	}
	return 0;
}