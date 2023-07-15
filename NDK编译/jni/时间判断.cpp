#include <iostream>
#include <thread>
#include <string>
#include <unistd.h>
#include "include/Sea.h"


int main(int argc, char *argv[])
{
  
	int TiemS = Timecheck(2025, 5, 23, 18, 33, 0);
    //设置目标时间
	printf("剩余 %d S \n", TiemS);
	if (TiemS < 0)
	{
		printf("软件过期 %d ", TiemS);
	}
    return 0;
}