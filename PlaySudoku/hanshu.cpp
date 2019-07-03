#include <stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct params{
	char* string;
	int sum;
}params;

/**
计算string中有多少个与pattern匹配的字符串数量
*/
int count(char* string, char* pattern)
{
	int count = 0;
	for (int i = 0; string[i]!='\0'; i++)
	{
		if (string[i] == pattern[0])
		{
			count++;
			i++;
			for (int j = 1; pattern[j]!='\0'; j++, i++)
			{
				if (string[i] != pattern[j])
				{
					count--;
					i--;
					break;
				}
			}
		}
	}
	return count;
}

/**
获取第n个子串的索引位置
*/
int getindex(char* string, char* pattern, int count)
{
	int index = 0;
	for (int i = 0; string[i] != '\0'; i++)
	{
		if (string[i] == pattern[0])
		{
			index = i;
			count--;
			i++;
			for (int j = 1; pattern[j] != '\0'; j++, i++)
			{
				if (string[i] != pattern[j])
				{
					count++;
					i = i  - j;
					break;
				}
			}
		}
		if (!count)
		{
			return index;
		}
	}
	return NULL;
}

/*
用于获取字符串中的子串
*/
char* substring(char* string, int start, int end)
{
	char* sub = (char*)malloc(sizeof(char) * (end - start));
	for (int i = start; i < end; i++)
	{
		sub[i - start] = string[i];
	}
	return sub;
}

char** split(char* string, char* pattern)
{
	int length = count(string, pattern);
	int endindex = 0;
	int preindex = 0;
	int patternsize = strlen(pattern);
	if (!length)
	{
		return NULL;
	}
	char** array = (char**)malloc(sizeof(char*)*(length + 1));
	for (int i = 0; i < length + 1; i++)
	{
		endindex = getindex(string, pattern, i);
		array[i] = substring(string, preindex, endindex);
		preindex +=  patternsize;
	}
	return array;
}

void freestrarray(char** array)
{
	for (int i = 0; i < sizeof(array) / sizeof(char); i++)
	{
		free(array[i]);
	}
}

char* doreplace(char* calstring,char* aimstring)
{
	return NULL;
}

char** equalsplit(char* string)
{
	
	return NULL;
}

void main3()
{
	char* str = "are you ok?";
	char* pattern = "o";
	//printf("%d", count(str, pattern));
	//printf("%d", getindex(str, pattern,1));
	char** strings = split(str, pattern);
	//freestrarray(strings);
	system("pause");
}