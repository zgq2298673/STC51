#include "zos.h"
int main()
{
	//B = 0x09;
	ZOS_Init();//初始化程序并允许操作系统
	while(1);//运行服务
}

