#define _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
///水管工游戏
/*
利用栈，来输出解决方案.
*/

int a[51][51];//假设土地的大小不超过50*50
int book[51][51], n, m, flag = 0;
struct node
{
	int x;//横坐标
	int y;//纵坐标
}s[100];
int top = 0;


void dfs(int x, int y, int front)
{
	//判断是否达到终点，请注意这里的y的坐标是m+1
	//另外判断是否到达终点一定要放在越界判断前面
	if ((x == n) && (y == m + 1))
	{
		flag = 1;//找到铺设方案
		for (int i = 1; i <= top; i++)
		{
			printf("(%d,%d) ,", s[i].x, s[i].y);
		}
		return;
	}

	//判断是否越界
	if (x<1 || x>n || y<1 || y>m)
	{
		return;
	}
	//判断这个管道是否在路径中已经使用过
	if (book[x][y] == 1)
	{
		return;
	}


	book[x][y] = 1;//标记使用当前这个管道

	//将当前尝试的坐标入栈
	top++;
	s[top].x = x;
	s[top].y = y;



	//当前水管是直管的情况
	if (a[x][y] >= 5 && a[x][y] <= 6)
	{
		//进水口在左边的情况
		if (1 == front)
		{
			dfs(x, y + 1, 1);//只能使用5号这种摆放方式
		}

		//进水口在上边的情况
		if (2 == front)
		{
			dfs(x + 1, y, 2);// 只能使用6号这种摆放方式
		}

		//进水口在右边的情况
		if (3 == front)
		{
			dfs(x , y-1, 3);//只能使用5号这种摆放方式
		}

		//进水口在下边的情况
		if (4 == front)
		{
			dfs(x, y + 1, 4);//只能使用6号这种摆放方式
		}
	}

	//当前水管是弯管的情况
	if (a[x][y] >= 1 && a[x][y] <= 4)
	{
		//进水口在左边
		if (1 == front)
		{
			dfs(x + 1, y, 2);//3号状态
			dfs(x - 1, y, 4);//4号状态
		}

		//进水口在上边
		if (2 == front)
		{
			dfs(x, y - 1, 3);//4号状态
			dfs(x, y + 1, 1);//1号状态
		}

		//进水口在右边
		if (3 == front)
		{
			dfs(x - 1, y, 4);//1号状态 
			dfs(x + 1, y, 2);//2号状态
		}

		//进水口在下边的情况
		if (4 == front)
		{
			dfs(x, y + 1, 1);//2号状态
			dfs(x, y - 1, 3);//3号状态
		}
	}

	book[x][y] = 0;//取消标记
	top--;
	return;
}




int main()
{
	int i, j, num = 0;
	scanf("%d %d", &n, &m);
	//读入游戏地图
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= m; j++)
		{
			scanf("%d", &a[i][j]);
		}
	}


	//开始搜索，从1,1点开始，进水方向也是1 
	dfs(1, 1, 1);

	//判断是否能找到铺设方案
	if (0 == flag)
	{
		printf("impossible  \r\n");
	}
	else
	{
		printf("can find. \r\n");
	}




	printf("\r\n");
	system("pause");
	return 0;
}


/*


输入的数据（0表示此处不通，没有管道）

5 4 
5 3 5 3 
1 5 3 0 
2 3 5 1
6 1 1 5
1 5 5 4




///////////////////////////
水管的6种摆放状态

0 0 1 1 0 0
0 0 1 1 0 0
0 0 1 1 0 0
0 0 1 1 1 1
0 0 1 1 1 1
0 0 0 0 0 0
0 0 0 0 0 0
1号状态


0 0 0 0 0 0
0 0 0 0 0 0
0 0 1 1 1 1
0 0 1 1 1 1
0 0 1 1 0 0
0 0 1 1 0 0
0 0 1 1 0 0
2号状态



0 0 0 0 0 0
0 0 0 0 0 0
1 1 1 1 0 0
1 1 1 1 0 0
0 0 1 1 0 0
0 0 1 1 0 0
0 0 1 1 0 0
3号状态


0 0 1 1 0 0
0 0 1 1 0 0
0 0 1 1 0 0
1 1 1 1 0 0
1 1 1 1 0 0
0 0 0 0 0 0
0 0 0 0 0 0
4号状态




0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0
1 1 1 1 1 1
1 1 1 1 1 1
0 0 0 0 0 0
0 0 0 0 0 0
5号状态



0 0 1 1 0 0
0 0 1 1 0 0
0 0 1 1 0 0
0 0 1 1 0 0
0 0 1 1 0 0
0 0 1 1 0 0
0 0 1 1 0 0
6号状态


将进水口在左边用1表示，
进水口在上边用2表示，
进水口在右边用3表示，
进水口在下边用4表示；

			[2]
		 0 0 0 0 0
	[1]	 0 0 0 0 0  [3]
		 0 0 0 0 0
		 0 0 0 0 0
			[4]



//// 一块矩形土地被分为N*M的单位正方形，现在这块土地上已经埋设有一些水管，水管将从坐标（1，1）的矩形土地的左上角左部边缘，延伸到坐标为（N,M）的矩形土地的右下角右部边缘。



直到(n,m+1)的时候为止，便会产生一种方案。


*/


