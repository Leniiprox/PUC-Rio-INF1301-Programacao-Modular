#if ! defined(PECASCAPTURADAS_)
#define PECASCAPTURADAS_

#include "PECA.H"

/***************************************************************************
*
*  $MCD M�dulo de defini��o: M�dulo pe�as capturadas
*
*  Arquivo gerado:              PECASCAPTURADAS.H
*  Letras identificadoras:      BAR
*
*  Projeto: Disciplina INF 1301
*
*  Autores: fmc - Fernanda de Miranda Carvalho
*			mpjv - Marcelo Paulon Juc� Vasconcelos
*			rfss - Renan da Fonte Simas dos Santos
*
*  $HA Hist�rico de evolu��o:
*     Vers�o       Autor          Data          Observa��es
*       1.00   fmc/mpjv/rfss   20/09/2015 In�cio do desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Este m�dulo implementa fun��es para operar uma lista de pe�as capturadas
*     O m�dulo � capaz de trabalhar com n pe�as.
*     Ao iniciar a execu��o do programa n�o existe lista de pe�as.
*
***************************************************************************/
 
#if defined(PECASCAPTURADAS_OWN)
   #define PECASCAPTURADAS_EXT
#else
   #define PECASCAPTURADAS_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma lista de pe�as capturadas */

typedef struct BAR_tagPecasCapturadas BAR_tpPecasCapturadas;

/***********************************************************************
*
*  $TC Tipo de dados: BAR Condi��es de retorno
*
*
***********************************************************************/

   typedef enum {

         BAR_CondRetOK,
               /* Executou correto */

		 BAR_CondRetListaPecasCapturadasNaoExiste,
			   /* Lista de pe�as capturadas n�o existe */

		 BAR_CondRetPecaNaoExiste,
			   /* Pe�a n�o existe na lista de pe�as capturadas */

         BAR_CondRetFaltouMemoria
               /* Faltou mem�ria ao alocar dados */

   } BAR_tpCondRet;


/***********************************************************************
*
*  $FC Fun��o: BAR Criar lista de pe�as capturadas
*
*  $ED Descri��o da fun��o
*     Cria uma nova lista de pe�as capturadas.
*
*  $EP Par�metros
*     $P pPecasCapturadas - ponteiro para a lista de pe�as capturadas a ser criada. Passado por refer�ncia.
*
*  $FV Valor retornado
*     BAR_CondRetOK
*     BAR_CondRetFaltouMemoria
*
***********************************************************************/

   BAR_tpCondRet BAR_CriarListaPecasCapturadas(BAR_tpPecasCapturadas **pPecasCapturadas);

/***********************************************************************
*
*  $FC Fun��o: BAR Inserir pe�a
*
*  $ED Descri��o da fun��o
*     Insere uma pe�a na lista de pe�as capturadas.
*
*  $EP Par�metros
*     $P pPecasCapturadas - ponteiro para a lista de pe�as capturadas a ser utilizada.
*     $P pPeca - ponteiro para a pe�a a ser utilizada.
*
*  $FV Valor retornado
*     BAR_CondRetOK
*     BAR_CondRetListaPecasCapturadasNaoExiste
*	  BAR_CondRetFaltouMemoria
*
***********************************************************************/

   BAR_tpCondRet BAR_InserirPeca(BAR_tpPecasCapturadas *pPecasCapturadas, PCA_tpPeca *pPeca);

/***********************************************************************
*
*  $FC Fun��o: BAR Remover pe�a
*
*  $ED Descri��o da fun��o
*     Removee uma pe�a na lista de pe�as capturadas.
*
*  $EP Par�metros
*     $P pPecasCapturadas - ponteiro para a lista de pe�as capturadas a ser utilizada.
*     $P pPeca - ponteiro para a pe�a a ser utilizada.
*
*  $FV Valor retornado
*     BAR_CondRetOK
*     BAR_CondRetListaPecasCapturadasNaoExiste
*     BAR_CondRetPecaNaoExiste
*	  BAR_CondRetFaltouMemoria
*
***********************************************************************/

   BAR_tpCondRet BAR_RemoverPeca(BAR_tpPecasCapturadas *pPecasCapturadas, PCA_tpCorPeca CorPeca, PCA_tpPeca **pPeca);

/***********************************************************************
*
*  $FC Fun��o: BAR Contar pe�as
*
*  $ED Descri��o da fun��o
*     Conta as pe�as de uma determinada cor na lista de pe�as capturadas
*
*  $EP Par�metros
*     $P pPecasCapturadas - ponteiro para a lista de pe�as capturadas a ser utilizada.
*     $P CorPeca - cor das pe�as a serem contadas.
*     $P pContagem - ponteiro para o inteiro onde ser� armazenado o n�mero de pe�as.
*
*  $FV Valor retornado
*     BAR_CondRetOK
*	  BAR_CondRetListaPecasCapturadasNaoExiste
*
***********************************************************************/

   BAR_tpCondRet BAR_ContarPecas(BAR_tpPecasCapturadas *pPecasCapturadas, PCA_tpCorPeca CorPeca, int *pContagem);

/***********************************************************************
*
*  $FC Fun��o: BAR Destruir lista de pe�as capturadas
*
*  $ED Descri��o da fun��o
*     Destr�i a lista de pe�as capturadas.
*
*  $EP Par�metros
*     $P pPecasCapturadas - ponteiro para a lista de pe�as capturadas a ser utilizada. Passado por refer�ncia.
*
*  $FV Valor retornado
*     BAR_CondRetOK
*	  BAR_CondRetListaPecasCapturadasNaoExiste
*
***********************************************************************/

   BAR_tpCondRet BAR_DestruirListaPecasCapturadas(BAR_tpPecasCapturadas **pPecasCapturadas);

#undef BAR_EXT

/********** Fim do m�dulo de defini��o: M�dulo pe�as capturadas **********/

#else
#endif