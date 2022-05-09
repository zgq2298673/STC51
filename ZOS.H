#include <reg52.h>
/*******************************************************************************
	时间：2017.9.14
	作者：钟国庆
	解释：
			简单操作系统头文件
			纯c语言打造
*******************************************************************************/

//外部接口：
void ZOS_Init(void);//初始化操作系统

//函数描述结构体
typedef idata unsigned char* ichar;
typedef struct _Funs{
	unsigned char   PC_L;//程序指针寄存器低8位
	unsigned char   PC_H;//程序指针寄存器高8位
	unsigned char   A;//A寄存器
	unsigned char   B;//B寄存器
	unsigned char   DPTR_H;//PTSR高8寄存器
	unsigned char   DPTR_L;//PTSR低8寄存器
	unsigned char   PSW;//PTSR高8寄存器
} Funs, *pFuns;

typedef void (*ThreadFun)(void);

#define RESULT char
	
#define		SP_PSW *(ichar)(SP - 0)
#define		SP_DPTRL *(ichar)(SP - 1)
#define		SP_DPTRH *(ichar)(SP - 2)
#define		SP_B *(ichar)(SP - 3)
#define		SP_A *(ichar)(SP - 4)
#define		SP_PCH *(ichar)(SP - 5)
#define		SP_PCL *(ichar)(SP - 6)
//函数说明格式：
/*******************************************************************************
名：
说明：
参数：
返回值：
任务：
*******************************************************************************/
