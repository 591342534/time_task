/*****************************************************************
* Copyright (C) 2015 Maipu Communication Technology Co.,Ltd.*
******************************************************************
* timer.h
*
* DESCRIPTION:
*
*       ��ʱ����ͷ�ļ����ṩ��ʱ���ܣ�������λΪ�루S��
* AUTHOR:
*       ���ֿ�
* CREATED DATE:
*       2015��4��1��
* REVISION:
* 1.0
* MODIFICATION HISTORY
* --------------------
* $Log:$
*
*****************************************************************/

#ifndef _TIMER_H
#define _TIMER_H

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

/* ��װ������������*/
typedef int             int16;
typedef unsigned int    uint16;
typedef char            int8;

/*��ʱ��״̬����  ö��*/
typedef enum timeState{
    ready = 0,
    start,
    stop
} TimeState;
/*��ʱ���ڵ�����ݽṹ*/
typedef struct timerNode{
    int16(*ptr)();      /*������ڵ�ַ*/
    uint16 type;        /*��ʱ�������ͣ���ʱһ�Σ�ָ����������������*/
    TimeState state;    /*��ʱ����״̬*/
    uint16 time;        /*��ʱʱ��*/
    uint16 timeToDead;  /*ʣ��ʱ��*/
    uint16 hitCnt;      /*���д���*/
    struct timerNode *next;
} TimerNode;



/*��������*/
int timerInit(int16 (*)(), int , int ); /*��ʼ����ʱ��*/
void timerStart();                      /*��ʱ������*/
int timerShutdowm();                    /*��ֹ��ʱ��*/
void timerInsert(TimerNode *);          /*����һ���µĶ�ʱ��*/
void timerDelete();                     /*ɾ����ʱ���ڵ㣬�ͷ��ڴ�*/
void timerRefresh();                    /*���¶�ʱ��*/
void timerShow();                       /*��ʾ��ǰ���ڶ�ʱ��*/



#endif