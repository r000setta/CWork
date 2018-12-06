#pragma once
#include<malloc.h>
#include<stdio.h>
#include <string.h>
#include<stdlib.h>
#include "GLOBAL.h"

typedef struct Info {
	char ID[MAX];
	int index;
	bool available;
}*pInfo, Info;

typedef struct BookTotal {

}BookTotal, *pBookTotal;
//ͼ����Ϣ
typedef struct Book {
	char ID[MAX];	//���
	char name[MAX];  //ͼ����
	char author[MAX];	//����
	int count;		//�ܿ��
	int left;		//ʣ������
	double price;	//ͼ�鵥��
	char date[MAX];	//��������
	TYPE type;   //ͼ�����
	char publisher[MAX];  //������
	int total;  //�ܹ�����Ĵ���
	Info info[MAXLENGTH];  //ά��ÿһ��ͼ������˭
}Book, *pBook;

//ͼ������
typedef struct ListNode {
	pBook book;  //ͼ����Ϣ
	struct ListNode* next;
}Node, *PNode;


/*
*@method: ���ͼ�麯��
*@param:
*@return: ��
*@others:
*/
void createBook(pBook book, char ID[MAX], char name[MAX], char author[MAX], int count, double price,
	char date[], TYPE type, char publisher[]) {
	strcpy(book->name, name);
	strcpy(book->ID, ID);
	strcpy(book->author, author);
	strcpy(book->publisher, publisher);
	strcpy(book->date, date);
	book->count = count;
	book->price = price;
	book->left = count;
	book->total = 0;
	for (int i = 0; i < MAXLENGTH; i++) {
		book->info[i].available=true;
	}
}
/*
*@method: ��ӡͼ�麯��
*@param: book:����ӡ��ͼ��
*@return: ��
*@others:
*/
void printBook(pBook book) {
	int t = book->count - book->left;
	printf("-------------------------------------------\n");
	printf("���:%8s\n", book->ID);
	printf("����:%8s\n", book->name);
	printf("����:%8s\n", book->author);
	printf("�۸�:%8lf\n", book->price);
	printf("������:%8s\n", book->publisher);
	printf("����:%8d\n", book->count);
	printf("���:%8d\n", book->left);
	printf("�����ѽ��%d��\n", book->total);
	for (int i = 0; i <t; i++) {
		if (book->info[i].available==false) {
			printf("��%d��������IDΪ%s��ͬѧ\n", i + 1, book->info[i].ID);
		}
	}
	if (book->left > 0) {
		printf("�ɽ���\n");
	}
	else {
		printf("�ѽ��\n");
	}
	printf("-------------------------------------------\n");
}
/*
*@method: ����ͼ��������ʼ��
*@param: ��
*@return: ������ͼ�������ͷָ��
*@others:
*/
PNode Create() {
	char ID[MAX], publisher[MAX], author[MAX], name[MAX], date[MAX];
	int len, count;
	double price;
	TYPE type;
	printf("�������ʼ���鱾:");
	scanf("%d", &len);
	PNode head = (PNode)calloc(1,sizeof(Node));
	if (head == NULL) {
		printf("����ʧ��!\n");
		exit(-1);
	}
	PNode tail = head;
	tail->next = NULL;
	for (int i = 1; i <= len; i++) {
		PNode pNew = (PNode)calloc(1,sizeof(Node));
		if (pNew == NULL)
		{
			printf("����ʧ��!\n");
			exit(-1);
		}
		pNew->book = (pBook)calloc(1,sizeof(Book)); //�����鱾
		printf("�������%d���������", i);
		scanf("%s", name);
		printf("�������%d���������", i);
		scanf("%s", author);
		printf("�������%d����ı��", i);
		scanf("%s", ID);
		printf("�������%d���������", i);
		scanf("%d", &count);
		printf("�������%d���������", i);
		scanf("%s", publisher);
		printf("�������%d���鷢������", i);
		scanf("%s", date);
		printf("�������%d����۸�", i);
		scanf("%lf", &price);
		printf("�������%d��������", i);
		scanf("%d", &type);
		createBook(pNew->book, ID, name, author, count, price, date, type, publisher);
		printf("��%d������ӳɹ�!\n", i);
		tail->next = pNew;
		pNew->next = NULL;
		tail = pNew;
	}
	return head;
}
/*
*@method: ����ͼ������
*@param: List��������������
*@return: ��
*@others:
*/
void Traverse(PNode List) {
	PNode p = List->next;
	int i = 1;
	if (p == NULL)
		printf("��ǰĿ¼Ϊ��\n");
	while (p != NULL)
	{
		printf(">>>>>>>>>>>>>��%d����<<<<<<<<<<<<\n", i);
		printBook(p->book);
		p = p->next;
		i++;
	}
}
/*
*@method: ����ͼ��
*@param: List:�����������;
*@return:void
*@others: �޸�Ϊβ��
*/
void Insert(PNode List) {
	char ID[MAX], publisher[MAX], author[MAX], name[MAX], date[MAX];
	int count;
	double price;
	TYPE type;
	int position = 0;
	PNode p = List;
	while (p != NULL)
	{
		p = p->next;
	}
	PNode tmp = (PNode)malloc(sizeof(PNode));
	if (tmp == NULL) {
		printf("����ʧ��!\n");
		exit(-1);
	}
	//����ڵ�
	tmp->book = (pBook)malloc(sizeof(Book));
	printf("����������");
	scanf("%s", name);
	printf("�������������");
	scanf("%s", author);
	printf("��������ı��");
	scanf("%s", ID);
	printf("�������������");
	scanf("%d", &count);
	printf("�������������");
	scanf("%s", publisher);
	printf("�������鷢������");
	scanf("%s", date);
	printf("��������۸�");
	scanf("%lf", &price);
	printf("������������");
	scanf("%d", &type);
	createBook(tmp->book, ID, name, author, count, price, date, type, publisher);
	tmp->next = p->next;
	p->next = tmp;
	printf("ͼ����ӳɹ�!\n");
}
/*
*@method: ɾ��ָ��λ�õ�ͼ��
*@param: List:��ɾ����ͼ������;ID: ��ɾ����ͼ��ID���
*@return: Void
*@others:  �޸�Ϊ����IDɾ��ͼ��
*/
void Delete(PNode List,char* ID) {
	PNode p = List;
	while (p != NULL && strcmp(p->book->ID,ID)!=0) {
		p = p->next;
	}
	//��ɾ���ڵ�
	PNode tmp = p->next;
	p->next = tmp->next;
	free(tmp);
	tmp = NULL;
	printf("ͼ��ɾ���ɹ�!\n");
}
/*
*@method: ���ͼ������
*@param: ����յ�����
*@return: ��
*@others:
*/
void Clear(PNode List) {
	PNode p = List->next, tmp;
	while (p != NULL) {
		tmp = p->next;
		free(p);
		p = tmp;
	}
	printf("ͼ���������\n");
}
/*
*@method: ����ͼ�麯��
*@param: List:������������;ID:������ͼ��ı��
*@return: ��������ͼ��ڵ�
*@others:
*/
pBook SearchBook(PNode List, char* ID) {
	PNode p = List->next;
	while (p != NULL && strcmp(p->book->ID, ID) != 0) {
		p = p->next;
	}
	if (p != NULL)
	{
		return p->book;
	}
	else {
		return NULL;
	}
}