#include <stdio.h>
#include <stdlib.h>

short array[9][9] = {
	{9,4,0,0,1,0,0,5,0},
	{7,8,0,0,0,0,0,0,9},
	{0,1,5,9,0,7,8,0,0},
	{0,0,0,4,8,0,3,0,7},
	{0,6,0,0,9,0,0,4,0},
	{8,0,4,0,3,2,0,0,0},
	{0,0,9,6,0,8,1,7,0},
	{1,0,0,0,0,0,0,8,4},
	{0,7,0,0,5,0,0,2,3}
};

short posibles[9][9][10] = { 0 };
short pocount[9][9] = { 0 };

bool analysis(short row,short col)
{
	if (array[row][col] != 0)
		return false;
	//printf("分析%d,%d",row + 1,col + 1);
	short i = 0, j = 0;
	for (; i < 9; i++)
	{
		if (array[row][i])
			posibles[row][col][array[row][i]] = 1;
		if (array[i][col])
			posibles[row][col][array[i][col]] = 1;
	}
	i = row / 3 * 3;
	j = col / 3 * 3;
	for (; i < (row / 3 * 3 + 3); i++)
	{
		for (j = col / 3 * 3; j < col / 3 * 3 + 3; j++)
		{
			if (i == 1 && j == 4 && array[i][j] == 6)
				printf("\n");
			posibles[row][col][array[i][j]] = 1;
		}
	}
	j = 0;
	int point = 0;
	//printf("不可能为:");
	for (i = 1; i < 10; i++)
	{
		if (posibles[row][col][i] == 0)
		{
			point = i;
			j++;
		}
		/*else
		{
			printf("%d\t",i);
		}*/
	}
	//printf("\n");
	pocount[row][col] = j;
	if (j == 1)
	{
		printf("\n%d,%d-> %d\n",row + 1,col + 1,point);
		array[row][col] = point;
		return true;
	}
	/*else
	{
		printf("->%d\n",j);
	}*/
	return false;
}

bool area(short row,short col)
{
	if (array[row][col])
		return false;
	bool flag = true;
	for (short i = 1; i < 10; i++)
	{
		if (posibles[row][col][i] == 0)
		{
			for (short j = 0; j < 9; j++)
			{
				if (j != row && pocount[j][col] > 1)
					flag &= posibles[j][col][i] == 1;
			}
			if (row == 0 && col == 5 && i == 6 && flag)
				printf("\n");
			if (flag)
			{
				goto end;
			}
			flag = true;
			for (short j = 0; j < 9; j++)
			{
				if (j != col && pocount[row][j] > 1)
					flag &= posibles[row][j][i] == 1;
			}
			if (row == 0 && col == 5 && i == 6 && flag)
				printf("\n");
			if (flag)
			{
				goto end;
			}
			flag = true;
			for (short j = row / 3 * 3; j < row / 3 * 3 + 3; j++)
			{
				for (short k = col / 3 * 3; k < col / 3 * 3 + 3; k++)
				{
					if (pocount[j][k] > 1 && (j != row || k != col))
						flag &= posibles[j][k][i] == 1;
				}
			}
			if (row == 0 && col == 5 && i == 6 && flag)
				printf("\n");
end:		if (flag)
			{
				array[row][col] = i;
				pocount[row][col] = 1;
				printf("\n%d,%d->%d\n",row+1,col+1,i);
				return flag;
			}
		}
	}
	return flag;;
}

void main2()
{
	//analysis(8,3);
	bool flag = false;
	/*for (short i = 0; i < 9; i++)
	{
	for (short j = 0; j < 9; j++)
	{
	if (array[i][j] == 0)
	{
	flag |= analysis(i, j);
	}
	}
	}*/
label1:for (short i = 0; i < 9; i++)
	{
		   printf("%d\n",i);
		for (short j = 0; j < 9; j++)
		{
			if (array[i][j] == 0)
			{
				flag |= analysis(i, j);
			}
		}
	}
	for (short i = 0; i < 9; i++)
	{
		for (short j = 0; j < 9; j++)
		{
			if (array[i][j] == 0)
			{
				if (area(i, j))
				{
					goto label1;
				}
			}
		}
	}
	
	   //flag |= area(0,2);

	if (flag)
	{
		flag = false;
		goto label1;
	 }

	system("pause");
}