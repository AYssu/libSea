#include <iostream>
#include <thread>
#include <string>
#include <unistd.h>
#include "include/Sea.h"


int main(int argc, char *argv[])
{
    printf("\nmmap测试开始\n");
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

	response = (Response*)build_mmap("/sdcard/mmap", false, sizeof(Response)); // false 可读可写
	recive = (Response*)build_mmap("/sdcard/mmap", true, sizeof(Response));	// true 只读 只用来访问数据

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