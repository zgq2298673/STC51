/*******************************************************************************
	ʱ�䣺2017.9.14
	���ߣ��ӹ���
	���ͣ�
			�򵥲���ϵͳʵ���ļ�
*******************************************************************************/
//���ͷ�ļ���
#include "zos.h"
void Thread1(void);
void Thread2(void);
RESULT CreatThread(ThreadFun newFun);
//����ϵͳ��ǵȱ�����
//static int Time_ms = 0;
static Funs Fun_s[3];
static char Fun_c,Fun_n;//��¼�߳�����
/*******************************************************************************
����ZOS_Init
˵����zos����ϵͳ��ʼ������
������void
����ֵ��void
���񣺳�ʼ��zos����ϵͳ
********************************************************************************/
void ZOS_Init()
{
	//�˶�ʱ����ʱ����ϵͳ�ĺ���
	TMOD = 0x21;//t0 16λ��ʱ��
	TH0 = 0xfe;
	TL0 = 0x34;//��������1s��ʱ
	TH1 = 0xfd;
	TL1 = 0xfd;//��������9600������
	PT0 = 1;
	TR0 = 1;
	TR1 = 1;
	SM0 = 0;
	SM1 = 1;//���ô��ڹ�����ʽ10λ�첽
	REN = 1;//ʹ�ܴ��ڽ���
	ET0 = 1;
	EA = 1;
	//ES = 1;//�ж�����
	
	//Thread1();
	Fun_c = 0;
	Fun_n = 2;//��ǰ�߳�
	CreatThread(Thread1);
	CreatThread(Thread2);
}
/*******************************************************************************
����Timer0Seriver
˵������ʱ��0�жϷ�����
������void
����ֵ��void
���񣺶�ʱ��t0����1ms�Ķ�ʱ���������»���ʱ���Լ�
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
����Timer0Seriver
˵������ʱ��0�жϷ�����
������void
����ֵ��void
���񣺶�ʱ��t0����1ms�Ķ�ʱ���������»���ʱ���Լ�
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
//	{//�л��̣߳�
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
����Uart1Seriver
˵���������жϷ�����
������void
����ֵ��void
���񣺴����жϷ��񣬿���ͨѶ
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

//�����̣߳�
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


























