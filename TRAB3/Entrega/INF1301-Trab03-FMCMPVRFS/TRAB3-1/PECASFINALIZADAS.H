#if ! defined(PECASFINALIZADAS_)
#define PECASFINALIZADAS_

#include "PECA.H"

/***************************************************************************
*
*  $MCD M�dulo de defini��o: M�dulo pe�as finalizadas
*
*  Arquivo gerado:              PECASFINALIZADAS.H
*  Letras identificadoras:      PCF
*
*  Projeto: Disciplina INF 1301
*
*  Autores: fmc - Fernanda de Miranda Carvalho
*			mpjv - Marcelo Paulon Juc� Vasconcelos
*			rfss - Renan da Fonte Simas dos Santos
*
*  $HA Hist�rico de evolu��o:
*     Vers�o       Autor          Data          Observa��es
*       1.00   fmc/mpjv/rfss   17/09/2015 In�cio do desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Este m�dulo implementa fun��es para operar uma lista de pe�as, finalizadas
*     O m�dulo � capaz de trabalhar com n pe�as.
*     Ao iniciar a execu��o do programa n�o existe lista de pe�as.
*
***************************************************************************/
 
#if defined(PECASFINALIZADAS_OWN)
   #define PECASFINALIZADAS_EXT
#else
   #define PECASFINALIZADAS_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma lista de pe�as finalizadas */

typedef struct PCF_tagPecasFinalizadas PCF_tpPecasFinalizadas;

/***********************************************************************
*
*  $TC Tipo de dados: PCF Condicoes de retorno
*
*
***********************************************************************/

   typedef enum {

         PCF_CondRetOK,
               /* Executou correto */

		 PCF_CondRetListaPecasFinalizadasNaoExiste,
			   /* Lista de pe�as finalizadas n�o existe */

         PCF_CondRetFaltouMemoria
               /* Faltou mem�ria ao alocar dados */

   } PCF_tpCondRet;


/***********************************************************************
*
*  $FC Fun��o: PCF Criar lista de pe�as finalizadas
*
*  $ED Descri��o da fun��o
*     Cria uma nova lista de pe�as finalizadas.
*
*  $EP Par�metros
*     $P pPecasFinalizadas - ponteiro para a lista de pe�as finalizadas a ser criada. Passado por refer�ncia.
*
*  $FV Valor retornado
*     PCF_CondRetOK
*     PCF_CondRetFaltouMemoria
*
***********************************************************************/

   PCF_tpCondRet PCF_CriarListaPecasFinalizadas(PCF_tpPecasFinalizadas **pPecasFinalizadas);

/***********************************************************************
*
*  $FC Fun��o: PCF Inserir pe�a
*
*  $ED Descri��o da fun��o
*     Insere uma pe�a na lista de pe�as finalizadas.
*
*  $EP Par�metros
*     $P pPecasFinalizadas - ponteiro para a lista de pe�as finalizadas a ser utilizada.
*     $P pPeca - ponteiro para a pe�a a ser utilizada.
*
*  $FV Valor retornado
*     PCF_CondRetOK
*     PCF_CondRetListaPecasFinalizadasNaoExiste
*	  PCF_CondRetFaltouMemoria
*
***********************************************************************/

   PCF_tpCondRet PCF_InserirPeca(PCF_tpPecasFinalizadas *pPecasFinalizadas, PCA_tpPeca *pPeca);

/***********************************************************************
*
*  $FC Fun��o: PCF Contar pe�as
*
*  $ED Descri��o da fun��o
*     Conta as pe�as de uma determinada cor na lista de pe�as finalizadas
*
*  $EP Par�metros
*     $P pPecasFinalizadas - ponteiro para a lista de pe�as finalizadas a ser utilizada.
*     $P CorPeca - cor das pe�as a serem contadas.
*     $P pContagem - ponteiro para o inteiro onde ser� armazenado o n�mero de pe�as.
*
*  $FV Valor retornado
*     PCF_CondRetOK
*	  PCF_CondRetListaPecasFinalizadasNaoExiste
*
***********************************************************************/

   PCF_tpCondRet PCF_ContarPecas(PCF_tpPecasFinalizadas *pPecasFinalizadas, PCA_tpCorPeca CorPeca, int *pContagem);

/***********************************************************************
*
*  $FC Fun��o: PCF Destruir lista de pe�as finalizadas
*
*  $ED Descri��o da fun��o
*     Destr�i a lista de pe�as finalizadas.
*
*  $EP Par�metros
*     $P pPecasFinalizadas - ponteiro para a lista de pe�as finalizadas a ser utilizada. Passado por refer�ncia.
*
*  $FV Valor retornado
*     PCF_CondRetOK
*	  PCF_CondRetListaPecasFinalizadasNaoExiste
*
***********************************************************************/

   PCF_tpCondRet PCF_DestruirListaPecasFinalizadas(PCF_tpPecasFinalizadas **pPecasFinalizadas);

#undef PCF_EXT

/********** Fim do m�dulo de defini��o: M�dulo pe�as finalizadas **********/

#else
#endif