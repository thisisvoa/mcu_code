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

#define ASC2StringCodeLeng         117           //ASC2�ַ��ֿⳤ��
#define ASC2StringCodeLeng_8X6     16            //ASC2�ַ�8*6�ֿⳤ��
#define GB2312StringCodeLeng       172           //GB2312�ַ��ֿⳤ��

/********************************************************
       ASC2���ַ���ģ�ṹ�� 8*16����
********************************************************/
struct ASC2StringCode
{
  unsigned char ASC2;                   //�ַ�����
  unsigned char ASC2Code[16];           //��ģ����
};

/********************************************************
       GB2312���ַ���ģ�ṹ�� 16*16����
********************************************************/
struct GB2312StringCode
{ 
  unsigned int GB2312;                         //�ַ�����
  unsigned char GB2312LeftCode[16];            //�ַ������ģ����
  unsigned char GB2312RightCode[16];           //�ַ��ұ���ģ����
};


/********************************************************
       ASC2���ַ���ģ�ṹ�� 8*6����
********************************************************/
struct ASC2StringCode_8X6
{
  unsigned char ASC2;                   //�ַ�����
  unsigned char ASC2Code[8];            //��ģ����
};


extern const struct ASC2StringCode ASC2Code[ASC2StringCodeLeng ];
extern const struct GB2312StringCode GB2312Code[GB2312StringCodeLeng];
extern const struct ASC2StringCode ASC2Code_8X6[ASC2StringCodeLeng_8X6];

extern const unsigned char logp[488];           //����ͼƬ
extern const unsigned char rightarrow[18];      //�Ҽ�ͷ
extern const unsigned char leftarrow[18];       //���ͷ
extern const unsigned char Hourglass[116];      //ɳ©


#endif /* #ifndef __ST7920CODE_H */