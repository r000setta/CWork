#pragma once
/*全局变量及宏定义*/


#define MAX 20			//最长名字字段
#define MAXLENGTH 999	//最多存放图书
#define MAXPERSON 20	//最多学生数量
#define BRORROW 5		//学生最多借阅图书本数
#define TIME 30			//单次借阅最长事件
#define RENEWTIMES 2	//单本图书最长续借次数

/*
状态变量
*/
#define LOGINSTU 1		//学生登录
#define LOGINTEA 2		//教师登录
#define LOGOUT 0		//登出
#define EXIT -1			//退出系统


/*
其他
*/
typedef enum TYPE{  //图书种类枚举
	NOVEL,ESSAY,POEM,TECH,
}TYPE;