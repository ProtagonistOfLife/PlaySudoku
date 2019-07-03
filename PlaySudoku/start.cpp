#include<stdio.h>
#include<stdlib.h>

short sudoku[9][9] = { 0 };
//剩余需要填写值的数量
short remain = 81;
short possible[9][9][9];
//每个格子可能的数量
short pcount[9][9];

void init()
{
	//可能值pssible数组的修改
	for (short x = 0; x < 9; x++)
	{
		for (short y = 0; y < 9; y++)
		{
			for (short z = 0; z < 9;z++)
			{
				possible[x][y][z] = z + 1;
			}
		}
	}
	//数独值sudoku中的值归0处理
	for (short x = 0; x < 9; x++)
	{
		for (short y = 0; y < 9; y++)
		{
			sudoku[x][y] = 0;
		}
	}
	for (short x = 0; x < 9; x++)
	{
		for (short y = 0; y < 9; y++)
		{
			pcount[x][y] = 9;
		}
	}
	remain = 81;
}

//将可能的数据进行整理
bool dealpossible(int row, int col)
{
	int point =0;
	for (int i = 0; i < 9; i++)
	{
		if (possible[row][col][i] == 0)
			continue;
		if (point == i)
		{
			point++;
			continue;
		}
		possible[row][col][point] = possible[row][col][i];
		possible[row][col][i] = 0;
	}
	if (possible[row][col][1] == 0)
	{
		if (possible[row][col][0] == 0)
			exit(-1);
		sudoku[row][col] = possible[row][col][0];
		remain--;
		return true;
	}
	return false;
}

void copyarray(short oldarray[9][9],short newarray[9][9])
{
	for (short i = 0; i < 9; i++)
	{
		for (short j = 0; j < 9; j++)
		{
			newarray[i][j] = oldarray[i][j];
		}
	}
}

//行排除
bool rowanalysis(int row,int col)
{
	short count = 0;
	for (short i = 0; i < pcount[row][col]; i++)
	{
		for (short y = 0; y < 9; y++)
		{
			if (possible[row][col][i] == sudoku[row][y])
			{
				possible[row][col][i] = 0;
				count++;
				break;
			}
		}
	}
	pcount[row][col] -= count;
	if (count)
		return dealpossible(row,col);
	return false;
}

bool colanalysis(int row, int col)
{
	short count = 0;
	for (short i = 0; i < pcount[row][col]; i++)
	{
		for (short y = 0; y < 9; y++)
		{
			if (possible[row][col][i] == sudoku[y][col])
			{
				possible[row][col][i] = 0;
				count++;
				break;
			}
		}
	}
	pcount[row][col] -= count;
	if (count)
		return dealpossible(row, col);
	return false;
}

void tableanalysis(int row, int col)
{

}

void test()
{
	init();
	short temp[9][9] = { 
	{ 4, 0, 2, 6, 0, 0, 0, 1, 8 }, 
	{ 6, 0, 7, 0, 0, 9, 2, 0, 0 }, 
	{ 8, 0, 0, 0, 0, 0, 0, 0, 7 },
	{ 5, 0, 3, 0, 6, 8, 0, 7, 0 }, 
	{ 0, 0, 6, 5, 0, 2, 3, 0, 0 }, 
	{ 0, 7, 0, 1, 3, 0, 6, 0, 5 }, 
	{ 9, 0, 0, 0, 0, 0, 0, 0, 6 }, 
	{ 0, 0, 1, 4, 0, 0, 7, 0, 9 }, 
	{ 7, 2, 0, 0, 0, 6, 5, 0, 1 }
	};
	/*short temp[9][9] = {
		{ 0, 1, 2, 3, 4, 5, 6, 7, 8 }, 
		{ 2, 4, 6, 8, 0, 1, 3, 5, 7 }, 
		{ 0, 3, 0, 5, 4, 6, 9, 8, 7 }, 
		{ 0, 5, 2, 3, 4, 6, 7, 8, 9 }, 
		{ 0, 8, 5, 9, 4, 6, 1, 2, 3 }, 
		{ 5, 8, 4, 7, 0, 1, 6, 9, 3 }
	};*/
	copyarray(temp, sudoku);
	for (short i = 0; i < 9; i++)
	{
		for (short j = 0; j < 9; j++)
		{
			if (sudoku[i][j] > 0)
				printf("%d\t", sudoku[i][j]);
			else
				printf("\t");
		}
		printf("\n\n");
	}
	for (short i = 0; i < 9; i++)
	{
		for (short j = 0; j < 9; j++)
		{
			if (sudoku[i][j] == 0)
			{
				rowanalysis(i, j);
				//colanalysis(i, j);
			}
		}
	}
	printf("------------------------------------------------\n");
	for (short i = 0; i < 9; i++)
	{
		for (short j = 0; j < 9; j++)
		{
			if (sudoku[i][j] > 0)
				printf("%d\t", sudoku[i][j]);
			else
				printf("\t");
		}
		printf("\n\n");
	}
}

void main1()
{
	/*init();
	for (short i = 0; i < 9; i++)
	{
		for (short j = 0; j < 9; j++)
		{
			printf("%d\t",pcount[i][j]);
		}
		printf("\n");
	}*/
	test();
	system("pause");
}