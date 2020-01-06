#include<reg52.h>
#include<math.h>
#define uint unsigned int
#define uchar unsigned char
#include<IMU_driver.h>
#include<string.h>
#include<init.h>
#include<drivers.h>

void main()
{
	delay(500);
	init_uart();
	InitMPU6050();
	P2 = 0xff;
	//delay(150);
	send("started!");
	while(1)
	{
		if(lm1 == 1 && !(flag&0x08))
		{
			speedtest[0] += 1;
			flag ^= 0x08;
		}
		else if(lm1 == 0 && flag&0x08)
			flag ^= 0x08;
		if(lm2 == 1 && !(flag&0x04))
		{
			speedtest[1] += 1;
			flag ^= 0x04;
		}
		else if(lm2 == 0 && flag&0x04)
			flag ^= 0x04;
		if(lm3 == 1 && !(flag&0x02))
		{
			speedtest[2] += 1;
			flag ^= 0x02;
		}
		else if(lm3 == 0 && flag&0x02)
			flag ^= 0x02;
		if(lm4 == 1 && !(flag&0x01))
		{
			speedtest[3] += 1;
			flag ^= 0x01;
		}
		else if(lm4 == 0 && flag&0x01)
			flag ^= 0x01;
	}
}
