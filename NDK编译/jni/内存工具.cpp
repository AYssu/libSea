#include <iostream>
#include <thread>
#include <string>
#include <unistd.h>
#include "include/Sea.h"

int main(int argc, char *argv[])
{
	int pid = getPID("com.pubg.mewstate");
	// 获取进程PID
	SetMemPID(pid);
	// 设置静态工具 全局PID 必须最先
	long libUE4 = Mem_get_module_cb("libUE4.so:bss", 1);

	int 测试读取D = Mem_getDword(libUE4 + 0xFFFF);
	float 测试读取F = Mem_getFloat(0x99999);

	Mem_WriteDword(0x333444, 100);
	Mem_WriteFloat(0x888888, 100.0f);

	int Dlist[100];
	mem_vm_readv(0x88888, Dlist, 0x4 * 100);
	// 使用syscall读取数据

	long 指针跳转 = Mem_lsp64(Mem_lsp64(libUE4 + 0x10) + 0X20) + 0x30;
	
	long 数组指针[4] = {0x10, 0x20, 0x30};
	long 数组指针使用 = Mem_readPointer(libUE4, 数组指针, sizeof(数组指针) / sizeof(long));
	//等价指针跳转

	// 测试写入
	printf("测试读取 [D] %d [F] %f", 测试读取D, 测试读取F);
	return 0;
}