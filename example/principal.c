/**<!--#####################    D O X Y G E N    #########################-->
 * \file:   principal.c
 * \author: lucio
 *
 * \date: 10 de Abril de 2013, 12:17
 */

//#######################     I N C L U D E S     #########################//
#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/time.h>

#include "ctrlTask.h"

//#################     DEFINICOES, TIPOS E ESTRUTURAS     #################//

//#########################     M A C R O S     ###########################//

//######################     V A R I A V E I S     ########################//

//#########################     F U N C O E S     #########################//
void callBack_01(void) 
{
	//printf("\n[%s - %d]\n", __FUNCTION__, __LINE__);
	
	struct timeval start;
	struct tm tmpTime;
	gettimeofday(&start, NULL);
	localtime_r(&start.tv_sec, &tmpTime);

	printf("\n[%s - %d] %.02d:%.02d:%.02d:%.03d\n\n",
				__FUNCTION__, __LINE__,
				tmpTime.tm_hour,
				tmpTime.tm_min,
				tmpTime.tm_sec,
				(int) (start.tv_usec / 1000)
				);
}

void callBack_02(void) 
{
	//printf("[%s - %d]\n", __FUNCTION__, __LINE__);
	
	struct timeval start;
	struct tm tmpTime;
	gettimeofday(&start, NULL);
	localtime_r(&start.tv_sec, &tmpTime);

	printf("[%s - %d] %.02d:%.02d:%.02d:%.03d\n",
			__FUNCTION__, __LINE__,
			tmpTime.tm_hour,
			tmpTime.tm_min,
			tmpTime.tm_sec,
			(int) (start.tv_usec / 1000)
			);
}

void callBack_03(void) 
{
	//printf("[%s - %d]\n", __FUNCTION__, __LINE__);
	
	struct timeval start;
	struct tm tmpTime;
	gettimeofday(&start, NULL);
	localtime_r(&start.tv_sec, &tmpTime);

	printf("[%s - %d] %.02d:%.02d:%.02d:%.03d\n",
			__FUNCTION__, __LINE__,
			tmpTime.tm_hour,
			tmpTime.tm_min,
			tmpTime.tm_sec,
			(int) (start.tv_usec / 1000)
			);
}

int main(void)
{
	ptrArrayTask_T ptrArrayTask;
	uint8_t taskID[MAX_ELEMENTS];
	
	printf("***\tNAME: [%s]\tVERSION: [%04d]\t***\n\n", getNameTimeTask(), getVersionLibTimeTask());
	
	Array_new_r(&ptrArrayTask);
	if (NULL == ptrArrayTask) {
		printf("[%s - %d] Erro ao inicializar ptrArrayTask\n", __FUNCTION__, __LINE__);
		return -1;
	}
	
	Array_append(ptrArrayTask, &taskID[0], 500, callBack_01);
	Array_append(ptrArrayTask, &taskID[1], 200, callBack_02);
	Array_append(ptrArrayTask, &taskID[2], 100, callBack_03);
	
	uint32_t count = 200;
	while(--count > 0) {
		execTask(ptrArrayTask);
		usleep(10000);
		if (100 == count) {
			stopTask(ptrArrayTask, taskID[2]);
		}
		if (50 == count) {
			startTask(ptrArrayTask, taskID[2], 150);
		}
	};
	
	return 0;
}
