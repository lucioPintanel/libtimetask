/**<!--#####################    D O X Y G E N    #########################-->
 * \file:   timer.c
 * \author: lucio
 *
 * \date: 10 de Abril de 2013, 12:17
 */

//#######################     I N C L U D E S     #########################//
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "ctrlTask.h"
#include "timer.h"

//#################     DEFINICOES, TIPOS E ESTRUTURAS     #################//
#ifndef VRS_LIB
#define VERSAO_LIB	0 
#else
#define VERSAO_LIB  VRS_LIB     /*!< Versao da biblioteca eh alterada >APENAS< no Makefile (variavel VRS_LIB) */
#endif

#ifndef NAMELIB
#define LIBNAME	" " 
#else
#define LIBNAME  NAMELIB        /*!< nome da biblioteca eh alterada >APENAS< no Makefile (variavel NAMELIB) */
#endif

typedef struct {
	struct stTimeoutGeral_t stTimerGeral;	/*!< estrutura de tempo */
	uint32_t countTimer;	/*!< contador de tempo */
	uint32_t valueTimer;	/*!< valor de intervalo em que a tarefa irá ser executada */
	void (*proc)(void);	/*!< funcao que sera executada */
} stTask_t;
    
struct stArrayTask {
	stTask_t task[MAX_ELEMENTS];	/*!< lista de tarefa a ser executada */
	uint8_t num_elements;	/*!< quantidade de elementos na lista */
};

//#########################     M A C R O S     ###########################//

//######################     V A R I A V E I S     ########################//

//#########################     F U N C O E S     #########################//
/**
 * \brief funcao que retorna a versao da bilbioteca, versao esta passada via Makefile
 * \author Lucio Pintanel
 * \date 29/01/15 14:44
 * 
 * @return VERSAO_LIB - versao da biblioteca recebida via Makefile
 */
int getVersionLibTimeTask(void)
{
    return VERSAO_LIB;
}

/**
 * \brief funcao que retorna o nome da bilbioteca, nome este passado via Makefile
 * \author Lucio Pintanel
 * \date 29/01/15 14:44
 * 
 * @return LIBNAME - nome da biblioteca recebido via Makefile
 */
char* getNameTimeTask(void)
{
    return LIBNAME;
}

/**
 * \brief funcao que inicializa a estrutura com a lista de tarefas
 * \author Lucio Mauro da Silva Pintanel
 * \date criado em: 28/03/14 15:55
 * 
 * @return newstArrayTask - ponteiro para a nova estrutura
 * @return NULL - se nao pode inicializar a estrutura
 */
int Array_new_r(ptrArrayTask_T* ptrArrayTask)
{
	//printf("[%s - %d]\n", __FUNCTION__, __LINE__);
	
	if (MAX_ELEMENTS <= 0) {
		printf("[%s - %d] MAX_ELEMENTS tem que ser maior que zero\n", __FUNCTION__, __LINE__);
		*ptrArrayTask = NULL;
		return -1;
	}
	static struct stArrayTask newstArrayTask;
	memset(&newstArrayTask, 0, sizeof(struct stArrayTask));
	
	*ptrArrayTask = &newstArrayTask;
	
	return 0;
}

/**
 * \brief funcao que retorna a quantidade de elementos atribuidos a lista de tarefas
 * \author Lucio Mauro da Silva Pintanel
 * \date criado em: 28/03/14 15:55
 * 
 * @param ptrArrayTask - ponteiro para a estrutura com a lista de tarefas
 * @return dt->num_elements - quantidade de elemtos da lista de tarefas
 * @return -1 - se o ponteiro para ptrArrayTask nao foi inicializado
 */
int Array_getLength(ptrArrayTask_T ptrArrayTask)
{
	if (NULL == ptrArrayTask) {
		printf("[%s - %d] ptrArrayTask nao pode ser NULL\n", __FUNCTION__, __LINE__);
		return -1;
	}
	
	//printf("[%s - %d]\n", __FUNCTION__, __LINE__);
	struct stArrayTask *dt = (struct stArrayTask *)ptrArrayTask;
	
	return dt->num_elements;
}

/**
 * \brief funcao que adiciona elementos a lista de tarefas e inicializa o time
 * \author Lucio Mauro da Silva Pintanel
 * \date criado em: 28/03/14 15:55
 * 
 * @param ptrArrayTask - ponteiro para a estrutura com a lista de tarefas
 * @param valueTimer - intervalo de tempo em que a tarefa sera executada em milisegundos
 * @param proc - ponteiro para função que será executada
 * @return dt->num_elements - quantidade de elemtos da lista de tarefas
 * @return -1 - se o ponteiro para ptrArrayTask nao foi inicializado
 * @return -2 - se o ponteiro para proc estiver vazio
 * @return -3 - se ja atingil a quantidade maxima de elementos
 */
int Array_append(ptrArrayTask_T ptrArrayTask, uint8_t* taskID, uint32_t valueTimer, void (*proc)(void))
{
	//printf("[%s - %d]\n", __FUNCTION__, __LINE__);
	
	if (NULL == ptrArrayTask) {
		printf("[%s - %d] ptrArrayTask nao pode ser NULL\n", __FUNCTION__, __LINE__);
		return -1;
	}
	
	if (NULL == proc) {
		printf("[%s - %d] A funcao de callback nao pode ser NULL\n", __FUNCTION__, __LINE__);
		return -2;
	}
	
	struct stArrayTask *dt = (struct stArrayTask *)ptrArrayTask;
	if (MAX_ELEMENTS < (dt->num_elements + 1)) {
		printf("[%s - %d] Ja atingil a quantidade maxima de elementos\n", __FUNCTION__, __LINE__);
		return -3;
	}
	int index = dt->num_elements;
	
	dt->task[index].countTimer = 0;
	dt->task[index].proc = proc;
	
	dt->task[index].valueTimer = valueTimer;
	timeoutInit(&dt->task[index].stTimerGeral, dt->task[index].valueTimer);
	
	*taskID = index;
	dt->num_elements++;
	
	return dt->num_elements;
}

/**
 * \brief funcao que executa as tarefas conforme o intervalo de tempo parametrizado
 * \author Lucio Mauro da Silva Pintanel
 * \date criado em: 28/03/14 15:55
 * 
 * @param ptrArrayTask - ponteiro para a estrutura com a lista de tarefas
 * @return 0 - se tudo ocorreu com sucesso
 * @return -1 - se o ponteiro para ptrArrayTask nao foi inicializado
 * @return -2 - se o ponteiro para proc estiver vazio
 */
int execTask(ptrArrayTask_T ptrArrayTask)
{
	//printf("[%s - %d]\n", __FUNCTION__, __LINE__);
	
	if (NULL == ptrArrayTask) {
		printf("[%s - %d] ptrArrayTask nao pode ser NULL\n", __FUNCTION__, __LINE__);
		return -1;
	}
	
	struct stArrayTask *dt = (struct stArrayTask *)ptrArrayTask;
	
	if (MAX_ELEMENTS < dt->num_elements) {
		printf("[%s - %d] dt->num_elements maior que MAX_ELEMENTS\n", __FUNCTION__, __LINE__);
		return -2;
	}
	
	int index;
	for (index = 0; index < dt->num_elements; index++) {
		if (getInitTimer(&dt->task[index].stTimerGeral)) {
			if (timeoutCheck(&dt->task[index].stTimerGeral) == TimeoutResultElapsed) {
				timeoutInit(&dt->task[index].stTimerGeral, dt->task[index].valueTimer);
				dt->task[index].countTimer = 0;
				dt->task[index].proc();
			}
		}
	}
	return 0;
}

/**
 * \brief funcao que adiciona elementos a lista de tarefas e inicializa o time
 * \author Lucio Mauro da Silva Pintanel
 * \date criado em: 28/03/14 15:55
 * 
 * @param ptrArrayTask - ponteiro para a estrutura com a lista de tarefas
 * @param valueTimer - intervalo de tempo em que a tarefa sera executada em milisegundos
 * @param proc - ponteiro para função que será executada
 * @return dt->num_elements - quantidade de elemtos da lista de tarefas
 * @return -1 - se o ponteiro para ptrArrayTask nao foi inicializado
 * @return -2 - se o index for maior que a quantidade de elementos ativos na lista
 * @return -3 - se o ponteiro para proc estiver vazio
 */
int startTask(ptrArrayTask_T ptrArrayTask, uint8_t index, uint32_t valueTimer)
{
	//printf("[%s - %d]\n", __FUNCTION__, __LINE__);
	
	if (NULL == ptrArrayTask) {
		printf("[%s - %d] ptrArrayTask nao pode ser NULL\n", __FUNCTION__, __LINE__);
		return -1;
	}
	
	struct stArrayTask *dt = (struct stArrayTask *)ptrArrayTask;
	if (dt->num_elements < index) {
		printf("[%s - %d] index maior que dt->num_elements\n", __FUNCTION__, __LINE__);
		return -2;
	}
	
	if (NULL == dt->task[index].proc) {
		printf("[%s - %d] A funcao de callback nao pode ser NULL\n", __FUNCTION__, __LINE__);
		return -3;
	}

	if (!(getInitTimer(&dt->task[index].stTimerGeral))) {
		printf("[%s - %d] Reiniciando a tarefa da posicao - [%d]\n", __FUNCTION__, __LINE__, index);
		dt->task[index].countTimer = 0;
		dt->task[index].valueTimer = valueTimer;
		timeoutInit(&dt->task[index].stTimerGeral, dt->task[index].valueTimer);
	} else {
		printf("[%s - %d] A tarefa da posicao - [%d], ja esta rodando\n", __FUNCTION__, __LINE__, index);
	}
	
	return index;
}

/**
 * \brief funcao que executa as tarefas conforme o intervalo de tempo parametrizado
 * \author Lucio Mauro da Silva Pintanel
 * \date criado em: 28/03/14 15:55
 * 
 * @param ptrArrayTask - ponteiro para a estrutura com a lista de tarefas
 * @return 0 - se tudo ocorreu com sucesso
 * @return -1 - se o ponteiro para ptrArrayTask nao foi inicializado
 * @return -2 - se o index for maior que a quantidade de elementos ativos na lista
 */
int stopTask(ptrArrayTask_T ptrArrayTask, uint8_t index)
{
	if (NULL == ptrArrayTask) {
		printf("[%s - %d] ptrArrayTask nao pode ser NULL\n", __FUNCTION__, __LINE__);
		return -1;
	}
	
	struct stArrayTask *dt = (struct stArrayTask *)ptrArrayTask;
	
	if (dt->num_elements < index) {
		printf("[%s - %d] index maior que dt->num_elements\n", __FUNCTION__, __LINE__);
		return -2;
	}
	
	setInitTimer(&dt->task[index].stTimerGeral, 0);
	dt->task[index].countTimer = 0;
	
	printf("[%s - %d] Parando a tarefa da posicao - [%d]\n", __FUNCTION__, __LINE__, index);
	
	return 0;
}
