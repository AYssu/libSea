#include <iostream>
#include <thread>
#include <string>
#include <unistd.h>
#include "include/Sea.h"

int main(int argc, char *argv[])
{
	setColor(COLOR_GREEN);
	printf("我是绿色\n");
	setColor(COLOR_SKY_BLUE);
	printf("我是天空蓝\n");
	setColor(COLOR_RED);
	printf("我是红色\n");
	setColor(COLOR_WHITE); // 恢复白色

	return 0;
}