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

int Test_T3_Login()
{
    const char *url = (char *)"http://w.t3yanzheng.com/E5633A3CA5023084";
	const char *unurl = (char *)"http://w.t3yanzheng.com/520AE8C6B453B9C0";
	const char *base64 = (char *)"bCY/Pxg0VMUsXahjNIoi4LDzfAKRZTQ7S3dkWvOqwl9Jycnm1p5Ft6uBHr+2EeG8";
	const char *key = (char *)"aa199d730b93da766143de1fe640bcb2";

	char *kami = (char *)malloc(512);
	char *imei = (char *)malloc(512);
	if (access("/sdcard/kami", F_OK) == 0 && access("/sdcard/imei", F_OK) == 0)
	{
		sprintf(kami, "%s", Read("/sdcard/kami"));
		sprintf(imei, "%s", Read("/sdcard/imei"));
	}
	else
	{
		sprintf(kami, "%s", "STY6AB2108B713C6D60C969D8BA87CBE");
		sprintf(imei, "%s", "A5B2C0D1E3F1G4");
	}

	int code = 200;

	T3_Json t3_Json{};
	T3_LogIn(url, base64, key, kami, imei, code, t3_Json);

	if (!t3_Json.isLogin)
	{
		printf("kami: %s imei: %s 登录失败:%s\n", kami, imei, t3_Json.msg.c_str());
		exit(1);
	}
	else
	{
		char *timeBuff = (char *)malloc(512);
		printf("登录成功!\n到期时间:%s \n", t3_Json.end_time.c_str());
	}
	free(kami);
	free(imei);
    return 0;
}

int Test_T3_Updata()
{
    int version = 1029;
	int code = 200;
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

int Test_T3_Notice()
{
    T3_Json t3_Json{};
	int code = 200;
	T3_Notice("http://w.t3yanzheng.com/499D930AE737D128", code, t3_Json);
	printf("T3公告:%s\n", t3_Json.msg.c_str());
    return 0;
}

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
int main(int argc, char const *argv[])
{
    /* code */
    Test_T3_Notice();
    Test_mmap();
    
    return 0;
}