#include "sys.h"
#include "delay.h"
#include "silencht_usart.h"	
#include "led.h"
#include "fdc2214.h"
#include "DataScope_DP.h"
#define FILTER_N 12
//3.3nF ��ʾ3200 ��ʾ��ֵΪpF
float res0,res1,res2,res3;
float temp0,temp1,temp2,temp3;

//�������ӣ� SCL:PC4  SDA:PC5  SD/ADDR:GND VCC:3.3V

float filter0_buf[FILTER_N+1],filter1_buf[FILTER_N+1],filter2_buf[FILTER_N+1],filter3_buf[FILTER_N+1];
float Filter(u8 t);


int main(void)
{ 

  unsigned char i;          //��������
	unsigned char Send_Count; //������Ҫ���͵����ݸ���
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);      //��ʼ����ʱ����
	usart1_init(115200);  //���Դ��� 
	LED_Init();					  //��ʼ��LED
	u1_printf ("test FDC2214!\r\n");
	delay_ms(10);
		
	while(FDC2214_Init())delay_ms(100);//FDC2214��ʼ��
	delay_ms(500);
	temp0 = Cap_Calculate(0);;//��ȡ��ʼֵ
	temp1 = Cap_Calculate(1);
	temp2 = Cap_Calculate(2);
	temp3 = Cap_Calculate(3);
	
  while(1)
	{		
    res0 = Filter(0);	
		res1 = Filter(1);
		res2 = Filter(2);
		res3 = Filter(3);
		if(res0>1&&res1>1&res2>1&&res3>1)
		{
			res0 = res0-temp0;//���ݽӿڿ��ؼ�����ʼֵ
			res1 = res1-temp1;
			res2 = res2-temp2;
			res3 = res3-temp3;
					
			DataScope_Get_Channel_Data( res0*10 , 1 ); //������ 1.0  д��ͨ�� 1
      DataScope_Get_Channel_Data( res1*10 , 2 ); //������ 2.0  д��ͨ�� 2
      DataScope_Get_Channel_Data( res2*10 , 3 ); //������ 3.0  д��ͨ�� 3
      DataScope_Get_Channel_Data( res3*10 , 4 ); //������ 4.0  д��ͨ�� 4
			Send_Count = DataScope_Data_Generate(4); //����4��ͨ���� ��ʽ��֡���ݣ�����֡���ݳ���
			for( i = 0 ; i < Send_Count; i++)  //ѭ������,ֱ���������   
	 	  {
		    while((USART1->SR&0X40)==0);  
  	    USART1->DR = DataScope_OutPut_Buffer[i]; //�Ӵ��ڶ�һ���ֽ����ݳ�ȥ      
		  }
      delay_ms(10); //20fps, ֡���ʱ�䡣 ��ͬ�������ü� USB-TTL �豸�����Ӿ���Ӱ���ʱ��ĳ��̣�����ʵ��Ϊ׼��  
		}		
	}
}


float Filter(u8 t) {
    int i;
    float filter0_sum = 0,filter1_sum = 0,filter2_sum = 0,filter3_sum = 0;
		switch(t)
		{
			case 0:
							filter0_buf[FILTER_N] = Cap_Calculate(0);
							for(i = 0; i < FILTER_N; i++) {filter0_buf[i] = filter0_buf[i + 1]; filter0_sum += filter0_buf[i];}
							return (float)(filter0_sum / FILTER_N);
							
			case 1:
							filter1_buf[FILTER_N] = Cap_Calculate(1);
							for(i = 0; i < FILTER_N; i++) {filter1_buf[i] = filter1_buf[i + 1]; filter1_sum += filter1_buf[i];}
							return (float)(filter1_sum / FILTER_N);
							
			case 2:
							filter2_buf[FILTER_N] = Cap_Calculate(2);
							for(i = 0; i < FILTER_N; i++) {filter2_buf[i] = filter2_buf[i + 1]; filter2_sum += filter2_buf[i];}
							return (float)(filter2_sum / FILTER_N);
							
			case 3: 
							filter3_buf[FILTER_N] = Cap_Calculate(3);
							for(i = 0; i < FILTER_N; i++) {filter3_buf[i] = filter3_buf[i + 1]; filter3_sum += filter3_buf[i];}
							return (float)(filter3_sum / FILTER_N);
								
			default:return (float)(0);
		 
		}
}


//			u1_printf("CH0:%3.3f CH1:%3.3f CH2:%3.3f CH3:%3.3f\r\n",res0,res1,res2,res3); 

