#include <stdio.h>
#include <stdlib.h>

#define SUM 511
#define FALSE 0
#define TRUE 1

int array[9][9];
short flags[9][9];

void init3();
void clean(int row, int col);
void fenxi();

int log2(int number){
	int i = 0;
	for (; i < 10; i++){
		if (number >> i == 0)
		{
			break;
		}
	}
	return i;


}

//比较两个字符串数组是否相等
int equals(char* cs1, char* cs2){
	int length = sizeof(cs1) > sizeof(cs2) ? sizeof(cs1) : sizeof(cs2);
	length /= sizeof(char);
	for (int i = 0; i < length; i++){
		if (cs1[i] != cs2[i])
		{
			return FALSE;
		}
	}
	return true;
}

void main(){
	char script[20];
	int w = 0;
start:
	init3();
jisuan:
	//清除可能未知框中的可能性
	for (int i = 0; i < 9; i++){
		for (int j = 0; j < 9; j++)
		{
			if (flags[i][j] == 1){
				clean(i, j);
			}
		}
	}
	fenxi();
	while (w < 100)
	{
		w++;
		goto jisuan;
	}
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++){
			if (flags[i][j] == 1)
			{
				printf("%d\t", log2(array[i][j]));
			}
			else
			{
				printf("%d(B)\t", array[i][j]);
			}
		}
		printf("\n");
	}
	gets_s(script);
	if (!equals(script, "over")){
		goto start;
	}
	system("pause");
}

//通过输入的数据初始化数独数组中的数据
void init3(){
	char string[82];
	gets_s(string);
	int num, row, col;
	for (int i = 0; i < 81; i++){
		row = i / 9;
		col = i % 9;
		num = string[i] - 49;
		if (num>-1 && num < 9)
		{
			num = 1 << num;
			flags[row][col] = 1;
		}
		else
		{
			num = SUM;
			flags[row][col] = 9;
		}
		array[row][col] = num;
	}
}

//去可能性
void clean(int i, int j){
	int num = array[i][j];
	for (int k = 0; k < 9; k++){
		if (array[i][k] & num && k != j)
		{
			array[i][k] -= num;
			if (array[i][k] == 0)
			{
				printf("");
			}
			flags[i][k]--;
			if (flags[i][k] == 1)
			{
				clean(i, k);
			}
		}
		if (array[k][j] & num && k != i)
		{
			array[k][j] -= num;
			flags[k][j]--;
			if (flags[k][j] == 1)
			{
				clean(k, j);
			}
		}
	}
	for (int a = (i / 3) * 3; a < (i / 3 + 1) * 3; a++){
		for (int b = (j / 3) * 3; b < (j / 3 + 1) * 3; b++)
		{
			if (array[a][b] & num && array[a][b] != num){
				array[a][b] -= num;
				flags[a][b]--;
				if (flags[a][b] == 1)
				{
					clean(a, b);
					continue;
				}
			}
		}
	}
}

//行间排除分析
void colExclude(){
	int col;
	int num, tempnum;
	for (int i = 0; i < 9; i++){
		col = -1;
		tempnum = 1;
		for (int j = 0; j < 9; j++)
		{
			tempnum <<= 1;
			for (int k = 0; k < 9; k++){
				if (flags[i][k] == 1)
					continue;
				if (array[i][k] & tempnum && col < 0){
					col = k;
					num = tempnum;
				}
				else
				{
					col = -1;
					break;
				}
			}
			if (col > -1)
			{
				flags[i][col] = 1;
				array[i][col] = num;
				clean(i, col);
			}
		}
	}
}

//列间排除分析
void rowExclude(){
	int row;
	int num, tempnum;
	for (int i = 0; i < 9; i++){
		row = -1;
		tempnum = 1;
		for (int j = 0; j < 9; j++)
		{
			tempnum <<= 1;
			for (int k = 0; k < 9; k++){
				if (flags[k][i] == 1)
					continue;
				if (array[k][i] & tempnum && row < 0){
					row = k;
					num = tempnum;
				}
				else
				{
					row = -1;
					break;
				}
			}
			if (row > -1)
			{
				flags[row][i] = 1;
				array[row][i] = num;
				clean(row, i);
			}
		}
	}
}

void cleanrowpossible(int row, int number, int num){
	for (int i = 0; i < 9; i++)
	{
		if (i /3 != number && number & array[row][i])
		{
			array[row][i] -= num;
		}
	}
}

void cleancolpossible(int col, int number, int num){
	for (int i = 0; i < 9; i++)
	{
		if (i / 3 != number && number & array[i][col])
		{
			array[i][col] -= num;
		}
	}
}

void delrowpossible(){
	int tempnum,num, row;
	int row_start, col_start;
	for (int i = 0; i < 9; i++)
	{
		row_start = i / 3 * 3;
		col_start = i % 3 * 3;
		for (int j = row_start; j < row_start + 3; j++){
			tempnum = SUM;
			for (int k = col_start; k < col_start + 3; k++){
				if (flags[j][k] > 1)
				{
					tempnum &= array[j][k];
				}
			}
			if (tempnum == 0)
			{
				continue;
			}
			for (int m = row_start; m < row_start + 3; m++){
				if (m == j)
				{
					continue;
				}
				for (int n = col_start;n < col_start+3; n++)
				{
					num = tempnum & array[m][n];
					if (num)
					{
						tempnum -= num;
						continue;
					}
					if (!tempnum)
					{
						break;
					}
				}
				if (!tempnum){
					break;
				}
			}
			if (!tempnum)
			{
				continue;
			}
			cleanrowpossible(j, i, tempnum);
		}
	}
}

void delcolpossible(){
	int tempnum, num, row;
	int row_start, col_start;
	for (int i = 0; i < 9; i++)
	{
		row_start = i / 3 * 3;
		col_start = i % 3 * 3;
		for (int j = col_start; j < col_start + 3; j++){
			tempnum = SUM;
			for (int k = row_start; k < row_start + 3; k++){
				if (flags[k][j] > 1)
				{
					tempnum &= array[k][j];
				}
			}
			if (tempnum == 0)
			{
				continue;
			}
			for (int m = col_start; m < col_start + 3; m++){
				if (m == j)
				{
					continue;
				}
				for (int n = row_start; n < row_start + 3; n++)
				{
					num = tempnum & array[n][m];
					if (num)
					{
						tempnum -= num;
						continue;
					}
					if (!tempnum)
					{
						break;
					}
				}
				if (!tempnum){
					break;
				}
			}
			if (!tempnum)
			{
				continue;
			}
			cleancolpossible(j, i, tempnum);
		}
	}
}

//田间排除分析(计算有问题，暂时挂起)
void tianExclude(){
	int row, col, num, tempnum;
	int row_start, col_start;
	for (int m = 0; m < 9; m++){
		row = -1;
		row_start = m / 3 * 3;
		col_start = m % 3 * 3;
		tempnum = 1;
	label1:
		row = -1;
		col = -1;
		for (int i = row_start; i < row_start + 3; i++){
			for (int j = col_start; j < col_start + 3; j++)
			{
				if (i == 2 && j == 3)
				{
					printf("");
				}
				if (flags[i][j] == 1)
				{
					continue;
				}
				if (tempnum&array[i][j])
				{
					if (row == -1 && col == -1)
					{
						row = i; col = j;
						num = tempnum;
					}
					else
					{
						row = -1;
						break;
					}
				}
			}
			//表示已存在相同的可能性时跳出
			if (row == -1 && col > -1)
			{
				break;
			}
		}
		if (row > -1 & col > -1)
		{
			if (row == 3 && col == 0)
			{
				printf("");
			}
			flags[row][col] = 1;
			array[row][col] = num;
			clean(row, col);
		}
		tempnum <<= 1;
		if (tempnum < 257){
			goto label1;

		}
	}
}



//分析代码块
void fenxi(){
	rowExclude();
	colExclude();
	tianExclude();
	//出现了负数,暂时注释掉
//	delcolpossible();
//	delrowpossible();
}
//