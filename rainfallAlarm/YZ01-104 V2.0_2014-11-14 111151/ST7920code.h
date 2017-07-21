/*********************************************************
*�ļ����ƣ�ST7920code.h
*ժ    Ҫ���ֿ���ģ����
*          �����ֿ������޸��ֿⳤ�ȵĺ궨��
*
*��    �ߣ�����
*��ʼ���ڣ�2012��5��23��
*������ڣ�2012��5��24��
*           
**********************************************************/

#ifndef __ST7920CODE_H
#define __ST7920CODE_H 

/************�����ֿ������޸��ֿⳤ�ȵĺ궨��***********/

#define ASC2StringCodeLeng         117            //ASC2�ַ��ֿⳤ��
#define ASC2StringCodeLeng_8X6     16            //ASC2�ַ�8*6�ֿⳤ��
#define GB2312StringCodeLeng       161           //GB2312�ַ��ֿⳤ��

/********************************************************
       ASC2���ַ���ģ�ṹ�� 8*16����
********************************************************/
struct ASC2StringCode
{
  char ASC2;                   //�ַ�����
  char ASC2Code[16];           //��ģ����
};

/********************************************************
       GB2312���ַ���ģ�ṹ�� 16*16����
********************************************************/
struct GB2312StringCode
{ 
  unsigned int GB2312;                        //�ַ�����
  char GB2312LeftCode[16];            //�ַ������ģ����
  char GB2312RightCode[16];           //�ַ��ұ���ģ����
};


/********************************************************
       ASC2���ַ���ģ�ṹ�� 8*6����
********************************************************/
struct ASC2StringCode_8X6
{
  char ASC2;                   //�ַ�����
  char ASC2Code[8];            //��ģ����
};


extern const struct ASC2StringCode ASC2Code[ASC2StringCodeLeng ];
extern const struct GB2312StringCode GB2312Code[GB2312StringCodeLeng];
extern const struct ASC2StringCode ASC2Code_8X6[ASC2StringCodeLeng_8X6];

extern const char logp[488];           //����ͼƬ
extern const char rightarrow[18];      //�Ҽ�ͷ
extern const char leftarrow[18];       //���ͷ
extern const char Hourglass[116];      //ɳ©
extern const char qingtian[32];        //����ͼƬ
extern const char baojing[32];         //����ͼƬ
#endif /* #ifndef __ST7920CODE_H */