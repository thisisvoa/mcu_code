/*********************************************************
 *�ļ����ƣ�AT24C04.c
 *ժ    Ҫ��EEPROM AT24C04��������
 *
 *��ǰ�汾��1.0 ȫ�������������Կ�������ʹ�á��޸�д��ȴ�ʱ��Ϊ5ms��
 *��    �ߣ�����
 *��ʼ���ڣ�2012��5��17��
 *������ڣ�2012��5��17��
 *
 *ע�⣺ʹ������д�뺯��Write_NByteʱ�����ܳ���ҳ�߽硣
 ***********************************************************/

#include "AT24C04.h"
#include "Public.h"     /*����WriteSInt32��ReadSInt32��WriteUInt16��ReadUInt16ʹ��*/
#include "lcd_12864.h"
/*
 * ��������set_io_dir
 * ���ܣ�������ӦIO���������ģʽ
 * ������1->��� 0->����
 *
 */
void set_sda_dir(uint32_t mode) {
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.Mode = mode;
	GPIO_InitStruct.Pin = SDA_PIN;
	HAL_GPIO_Init(SDA_PORT, &GPIO_InitStruct);
}

/*******************************************
 �������ƣ�start
 ��    �ܣ����IIC����ʼ��������
 ��    ������
 ����ֵ  ����
 ********************************************/
void start(void) {
//  IniRAM;       //��ʼ��I/O
	SDA_OUT();
	SCL_H();
	SDA_H();
	AT24C04delayus(25);
	SDA_L();
	AT24C04delayus(25);
	SCL_L();
	AT24C04delayus(25);
}
/*******************************************
 �������ƣ�stop
 ��    �ܣ����IIC����ֹ��������
 ��    ������
 ����ֵ  ����
 ********************************************/
void stop(void) {
	SDA_L();
	AT24C04delayus(25);
	SCL_H();
	AT24C04delayus(25);
	SDA_H();
	AT24C04delayus(25);

}
/*******************************************
 �������ƣ�mack
 ��    �ܣ����IIC������Ӧ�����
 ��    ������
 ����ֵ  ����
 ********************************************/
void mack(void) {
	SDA_L();
	AT24C04delayus(10);
	SCL_H();
	AT24C04delayus(25);
	SCL_L();
	AT24C04delayus(10);
	SDA_H();
	AT24C04delayus(25);
}
/*******************************************
 �������ƣ�mnack
 ��    �ܣ����IIC��������Ӧ�����
 ��    ������
 ����ֵ  ����
 ********************************************/
void mnack(void) {
	SDA_H();
	AT24C04delayus(10);
	SCL_H();
	AT24C04delayus(25);
	SCL_L();
	AT24C04delayus(10);
	SDA_L();
	AT24C04delayus(25);
}

/**********���Ӧ���źź���******************/
/*�������ֵΪ1��֤����Ӧ���źţ���֮û��*/
/*******************************************
 �������ƣ�check
 ��    �ܣ����ӻ���Ӧ�����
 ��    ������
 ����ֵ  ���ӻ��Ƿ���Ӧ��1--�У�0--��
 ********************************************/
unsigned char check(void) {
	unsigned char slaveack;

	SDA_H();
	AT24C04delayus(25);

	SCL_H();
	AT24C04delayus(25);

	SDA_IN();
	AT24C04delayus(25);

	slaveack = SDA_VAL();   //����SDA��ֵ
	SCL_L();
	AT24C04delayus(25);

	SDA_OUT();

	if (slaveack)
		return 0;
	else
		return 1;
}
/*******************************************
 �������ƣ�write1
 ��    �ܣ���IIC���߷���һ��1
 ��    ������
 ����ֵ  ����
 ********************************************/
void write1(void) {
	SDA_H();
	AT24C04delayus(25);
	SCL_H();
	AT24C04delayus(25);
	SCL_L();
	AT24C04delayus(25);
}
/*******************************************
 �������ƣ�write0
 ��    �ܣ���IIC���߷���һ��0
 ��    ������
 ����ֵ  ����
 ********************************************/
void write0(void) {
	SDA_L();
	AT24C04delayus(25);
	SCL_H();
	AT24C04delayus(25);
	SCL_L();
	AT24C04delayus(25);
}
/*******************************************
 �������ƣ�write1byte
 ��    �ܣ���IIC���߷���һ���ֽڵ�����
 ��    ����wdata--���͵�����
 ����ֵ  ����
 ********************************************/
void write1byte(unsigned char wdata) {
	unsigned char i;
	for (i = 8; i > 0; i--) {
		if (wdata & 0x80)
			write1();
		else
			write0();
		wdata <<= 1;
	}
	SDA_H();
	AT24C04delayus(10);
}
/*******************************************
 �������ƣ�writeNbyte
 ��    �ܣ���IIC���߷���N���ֽڵ�����
 ��    ����outbuffer--ָ�������ݴ���׵�ַ
 ��ָ��
 n--���ݵĸ���
 ����ֵ  �������Ƿ�ɹ��ı�־��1--�ɹ���0--ʧ��
 ********************************************/
unsigned char writeNbyte(unsigned char * outbuffer, unsigned char n) {
	unsigned char i;

	for (i = 0; i < n; i++) {
		write1byte(*outbuffer);
		if (check()) {
			outbuffer++;
		} else {
			stop();
			return 0;
		}
	}

	stop();
	return 1;
}
/*******************************************
 �������ƣ�read1byte
 ��    �ܣ���IIC���߶�ȡһ���ֽ�
 ��    ������
 ����ֵ  ����ȡ������
 ********************************************/
unsigned char read1byte(void) {
	unsigned char rdata = 0x00, i;
	unsigned char flag;

	for (i = 0; i < 8; i++) {
		SDA_H();
		AT24C04delayus(25);
		SCL_H();
		SDA_IN();
		AT24C04delayus(25);
		flag = SDA_VAL();
		rdata <<= 1;

		if (flag)
			rdata |= 0x01;

		SDA_OUT();
		SCL_L();
		AT24C04delayus(25);
	}
	return rdata;
}
/*******************************************
 �������ƣ�readNbyte
 ��    �ܣ���IIC���߶�ȡN���ֽڵ�����
 ��    ����inbuffer--��ȡ�����ݴ�ŵ��׵�ַ
 n--���ݵĸ���
 ����ֵ  ����
 ********************************************/
void readNbyte(unsigned char * inbuffer, unsigned char n) {
	unsigned char i;

	for (i = 0; i < n; i++) {
		inbuffer[i] = read1byte();

		if (i < (n - 1))
			mack();
		else
			mnack();
	}
	stop();
}

/*******************************************
 �������ƣ�Write_1Byte
 ��    �ܣ���EEPROM��д��1���ֽڵ�����
 ��    ����Wdata--д�������
 dataaddress--���ݵ�д���ַ
 ����ֵ  ��д������1--�ɹ���0--ʧ��
 ********************************************/
unsigned char Write_1Byte(unsigned char wdata, unsigned char dataaddress) {
	start();

	write1byte(deviceaddress);

	if (check())
		write1byte(dataaddress);
	else
		return 0;
	if (check()) {
		write1byte(wdata);
		AT24C04delayus(25);
	} else
		return 0;
	if (check())
		stop();
	else
		return 0;

	AT24C04delayms(5);                                   //�ȴ�EEPROM����ڲ�д��
	return 1;
}

/*******************************************
 �������ƣ�Write_NByte
 ��    �ܣ���EEPROM��д��N���ֽڵ�����
 ��    ����outbuf--ָ��д�����ݴ���׵�ַ��ָ��
 n--���ݸ���������ܳ���8����ҳ��ַ
 ��������󳤶�
 dataaddress--����д����׵�ַ
 ����ֵ  ��д������1--�ɹ���0--ʧ��
 ********************************************/
unsigned char Write_NByte(unsigned char *outbuf, unsigned char n,
		unsigned char dataaddress) {
	unsigned char flag;
	start();
	write1byte(deviceaddress);                                //д��������ַ
	if (check() == 1)
		write1byte(dataaddress);                                //д�������ֵ�ַ
	else
		return 0;
	if (check())
		flag = writeNbyte(outbuf, n);
	else
		return 0;
	AT24C04delayms(5);                                   //�ȴ�EEPROM����ڲ�д��
	if (flag)
		return 1;
	else
		return 0;
}

/*******************************************
 �������ƣ�Read_1Byte_currentaddress
 ��    �ܣ���EEPROM�ĵ�ǰ��ַ��ȡ1���ֽڵ�����
 ��    ������
 ����ֵ  ����ȡ������
 ********************************************/
/*unsigned char Read_1Byte_currentaddress(void)
 {
 unsigned char temp;

 start();
 write1byte((deviceaddress|0x01));
 if(check())
 temp = read1byte();
 else
 return 0;
 mnack();
 stop();
 return temp;
 }*/
/*******************************************
 �������ƣ�Read_NByte_currentaddress
 ��    �ܣ���EEPROM�ĵ�ǰ��ַ��ȡN���ֽڵ�����
 ��    ����readbuf--ָ�򱣴����ݵ�ַ��ָ��
 n--��ȡ���ݵĸ���
 ����ֵ  ����ȡ�����1--�ɹ���0--ʧ��
 ********************************************/
/*unsigned char Read_NByte_currentaddress(unsigned char * readbuf,unsigned char n)
 {
 start();
 write1byte((deviceaddress|0x01));
 if(check())
 readNbyte(readbuf,n);
 else
 return 0;
 return  1;
 }*/

/*******************************************
 �������ƣ�Read_1Byte_Randomaddress
 ��    �ܣ���EEPROM��ָ����ַ��ȡ1���ֽڵ�����
 ��    ����dataaddress--���ݶ�ȡ�ĵ�ַ
 ����ֵ  ����ȡ������
 ********************************************/
unsigned char Read_1Byte_Randomaddress(unsigned char dataaddress) {
	unsigned char temp;
	start();
	write1byte(deviceaddress);
	if (check())
		write1byte(dataaddress);
	else
		return 0;
	if (check()) {
		start();
		write1byte((deviceaddress | 0x01));
		AT24C04delayus(25);
	} else
		return 0;
	if (check())
		temp = read1byte();
	else
		return 0;

	mnack();
	stop();
	return temp;
}
/*******************************************
 �������ƣ�Read_NByte_Randomaddress
 ��    �ܣ���EEPROM��ָ����ַ��ȡN���ֽڵ�����
 ��    ����readbuf--ָ�򱣴����ݵ�ַ��ָ��
 n--��ȡ���ݵĸ���
 dataaddress--���ݶ�ȡ���׵�ַ
 ����ֵ  ����ȡ�����1--�ɹ���0--ʧ��
 ********************************************/
unsigned char Read_NByte_Randomaddress(unsigned char * readbuf, unsigned char n,unsigned char dataaddress) {
	start();
	write1byte(deviceaddress);
	if (check())
		write1byte(dataaddress);
	else
		return 0;
	if (check()) {
		start();
		write1byte(deviceaddress | 0x01);
	} else
		return 0;
	if (check())
		readNbyte(readbuf, n);
	else
		return 0;
	return 1;
}

/**************************************************************
 �������ƣ�unsigned char WriteInt(unsigned char dataaddr,unsigned int num)
 �������ܣ���洢��д��һ��16bit������
 ���������unsigned char dataaddr--->�洢����ʼд���ַ
 unsigned int num--------->��Ҫд���16bit����
 �����������
 ����ֵ  ��д��ɹ�����1��ʧ�ܷ���0.
 ˵�����洢ʱ��λ��ǰ����λ�ں�
 �����������ݣ�0X1234   �洢��ʼ��ַΪ 0X02
 �洢����ַ      �洢����
 0X02            0X12
 0X03            0X34
 *************************************************************/
unsigned char WriteUInt16(unsigned int num, unsigned char dataaddr) {
	Uint16 u16b = { 0 };                       //16bit�����ṹ

	u16b.num = num;

	if (Write_1Byte(u16b.bit16.nHigh, dataaddr) == 0)   //д���8bit
		return 0;

	if (Write_1Byte(u16b.bit16.nLow, dataaddr + 1) == 0) //д���8bit
		return 0;

	return 1;     //����д��ɹ�
}

/**************************************************************
 �������ƣ�unsigned int ReadInt(unsigned char addr)
 �������ܣ��Ӵ洢������һ��16bit������
 ���������unsigned char dataaddr--->���ݱ����ַ
 
 �����������
 ����ֵ  ������������
 *************************************************************/
unsigned int ReadUInt16(unsigned char addr) {
	unsigned char data8[2] = { 0, 0 };
	Uint16 u16b = { 0 };                       //16bit�����ṹ

	Read_NByte_Randomaddress(data8, 2, addr);                      //��������2byte����

	u16b.bit16.nLow = data8[1];           //��8bit
	u16b.bit16.nHigh = data8[0];          //��8bit

	return u16b.num;
}

/**************************************************************
 �������ƣ�unsigned char WriteSInt32(unsigned char dataaddr,long num)
 �������ܣ���洢��д��һ��32bit�з���������
 ���������unsigned char dataaddr--->�洢����ʼд���ַ
 long num--------->��Ҫд���32bit����
 �����������
 ����ֵ  ��д��ɹ�����1��ʧ�ܷ���0.
 ˵�����洢ʱ��λ��ǰ����λ�ں�
 �����������ݣ�0X12345678   �洢��ʼ��ַΪ 0X02
 �洢����ַ      �洢����
 0X02            0X12
 0X03            0X34
 0X04            0X56
 0X05            0X78
 ע�⣺д������ʱע��洢��ҳ�߽硣
 *************************************************************/
unsigned char WriteSInt32(long num, unsigned char dataaddr) {
	Slong32 s32 = { 0 };                       //32bit�����ṹ
	unsigned char temp[4] = { 0 };

	s32.num = num;

	temp[0] = s32.bit32.nHigh.bit16.nHigh;
	temp[1] = s32.bit32.nHigh.bit16.nLow;
	temp[2] = s32.bit32.nLow.bit16.nHigh;
	temp[3] = s32.bit32.nLow.bit16.nLow;

	return Write_NByte(temp, 4, dataaddr);
	/*Ϊ�����д��Ч��ʹ�õ�������д������д������ʱע�ⲻҪԽ�磬
	 �����޷�����д��4byte���ݡ�*/
}

/**************************************************************
 �������ƣ�unsigned char WriteSInt32(unsigned char dataaddr,long num)
 �������ܣ��Ӵ洢������һ��32bit�з���������
 ���������unsigned char dataaddr--->���ݱ����ַ
 �����������
 ����ֵ  ��������32bit�з���������
 ˵�����洢ʱ��λ��ǰ����λ�ں�
 �����������ݣ�0X12345678   �洢��ʼ��ַΪ 0X02
 �洢����ַ      �洢����
 0X02            0X12
 0X03            0X34
 0X04            0X56
 0X05            0X78
 *************************************************************/
signed long ReadSInt32(unsigned char addr) {
	unsigned char data8[4] = { 0, 0 };
	Slong32 s32 = { 0 };                       //32bit�����ṹ

	Read_NByte_Randomaddress(data8, 4, addr);                      //��������4byte����

	s32.bit32.nLow.bit16.nLow = data8[3];           //��16bit�еĵ�8bit
	s32.bit32.nLow.bit16.nHigh = data8[2];          //��16bit�еĸ�8bit
	s32.bit32.nHigh.bit16.nLow = data8[1];           //��16bit�еĵ�8bit
	s32.bit32.nHigh.bit16.nHigh = data8[0];          //��16bit�еĸ�8bit

	return s32.num;
}

unsigned char AT24C04TEST(unsigned char testadd) {
	unsigned int x = 0XAAAA;
	unsigned int y = 0;

	if(WriteUInt16(x, testadd)){

		//lcd_show_strings(1,0,(uint8_t *)"wrok");
	}

	y = ReadUInt16(testadd);

	if (x == y)
		return 1;
	else
		return 0;
}
