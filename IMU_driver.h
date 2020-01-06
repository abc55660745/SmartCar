// 2012.3.1
// ??: ???????????10?????
//****************************************
// GY-52 MPU3050 IIC????
// ?????STC89C51 
// ??:11.0592M
// ??:LCD1602
// ???? Keil uVision2
// ??????24c04????
// ??:2011?9?1?
// QQ:531389319
//****************************************
#include <stdio.h>   //Keil library	
#include <INTRINS.H>
typedef unsigned short ushort;
//****************************************
// ??51?????
//****************************************
sbit    SCL=P0^4;				//IIC??????
sbit    SDA=P0^5;				//IIC??????
//****************************************
// ??MPU6050????
//****************************************
#define	SMPLRT_DIV		0x19	//??????,???:0x07(125Hz)
#define	CONFIG				0x1A	//??????,???:0x06(5Hz)
#define	GYRO_CONFIG		0x1B	//??????????,???:0x18(???,2000deg/s)
#define	ACCEL_CONFIG	0x1C	//?????????????????,???:0x01(???,2G,5Hz)
#define	ACCEL_XOUT_H	0x3B
#define	ACCEL_XOUT_L	0x3C
#define	ACCEL_YOUT_H	0x3D
#define	ACCEL_YOUT_L	0x3E
#define	ACCEL_ZOUT_H	0x3F
#define	ACCEL_ZOUT_L	0x40
#define	TEMP_OUT_H		0x41
#define	TEMP_OUT_L		0x42
#define	GYRO_XOUT_H		0x43
#define	GYRO_XOUT_L		0x44	
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48
#define	PWR_MGMT_1		0x6B	//????,???:0x00(????)
#define	WHO_AM_I			0x75	//IIC?????(????0x68,??)
#define	SlaveAddress	0xD0	//IIC??????????,+1???
//****************************************
//???????
//****************************************
uchar dis[7];							//????(-511?512)?????
int	dis_data;						//??
//int	Temperature,Temp_h,Temp_l;	//????????
//****************************************
//????
//****************************************
void  delay(unsigned int k);										//??						
void  lcd_printf(uchar *s,int temp_data);

//MPU6050????
void  InitMPU6050();													//???MPU6050
void  Delay5us();
void  I2C_Start();
void  I2C_Stop();
void  I2C_SendACK(bit ack);
bit   I2C_RecvACK();
void  I2C_SendByte(uchar dat);
uchar I2C_RecvByte();
void  I2C_ReadPage();
void  I2C_WritePage();
uchar Single_ReadI2C(uchar REG_Address);						//??I2C??
void  Single_WriteI2C(uchar REG_Address,uchar REG_data);	//?I2C????
//****************************************
//??????
//****************************************
void to_int(uchar *s,int temp_data)
{
	if(temp_data<0)
	{
		temp_data=-temp_data;
		*s='-';
	}
	else *s=' ';

	*++s =temp_data/10000+0x30;
	temp_data=temp_data%10000;     //????

	*++s =temp_data/1000+0x30;
	temp_data=temp_data%1000;     //????

	*++s =temp_data/100+0x30;
	temp_data=temp_data%100;     //????
	*++s =temp_data/10+0x30;
	temp_data=temp_data%10;      //????
	*++s =temp_data+0x30; 	
	s[7] = '!';
}
//****************************************


//****************************************
//??
//****************************************
void delay(unsigned int k)	
{						
	unsigned int i,j;				
	for(i=0;i<k;i++)
	{			
		for(j=0;j<121;j++);
	}						
}

//**************************************
//??5??(STC90C52RC@12M)
//???????,???????
//???1T?MCU?,????????
//**************************************
void Delay5us()
{
	_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
}
//**************************************
//I2C????
//**************************************
void I2C_Start()
{
    SDA = 1;                    //?????
    SCL = 1;                    //?????
    Delay5us();                 //??
    SDA = 0;                    //?????
    Delay5us();                 //??
    SCL = 0;                    //?????
}
//**************************************
//I2C????
//**************************************
void I2C_Stop()
{
    SDA = 0;                    //?????
    SCL = 1;                    //?????
    Delay5us();                 //??
    SDA = 1;                    //?????
    Delay5us();                 //??
}
//**************************************
//I2C??????
//????:ack (0:ACK 1:NAK)
//**************************************
void I2C_SendACK(bit ack)
{
    SDA = ack;                  //?????
    SCL = 1;                    //?????
    Delay5us();                 //??
    SCL = 0;                    //?????
    Delay5us();                 //??
}
//**************************************
//I2C??????
//**************************************
bit I2C_RecvACK()
{
    SCL = 1;                    //?????
    Delay5us();                 //??
    CY = SDA;                   //?????
    SCL = 0;                    //?????
    Delay5us();                 //??
    return CY;
}
//**************************************
//?I2C??????????
//**************************************
void I2C_SendByte(uchar dat)
{
    uchar i;
    for (i=0; i<8; i++)         //8????
    {
        dat <<= 1;              //????????
        SDA = CY;               //????
        SCL = 1;                //?????
        Delay5us();             //??
        SCL = 0;                //?????
        Delay5us();             //??
    }
    I2C_RecvACK();
}
//**************************************
//?I2C??????????
//**************************************
uchar I2C_RecvByte()
{
    uchar i;
    uchar dat = 0;
    SDA = 1;                    //??????,??????,
    for (i=0; i<8; i++)         //8????
    {
        dat <<= 1;
        SCL = 1;                //?????
        Delay5us();             //??
        dat |= SDA;             //???               
        SCL = 0;                //?????
        Delay5us();             //??
    }
    return dat;
}
//**************************************
//?I2C??????????
//**************************************
void Single_WriteI2C(uchar REG_Address,uchar REG_data)
{
    I2C_Start();                  //????
    I2C_SendByte(SlaveAddress);   //??????+???
    I2C_SendByte(REG_Address);    //???????,
    I2C_SendByte(REG_data);       //???????,
    I2C_Stop();                   //??????
}
//**************************************
//?I2C??????????
//**************************************
uchar Single_ReadI2C(uchar REG_Address)
{
	uchar REG_data;
	I2C_Start();                   //????
	I2C_SendByte(SlaveAddress);    //??????+???
	I2C_SendByte(REG_Address);     //????????,?0??	
	I2C_Start();                   //????
	I2C_SendByte(SlaveAddress+1);  //??????+???
	REG_data=I2C_RecvByte();       //???????
	I2C_SendACK(1);                //??????
	I2C_Stop();                    //????
	return REG_data;
}
//**************************************
//???MPU6050
//**************************************
void InitMPU6050()
{
	Single_WriteI2C(PWR_MGMT_1, 0x00);	//??????
	Single_WriteI2C(SMPLRT_DIV, 0x07);
	Single_WriteI2C(CONFIG, 0x06);
	Single_WriteI2C(GYRO_CONFIG, 0x18);
	Single_WriteI2C(ACCEL_CONFIG, 0x01);
}
//**************************************
//????
//**************************************
int GetData(uchar REG_Address)
{
	uchar H,L;
	H=Single_ReadI2C(REG_Address);
	L=Single_ReadI2C(REG_Address+1);
	return (H<<8)+L;   //????
}