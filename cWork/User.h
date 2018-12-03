#pragma once
#include<malloc.h>
#include<stdio.h>
#include <string.h>
#include<stdlib.h>
#include "GLOBAL.h"


//教师信息
typedef struct Teacher {
	char ID[MAX];
	char name[MAX];
	int priority;
}Teacher;


//学生信息
typedef struct Person {
	int priority;  //优先级
	char ID[MAX];  //学生ID
	char name[MAX];  //学生姓名
	int count;		//学生已借书目
	pBook borrow[BRORROW];  //学生借阅书本集合
	int overTime;	//超时书本
}Person,*pPerson;


int length = 5;
Person persons[5] = {
	{1,"1","Jack",0},
	{1,"2","Tom",0},
	{1,"3","Bruce",0},
	{1,"4","Alex",0},
	{1,"5","JQY",0}
};


int lengthT = 1;
Teacher teachers[1] = {
	{"1","Tea1",0}
};


/*
*@method: 打印教师信息
*@param:
*@return:
*@others:
*/
void printTeacher(int index) {
	Teacher teacher = teachers[index];
	printf("-----------------------------\n");
	printf("ID:%3s\n", teacher.ID);
	printf("姓名:%3s\n", teacher.name);
	printf("-----------------------------\n");
}


/*
*@method: 打印学生信息
*@param:
*@return:
*@others:
*/
void printPerson(int index) {
	printf("-----------------------------\n");
	printf("ID:%3s\n", persons[index].ID);
	printf("姓名:%3s\n", persons[index].name);
	printf("已借阅书本:%3d\n", persons[index].count);
	printf("可借阅书本:%3d\n",BRORROW-persons[index].count);
	printf("借阅超时书本:%3d\n", persons[index].overTime);
	printf("------------------------------\n");
}


/*
*@method: 登录系统函数
*@param:
*@return:
*@others:
*/
bool Login(char* ID,const char* type) {
	if (strcmp(type,"stu")==0)
	{
		for (int i = 0; i < length; i++) {
			if (strcmp(persons[i].ID, ID) == 0) {
				printf("登录成功!\n");
				return true;
			}
		}
		return false;
	}
	else if (strcmp(type, "tea") == 0) {
		for (int i = 0; i < lengthT; i++) {
			if (strcmp(teachers[i].ID, ID) == 0) {
				printf("登录成功!\n");
				return true;
			}
		}
		return false;
	}
	else {
		return false;
	}
}


/*
*@method: 获取具体用户
*@param:
*@return:
*@others:
*/
int getIndex(char* ID,const char type[]) {
	if (strcmp(type,"stu")==0)
	{
		for (int i = 0; i < length; i++) {
			if (strcmp(persons[i].ID, ID) == 0) {
				return i;
			}
		}
		printf("未找到\n");
		return -1;
	}
	else if (strcmp(type, "tea") == 0) {
		for (int i = 0; i < lengthT; i++) {
			if (strcmp(teachers[i].ID, ID) == 0) {
				return i;
			}
		}
		printf("未找到\n");
		return -1;
	}
	else {
		return -1;
	}
}


/*
*@method: 借书
*@param:
*@return:
*@others:
*/
void Borrow(int index, pBook book) {
	Person person = persons[index];
	person.borrow[person.count] = book;
	book->left--;
	person.count++;
	printf("借阅成功,书本剩余%d\n",book->left);
}


/*
*@method: 还书
*@param:
*@return:
*@others:
*/
bool returnBook(Person person,char ID[]) {
	for (int i = 0; i < person.count; i++) {
		pBook book = person.borrow[i];
		if (book->ID==ID)
		{
			book->left++;
			person.count--;
			person.borrow[i] = NULL;
			return true;
		}
	}
	return false;
}