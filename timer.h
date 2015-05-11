/*****************************************************************
* Copyright (C) 2015 Maipu Communication Technology Co.,Ltd.*
******************************************************************
* timer.h
*
* DESCRIPTION:
*
*       定时器的头文件，提供定时功能，基本单位为秒（S）
* AUTHOR:
*       胡林康
* CREATED DATE:
*       2015年4月1日
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

/* 封装基本数据类型*/
typedef int             int16;
typedef unsigned int    uint16;
typedef char            int8;

/*定时器状态类型  枚举*/
typedef enum timeState{
    ready = 0,
    start,
    stop
} TimeState;
/*定时器节点的数据结构*/
typedef struct timerNode{
    int16(*ptr)();      /*任务入口地址*/
    uint16 type;        /*定时器的类型，定时一次，指定次数或者周期性*/
    TimeState state;    /*定时器的状态*/
    uint16 time;        /*定时时长*/
    uint16 timeToDead;  /*剩余时长*/
    uint16 hitCnt;      /*命中次数*/
    struct timerNode *next;
} TimerNode;



/*函数声明*/
int timerInit(int16 (*)(), int , int ); /*初始化定时器*/
void timerStart();                      /*定时器启动*/
int timerShutdowm();                    /*终止定时器*/
void timerInsert(TimerNode *);          /*插入一个新的定时器*/
void timerDelete();                     /*删除定时器节点，释放内存*/
void timerRefresh();                    /*更新定时器*/
void timerShow();                       /*显示当前存在定时器*/



#endif