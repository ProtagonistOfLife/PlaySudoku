#include <stdio.h>
#include <stdlib.h>

#define SUM 1023

int array[9][9];
short flags[9][9];

void init3();
void clean(int row,int col);

int log2(int number){
	for (int i = 1; i < 10; i++){
		if (number >> i)
		{
			continue;
		}
		return i;
	}
}

void main(){
	
	init3();
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++){
			if (flags[i][j] == 1)
			{
				printf("%d\t",log2(array[i][j]));
			}
			else
			{
				printf("%d\t",array[i][j]);
			}
		}
		printf("\n");
	}
	system("pause");
}

void init3(){
	char string[81];
	gets_s(string);
	int num,row,col;
	for (int i = 0; i < 81; i++){
		row = i / 9;
		col = i % 9;
		num = string[i] - 48;
		if (num>0 && num<10)
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

	for (int i = 0; i < 9; i++){
		for (int j = 0; j < 9; j++)
		{
			if (flags[i][j] == 1){
				clean(i,j);
			}
		}
	}
}

//去除代码块
void clean(int i,int j){
	int num = array[i][j];
	for (int k = 0; k < 9; k++){
		if (array[i][k]&num && k !=j)
		{
			array[i][k] -= num;
			flags[i][k]--;
			if (flags[i][k] == 1)
			{
				clean(i,k);
				continue;
			}
		}
		if (array[k][j]&num && k!=i)
		{
			array[k][j] -= num;
			flags[k][j]--;
			if (flags[k][j] == 1)
			{
				clean(k, j);
				continue;
			}
		}
	}
	for (int a = (i / 3) * 3; a < (i / 3) * 4; a++){
		for (int b = (j / 3) * 3; a < (j / 3) * 4; b++)
		{
			if (array[a][b]&num && array[a][b] != num){
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

//分析代码块
void fenxi(){
	
}
//

