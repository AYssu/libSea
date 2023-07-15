#include <iostream>
#include <thread>
#include <string>
#include <unistd.h>
#include "include/Sea.h"

int main(int argc, char *argv[])
{
	char *http = http_get("www.baidu.com");
	printf("读取内容:%s",http);
	char *post = http_post("www.abc.com","a=10&b=100");
	//随便写的例子 这么用就对了
	printf("提交返回内容:%s",post);
	return 0;
}