#define PIDa 1
#define PIDb 3
#define PIDc 50
#define min 0
#define max_speed 0x28

void init_uart()
{
	SCON = 0x50;
	TMOD = 0x22;
	PCON = 0x00;
	TL0 = 0x23;
	TH0 = 0x23;
	TL1 = 0xfd;
	TH1 = 0xfd;
	ES = 1;
	ET0 = 1;
	EA = 1;
	TCON = 0x50;
}