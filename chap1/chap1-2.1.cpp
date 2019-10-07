#define _CRT_SECURE_NO_WARNINGS 

#include <stdlib.h>
#include <stdio.h>

////冒泡排序：核心是双重嵌套循环。时间复杂度(O(N的平方))，这是一个非常高的时间复杂度
////一句话概括：冒泡循环需要循环N次（外层循环），每次需要从第【1】个元素到第【n-i】个元素的【位置】进行一次两两比较

int main()
{
	int a[100], i, j, t, n;
	scanf("%d", &n);//输入一个数n，表示接下来有n个数

	//循环读入n个数到数组a中
	for (i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
	}

	/////////冒泡排序的核心部分 
	for (i = 1; i <= n - 1; i++)///累记循环的次数
	{

	/////////数组的下表是j，，，i只是累记循环的次数
    ////一句话概括：冒泡循环需要循环N次（外层循环），每次需要从第【1】个元素到第【n-i】个元素的【位置】进行一次两两比较
		for (j = 1; j <= n - i; j++)  ////核心的核心..此处是(n-i)
		{
			//从第1位开始比较直到最后一个尚未归位的数，想一想为什么到n-i就可以了
			if (a[j] < a[j + 1]) //比较大小并交换
			{
				t = a[j];
				a[j] = a[j + 1];
				a[j + 1] = t;
			}
		}
	}

	for (i = 1; i <= n; i++)//输出结果
	{
		printf("%d ", a[i]);
	}

	system("pause");
	return 0;
}
