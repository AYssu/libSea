#include <iostream>
#include <thread>
#include <string>
#include <unistd.h>
#include "include/Sea.h"
using namespace std;
/// @brief 校验时间 传入目标时间 返回 对比时间/S

void t1()
{
	printf("\n时间校验开始\n");

	int TiemS = Timecheck(2023, 5, 23, 18, 33, 0);
	printf("剩余 %d S \n", TiemS);
	if (TiemS < 0)
	{
		printf("软件过期 %d ", TiemS);
	}
}

/// @brief 获取进程PID 理论通杀所有游戏
void t2()
{
	printf("\n进程获取开始\n");

	int pid = getPID("com.pubg.newstate");
	if (pid < 0)
	{
		printf("游戏未运行 捕捉进程失败！\n");
	}
	printf("游戏获取pid成功 %d \n",pid);
}

/// @brief mmap测试 传入任意类型数据 结构体 char int float ...
void t3()
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
}

/// @brief 定义终端的显示字体颜色
void t4()
{
	printf("\n颜色测试开始\n");

	setColor(COLOR_GREEN);
	printf("我是绿色\n");
	setColor(COLOR_SKY_BLUE);
	printf("我是天空蓝\n");
	setColor(COLOR_RED);
	printf("我是红色\n");
	setColor(COLOR_WHITE); // 恢复白色
}


int main(int argc, char *argv[])
{
    t1();
    t2();
    t3();
    t4();
    return 0;
}