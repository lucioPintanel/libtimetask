/**<!--#####################    D O X Y G E N    #########################-->
 * \file:   timer.c
 * \author: lucio
 *
 * \date: 10 de Abril de 2013, 12:17
 */

//#######################     I N C L U D E S     #########################//
#include <time.h>
#include <unistd.h>
#include <stdint.h>
#include <errno.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "timer.h"

//#################     DEFINICOES, TIPOS E ESTRUTURAS     #################//

//#########################     M A C R O S     ###########################//

//######################     V A R I A V E I S     ########################//

//#########################     F U N C O E S     #########################//

/**
 * \brief Inicializa a estrutura fb_stTimeoutGeral
 * \author Lucio Mauro da Silva Pintanel
 * \date criado em: 28/03/14 15:55
 * 
 * @param timeoutStruct estrutura que sera inicializada
 * @param timeoutValue valor a ser verificado se foi atingido
 */
void timeoutInit(stTimeoutGeral_t* timeoutStruct, uint32_t timeoutValue)
{
	struct timezone tmpTimezone;
	gettimeofday(&timeoutStruct->StartTime, &tmpTimezone);
	timeoutStruct->TimeoutValue = timeoutValue;
	timeoutStruct->Initialized = 1;
}

/**
 * \brief funcao que calcula o tempo decorrido desde a inicializacao
 * \author Lucio Mauro da Silva Pintanel
 * \date criado em 13/11/13 08:57
 * 
 * @param timeoutStruct - ponteiro para a estrutura de controle de tempo
 * @return tmpDiffMiliSecs - tempo decorrido
 * @return TimeoutResultElapsed - informa que decorreu o tempo
 */
static uint32_t timeoutGeral(stTimeoutGeral_t* timeoutStruct)
{
	struct timeval tmpTimeval;
	struct timezone tmpTimezone;

	if (timeoutStruct->TimeoutValue == 0) {
		return TimeoutResultElapsed;
	}
	gettimeofday(&tmpTimeval, &tmpTimezone);

	uint32_t tmpDiffMiliSecs = ((tmpTimeval.tv_sec * 1000)
		+ (tmpTimeval.tv_usec / 1000));

	tmpDiffMiliSecs -= ((timeoutStruct->StartTime.tv_sec * 1000)
		+ (timeoutStruct->StartTime.tv_usec / 1000));

	return tmpDiffMiliSecs;
}

/**
 * \brief funcao que verifica se o valor passado valor alvo foi atingido
 * \author Lucio Mauro da Silva Pintanel
 * \date criado em: 28/03/14 15:55
 * 
 * @param timeoutStruct estrutura inicializada com os valores para verificacao
 * @return fb_TimeoutResultElapsed se ja decorreu o tempo
 * @return fb_TimeoutResultNotElapsed se ainda nao decorreu o tempo esperado
 */
enTimeoutResult_t timeoutCheck(stTimeoutGeral_t* timeoutStruct)
{
	return( (timeoutGeral(timeoutStruct) > timeoutStruct->TimeoutValue)
		? TimeoutResultElapsed
		: TimeoutResultNotElapsed);
}

/**
 * \brief funcao que retorna se a estrutura foi inicializada
 * \author Lucio Mauro da Silva Pintanel
 * \date criado em: 28/03/14 15:55
 * 
 * @param timeoutStruct - ponteiro para a estrutura de controle de tempo
 * @return 1 - se a estrutura foi inicializada
 * @return 0 - se a estrutura nao foi inicializada
 */
uint8_t getInitTimer(stTimeoutGeral_t* timeoutStruct)
{
	return timeoutStruct->Initialized ? 1 : 0;
}

/**
 * \brief funcao que retorna se a estrutura foi inicializada
 * \author Lucio Mauro da Silva Pintanel
 * \date criado em: 28/03/14 15:55
 * 
 * @param timeoutStruct - ponteiro para a estrutura de controle de tempo
 * @return 1 - se a estrutura foi inicializada
 * @return 0 - se a estrutura nao foi inicializada
 */
void setInitTimer(stTimeoutGeral_t* timeoutStruct, uint8_t state)
{
	timeoutStruct->Initialized = state;
}
