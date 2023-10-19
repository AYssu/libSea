#include <stdio.h>
#include <ctime>
#include <dirent.h>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <malloc.h>
#include <pthread.h>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <sys/mman.h>
#include <thread>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <ctype.h>
#include <chrono>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <ctype.h>
#include <string>
#include "include/Sea.hpp"


int Test_mmap()
{
	struct Response
	{
		char name[4096];
		float x;
		float y;
		float w;
		//....
	};

	Response *response; // 好习惯嗷
	Response *recive;

	response = (Response *)build_mmap("/sdcard/mmap", false, sizeof(Response)); // false 可读可写
	recive = (Response *)build_mmap("/sdcard/mmap", true, sizeof(Response));	// true 只读 只用来访问数据

	for (size_t i = 0; i < 10; i++)
	{
		sprintf(response->name, "%s", "阿夜");
		response->x = (float)i; // 更改response recive映射的地址相同也会随之改变 实现最高效率数据交互
		response->y = (float)i * 2;
		response->w = (float)i * 3;
		printf("name-> %s X-> %.2f Y-> %.2f W -> %.2f\n", recive->name, recive->x, recive->y, recive->w); // 注意这边是打印的recive的结构体映射
		usleep(30000);
	}
	return 0;
}

#include "include/Sea.hpp"

int main(int argc, char const *argv[])
{
	//在后台验证的是code 不是那个版本号 注意区分
	int version = 1029;
	int code = 200;
	//状态码
	T3_Json t3_Json{};
	T3_Update("http://w.t3yanzheng.com/3E437A3B7C9A3193", code, version, t3_Json);
	if (t3_Json.isUpdate)
	{
		printf("更新公告:%s\n更新链接:%s\n", t3_Json.uplog.c_str(), t3_Json.upurl.c_str());
	}
	else
	{
		printf("其他提示:%s\n", t3_Json.msg.c_str());
	}
	return 0;
}