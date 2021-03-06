#if ! defined(PECA_)
#define PECA_

/***************************************************************************
*
*  $MCD M�dulo de defini��o: M�dulo pe�a
*
*  Arquivo gerado:              PECA.H
*  Letras identificadoras:      PCA
*
*  Projeto: Disciplina INF 1301
*
*  Autores: fmc - Fernanda de Miranda Carvalho
*			mpjv - Marcelo Paulon Juc� Vasconcelos
*			rfss - Renan da Fonte Simas dos Santos
*
*  $HA Hist�rico de evolu��o:
*     Vers�o       Autor          Data          Observa��es
*       1.00   fmc/mpjv/rfss   02/09/2015 In�cio do desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Este m�dulo implementa fun��es para operar uma pe�a de um jogo, que
*     seja de cor branca ou preta.
*     O m�dulo � capaz de trabalhar com n pe�as.
*     Ao iniciar a execu��o do programa n�o existe pe�a.
*
***************************************************************************/
 
#if defined(PECA_OWN)
   #define PECA_EXT
#else
   #define PECA_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma pe�a */

typedef struct PCA_tagPeca PCA_tpPeca;

/***********************************************************************
*
*  $TC Tipo de dados: PCA Condicoes de retorno
*
*
***********************************************************************/

   typedef enum {

         PCA_CondRetOK,
               /* Executou correto */

		 PCA_CondRetPecaNaoExiste,
			   /* Pe�a n�o existe */

         PCA_CondRetFaltouMemoria
               /* Faltou mem�ria ao alocar dados */

   } PCA_tpCondRet;


/***********************************************************************
*
*  $TC Tipo de dados: PCA Cores das pe�as
*
*
***********************************************************************/

   typedef enum {

         PCA_PecaBranca = 0 ,
               /* Pe�a Branca */

         PCA_PecaPreta = 1 ,
               /* Pe�a Preta */

   } PCA_tpCorPeca;


/***********************************************************************
*
*  $FC Fun��o: PCA Criar pe�a
*
*  $ED Descri��o da fun��o
*     Cria uma nova pe�a.
*
*  $EP Par�metros
*     $P pPeca - ponteiro para a pe�a a ser criada. Passado por refer�ncia.
*     $P CorPeca - cor da pe�a a ser criada.
*
*  $FV Valor retornado
*     PCA_CondRetOK
*     PCA_CondRetFaltouMemoria
*
***********************************************************************/

   PCA_tpCondRet PCA_CriarPeca(PCA_tpPeca **pPeca, PCA_tpCorPeca CorPeca);

/***********************************************************************
*
*  $FC Fun��o: PCA Obter cor da pe�a
*
*  $ED Descri��o da fun��o
*     Obt�m a cor da pe�a.
*
*  $EP Par�metros
*     $P pPeca - ponteiro para a pe�a a ser utilizada.
*     $P pCorPeca - ponteiro para a cor a ser obtida.
*
*  $FV Valor retornado
*     PCA_CondRetOK
*     PCA_CondRetPecaNaoExiste
*
***********************************************************************/

   PCA_tpCondRet PCA_ObterCorPeca(PCA_tpPeca *pPeca, PCA_tpCorPeca *pCorPeca);

/***********************************************************************
*
*  $FC Fun��o: PCA Destruir pe�a
*
*  $ED Descri��o da fun��o
*     Destr�i a pe�a.
*
*  $EP Par�metros
*     $P pPeca - ponteiro para a pe�a a ser exclu�da.
*
*  $FV Valor retornado
*     PCA_CondRetOK
*	  PCA_CondRetPecaNaoExiste
*
***********************************************************************/

   PCA_tpCondRet PCA_DestruirPeca(PCA_tpPeca ** pPeca);

#undef PCA_EXT

/********** Fim do m�dulo de defini��o: M�dulo pe�a **********/

#else
#endif