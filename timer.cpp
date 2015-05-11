#include "timer.h"

TimerNode *head = NULL;

/***************************************************************
*DESCRIPTION:
*		定时器的初始化函数，定时器初始化默认为ready状态，需要
*       timerStart（）函数启动定时器才开始定时。
*INPUTS：
*		ptr: 需要定时的函数的地址
*		time:定时时长
*       num: 该函数需要定时的次数 
*               0：表示周期性执行
*               1：执行一次
*               >1:执行指定的次数
*
*       例如：
*           timerInit(task1, 10, 3);
*           表示task1任务将每隔10s运行一次，一共运行3次
*OUTPUTS：
*		NONE
*RETURNS：
*       FALSE：分配内存失败，函数出错返回
*       TRUE:  正常
*****************************************************************/
int timerInit(int16 (*ptr)(), int time, int num)
{   
    TimerNode *newTimer = (TimerNode *)malloc(sizeof(TimerNode));
    if (newTimer == NULL) {
        return FALSE;
    }
    newTimer->ptr =  ptr;
    newTimer->type = num;
    newTimer->state = ready;
    newTimer->time = time;
    newTimer->timeToDead = time;
    newTimer->hitCnt = 0;
    newTimer->next = NULL;
    timerInsert(newTimer);
    return TRUE;
}

/***************************************************************
*DESCRIPTION:
*		启动所有的定时器，并开始定时功能
*       ！！！先初始化定时器，再启动定时器
*INPUTS：
*		NONE
*OUTPUTS：
*		NONE
*RETURNS：
*		0：正常返回
*****************************************************************/
void timerStart(void)
{
    TimerNode *pScan = head;
    while (pScan != NULL) {
        pScan->state = start;
        printf("start!");
        pScan = pScan->next;
    }
    timerRefresh();
}

/***************************************************************
*DESCRIPTION:
*		停止所有的定时器，并向屏幕输出“stop！”
*INPUTS：
*		NONE
*OUTPUTS：
*		NONE
*RETURNS：
*		NONE
*****************************************************************/
void timerStop(void)
{
    TimerNode *pScan = head;
    while (pScan != NULL) {
        pScan->state = stop;
        printf("stop!");
        pScan = pScan->next;
    }
}

/***************************************************************
*DESCRIPTION:
*		顺序插入新建的定时器
*INPUTS：
*		TimerNode *newTimer:新的定时器结构体地址
*OUTPUTS：
*		NONE
*RETURNS：
*		NONE
*****************************************************************/
void timerInsert(TimerNode *newTimer)
{
    TimerNode *pScan = head;
    if (pScan == NULL) {    /*空链表，因此把pNew放在列表头部*/
        head = newTimer;
    }
    else {
        while ((pScan->next != NULL)) {/*寻找插入的位置*/
            if (newTimer->time < pScan->next->time)
                break;
            pScan = pScan->next;
        }
        newTimer->next = pScan->next;
        pScan->next = newTimer;
    }
}

/***************************************************************
*DESCRIPTION:
*		删除所有的定时器节点，释放内存
*INPUTS：
*		NONE
*OUTPUTS：
*		NONE
*RETURNS：
*		NONE
*****************************************************************/
void timerDelete(void)
{
    TimerNode *pSave;
    while (head != NULL) {
        pSave = head->next;/*保存下一个节点的地址*/
        free(head);
        head = pSave;
    }
}

/***************************************************************
*DESCRIPTION:
*		每隔1s更新一次定时器各节点的状态，如果定时时间到将会回调执行外部定时
*       函数
*INPUTS：
*		NONE
*OUTPUTS：
*		NONE
*RETURNS：
*		NONE
*****************************************************************/
void timerRefresh(void)
{
    TimerNode *pScan;
    int8 ch = 0;
    while (1) {
        pScan = head;
        Sleep(1000);    //挂起1s
        while (pScan != NULL) {
            if (pScan->state == start) {    /*判断定时器的状态*/
                if (pScan->timeToDead > 0) {
                    (pScan->timeToDead)--;
                }
                else {
                    if (pScan->hitCnt >= pScan->type) { /*已经执行预定的次数*/
                        pScan->state = stop;
                    (pScan->ptr)();          /*执行外部模块##########*/
                    }
                    else if (pScan->type > 1) { 
                        pScan->hitCnt ++;
                        pScan->timeToDead = pScan->time;
                    }
                }
            }
            pScan = pScan->next;
        }
    }
}

/***************************************************************
*DESCRIPTION:
*		打印出当前所有定时器的信息
*INPUTS：
*		NONE
*OUTPUTS：
*		NONE
*RETURNS：
*		NONE
*****************************************************************/
void timerShow(void)
{
    TimerNode *pScan = head;
    while (pScan != NULL) {
        printf("定时器：%p \n定时：%d 剩余时间：%d 类型：%d 状态：%d 命中次数:%d\n",
            pScan->ptr, pScan->time, pScan->timeToDead, pScan->type, pScan->state, pScan->hitCnt);
        pScan = pScan->next;
    }
}
