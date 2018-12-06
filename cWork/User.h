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
}Person, *pPerson;


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
void printTeacher(Teacher* teacher) {
	printf("-----------------------------\n");
	printf("ID:%3s\n", teacher->ID);
	printf("姓名:%3s\n", teacher->name);
	printf("-----------------------------\n");
}


/*
*@method: 打印学生信息
*@param:
*@return:
*@others:
*/
void printPerson(pPerson person) {
	printf("-----------------------------\n");
	printf("ID:%3s\n", person->ID);
	printf("姓名:%3s\n", person->name);
	printf("已借阅书本:%3d\n", person->count);
	printf("可借阅书本:%3d\n", BRORROW - person->count);
	printf("借阅超时书本:%3d\n", person->overTime);
	printf("------------------------------\n");
}


/*
*@method: 登录系统函数
*@param:
*@return:
*@others:
*/
bool Login(char* ID, const char* type) {
	if (strcmp(type, "stu") == 0)
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
*@method: 获取用户的index
*@param:
*@return:
*@others:
*/
int getIndex(char* ID, const char type[]) {
	if (strcmp(type, "stu") == 0)
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
*@param: index:学生序号(不是学号);book:待借书本
*@return:
*@others:
*/
void Borrow(pPerson person, pBook book) {
	person->borrow[person->count] = book;
	book->left--;
	book->total++;
	int t = book->count - book->left;
	for (int i = 0; i <t; i++) {
		if (book->info[i].available==true)
		{
			strcpy(book->info[i].ID, person->ID);
			book->info[i].available = false;
		}
	}
	person->count++;
	printf("借阅成功,书本剩余%d\n", book->left);
}


/*
*@method: 还书
*@param:person: 还书的学生;ID:待还书的ID
*@return: 还书是否成功
*@others:
*/
bool returnBook(pPerson person, char ID[MAX]) {
	for (int i = 0; i <= person->count; i++) {
		pBook book = person->borrow[i];
		int t = book->count - book->left;
		if (strcmp(book->ID , ID)==0)
		{
			for (int i = 0; i <= t; i++) {
				if (strcmp(book->info[i].ID,ID)==0)
				{
					book->info[i].available = true;
					strcpy(book->info[i].ID, "\0");
				}
			}
			book->left++;
			person->count--;
			person->borrow[i] = NULL;
			return true;
		}
	}
	return false;
}