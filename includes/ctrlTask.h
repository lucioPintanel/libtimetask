/**<!--#####################    D O X Y G E N    #########################-->
 * \file:   timer.h
 * \author: lucio
 *
 * \date: 10 de Abril de 2013, 12:17
 */

#ifndef CTRLTASK_H
#define	CTRLTASK_H

#ifdef	__cplusplus
extern "C" {
#endif

	//#######################     I N C L U D E S     #########################//

	//#################     DEFINICOES, TIPOS E ESTRUTURAS     #################//
#define MAX_ELEMENTS 3	/*!< Definicao da quantidade maxima de tarefas a ser controlada */

typedef struct stArrayTask* ptrArrayTask_T;

	//#########################     M A C R O S     ###########################//

	//######################     V A R I A V E I S     ########################//

	//#######################  PROTOTIPOS DAS ROTINAS  ########################//
	/**
	* \brief funcao que retorna a versao da bilbioteca, versao esta passada via Makefile
	* \author Lucio Pintanel
	* \date 29/01/15 14:44
	* 
	* @return VERSAO_LIB - versao da biblioteca recebida via Makefile
	*/
	int getVersionLibTimeTask(void);

	/**
	* \brief funcao que retorna o nome da bilbioteca, nome este passado via Makefile
	* \author Lucio Pintanel
	* \date 29/01/15 14:44
	* 
	* @return LIBNAME - nome da biblioteca recebido via Makefile
	*/
	char* getNameTimeTask(void);

	/**
	* \brief funcao que inicializa a estrutura com a lista de tarefas
	* \author Lucio Mauro da Silva Pintanel
	* \date criado em: 28/03/14 15:55
	* 
	* @return newstArrayTask - ponteiro para a nova estrutura
	* @return NULL - se nao pode inicializar a estrutura
	*/
	int Array_new_r(ptrArrayTask_T* ptrArrayTask);

	/**
	* \brief funcao que retorna a quantidade de elementos atribuidos a lista de tarefas
	* \author Lucio Mauro da Silva Pintanel
	* \date criado em: 28/03/14 15:55
	* 
	* @param ptrArrayTask - ponteiro para a estrutura com a lista de tarefas
	* @return dt->num_elements - quantidade de elemtos da lista de tarefas
	* @return -1 - se o ponteiro para ptrArrayTask nao foi inicializado
	*/
	int Array_getLength(ptrArrayTask_T ptrArrayTask);

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
	int Array_append(ptrArrayTask_T ptrArrayTask, uint8_t* taskID, uint32_t valueTimer, void (*proc)(void));

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
	int execTask(ptrArrayTask_T ptrArrayTask);
	
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
	int startTask(ptrArrayTask_T ptrArrayTask, uint8_t index, uint32_t valueTimer);

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
	int stopTask(ptrArrayTask_T ptrArrayTask, uint8_t index);



#ifdef	__cplusplus
}
#endif

#endif	/* CTRLTASK_H */
