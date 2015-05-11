#include "timer.h"

TimerNode *head = NULL;

/***************************************************************
*DESCRIPTION:
*		��ʱ���ĳ�ʼ����������ʱ����ʼ��Ĭ��Ϊready״̬����Ҫ
*       timerStart��������������ʱ���ſ�ʼ��ʱ��
*INPUTS��
*		ptr: ��Ҫ��ʱ�ĺ����ĵ�ַ
*		time:��ʱʱ��
*       num: �ú�����Ҫ��ʱ�Ĵ��� 
*               0����ʾ������ִ��
*               1��ִ��һ��
*               >1:ִ��ָ���Ĵ���
*
*       ���磺
*           timerInit(task1, 10, 3);
*           ��ʾtask1����ÿ��10s����һ�Σ�һ������3��
*OUTPUTS��
*		NONE
*RETURNS��
*       FALSE�������ڴ�ʧ�ܣ�����������
*       TRUE:  ����
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
*		�������еĶ�ʱ��������ʼ��ʱ����
*       �������ȳ�ʼ����ʱ������������ʱ��
*INPUTS��
*		NONE
*OUTPUTS��
*		NONE
*RETURNS��
*		0����������
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
*		ֹͣ���еĶ�ʱ����������Ļ�����stop����
*INPUTS��
*		NONE
*OUTPUTS��
*		NONE
*RETURNS��
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
*		˳������½��Ķ�ʱ��
*INPUTS��
*		TimerNode *newTimer:�µĶ�ʱ���ṹ���ַ
*OUTPUTS��
*		NONE
*RETURNS��
*		NONE
*****************************************************************/
void timerInsert(TimerNode *newTimer)
{
    TimerNode *pScan = head;
    if (pScan == NULL) {    /*��������˰�pNew�����б�ͷ��*/
        head = newTimer;
    }
    else {
        while ((pScan->next != NULL)) {/*Ѱ�Ҳ����λ��*/
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
*		ɾ�����еĶ�ʱ���ڵ㣬�ͷ��ڴ�
*INPUTS��
*		NONE
*OUTPUTS��
*		NONE
*RETURNS��
*		NONE
*****************************************************************/
void timerDelete(void)
{
    TimerNode *pSave;
    while (head != NULL) {
        pSave = head->next;/*������һ���ڵ�ĵ�ַ*/
        free(head);
        head = pSave;
    }
}

/***************************************************************
*DESCRIPTION:
*		ÿ��1s����һ�ζ�ʱ�����ڵ��״̬�������ʱʱ�䵽����ص�ִ���ⲿ��ʱ
*       ����
*INPUTS��
*		NONE
*OUTPUTS��
*		NONE
*RETURNS��
*		NONE
*****************************************************************/
void timerRefresh(void)
{
    TimerNode *pScan;
    int8 ch = 0;
    while (1) {
        pScan = head;
        Sleep(1000);    //����1s
        while (pScan != NULL) {
            if (pScan->state == start) {    /*�ж϶�ʱ����״̬*/
                if (pScan->timeToDead > 0) {
                    (pScan->timeToDead)--;
                }
                else {
                    if (pScan->hitCnt >= pScan->type) { /*�Ѿ�ִ��Ԥ���Ĵ���*/
                        pScan->state = stop;
                    (pScan->ptr)();          /*ִ���ⲿģ��##########*/
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
*		��ӡ����ǰ���ж�ʱ������Ϣ
*INPUTS��
*		NONE
*OUTPUTS��
*		NONE
*RETURNS��
*		NONE
*****************************************************************/
void timerShow(void)
{
    TimerNode *pScan = head;
    while (pScan != NULL) {
        printf("��ʱ����%p \n��ʱ��%d ʣ��ʱ�䣺%d ���ͣ�%d ״̬��%d ���д���:%d\n",
            pScan->ptr, pScan->time, pScan->timeToDead, pScan->type, pScan->state, pScan->hitCnt);
        pScan = pScan->next;
    }
}
