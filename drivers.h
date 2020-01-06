sbit m1a = P1^0;
sbit m1b = P1^1;
sbit m2a = P1^2;
sbit m2b = P1^3;
sbit m3a = P1^4;
sbit m3b = P1^5;
sbit m4a = P1^6;
sbit m4b = P1^7;
sbit dja = P3^7;
sbit lf1 = P2^0;
sbit lf2 = P2^1;
sbit lf3 = P2^2;
sbit lf4 = P2^3;
sbit lb1 = P2^4;
sbit lb2 = P2^5;
sbit lb3 = P2^6;
sbit lb4 = P2^7;
sbit sda = P0^3;
sbit scl = P0^4;
sbit lm1 = P0^0;
sbit lm2 = P0^1;
sbit lm3 = P0^3;
sbit lm4 = P0^2;
uchar pwm_i = 0;
uchar m1 = 255;
uchar m2 = 255;
uchar m3 = 255;
uchar m4 = 255;
uchar dj = 236;
uchar di = 255;
uchar flag = 0;
uchar speed[4] = {0};
uchar speedtest[4] = {0};
uchar PID_i = 0;

uchar time = 0;

int PIDlast[5][2] = {0};
int PIDsum[5] = {0};
uchar PIDto[5] = {10, 10, 10, 10, 255};
//uchar PIDto[5] = {0};
void PIDm1();
void PIDm2();
void PIDm3();
void PIDm4();
void PIDdj();
int temppp;
void send(char s[])
{
	uchar i;
	for(i = 0;s[i] != '!';i++)
	{
		SBUF = s[i];
		while(!TI);
		TI = 0;
	}
}

void recive() interrupt 4
{
	uchar i1;
	RI = 0;
	//dj = SBUF;
	for(i1=0;i1<5;i1++)
		PIDto[i1] = SBUF;
	send("recived");
}

void pwm() interrupt 1
{

	pwm_i++;
	if(pwm_i >= 254)
	{
		pwm_i = 0;
		P1 = 0;
		dja = 0;
		PID_i++;
		
	}
	if(PID_i >= 10)
	{
		PID_i = 0;
		speed[0] = speedtest[0];
		speed[1] = speedtest[1];
		speed[2] = speedtest[2];
		speed[3] = speedtest[3];
		//speed[3] = 0;
		speedtest[0] = 0;
		speedtest[1] = 0;
		speedtest[2] = 0;
		speedtest[3] = 0;
		PIDm1();
		PIDm2();
		PIDm3();
		PIDm4();
		//PIDdj();
		//send(speed);
		time++;
		send("now!");
		//to_int(dis, GetData(ACCEL_XOUT_H));
		to_int(dis, speed[0]);
		send(dis);
		send("\n!");
	}
	/*if(time == 10)
	{
		time = 0;
		if(di != 0)
			di = 0;
		else
			di =255;
	}*/
	if(pwm_i > m1)
	{
		if(di == 0)
			m1a = 1;
		else
			m1b = 1;
	}
	if(pwm_i > m2)
	{
		if(di == 0)
			m2a = 1;
		else
			m2b = 1;
	}
	if(pwm_i > m3)
	{
		if(di == 0)
			m3a = 1;
		else
			m3b = 1;
	}
	if(pwm_i > m4)
	{
		if(di == 0)
			m4a = 1;
		else
			m4b = 1;
	}
	if(pwm_i > dj)
		dja = 1;
}

void PIDm1()
{
	int result;
	if(abs(PIDto[0] - speed[0]) > min)
	{
		result = (PIDto[0] - speed[0]) / PIDa;
		if(PIDlast[0][0] && PIDlast[0][1])
			result -= (PIDlast[0][0] - PIDlast[0][1]) / PIDb;
		result += PIDsum[0] / PIDc;
		if(m1 - result > 255)
			m1 = 0;
		else if(m1 - result < 0)
			m1 = 255;
		m1 -= result;
		PIDlast[0][1] = PIDlast[0][0];
		PIDlast[0][0] = (PIDto[0] - speed[0]);
		if(abs(PIDsum[0] + result) > 30000)
			PIDsum[0] = 0;
		PIDsum[0] += result;
	}
	else
	{
		PIDlast[0][0] = 0;
		PIDlast[0][1] = 0;
		PIDsum[0] = 0;
	}
	if(PIDto[0] == 0)
		m1 = 255;
}

void PIDm2()
{
	int result;
	if(abs(PIDto[1] - speed[1]) > min)
	{
		result = (PIDto[1] - speed[1]) / PIDa;
		if(PIDlast[1][0] && PIDlast[1][1])
			result -= (PIDlast[1][0] - PIDlast[1][1]) / PIDb;
		result += PIDsum[1] / PIDc;
		if(m2 - result > 255)
			m2 = 0;
		else if(m2 - result < 0)
			m2 = 255;
		m2 -= result;
		PIDlast[1][1] = PIDlast[1][0];
		PIDlast[1][0] = (PIDto[1] - speed[1]);
		if(abs(PIDsum[1] + result) > 30000)
			PIDsum[1] = 0;
		PIDsum[1] += result;
	}
	else
	{
		PIDlast[1][0] = 0;
		PIDlast[1][1] = 0;
		PIDsum[1] = 0;
	}
	if(PIDto[1] == 0)
		m2 = 255;
}

void PIDm3()
{
	int result;
	if(abs(PIDto[2] - speed[2]) > min)
	{
		result = (PIDto[2] - speed[2]) / PIDa;
		if(PIDlast[2][0] && PIDlast[2][1])
			result -= (PIDlast[2][0] - PIDlast[2][1]) / PIDb;
		result += PIDsum[2] / PIDc;
		if(m3 - result > 255)
			m3 = 0;
		else if(m3 - result < 0)
			m3 = 255;
		m3 -= result;
		PIDlast[2][1] = PIDlast[2][0];
		PIDlast[2][0] = (PIDto[2] - speed[2]);
		if(abs(PIDsum[2] + result) > 30000)
			PIDsum[2] = 0;
		PIDsum[2] += result;
	}
	else
	{
		PIDlast[2][0] = 0;
		PIDlast[2][1] = 0;
		PIDsum[2] = 0;
	}
	if(PIDto[2] == 0)
		m3 = 255;
}

void PIDm4()
{
	int result;
	if(abs(PIDto[3] - speed[3]) > min)
	{
		result = (PIDto[3] - speed[3]) / PIDa;
		if(PIDlast[3][0] && PIDlast[3][1])
			result -= (PIDlast[3][0] - PIDlast[3][1]) / PIDb;
		result += PIDsum[3] / PIDc;
		if(m4 - result > 255)
			m4 = 0;
		else if(m4 - result < 0)
			m4 = 255;
		m4 -= result;
		PIDlast[3][1] = PIDlast[3][0];
		PIDlast[3][0] = (PIDto[3] - speed[3]);
		if(abs(PIDsum[3] + result) > 30000)
			PIDsum[3] = 0;
		PIDsum[3] += result;
	}
	else
	{
		PIDlast[3][0] = 0;
		PIDlast[3][1] = 0;
		PIDsum[3] = 0;
	}
	if(PIDto[3] == 0)
		m4 = 255;
}

void PIDdj()
{
	int result;
	if(abs(PIDto[4] - dj) >= min)
	{
		result = (PIDto[4] - dj) / PIDa;
		if(PIDlast[4][0] && PIDlast[4][1])
			result -= (PIDlast[4][0] - PIDlast[4][1]) / PIDb;
		result += PIDsum[4] / PIDc;
		dj += result;
		PIDlast[4][1] = PIDlast[4][0];
		PIDlast[4][0] = dj;
		PIDsum[4] += result;
	}
	else
	{
		PIDlast[4][0] = 0;
		PIDlast[4][1] = 0;
		PIDsum[4] = 0;
		dj = PIDto[4];
	}
}

