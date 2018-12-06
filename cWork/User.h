#pragma once
#include<malloc.h>
#include<stdio.h>
#include <string.h>
#include<stdlib.h>
#include "GLOBAL.h"


//��ʦ��Ϣ
typedef struct Teacher {
	char ID[MAX];
	char name[MAX];
	int priority;
}Teacher;


//ѧ����Ϣ
typedef struct Person {
	int priority;  //���ȼ�
	char ID[MAX];  //ѧ��ID
	char name[MAX];  //ѧ������
	int count;		//ѧ���ѽ���Ŀ
	pBook borrow[BRORROW];  //ѧ�������鱾����
	int overTime;	//��ʱ�鱾
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
*@method: ��ӡ��ʦ��Ϣ
*@param:
*@return:
*@others:
*/
void printTeacher(Teacher* teacher) {
	printf("-----------------------------\n");
	printf("ID:%3s\n", teacher->ID);
	printf("����:%3s\n", teacher->name);
	printf("-----------------------------\n");
}


/*
*@method: ��ӡѧ����Ϣ
*@param:
*@return:
*@others:
*/
void printPerson(pPerson person) {
	printf("-----------------------------\n");
	printf("ID:%3s\n", person->ID);
	printf("����:%3s\n", person->name);
	printf("�ѽ����鱾:%3d\n", person->count);
	printf("�ɽ����鱾:%3d\n", BRORROW - person->count);
	printf("���ĳ�ʱ�鱾:%3d\n", person->overTime);
	printf("------------------------------\n");
}


/*
*@method: ��¼ϵͳ����
*@param:
*@return:
*@others:
*/
bool Login(char* ID, const char* type) {
	if (strcmp(type, "stu") == 0)
	{
		for (int i = 0; i < length; i++) {
			if (strcmp(persons[i].ID, ID) == 0) {
				printf("��¼�ɹ�!\n");
				return true;
			}
		}
		return false;
	}
	else if (strcmp(type, "tea") == 0) {
		for (int i = 0; i < lengthT; i++) {
			if (strcmp(teachers[i].ID, ID) == 0) {
				printf("��¼�ɹ�!\n");
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
*@method: ��ȡ�û���index
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
		printf("δ�ҵ�\n");
		return -1;
	}
	else if (strcmp(type, "tea") == 0) {
		for (int i = 0; i < lengthT; i++) {
			if (strcmp(teachers[i].ID, ID) == 0) {
				return i;
			}
		}
		printf("δ�ҵ�\n");
		return -1;
	}
	else {
		return -1;
	}
}


/*
*@method: ����
*@param: index:ѧ�����(����ѧ��);book:�����鱾
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
	printf("���ĳɹ�,�鱾ʣ��%d\n", book->left);
}


/*
*@method: ����
*@param:person: �����ѧ��;ID:�������ID
*@return: �����Ƿ�ɹ�
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