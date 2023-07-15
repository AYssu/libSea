#include <iostream>
#include <thread>
#include <string>
#include <unistd.h>
#include "include/Sea.h"

int main(int argc, char *argv[])
{
	bool VPN =  checkVPN();                                     // VPN检测
    bool HTTP =  checkHttp();                                    // 抓包检测
    bool Root =  Mem_isRoot();                                   // Root判断
	printf("VPN %d HTTP %d Root %d",VPN,HTTP,Root);
	return 0;
}