#include <stdio.h>
#include <stdlib.h>

#define SUM 511
#define FALSE 0
#define TRUE 1

int array[9][9];
short flags[9][9];

void init3();
void clean(int row,int col);

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
start:	init3();
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
	gets_s(script);
	if (!equals(script, "over")){
		goto start;
	}
	system("pause");
}

void init3(){
	char string[82];
	gets_s(string);
	int num,row,col;
	for (int i = 0; i < 81; i++){
		row = i / 9;
		col = i % 9;
		num = string[i] - 49;
		if (num>-1 && num<9)
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
			}
		}
		if (array[k][j]&num && k!=i)
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

