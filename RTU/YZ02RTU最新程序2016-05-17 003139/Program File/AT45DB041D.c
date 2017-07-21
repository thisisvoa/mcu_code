/******************************************************************************* 
at45db041b���ԣ�
  ����������ѹΪ2.7~3.6V��ʵ���з��ֵ���ѹ����4.25V�������״̬�ֽ�Ϊ9A������  
��״̬�ֽ�ֵΪ9D�������Ҷ�д���ݾ���׼ȷ������Ӧ����֤��Ƭ�Ĺ����ѹ������4.25V��
SPI�淶��
  Data is always clocked into the device on the rising edge of SCK a- 
   nd clocked out of the device on the falling edge of SCK.All instruction-
   s,addresses and data are transferred with the most significant bit(MSB)  
   first.            
                 2005-06-02 
�޸�ʱ�䣺2013-04-22 �����ַ�������ݵ�д��
*******************************************************************************/ 

#include "include.h"
#include "AT45DB041D.h"

void SPI_Init(void)
{
  P3DIR |= BIT0+BIT1+BIT2+BIT3;
  P3OUT |= BIT0+BIT1+BIT2+BIT3;
  Flash_SO_in;
  delayus(100);
}

void SPI_End(void)
{ 
  Flash_CS_H;
  P3DIR &= ~(BIT1+BIT2+BIT3);
}




/*���ֽ�*/
unsigned char SPI_HostReadByte(void) 
{ 
  unsigned char i, rByte = 0; 
  for(i = 0; i < 8; i++)
  { 
    Flash_CLK_L; 
    Flash_CLK_H; 
    rByte <<= 1; 
    if(Flash_SO_val)
      rByte = rByte+1; 
  } 

  return rByte;   
} 

/*д�ֽ�*/
void SPI_HostWriteByte(unsigned char wByte) 
{ 
  unsigned char i; 
  for(i = 0; i < 8; i++) 
  { 
    if(wByte& 0x80) 
    {
      Flash_SI_H;
    }
    else    
    {
      Flash_SI_L;
    }
    wByte <<= 1;
    Flash_CLK_L; ;
    Flash_CLK_H; ;
  } 

} 

/*******************************************************************************
������  ��ȡ�����������ݵ�ָ����������
������             
   buffer  - ָ��buffer ID-1��2          
   BFA   - ָ��BUFFER�е���ʼд���ַ        
   pHeader - ָ���洢���ݵ��׵�ַ         
   len   - ָ�����ݵĳ���          
*******************************************************************************/ 
void Read_Buffer(unsigned char buffer, unsigned int BFA, unsigned char *pHeader, unsigned int len) 
{
  unsigned int i = 0; 
  
  while(i++ < 255) 
  {
    if(AT45DB041B_StatusRegisterRead() & 0x80) 
    { 
      break;
    }
  } 
  
  Flash_CS_L;   
  delayus(20);
  
  switch(buffer) 
  { 
    case 1 : SPI_HostWriteByte(Read_Buffer1);//#define Write_Buffer1 0x84
      break; 
    case 2 : SPI_HostWriteByte(Read_Buffer2);////#define Write_Buffer2 0x87
      break; 
  }
  SPI_HostWriteByte(0x00);//the don't care 15bits of high eight bits
  SPI_HostWriteByte((unsigned char)(BFA >> 8));//the don't care 15bits of low seven bits and the BFA of high one bit
  SPI_HostWriteByte((unsigned char)BFA);   //the BFA of low eight bits
  SPI_HostWriteByte(0x00);       //the eight don't care bits
  for(i = 0; i < len; i++) 
  {
    pHeader[i] = SPI_HostReadByte();
  } 
  Flash_CS_H;
}

/******************************************************************************/ 
/*��ȡ״̬�Ĵ���:           */ 
/*   -----------------------------------------------------------------------  */ 
/* | bit7 | bit6 | bit5 | bit4 | bit3 | bit2 | bit1 | bit0 | */ 
/* |--------|--------|--------|--------|--------|--------|--------|--------|  */ 
/* |RDY/BUSY| COMP |   0   |   1   |   1   |   1   |   X   |   X   | */ 
/*   -----------------------------------------------------------------------  */ 
/* bit7 - æ��ǣ�0Ϊæ1Ϊ��æ��            */ 
/*   ��Status Register��λ0�Ƴ�֮�󣬽�������ʱ���������н�ʹSPI��������  */ 
/*   �����µ�״̬�ֽ��ͳ���             */ 
/* bit6 - ������һ��Main Memory Page��Buffer�ıȽϽ����0��ͬ��1��ͬ��  */ 
/* bit5                   */ 
/* bit4                   */ 
/* bit3                   */ 
/* bit2 - ��4λ������������ܶȣ�����AT45DB041B����4λӦ����0111��һ���ܱ��  */ 
/*   16�ֲ�ͬ�ܶȵ�������             */ 
/* bit1                   */ 
/* bit0 - ��2λ��ʱ��Ч               */ 
/******************************************************************************/ 
unsigned char AT45DB041B_StatusRegisterRead(void) 
{ 
  unsigned char status; 
  
  Flash_CS_L;   
  SPI_HostWriteByte(Status_Register_Read);//#define Status_Register_Read 0xd7//д���ȡAT45DB041B״̬�Ĵ�������'0xd7' 
  status = SPI_HostReadByte(); 
  Flash_CS_H;
  return status;   
}
 
/******************************************************************************
������  ���洢��������              
������             
   PA  - ҳ��ַ��0~2047          
   BFA   - ָ��BUFFER�е���ʼд���ַ        
   pHeader - ָ�����ݵ��׵�ַ         
   len   - ָ�����ݵĳ���          
******************************************************************************/ 
void AT45DB041B_ContinuousArrayRead(unsigned int PA, unsigned int BFA, unsigned char *pHeader, unsigned int len) 
{   
  unsigned int i = 0;  
  
  while(i++ < 255) //i++ < 255������ʱ�ȴ�AT...����
  {
    if(AT45DB041B_StatusRegisterRead() & 0x80) //��ȡ״̬�Ĵ������λ,�ж��Ƿ�Ϊæ
    {
      break;                   //Ϊ1��ʾ����������
    }
  } 
  Flash_CS_L;   
  SPI_HostWriteByte(Continuous_Array_Read);//#define Continuous_Array_Read 0xe8//�����������ȡ   
  SPI_HostWriteByte((unsigned char)(PA >> 7));//�˴�������,PA >> 7���Ƿ���PA�ĸ�4λ�Լ��ʼ��4λ�޹ؽ�Ҫλ   
  SPI_HostWriteByte((unsigned char)((PA << 1) | (BFA >> 8)));//��ΪPA��2���ֽڹ�16λ,����PAֻ�õ��˵�1λ��11λ,
  SPI_HostWriteByte((unsigned char)BFA);//PA����һλ�ٻ���BFA >> 8���Ƿ���PA�ĵ�7λ��BFA���λ,����ٷ���BFA�ĵ�8λ
  for(i = 0; i < 4; i++) 
  {
    SPI_HostWriteByte(0x00);
  } 
  for(i = 0; i < len; i++) 
  {
    pHeader[i] = SPI_HostReadByte();
    //delayus(20);
  } 
  Flash_CS_H; 
}

/*******************************************************************************
������
   ���洢��ҳ��.
������             
   PA   - ҳ��ַ��0~2047          
   BFA   - ָ��BUFFER�е���ʼд���ַ        
   pHeader - ָ�����ݵ��׵�ַ         
   len   - ָ�����ݵĳ���          
******************************************************************************/
void AT45DB041B_MainMemoryPageRead(unsigned int PA, unsigned int BFA, unsigned char *pHeader, unsigned int len) 
{   
  unsigned int i = 0;
  
  while(i++ < 255) //i++ < 255������ʱ�ȴ�AT...����
  {
    if(AT45DB041B_StatusRegisterRead() & 0x80) //��ȡ״̬�Ĵ������λ,�ж��Ƿ�Ϊæ
    {
      break;                                    //Ϊ1��ʾ����������
    }
  } 
  Flash_CS_L;   
  SPI_HostWriteByte(Main_Memory_Page_Read);//#define Continuous_Array_Read 0xe8//�����������ȡ   
  SPI_HostWriteByte((unsigned char)(PA >> 7));//�˴�������,PA >> 7���Ƿ���PA�ĸ�4λ�Լ��ʼ��4λ�޹ؽ�Ҫλ   
  SPI_HostWriteByte((unsigned char)((PA << 1) | (BFA >> 8)));//��ΪPA��2���ֽڹ�16λ,����PAֻ�õ��˵�1λ��11λ,
  SPI_HostWriteByte((unsigned char)BFA);//PA����һλ�ٻ���BFA >> 8���Ƿ���PA�ĵ�7λ��BFA���λ,����ٷ���BFA�ĵ�8λ
  for(i = 0; i < 4; i++) 
  {
    SPI_HostWriteByte(0x00);//����32λ�޹ؽ�Ҫ������
  } 
  for(i = 0; i < len; i++) 
  {
    pHeader[i] = SPI_HostReadByte();
  } 
  Flash_CS_H; 
} 

/****************************************************************************** 
������ 
  ��ָ������д���ĳ����ַ��0~263����ʼ��BUFFER�С�    
������            
   buffer - ѡ��BUFFER��01Hѡ��BUFFER 1��02Hѡ��BUFFER 2    
  �ڸ�ָ�������У�������84Hѡ��BUFFER 1��87Hѡ��BUFFER 2   
   BFA   - BUFFER�е���ʼ��ַ��0~263       
   pHeader - �������ݵ�ͷָ��        
   len   - �������ݵĳ���1~264        
******************************************************************************/ 
void AT45DB041B_BufferWrite(unsigned char buffer, unsigned int BFA, unsigned char *pHeader, unsigned int len) 
{ 
  unsigned int i = 0; 
  
  while(i++ < 255) 
  {
    if(AT45DB041B_StatusRegisterRead() & 0x80) 
    { 
      break;
    }
  }  
  Flash_CS_L; 
  switch(buffer) 
  { 
    case 1 : SPI_HostWriteByte(Write_Buffer1);//#define Write_Buffer1 0x84
      break; 
    case 2 : SPI_HostWriteByte(Write_Buffer2);//#define Write_Buffer2 0x87
      break; 
  } 
  SPI_HostWriteByte(0x00); 
  SPI_HostWriteByte((unsigned char)(BFA >> 8)); 
  SPI_HostWriteByte((unsigned char)BFA);  
  for(i = 0; i < len; i++) 
  {
    SPI_HostWriteByte(pHeader[i]);//delayus(20);
  } 
  Flash_CS_H; delayus(20);  
} 

/****************************************************************************** 
������             
   ��ָ������д���ĳ����ַ��0~263����ʼ��ҳ�У�����3�����������Ƚ�ĳָ��ҳ�����ݶ���
   ��BUFFER 1����BUFFER 2�У��ٽ�ָ������ 
   д�뵽BUFFER 1����BUFFER 2�У����п���ָ��BUFFER�е���ʼд���ַ����д�� 
   ������Ӱ��BUFFER��������ַ�е����ݣ�Ȼ���ٽ�BUFFER�е���������д�뵽ĳָ 
   ��ҳ��(��Ԥ����)��          
������            
   buffer - ѡ��BUFFER��01Hѡ��BUFFER 1��02Hѡ��BUFFER 2    
   PA   - ҳ��ַ��0~2047          
   BFA   - ָ��BUFFER�е���ʼд���ַ        
   pHeader - ָ�����ݵ��׵�ַ         
   len   - ָ�����ݵĳ���         
******************************************************************************/ 
void Save_data_to_Flash_inErase(unsigned char buffer, unsigned int PA, unsigned int BFA, unsigned char *pHeader, unsigned int len) 
{ 
  unsigned int i = 0; 
  
  /*2013-04-22 22:46:18��Ӹ���䣬ԭ����������д������ʱ�д����޸ĺ��������ҳ�����ַд������*/
  Flash_to_buffer(buffer,PA);   //��ȡ��ҳ���ݵ�����
  
  AT45DB041B_BufferWrite(buffer, BFA, pHeader, len); //�ı仺������
  
  while(i++ < 1000) 
  {
    if(AT45DB041B_StatusRegisterRead() & 0x80) 
    {
      break;
    }
  }  
  Flash_CS_L;  
  switch(buffer)
  { 
    case 1 : SPI_HostWriteByte(Buffer1_To_MainMemory_PageProgram_WithBuilt_inErase);//#define Buffer1_To_MainMemory_PageProgram_WithBuilt_inErase x083
      break; 
    case 2 : SPI_HostWriteByte(Buffer2_To_MainMemory_PageProgram_WithBuilt_inErase);//#define Buffer2_To_MainMemory_PageProgram_WithBuilt_inErase x086
      break; 
  } 
  SPI_HostWriteByte((unsigned char)(PA >> 7)); 
  SPI_HostWriteByte((unsigned char)(PA << 1)); 
  SPI_HostWriteByte(0x00);  
  Flash_CS_H;
} 

/****************************************************************************** 
������            
   ����һ��������Ψһ�����ǲ���Ԥ������        
******************************************************************************/ 
void AT45DB041B_BufferToMainMemoryPageProgramWithoutBuilt_inErase(unsigned char buffer, unsigned int PA, unsigned int BFA, unsigned char *pHeader, unsigned int len)
{ 
  unsigned int i = 0; 
  
  AT45DB041B_BufferWrite(buffer, BFA, pHeader, len); 
  
  while(i++ < 1000) 
  { 
    if(AT45DB041B_StatusRegisterRead() & 0x80) 
    {
      break;
    }
  } 
  Flash_CS_L; 
  SPI_HostWriteByte(0x87 + buffer);//��buffer=1,��д��0x88����.��buffer=2��д��0x89����,Ч��������ע�ʹ��빦��һ�� 
  /*switch(buffer){ 
  case 1 : SPI_HostWriteByte(Buffer1_To_MainMemory_PageProgram_WithoutBuilt_inErase);//#define Buffer1_To_MainMemory_PageProgram_WithoutBuilt_inErase x088
    break; 
  case 2 : SPI_HostWriteByte(Buffer2_To_MainMemory_PageProgram_WithoutBuilt_inErase);//#define Buffer2_To_MainMemory_PageProgram_WithoutBuilt_inErase x089
    break; 
  }*/ 
  SPI_HostWriteByte((unsigned char)(PA >> 7)); 
  SPI_HostWriteByte((unsigned char)(PA << 1)); 
  SPI_HostWriteByte(0x00); 
  for(i = 0; i < len; i++) 
  {
    SPI_HostWriteByte(pHeader[i]);delayus(20);
  } 
  Flash_CS_H; 
} 

/****************************************************************************** 
������             
  When a low-to-high transition occurs on the /C/S pin,the part will erase the
   selected page to 1s.The erase operation is internally self-timed and should
   take place in a maximum time of tPE.During this time,the status register will
   indicate that the part is busy.         
������                 
   PA   - ҳ��ַ��0~2047                  
******************************************************************************/
void AT45DB041B_PageErase(unsigned int PA) 
{
  unsigned int i = 0; 
  
  while(i++ < 255) 
  {
    if(AT45DB041B_StatusRegisterRead() & 0x80) 
    { 
      break;
    }
  } 
  Flash_CS_L;  
  SPI_HostWriteByte(Page_Erase);
  SPI_HostWriteByte((unsigned char)(PA >> 7));//ҳ��ַ��4λ��4Ϊ�޹�λ
  SPI_HostWriteByte((unsigned char)(PA << 1));//ҳ��ַ��7λ��1λ�޹�λ
  SPI_HostWriteByte(0x00);//8λ�޹�λ
  Flash_CS_H;
  while(!(AT45DB041B_StatusRegisterRead() & 0x80));//�ȴ��������
}

/****************************************************************************** 
������             
  When a low-to-high transition occurs on the /C/S pin,the part will erase the
   selected block of eight pages to 1s.The erase operation is internally self-t-
  imed and should take place in a maximum time of tBE.During this time,the sta-
  tus register will indicate that the part is busy.         
������                 
   BLKA   - ���ַ��0~255                  
******************************************************************************/
void AT45DB041B_BlockErase(unsigned char BLKA) 
{
  unsigned int i = 0; 
  
  while(i++ < 255) 
  {
    if(AT45DB041B_StatusRegisterRead() & 0x80) 
    { 
      break;
    }
  } 
  Flash_CS_L;  
  SPI_HostWriteByte(Block_Erase);
  SPI_HostWriteByte((unsigned char)(BLKA >> 4));//���ַ��4λ��4Ϊ�޹�λ
  SPI_HostWriteByte((unsigned char)(BLKA << 4));//���ַ��4λ��4λ�޹�λ
  SPI_HostWriteByte(0x00);//8λ�޹�λ
  Flash_CS_H;
  while(!(AT45DB041B_StatusRegisterRead() & 0x80));//�ȴ��������
}

/****************************************************************************** 
������             
  �����洢��ҳ���뻺����      
������                 
   buffer   - ѡ��BUFFER��01Hѡ��BUFFER1��02Hѡ��BUFFER2
  PA  - ҳ��ַ��0~2047    
******************************************************************************/
void Flash_to_buffer(unsigned char buffer, unsigned int PA) 
{
  unsigned int i = 0;
  
  while(i++ < 255) 
  {
    if(AT45DB041B_StatusRegisterRead() & 0x80) 
    { 
      break;
    }
  } 
  Flash_CS_L;
  switch(buffer)
  { 
    case 1 : SPI_HostWriteByte(Main_Memory_Page_To_Buffer1_Transfer);
      break; 
    case 2 : SPI_HostWriteByte(Main_Memory_Page_To_Buffer2_Transfer);
      break; 
  }
  SPI_HostWriteByte((unsigned char)(PA >> 7)); 
  SPI_HostWriteByte((unsigned char)(PA << 1)); 
  SPI_HostWriteByte(0x00);
  Flash_CS_H;
  i = 0;
  while(!(AT45DB041B_StatusRegisterRead() & 0x80))//�ȴ��������
  {
    if(i++ > 100)
      return;
  }
}

/****************************************************************************** 
������             
  �������뻺�������ݱȽ�        
������                 
   buffer   - ѡ��BUFFER��01Hѡ��BUFFER1��02Hѡ��BUFFER2
  PA  - ҳ��ַ��0~2047                
******************************************************************************/
unsigned char AT45DB041B_MainMemoryPageToBufferCompare(unsigned char buffer, unsigned int PA) 
{
  unsigned int i = 0; 
  
  while(i++ < 255) 
  {
    if(AT45DB041B_StatusRegisterRead() & 0x80) 
    { 
      break;
    }
  } 
  Flash_CS_L;
  switch(buffer)
  { 
    case 1 : SPI_HostWriteByte(Main_Memory_Page_To_Buffer1_Compare);
      break; 
    case 2 : SPI_HostWriteByte(Main_Memory_Page_To_Buffer2_Compare);
      break; 
  }
  SPI_HostWriteByte((unsigned char)(PA >> 7)); 
  SPI_HostWriteByte((unsigned char)(PA << 1)); 
  SPI_HostWriteByte(0x00);
  Flash_CS_H;
  while(!(AT45DB041B_StatusRegisterRead() & 0x80));
  return(((AT45DB041B_StatusRegisterRead()& 0x40) ? 0 : 1));//���رȽϽ����if StatusRegister's bit6 is 0,then match, is 1,then not match
}

/****************************************************************************** 
������             
        
������                 
   buffer  - ѡ��BUFFER��01Hѡ��BUFFER1��02Hѡ��BUFFER2
  PA  - ҳ��ַ��0~2047 
  BFA   - buffer��ַ��0~263
  pHeader - ��д�����ݵ��׵�ַ
  len   - д�����ݵĳ���             
******************************************************************************/
void AT45DB041B_MainMemoryPageProgramThroughBuffer(unsigned char buffer, unsigned int PA, unsigned int BFA, unsigned char *pHeader, unsigned int len) 
{ 
  unsigned int i = 0; 
  
  AT45DB041B_BufferWrite(buffer, BFA, pHeader, len); 
  
  while(i++ < 1000) 
  {
    if(AT45DB041B_StatusRegisterRead() & 0x80) 
    {
      break;
    }
  } 
  Flash_CS_L;   
  switch(buffer)
  { 
    case 1 : SPI_HostWriteByte(Main_Memory_Page_Program_Through_Buffer1);
      break; 
    case 2 : SPI_HostWriteByte(Main_Memory_Page_Program_Through_Buffer2);
      break; 
  }
  SPI_HostWriteByte((unsigned char)(PA >> 7)); 
  SPI_HostWriteByte((unsigned char)(PA << 1 | BFA >> 8)); 
  SPI_HostWriteByte((unsigned char)BFA);
  for(i = 0; i < len; i++) 
  {
    SPI_HostWriteByte(pHeader[i]);
  }
  Flash_CS_H;
}

/****************************************************************************** 
������             
  �Զ�ҳ��д         
������                 
   buffer  - ѡ��BUFFER��01Hѡ��BUFFER1��02Hѡ��BUFFER2
  PA  - ҳ��ַ��0~2047 
  BFA   - buffer��ַ��0~263
  pHeader - ��д�����ݵ��׵�ַ
  len   - д�����ݵĳ���             
******************************************************************************/
void AT45DB041B_AutoPageRewrite(unsigned char buffer, unsigned int PA) 
{
  unsigned int i = 0;
  
  Flash_to_buffer(buffer, PA);
  while(i++ < 1000) 
  { 
    if(AT45DB041B_StatusRegisterRead() & 0x80) 
    {
      break;
    }
  }
  Flash_CS_L;
  switch(buffer)
  { 
    case 1 : SPI_HostWriteByte(Auto_Page_Rewrite_With_Buffer1);
      break; 
    case 2 : SPI_HostWriteByte(Auto_Page_Rewrite_With_Buffer2);
      break; 
  }
  SPI_HostWriteByte((unsigned char)(PA >> 7)); 
  SPI_HostWriteByte((unsigned char)(PA << 1)); 
  SPI_HostWriteByte(0x00);
  Flash_CS_H;
  while(!(AT45DB041B_StatusRegisterRead() & 0x80));
} 
/*���Falsh,�ɹ�����1��ʧ�ܷ���0*/
unsigned char FindFlash(void)
{
  unsigned char temp=0;
  unsigned char i=10;                   //����ظ�������
  SPI_Init();
  while(i--)
  {   
    temp = AT45DB041B_StatusRegisterRead();//����flash״̬�Ĵ���
    temp &= ~(BIT0+BIT1+BIT6);             //������Чλ
    if(temp & 0X80)
      break;
  }  
  SPI_End();
  if(temp != 0X9C)  
  {
    return 0;                           //���ؼ��ʧ��
  }
  return 1;                             //���ؼ��ɹ�
}

