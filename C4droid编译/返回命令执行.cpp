#include <iostream>
#include <thread>
#include <string>
#include <unistd.h>
#include "include/Sea.h"

int main(int argc, char *argv[])
{
	std::string 返回命令 = executeShellCommand("ls /sdcard");
	printf("返回的信息: %s",返回命令.c_str());
	return 0;
}