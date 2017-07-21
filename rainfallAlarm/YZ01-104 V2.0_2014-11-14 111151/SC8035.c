/*********************************************************
*�ļ����ƣ�SC8035.c
*ժ    Ҫ������оƬ����
*          
*��    �ߣ�����
**********************************************************/
#include "include.h"
#include "SC8035.h"


void SC_WBusy(unsigned int t) 						 //�������Ŷ�æ
{     
  unsigned int times;     
  for(times=0;times<t;times++)            //�ȴ�����7����������Զ��˳�      
  {  
    delayms(10);
       
   }
}

void SC_Reset(void)							 //�ϵ縴λ��ֹ���ŷ���оƬ����
{
  SC_RST_OUT;
  SC_DATA_OUT;
  _NOP();
  SC_DATA_0;     							 //���������
  SC_RST_1;     							 //��λ�����
  delayus(100);                    		                         //��ʱ100US
  SC_RST_0;     							 //��λ�����
  delayus(100); 							 //��ʱ100US 
  SC_RST_IN;
  SC_DATA_IN;
}

void SC_Speech(char cnt) 		//��������   �� cot(cot>0) ��
{      
  char i;	
  
  SC_Reset();  
  
  SC_RST_OUT;
  SC_DATA_OUT;
  										 //�������Ÿ�λ
  SC_RST_1;      						 //��λ�����
  delayus(100);						 //��ʱ100US										     //�˳������ж�
  SC_RST_0;      						 //��λ�����
  delayus(100);						 //��ʱ100US	         

  for(i=0;i<cnt;i++)      
  {          
    SC_DATA_1;              		 //���������          
    delayus(100);           		 //��ʱ100US   			
    SC_DATA_0;              		 //���������          
    delayus(100);           		 //��ʱ100US 		       
  } 
} 