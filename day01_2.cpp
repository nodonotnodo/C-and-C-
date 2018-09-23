////输出乘法口诀表
//
//
//#include <stdio.h>
//int main()
//{
//	int i = 1;
//	int j = 1;
//	int k = 0;
//	for (i = 1; i < 10; i++)         //确定行数和第一个乘数
//	{
//		for (j = 1; j <= i; j++)     //确定列数和第二个乘数
//		{
//			k = i*j;
//			if (i == j)              //最后一列时进行换行
//			{
//				printf("%d*%d=%2d\n",i,j,k);
//			}
//			else
//			printf("%d*%d=%2d  ", i, j, k);
//		}
//	}
//	return 0;
//}