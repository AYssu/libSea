#include <iostream>
#include <thread>
#include <string>
#include <unistd.h>
#include "include/Sea.h"


int main(int argc, char *argv[])
{
	int pid = getPID("com.pubg.newstate");
	//此pid为临时变量 
	if (pid <= 0)
	{
		printf("游戏未运行 捕捉进程失败！\n");
		exit(1);
	}
	printf("游戏获取pid成功 %d \n",pid);
    return 0;
}