#include "pch.h"
#include <stdio.h>
#include "List.h"
#include "init.h"

int main()
{
	FILE *f = NULL;
	f = fopen("D:/1.txt","r+");
	char buf[200];
	fgets(buf,200,f);
	fclose(f);
	printf("%s\n", buf);
	//Init();	
}
