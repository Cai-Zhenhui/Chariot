#ifndef _hwjs_H
#define _hwjs_H

#include "system.h"



void Hwjs_Init(void);
u8 HW_jssj(void);

//����ȫ�ֱ���

extern unsigned char IRcord[4];//������ŷ������ĸ��ֽڵ����� ���������� ��IRcord[2]��
//extern unsigned char IRdata[32];//�ô洢32λ��������
extern unsigned char IRok;

#endif
