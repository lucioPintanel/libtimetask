/**<!--#####################    D O X Y G E N    #########################-->
 * \file:   timer.h
 * \author: lucio
 *
 * \date: 10 de Abril de 2013, 12:17
 */

#ifndef TIMER_H
#define	TIMER_H

#ifdef	__cplusplus
extern "C" {
#endif

	//#######################     I N C L U D E S     #########################//
#include <sys/time.h>

	//#################     DEFINICOES, TIPOS E ESTRUTURAS     #################//
typedef enum {
	TimeoutResultInvalid, /*!< informa valor invalido */
	TimeoutResultElapsed, /*!< informa que decorreu o tempo */
	TimeoutResultNotElapsed, /*!< informa NAO que decorreu o tempo */
} enTimeoutResult_t;

struct stTimeoutGeral_t{
	struct timeval StartTime;	/*!< estrutura de tempo */
	unsigned long int TimeoutValue;	/*!< valor de tempo a ser verificado */
	unsigned long int Initialized;	/*!< flag de controle se tempo foi inicializado ou nao */
};

	//#########################     M A C R O S     ###########################//

	//######################     V A R I A V E I S     ########################//

	//#######################  PROTOTIPOS DAS ROTINAS  ########################//
	/**
	* \brief Inicializa a estrutura fb_stTimeoutGeral
	* \author Lucio Mauro da Silva Pintanel
	* \date criado em: 28/03/14 15:55
	* 
	* @param timeoutStruct estrutura que sera inicializada
	* @param timeoutValue valor a ser verificado se foi atingido
	*/
	void timeoutInit(struct stTimeoutGeral_t* timeoutStruct, uint32_t timeoutValue);

	/**
	* \brief funcao que verifica se o valor passado valor alvo foi atingido
	* \author Lucio Mauro da Silva Pintanel
	* \date criado em: 28/03/14 15:55
	* 
	* @param timeoutStruct estrutura inicializada com os valores para verificacao
	* @return fb_TimeoutResultElapsed se ja decorreu o tempo
	* @return fb_TimeoutResultNotElapsed se ainda nao decorreu o tempo esperado
	*/
	enTimeoutResult_t timeoutCheck(struct stTimeoutGeral_t* timeoutStruct);
	
	/**
	* \brief funcao que retorna se a estrutura foi inicializada
	* \author Lucio Mauro da Silva Pintanel
	* \date criado em: 28/03/14 15:55
	* 
	* @param timeoutStruct - ponteiro para a estrutura de controle de tempo
	* @return 1 - se a estrutura foi inicializada
	* @return 0 - se a estrutura nao foi inicializada
	*/
	uint8_t getInitTimer(struct stTimeoutGeral_t* timeoutStruct);

	/**
	* \brief funcao que retorna se a estrutura foi inicializada
	* \author Lucio Mauro da Silva Pintanel
	* \date criado em: 28/03/14 15:55
	* 
	* @param timeoutStruct - ponteiro para a estrutura de controle de tempo
	* @return 1 - se a estrutura foi inicializada
	* @return 0 - se a estrutura nao foi inicializada
	*/
	void setInitTimer(struct stTimeoutGeral_t* timeoutStruct, uint8_t state);


#ifdef	__cplusplus
}
#endif

#endif	/* TIMER_H */
