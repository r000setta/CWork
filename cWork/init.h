#pragma once
#include<malloc.h>
#include<stdio.h>
#include <string.h>
#include<stdlib.h>
#include "GLOBAL.h"
#include "List.h"
#include "User.h"
int state = LOGOUT; //当前状态


/*
*@method: 打印教师页面
*@param: 
*@return: 
*@others:
*/
void teacherPrint() {
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	printf("请选择操作:\n");
	printf("1.查看所有图书\n");
	printf("2.添加图书\n");
	printf("3.删除图书\n");
	printf("4.查看学生\n");
	printf("5.查看教师信息\n");
	printf("6.登出\n");
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
}


/*
*@method: 打印初始页面
*@param:
*@return:
*@others:
*/
void initPrint() {
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	printf("图书管理系统V1.0\n");
	printf("请选择功能:\n");
	printf("1.查询书本\n");
	printf("2.登录(学生通道)\n");
	printf("3.登录(教师通道)\n");
	printf("4.关于作者\n");
	printf("5.登出.\n");
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
}


/*
*@method: 打印学生页面
*@param:
*@return:
*@others:
*/
void loginInitPrint() {
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	printf("请选择操作:\n");
	printf("1.查询书本\n");
	printf("2.我要借书\n");
	printf("3.我要还书\n");
	printf("4.查看个人情况\n");
	printf("5.登出.\n");
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
}


/*
*@method: 打印作者信息
*@param:
*@return:
*@others:
*/
void printAuthor() {
	printf("JQY\n");
}


/*
*@method: 教师登录主函数
*@param:
*@return:
*@others:
*/
void loginInitTeacher(char* ID,PNode List) {
	int i = getIndex(ID,"tea");
	Teacher teacher = teachers[i];
	printf("教师%s登陆成功!\n", teachers[i].name);
	state = LOGINTEA;
	int mode;
	while (state==LOGINTEA)
	{
		teacherPrint();
		scanf("%d", &mode);
		switch (mode)
		{
		case 1: {  //查询图书
			Traverse(List);
			break;
		}
		case 2: {  //添加图书
			int position;
			printf("请输入待插入的位置\n");
			scanf("%d", &position);
			Insert(List, position);
			break;
		}
		case 3: {	//删除图书
			int position;
			printf("请输入待删除的位置\n");
			scanf("%d", &position);
			Delete(List, position);
			break;
		}	
		case 4: {	//查看学生信息
			char ID[MAX];
			int i = getIndex(ID, "stu");
			printPerson(i);
			break;
		}
		case 5: {  //查看教师信息
			printTeacher(i);
			break;
		}
		case 6: {	//登出系统
			printf("登出\n");
			state = LOGOUT;
			break;
		}
		default:
			printf("尚无此功能,请重新输入!\n");
			break;
		}
	}
}


/*
*@method: 学生登录主函数
*@param:
*@return:
*@others:
*/
void loginInit(char* ID,PNode List) {
	int i = getIndex(ID,"stu");
	Person person = persons[i];
	printf("学生%s登录成功!\n", persons[i].name);
	state = LOGINSTU;
	int mode;
	while (state == LOGINSTU)
	{
		loginInitPrint();
		scanf("%d", &mode);
		switch (mode)
		{
		case 1: {		//搜索图书
			char ID[MAX];
			printf("请输入书的编号:");
			scanf("%s", ID);
			pBook book = SearchBook(List, ID);
			printBook(book);
			break;
		}
		case 2: {	//借阅图书
			char ID[MAX];
			printf("请输入书的编号:");
			scanf("%s", ID);
			pBook book = SearchBook(List, ID);
			printBook(book);
			if (book->left > 0) {
				int flag;
				printf("是否借阅该书?(1:是,0:否)\n");
				scanf("%d", &flag);
				if (flag == 1)
				{
					Borrow(i, book);
				}
			}
			else {
				printf("库存不足\n");
			}
			break;
		}	
		case 3://归还图书
		{
			char id[MAX];
			printf("请输入你要归还的图书编号\n");
			scanf("%s\n", id);
			if (returnBook(person, id))
				printf("还书成功\n");
			else {
				printf("还书失败!\n");
			}
			break;
		}
		case 4:		//查看个人资料
			printPerson(i);
			break;
		case 5:		//登出系统
			printf("登出\n");
			state = LOGOUT;
			break;
		default:
			printf("尚无此功能,请重新输入!\n");
			break;
		}
	}
}


/*
*@method: 初始化登录界面函数
*@param:
*@return:
*@others:
*/
void Init() {
	PNode head = Create();
	Traverse(head);
	int mode;
	char ID[MAX];
	while (state != EXIT) {
			initPrint();
			scanf("%d", &mode);
			switch (mode) {
			case 1: {
				char ID[MAX];
				printf("请输入书的编号:");
				scanf("%s", ID);
				pBook book = SearchBook(head, ID);
				printBook(book);
				break;
			}
					case 2:	//登录系统（学生）
					printf("请输入你的学号");
					scanf("%s", ID);
					if (Login(ID,"stu")) {
						loginInit(ID,head);
					}
					else {
						printf("登录失败\n");
					}
					break;
			case 3: {	//登录系统（教师）
				char ID[MAX];
				printf("请输入你的教师号\n");
				scanf("%s", ID);
				if (Login(ID,"tea"))
				{
					loginInitTeacher(ID, head);
				}
				else {
					printf("登录失败\n");
				}
				break;
			}

					
				case 4: //查看开发者信息
					printAuthor();
					break;
				case 5: //退出程序
					state = EXIT;
					break;
				default: 
					printf("尚无此功能,请重新输入!\n");
					break;
		}
	}
}

