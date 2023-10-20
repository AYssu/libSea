# libSea 静态库简绍 下载最新请参考以下命令

食用方法 终端安装 **git** 

ubuntu 

```bash
apt install git 
```

termux

```bash 
pkg install git
```

```bash
git --version
git clone https://github.com/AYssu/libSea.git
```


如果一直没进度 尝试挂**VPN**解决 

libSea 是一款基于网络验证和内存工具集成的静态库 目前第一代已停更 现在是**SeaTools V2**

## 内置了很多强大实用的函数方法封装 
  - 包括T3网络验证的单码登录/解绑
  - 获取公告
  - 软件更新
  - 内存工具 进程PID获取 进程libUE4 CB/CD头获取 内存地址写入 内存地址读取
  - syscall 读写 模板读写封装
  

包含mmap模板文件映射 配合可实现mmap绘制高效传输

包含完整的网络POST/GET等...

包含base加解密 字符串转换工具等...

具体函数请自行查看头文件**Sea.hpp**

目前已支持C4droid jni未写示例 但是强者不需要例子也能知道如何对接

# T3验证对接示例
> 
  准备后台配置 <br>
  全局数据加密-> 开启 <br>
  加密算法->base64自定义编码集 <br>
  请求值，返回值加密->开启  <br>
  请求值编码->HEX  <br>
  时间戳校验->开启  <br>
  签名校验->双向签名  <br>
  返回值格式->文本  <br>
  返回带时间戳 <br>
  后台 `` https://www.t3yanzheng.com ``

![Alt text](/example/后台配置.png)
> ### 安全模块 **SafeModel**
>>  
```cpp
int main(int argc, char const *argv[])
{
  //使用方法 在 main函数最前面开启
  SafeModel(true,true);
  //参数1 第一个参数为开启抓包校验 目前只支持自身为Root权限的抓包 例如jniRoot Root调用二进制的情况 框架环境一律不支持
  //参数2 打印LOG 如果不需要 直接false
  return 0;
}
```

> ### 登录解绑方法
>> 
```cpp
int main(int argc, char const *argv[])
{
	//配置信息 分别为 单码登录 单吗解绑 base64自定义密钥 后台密钥
	const char *url = (char *)"http://w.t3yanzheng.com/E5633A3CA5023084";
	const char *unurl = (char *)"http://w.t3yanzheng.com/520AE8C6B453B9C0";
	const char *base64 = (char *)"bCY/Pxg0VMUsXahjNIoi4LDzfAKRZTQ7S3dkWvOqwl9Jycnm1p5Ft6uBHr+2EeG8";
	const char *key = (char *)"aa199d730b93da766143de1fe640bcb2";

	char *kami = (char *)malloc(512);
	char *imei = (char *)malloc(512);
	//前者读取指定文件内容 Read函数也封装在了静态库
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
	T3_LogIn(url, base64, key, kami, imei, code, t3_Json);//解绑登录取决于传入url

	//结果都在Json结构里面
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
```

![Alt text](/example/登录解绑.png)

> ### 获取公告
>> 
```cpp
int main(int argc, char const *argv[])
{
	T3_Json t3_Json{};
	int code = 200;
	//响应码 注意接口不能加密传输 明文即可 一个公告要什么飞机
	T3_Notice("http://w.t3yanzheng.com/499D930AE737D128", code, t3_Json);
	printf("T3公告:%s\n", t3_Json.msg.c_str());
	return 0;
}
```
![Alt text](/example/公告.png)

> ### 获取更新
>> 
```cpp
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
```

![Alt text](/example/更新.png)

> ### POST GET 示例
>>
```cpp
int main(int argc, char const *argv[])
{
	char *http = (char *)malloc(8888);
	http_get("w.t3yanzheng.com","/499D930AE737D128",&http);
	printf("读取内容:%s\n\n", http);

	char *post = (char *)malloc(8888);
	// 随便写的例子 这么用就对了 随便写的 注意前面是域名 后面是url 最后是post参数
	http_post("w.t3yanzheng.com","/499D930AE737D128","print=json",&post);
	printf("提交返回内容:%s\n", post);
	return 0;
}
```
![Alt text](/example/POST_GET.png)

> ### 文本读写

>> 
```cpp
int main(int argc, char const *argv[])
{
	Write((char*)"/sdcard/test.txt",(char*)"嗷呜现在是写入");
	char *txt = Read((char*)"/sdcard/test.txt");
	printf("读取的内容:%s\n",txt);
	return 0;
}
```

![Alt text](/example/写入读取.png)


