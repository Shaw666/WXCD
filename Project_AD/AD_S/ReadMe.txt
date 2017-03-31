//1. ������� DSP2803x_usDelay.asm�ļ�
//2. ����extern Uint16 RamfuncsLoadSize����RamfuncsRunStart��RamfuncsLoadStart��DSP2803x_GlobalPrototypes.h��������
//3. ʹ��memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (Uint32)&RamfuncsLoadSize);��ʼ����RAM���д���
//4. ����DELAY_US()���ɣ��βη�Χ�� long doubl����λΪus ��1��Ϊ1000���룬1����Ϊ1000΢�
/*
//## ����ԭ��ͼ��Ӳ����Դ��������#
//����	    IO��	                ˵��
//D400	    OPWM7B/LED_BK/GPIO41	IO���
//D401	    LED1/GPIO34             IO���
//D402	    GPIO43	                IO���
//
//D5�ĺ�ɫ	OPWM4B/GPIO7	        IO���
//D5����ɫ	OPWM5A/GPIO8	        IO���
//D5����ɫ	OPWM5B/GPIO9	        IO���
//
//��������S100 IKEY/GPIO27	        IO���� ����ɫ��
//ɨ�谴��S101 ��TM1650����	        �����̡�IndependentProject_IIC_TM1650��
//ɨ�谴��S102 ��TM1650����	        �����̡�IndependentProject_IIC_TM1650��

//## ��ɫ5050��װLED��λ�ڰ������½ǣ���74HC125��5V����������ߵ�ƽ������
//## J1����ñΪ74HC125��ʹ�ܶ�,��ɫLED��J1�Ŀ���
//## J2����ñΪʹ����ɫ LED��J2λ����ɫLED���Ϸ���������·��GND
//##
-------------------------------------------------------------------------------------*/


//--------AD���飬������Ӳ������--------------------------------------------
//Ĭ���£�VREF+��0ŷ����R408�����ӣ�
//������ѡ���ڲ���׼Դ��������VREF+���ⲿ���룻�������ⲿ��׼Դ�������Ϊ3.3V
//�������P10���루6�룬λ�ڰ������Ͻǣ���RG��Ϊ�ɵ������������ɽ�RGֱ�ӽ��뵽ģ�������A1��������

//------------------AD���飬SOC�������ã�ʹ��SOC0��SOC3------------
//SOC0��SOC3������Ϊ---A1 -- �ɵ�����RG

//--------AD���飬��������˵������Ҫ����--------------------------------------------
//��Ҫ������ ad.c ���  void ADC_Config(void)  �� interrupt void adc_isr(void);
//AD����Ϊ���������
//��AD�ж����ӡ������ֵ

//���ڵ����������ã�128000 8N1

//###########################################################################



	CANInit();//CAN��ʼ��
	//��ʼ�����Ͳ���
	PtrCanTx-> MBXnbr = 1;       //1�����䷢��
	PtrCanTx-> RevMBXnID = 0x50; //����ID ȡֵ��Χ 0x00 �� 0x3FF , 11bit ��׼֡ID
	PtrCanTx->DA = 0x0001;
	PtrCanTx->DB = 0x0B02;
	PtrCanTx->DC = 0x0C03;
	PtrCanTx->DD = 0x0D04;
	
	        //CAN���Է���
    	if(PtrCanTx->MBXnbr <= 6)
    	{
    		CAN_Send(PtrCanTx);
    		PtrCanTx->DA ++;   //�ı䷢������
        	PtrCanTx->MBXnbr++;//�ı䷢������
        	PtrCanTx->RevMBXnID++;//�ı��������
    	}
    	//����CAN���պ���,�������ʾһ��CAN�������byte���ݣ�HEX��ʽ��
    	handleCANRxFIFO();