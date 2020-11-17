// Binary_Search.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
const int Great = 1;
const int Sorry = 0;
typedef int ElemType;
typedef int KeyType;
int BS(ElemType *ST, KeyType key, int low, int high)
{
	if (low > high)
	{
		return Sorry;
	}
	if (low <= high)
	{
		int mid = (low + high) / 2;
		if (ST[mid] == key)
		{
			return mid;
		}
		else if (key < ST[mid])//左子表查找
		{
			return BS(ST, key, low, mid - 1);
		}
		else//右子表
		{
			return BS(ST, key, mid + 1, high);
		}
	}
}
int main()
{
	while (true)
	{
		int size = 0;
		std::cin >> size;
		if (!size)
		{
			break;
		}
		ElemType *inp = new ElemType[size];
		for (int i = 0; i < size; i++)
		{
			std::cin >> inp[i];
		}
		ElemType key = 0;
		std::cin >> key;
		if (BS(inp, key, 0, size - 1))
		{
			std::cout << "YES\n";
		}
		else
		{
			std::cout << "NO\n";
		}		
	}

	return 0;

}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
