//1. 工程添加 DSP2803x_usDelay.asm文件
//2. 声明extern Uint16 RamfuncsLoadSize，（RamfuncsRunStart和RamfuncsLoadStart在DSP2803x_GlobalPrototypes.h已声明）
//3. 使用memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (Uint32)&RamfuncsLoadSize);初始化在RAM运行代码
//4. 调用DELAY_US()即可，形参范围是 long doubl；单位为us （1秒为1000毫秒，1毫秒为1000微妙）
/*
//## 根据原理图，硬件资源分配如下#
//外设	    IO口	                说明
//D400	    OPWM7B/LED_BK/GPIO41	IO输出
//D401	    LED1/GPIO34             IO输出
//D402	    GPIO43	                IO输出
//
//D5的红色	OPWM4B/GPIO7	        IO输出
//D5的绿色	OPWM5A/GPIO8	        IO输出
//D5的蓝色	OPWM5B/GPIO9	        IO输出
//
//独立按键S100 IKEY/GPIO27	        IO输入 （黑色）
//扫描按键S101 由TM1650驱动	        见例程《IndependentProject_IIC_TM1650》
//扫描按键S102 由TM1650驱动	        见例程《IndependentProject_IIC_TM1650》

//## 三色5050封装LED，位于板子左下角，由74HC125的5V输出驱动（高电平点亮）
//## J1跳线帽为74HC125的使能端,三色LED受J1的控制
//## J2跳线帽为使能三色 LED（J2位于三色LED的上方）电流回路到GND
//##
-------------------------------------------------------------------------------------*/


//--------AD试验，开发板硬件配置--------------------------------------------
//默认下，VREF+的0欧电阻R408不焊接；
//程序里选择内部基准源，则无需VREF+从外部接入；若采用外部基准源，则最大为3.3V
//开发板的P10排针（6针，位于板子左上角）的RG，为可调电阻的输出，可将RG直接接入到模拟输入口A1进行试验

//------------------AD试验，SOC采样设置，使用SOC0到SOC3------------
//SOC0到SOC3都配置为---A1 -- 可调电阻RG

//--------AD试验，运行例程说明、重要函数--------------------------------------------
//主要函数在 ad.c 里的  void ADC_Config(void)  和 interrupt void adc_isr(void);
//AD配置为软件触发；
//在AD中断里打印采样的值

//串口调试助手设置：128000 8N1

//###########################################################################



	CANInit();//CAN初始化
	//初始化发送参数
	PtrCanTx-> MBXnbr = 1;       //1号邮箱发送
	PtrCanTx-> RevMBXnID = 0x50; //邮箱ID 取值范围 0x00 到 0x3FF , 11bit 标准帧ID
	PtrCanTx->DA = 0x0001;
	PtrCanTx->DB = 0x0B02;
	PtrCanTx->DC = 0x0C03;
	PtrCanTx->DD = 0x0D04;
	
	        //CAN测试发送
    	if(PtrCanTx->MBXnbr <= 6)
    	{
    		CAN_Send(PtrCanTx);
    		PtrCanTx->DA ++;   //改变发送数据
        	PtrCanTx->MBXnbr++;//改变发送邮箱
        	PtrCanTx->RevMBXnID++;//改变接收邮箱
    	}
    	//处理CAN接收函数,数码管显示一个CAN接收最低byte内容（HEX格式）
    	handleCANRxFIFO();