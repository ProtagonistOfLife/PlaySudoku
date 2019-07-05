#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

#define SUM 45
#define NULL 0

typedef struct linked{
	int row;
	int col;
	int value;
	char fun;
	int count;
	struct linked* next;
}*LINK;

typedef struct equation{
	LINK links;
	int sum;
	int count;
}EQUATION;

int arrays[9][9];
EQUATION equations[27];

//方程式解法初始化
void equation_init(){
	char string[82];
	gets_s(string);
	int row, col;
	for (int i = 0; i < 81; i++){
		row = i / 9;
		col = i % 9;
		arrays[row][col] = string[i] - 48;
	}
	int LINK_size = sizeof(LINK);
	int EQUATION_size = sizeof(EQUATION);

	LINK node = NULL;

	EQUATION *equation_row, *equation_col;
	LINK row_line, col_line;
	for (int i = 0; i < 9; i++){
		equation_row = (EQUATION*)malloc(EQUATION_size);
		equation_row->count = 9;
		equation_col = (EQUATION*)malloc(EQUATION_size);
		equation_col->count = 9;
		equation_row->sum = SUM;
		equation_col->sum = SUM;
		row_line = (LINK)malloc(LINK_size);
		equation_row->links = (LINK)malloc(LINK_size);
		equation_row->links->next = row_line;
		col_line = (LINK)malloc(LINK_size);
		equation_col->links = (LINK)malloc(LINK_size);
		equation_col->links->next = col_line;
		for (int j = 0; j < 9; j++){
			row_line->row = i;
			row_line->col = j;
			row_line->value = arrays[i][j];
			row_line->fun = '+';

			col_line->row = j;
			col_line->col = i;
			col_line->value = arrays[j][i];
			col_line->fun = '+';
			
			row_line->next = (LINK)malloc(LINK_size);
			row_line = row_line->next;
			col_line->next = (LINK)malloc(LINK_size);
			col_line = col_line->next;
		}
		equations[i] = *equation_row;
		equations[i + 9] = *equation_col;
	}

	int row_start, col_start;
	for (int i = 0; i < 9; i++)
	{
		row_line = (LINK)malloc(LINK_size);
		equation_row = (EQUATION*)malloc(EQUATION_size);
		equation_row->count = 9;
		equation_row->links = (LINK)malloc(LINK_size);
		equation_row->links->next = row_line;
		equation_row->sum = SUM;
		row_start = i / 3 * 3;
		col_start = i % 3 * 3;
		for (int j = row_start; j < row_start+3; j++)
		{
			for (int k = col_start; k < col_start; k++){
				row_line->row = j;
				row_line->col = k;
				row_line->value = arrays[j][k];
				row_line->fun = '+';

				row_line->next = (LINK)malloc(LINK_size);
				row_line = row_line->next;
			}
		}
		equations[18 + i] = *equation_row;
	}
}

void optimize(EQUATION eq){
	LINK before= eq.links;
	LINK next = eq.links->next;
	while (next->next)
	{
		if (next->value > 0)
		{
			eq.sum -= next->value;
			before->next = next->next;
			free(next);
			next = before->next;
			eq.count--;
		}
		else if (next->next == NULL)
		{
			before->next = NULL;
			free(next);
		}
		else
		{
			before = next;
			next = next->next;
		}
	}

}

void main5(){
	equation_init();
	for (int i = 0; i < 27; i++)
	{
		optimize(equations[i]);
		if (equations[i].count == 0){
			free(equations[i].links);
			free(&(equations[i]));
		}
	}

}