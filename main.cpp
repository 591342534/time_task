#include "timer.h"

int task1(void)
{
    printf("helloWorld!\n");
    return 0;
}

int task2(void)
{
    printf("Good\n");
    return 0;
}

int
main(void)
{
    timerInit(task1, 4, 3);
    timerInit(task2, 1, 5);
    timerShow();
    timerStart();
    system("pause");
	return 0;
}