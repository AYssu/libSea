#include <iostream>
#include <thread>
#include <string>
#include <unistd.h>
#include "include/Sea.h"

void T3_TestGG()
{
	T3_Json t3_Json{};
	int code = 200;
	T3_GG("http://w.t3yanzheng.com/499D930AE737D128", code, t3_Json);
	printf("T3公告:%s\n", t3_Json.msg.c_str());
}

void T3_TestGX()
{
	int version = 101;
	int code = 200;
	T3_Json t3_Json{};
	T3_GX("http://w.t3yanzheng.com/3E437A3B7C9A3193", code, version, t3_Json);
	if (t3_Json.isUpdate)
	{
		printf("更新公告:%s\n更新链接:%s\n", t3_Json.uplog.c_str(), t3_Json.upurl.c_str());
	}
	else
	{
		printf("其他提示:%s\n", t3_Json.msg.c_str());
	}
}

void T3_TestLOAD()
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
		sprintf(kami, "%s", "Y8178CEE3C905D896D5A3504CC1BA98B");
		sprintf(imei, "%s", "A5B2C0D1E3F1G4");
	}

	int code = 200;

	T3_Json t3_Json{};
	T3_LOAD(url, base64, key, kami, imei, code, t3_Json);

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
}

int main(int argc, char const *argv[])
{

	setSecurity(true,true,true);
	// 参数1 开启VPN检测 参数2 开启 网络抓包检测(Root有用) 参数3 打印更改信息
	T3_TestLOAD();
	T3_TestGX();
	T3_TestGG();
	return 0;
}