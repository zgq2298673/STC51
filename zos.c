/*******************************************************************************
	时间：2017.9.14
	作者：钟国庆
	解释：
			简单操作系统实现文件
*******************************************************************************/
//相关头文件：
#include "zos.h"
void Thread1(void);
void Thread2(void);
RESULT CreatThread(ThreadFun newFun);
//操作系统标记等变量：
//static int Time_ms = 0;
static Funs Fun_s[3];
static char Fun_c,Fun_n;//记录线程总数
/*******************************************************************************
名：ZOS_Init
说明：zos操作系统初始化函数
参数：void
返回值：void
任务：初始化zos操作系统
********************************************************************************/
void ZOS_Init()
{
	//此定时器将时操作系统的核心
	TMOD = 0x21;//t0 16位定时器
	TH0 = 0xfe;
	TL0 = 0x34;//用来产生1s定时
	TH1 = 0xfd;
	TL1 = 0xfd;//用来产生9600波特率
	PT0 = 1;
	TR0 = 1;
	TR1 = 1;
	SM0 = 0;
	SM1 = 1;//配置串口工作方式10位异步
	REN = 1;//使能串口接收
	ET0 = 1;
	EA = 1;
	//ES = 1;//中断配置
	
	//Thread1();
	Fun_c = 0;
	Fun_n = 2;//当前线程
	CreatThread(Thread1);
	CreatThread(Thread2);
}
/*******************************************************************************
名：Timer0Seriver
说明：定时器0中断服务函数
参数：void
返回值：void
任务：定时器t0产生1ms的定时，用来更新基础时间以及
*******************************************************************************/
RESULT CreatThread(ThreadFun newFun)
{
	Fun_s[Fun_c].A = 0;
	Fun_s[Fun_c].B = 0;
	Fun_s[Fun_c].PSW = 0;
	Fun_s[Fun_c].PC_L = (unsigned int)(newFun);
	Fun_s[Fun_c].PC_H = (unsigned int)(newFun) >> 8;
	Fun_s[Fun_c].DPTR_H = 0;
	Fun_s[Fun_c].DPTR_L = 0;
	Fun_c++;
	return 0;
}
/*******************************************************************************
名：Timer0Seriver
说明：定时器0中断服务函数
参数：void
返回值：void
任务：定时器t0产生1ms的定时，用来更新基础时间以及
*******************************************************************************/
void Timer0Seriver() interrupt 1 using 1
{
	//ichar pSpL,pSpH;
	TH0 = 0xf7;
	TL0 = 0x67;
	Fun_s[Fun_n].PC_L = SP_PCL;
	Fun_s[Fun_n].PC_H = SP_PCH;
	Fun_s[Fun_n].A = SP_A;
	Fun_s[Fun_n].B = SP_B;
	Fun_s[Fun_n].DPTR_H = SP_DPTRH;
	Fun_s[Fun_n].DPTR_L = SP_DPTRL;
	Fun_s[Fun_n].PSW = SP_PSW;
	Fun_n = !Fun_n;
	SP_PCL = Fun_s[Fun_n].PC_L;
	SP_PCH = Fun_s[Fun_n].PC_H;
	SP_A = Fun_s[Fun_n].A;
	SP_B = Fun_s[Fun_n].B;
	SP_DPTRH = Fun_s[Fun_n].DPTR_H;
	SP_DPTRL = Fun_s[Fun_n].DPTR_L;
	SP_PSW = Fun_s[Fun_n].PSW;
//	Time_ms++;
//	if (Time_ms > 999)
//	{//切换线程：
//		Fun_s[Fun_n].PC_L = SP_PCL;
//		Fun_s[Fun_n].PC_H = SP_PCH;
//		Fun_s[Fun_n].A = SP_A;
//		Fun_s[Fun_n].B = SP_B;
//		Fun_s[Fun_n].DPTR_H = SP_DPTRH;
//		Fun_s[Fun_n].DPTR_L = SP_DPTRL;
//		Fun_s[Fun_n].PSW = SP_PSW;
//		Fun_n = !Fun_n;
//		SP_PCL = Fun_s[Fun_n].PC_L;
//		SP_PCH = Fun_s[Fun_n].PC_H;
//		SP_A = Fun_s[Fun_n].A;
//		SP_B = Fun_s[Fun_n].B;
//		SP_DPTRH = Fun_s[Fun_n].DPTR_H;
//		SP_DPTRL = Fun_s[Fun_n].DPTR_L;
//		SP_PSW = Fun_s[Fun_n].PSW;
//		Time_ms = 0;
//	}
}
/*******************************************************************************
名：Uart1Seriver
说明：串口中断服务函数
参数：void
返回值：void
任务：串口中断服务，控制通讯
*******************************************************************************/
void Uart1Seriver() interrupt 4 using 2
{
	if (RI)
	{
		RI = 0;
	}
	if (TI)
	{
		TI = 0;
	}
}

//两个线程：
void Thread1()
{
	while(1)
	{
		TI = 0;
		SBUF = 0X11;
		while(!TI);
	}
}

void Thread2()
{
	while(1)
	{
		TI = 0;
		SBUF = 0X22;
		while(!TI);
	}
}


























