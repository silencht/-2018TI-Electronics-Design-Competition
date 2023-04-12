#ifndef __FDC2214_H
#define __FDC2214_H
#include "sys.h"
#include "silencht_usart.h"	

//IO��������
//#define FDC_SDA_IN()  {GPIOC->CRL&=0XFF0FFFFF;GPIOC->CRL|=8<<4*5;}  //STM32F103
//#define FDC_SDA_OUT() {GPIOC->CRL&=0XFF0FFFFF;GPIOC->CRL|=3<<4*5;}
#define FDC_SDA_IN()  {GPIOC->MODER&=~(3<<(5*2));GPIOC->MODER|=0<<(5*2);delay_us(1);}//STM32F407
#define FDC_SDA_OUT() {GPIOC->MODER&=~(3<<(5*2));GPIOC->MODER|=1<<(5*2);delay_us(1);}

//IO��������	 
#define FDC_IIC_SCL    PCout(4) 	//SCL
#define FDC_IIC_SDA    PCout(5)   //���SDA	 
#define FDC_READ_SDA   PCin(5) 		//����SDA 

/*FDC2214    iic�ӵ�ַ
 *ADDR = L , I2C Address = 0x2A
 *ADDR = H , I2C Address = 0x2B*/
#define FDC2214_ADDR 0x2A

/*FDC2214�����Ĵ�����ַ*/
#define DATA_CH0 0x00      //�������ݼĴ�����DATA_CH0����ͨ��0��8λ��ַ�������DATA_LSB_CH0�����8λ��ַ������ͨ��ͬ
#define DATA_LSB_CH0 0x01  //����ע������λ��ַ�����ڵ�λ��ַǰ��������ֵ��Ϊ0x00000000Ϊ���ڿɼ��ֵ��0xffffffffΪ������ⷶΧ
#define DATA_CH1 0x02			 //��ͨ��ת��ʱ�����ʱ��Ϊ������ʱ����ܺͣ��������֣��ֱ�Ϊ��1�������ʱ��2ת��ʱ��3ͨ���л�ʱ�䣨datasheet page16��
#define DATA_LSB_CH1 0x03	 //3ͨ���л�ʱ�䣬��datasheet page17 ��6����ʽ
#define DATA_CH2 0x04	
#define DATA_LSB_CH2 0x05	 
#define DATA_CH3 0x06			 
#define DATA_LSB_CH3 0x07	
#define RCOUNT_CH0 0x08    //ת��ʱ�����üĴ�����ַ��ͨ��0-3��ת��ʱ�乫ʽ��(CHx_RCOUNT*16+4)/fREFx 
#define RCOUNT_CH1 0x09		 //2ת��ʱ��������RCOUNT_CHx�Ĵ����У�ת��ʱ���������������������Ƶ�ʵĲο�ʱ�����ڵ�������Ŀ����������Ҫת������Чλ��Ϊ13,
#define RCOUNT_CH2 0x0A    //��ô��С��Ҫ2^13=8192��ʱ����������ת�������CHx_RCOUNT��ֵӦ������Ϊ0x0200.
#define RCOUNT_CH3 0x0B
//#define OFFSET_CH0 0x0C  //FDC2114
//#define OFFSET_CH1 0x0D
//#define OFFSET_CH2 0x0E
//#define OFFSET_CH3 0x0F
#define SETTLECOUNT_CH0 0x10 //1�������ʱ���Ŀ����ʹ�������ȶ����������ʱ���õ�ʱ��Ӧ�㹻���������������������ȶ�
#define SETTLECOUNT_CH1 0x11 //ÿ��ͨ�������õȴ��ȶ�ʱ�乫ʽΪ��tsx=��CHX_SETTLECOUNT*16��/fREFx 
#define SETTLECOUNT_CH2 0x12 //���õȴ����ʱ��Ĵ������õ�ַ��ͨ��0-3�����ֵ�������� datasheet page17�еģ�4����ʽ��������Сֵ�Ƽ�10
#define SETTLECOUNT_CH3 0x13
#define CLOCK_DIVIDERS_C_CH0 0x14   //ʱ�ӷ�Ƶ���üĴ�����[15:14]����������Ϊb00   datasheet page30
#define CLOCK_DIVIDERS_C_CH1 0x15		//CHx_FIN_SEL��������Ƶ��[13:12]���ڲ�ͬ�������õĴ���Ƶ��ѡ�� b01����Ƶ��Χ��0.01mhz-8.75mhz ��b10����Ƶ��Χ��0.01-10mhz
#define CLOCK_DIVIDERS_C_CH2 0x16		//��Ϊ������Ϊsingle_endedģʽ�ģ�����ѡ��b10������see datasheet page42
#define CLOCK_DIVIDERS_C_CH3 0x17		//CHx_REF_DIVIDER�ο�Ƶ�ʷָ�[9:0]������ʹ��b00 00000000������Frefx�ο�Ƶ��Ϊ�ڲ�ʱ������Ƶ�ʳ��Էָ�ֵ
#define STATUS 0x18               //״̬�Ĵ���
#define ERROR_CONFIG 0x19 				//���󱨸�����
#define CONFIG 0x1A  							//ʱ��Դ��INTB������/˯��/�ػ�ģʽ���͹��ĵ�ģʽ����
#define MUX_CONFIG 0x1B						//��ͨ������
#define RESET_DEV 0x1C						//д�üĴ�����ֹͣת�������мĴ����ָ���ʼֵ������ֵ����ʼ��Ϊ0
#define DRIVE_CURRENT_CH0 0x1E    //��ǰ���������ƼĴ���������������������
#define DRIVE_CURRENT_CH1 0x1F
#define DRIVE_CURRENT_CH2 0x20
#define DRIVE_CURRENT_CH3 0x21
#define MANUFACTURER_ID 0x7E      //��ȡֵ��0x5449
#define DEVICE_ID 0x7F            //��ȡֵ��0x3055

//extern u16 Data_FDC;

//��غ�������
u8 Set_FDC2214(u8 reg,u8 MSB,u8 LSB);

u16 FDC_Read(u8 reg);

//u16 FCD2214_ReadCH(u8 index);
u32 FCD2214_ReadCH(u8 index);
u8 FDC2214_Init(void);

float Cap_Calculate(u8 chx);

#endif
