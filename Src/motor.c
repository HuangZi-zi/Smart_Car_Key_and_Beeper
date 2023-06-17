#include "motor.h"
#include "main.h"
#include "tim.h"
#include "math.h"

void SetMotorSpeed(unsigned char ucChannel,signed char cSpeed)
{
		short sPWM;
	
		if (cSpeed>=100) 
			cSpeed = 100;
	  if (cSpeed<=-100) 
			cSpeed = -100;
	
		//cSpeed������ٶȰٷ�ֵ����Ҫ��������PWM��ֵ
		//����pwm����0-3599������ٶ�50%����Ҫ50%ռ�ձȣ�����ֵӦ�趨Ϊ1799
   	sPWM = 3599 - fabs(cSpeed)*36;
	switch(ucChannel)
	{
		case 0://����
			/*__HAL_TIM_SetCompare��������ռ�ձȡ�
				���һ������������ֵ������������ֵ�������ֵ���бȽ�
				���ն�ʱ�����������õõ���Ӧ��PWM��*/
			__HAL_TIM_SetCompare(&htim4,TIM_CHANNEL_3,sPWM);
			if (cSpeed>0) 
			//���Ʒ���
				RIGHT_MOTOR_RESET;
			else if(cSpeed<0) 
				RIGHT_MOTOR_SET;		
			break;
		case 1://����
			__HAL_TIM_SetCompare(&htim4,TIM_CHANNEL_4,sPWM);
			if (cSpeed>0) 
				LEFT_MOTOR_SET;
			else if (cSpeed<0)
				LEFT_MOTOR_RESET;
			break;			
	}
}

void forward(signed char speed, int time)//ǰ��
{
	SetMotorSpeed(1,-speed);//����  Ϊ����
	SetMotorSpeed(0,speed);//����   Ϊ����
	HAL_Delay(time);                 //ʱ��Ϊ����
}

void back(signed char speed,int time) //����
{
	  SetMotorSpeed(1,100-speed);//����   //Ϊ����
	  SetMotorSpeed(0,-speed);//���� //Ϊ����
		HAL_Delay(time);                 //ʱ��Ϊ����  
}

void brake(int time)//ɲ��
{
	SetMotorSpeed(1,0);//����   Ϊ0
	SetMotorSpeed(0,0);//����   Ϊ0
  RIGHT_MOTOR_RESET;
  LEFT_MOTOR_RESET;
	HAL_Delay(time);             //ʱ��Ϊ����  
}

void turn_left(signed char speed,int time) //��ת��
{
	  SetMotorSpeed(1,0);//���� ����
	  SetMotorSpeed(0,speed);  //����Ϊ��
		HAL_Delay(time);            //ʱ��Ϊ����  
}

void spin_left(signed char speed,int time) //����ת
{
 	  SetMotorSpeed(1,speed); //����    Ϊ��
	  SetMotorSpeed(0,100 - speed);     //����Ϊ��
		HAL_Delay(time);            //ʱ��Ϊ����  
}

void turn_right(signed char speed,int time)  //��ת��
{
	  SetMotorSpeed(1,-speed);     //����Ϊ��
	  SetMotorSpeed(0,0);                 //����Ϊ0
		HAL_Delay(time);                   //ʱ��Ϊ����  
}

void spin_right(signed char speed,int time) //����ת����
{
	  SetMotorSpeed(1,-(100-speed));//����     //����Ϊ��
	  SetMotorSpeed(0,-speed);            //����Ϊ��
		HAL_Delay(time);                    //ʱ��Ϊ����  
}
