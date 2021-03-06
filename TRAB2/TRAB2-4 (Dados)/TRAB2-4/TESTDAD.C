/***************************************************************************
*  $MCI M�dulo de implementa��o: TDAD Teste dado
*
*  Arquivo gerado:              TestDAD.c
*  Letras identificadoras:      TDAD
*
*  Projeto: Disciplina INF 1301

*  Autores: fmc - Fernanda de Miranda Carvalho
*			mpjv - Marcelo Paulon Juc� Vasconcelos
*			rfss - Renan da Fonte Simas dos Santos
*
*  $HA Hist�rico de evolu��o:
*     Vers�o       Autor          Data         Observa��es
*       1.00   fmc/mpjv/rfss   12/09/2015 In�cio do desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "DADO.h"

static const char RESET_DADOS_CMD        [] = "=resetteste";
static const char CRIAR_DADOS_CMD        [] = "=criardados";
static const char JOGAR_DADOS_CMD		 [] = "=jogardados";
static const char OBTER_VALORES_CMD		 [] = "=obtervalores";
static const char DESTRUIR_DADOS_CMD     [] = "=destruirdados";

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_DADO 10
#define DIM_VALOR   100

DAD_tpDado  *vtDado[DIM_VT_DADO];

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

   static int ValidarInxDado(int inxDado , int Modo);

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TDAD &Testar Dado
*
*  $ED Descri��o da fun��o
*     Podem ser criadas at� 10 dados, identificadas pelos �ndices 0 a 10
*
*     Comandos dispon�veis:
*
*     =resetteste
*           - anula o vetor de Dados.
*     =criardados                 inxDado    CondRetEsp
*     =jogardados                 inxDado    CondRetEsp
*     =obtervalores               inxDado    CondRetEsp
*     =destruirdados              inxDado	 CondRetEsp
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando(char * ComandoTeste)
   {

      int inxDado  = -1 ,
          numLidos   = -1 ,
          CondRetEsp = -1,
		  pValorDado1 = -1,
		  pValorDado2 = -1;

	  DAD_tpCondRet CondRetObtido   = DAD_CondRetOK;
      DAD_tpCondRet CondRetEsperado = DAD_CondRetOK;
		/* inicializa para qualquer coisa */

      int i;

      /* Efetuar reset de teste de dado */

         if(strcmp(ComandoTeste , RESET_DADOS_CMD) == 0)
         {

            for(i = 0; i < DIM_VT_DADO; i++)
			{
			   CondRetObtido = DAD_DestruirDados(&vtDado[i]);
               vtDado[i] = NULL;
            } /* for */

			return TST_CompararInt(CondRetEsperado , CondRetObtido ,
                                    "Retorno errado ao destruir dado.");

         } /* fim ativa: Efetuar reset de teste de dado */

      /* Testar Criar Dado */

         else if(strcmp(ComandoTeste , CRIAR_DADOS_CMD) == 0)
         {

            numLidos = LER_LerParametros("ii" ,
                       &inxDado, &CondRetEsp);

            if((numLidos != 2)
              || (! ValidarInxDado(inxDado , VAZIO)))
            {
               return TST_CondRetParm;
            } /* if */

            CondRetObtido =
                 DAD_CriarDados(&vtDado[inxDado]);

            return TST_CompararInt(CondRetEsp , CondRetObtido ,
               "Erro em ponteiro de novo dado.");

         } /* fim ativa: Testar Criar Dado */

		 /* Testar Jogar Dados */

         else if(strcmp(ComandoTeste , JOGAR_DADOS_CMD) == 0)
         {

            numLidos = LER_LerParametros("ii" ,
                               &inxDado, &CondRetEsp);
			
            if(numLidos != 2)
            {
               return TST_CondRetParm;
            } /* if */

			CondRetObtido =
                 DAD_JogarDados(vtDado[inxDado]);

            return TST_CompararInt(CondRetEsp , CondRetObtido ,
               "Erro ao jogar dados.");

         } /* fim ativa: Testar Jogar Dados */

		 /* Testar Jogar dados */

		 else if(strcmp(ComandoTeste , OBTER_VALORES_CMD) == 0)
         {
			 numLidos = LER_LerParametros("ii" ,
                               &inxDado, &CondRetEsp);

            if(numLidos != 2)
            {
               return TST_CondRetParm;
            } /* if */
			
			CondRetObtido =
                 DAD_ObterValores(vtDado[inxDado], &pValorDado1, &pValorDado2);
			
            if(TST_CompararInt(CondRetEsp , CondRetObtido ,
               "Erro ao obter valores do dado.") == TST_CondRetErro)
			{
				return TST_CondRetErro;
			} /* if */

			if((pValorDado1 < 0 || pValorDado1 > 6 || pValorDado2 < 0 || pValorDado2 > 6) && CondRetEsp == DAD_CondRetOK)
			{
				TST_NotificarFalha("Erro - valores obtidos dos dados estao fora do intervalo correto.");
				return TST_CondRetErro;
			}

			return TST_CondRetOK;
         } /* fim ativa: Testar Jogar dados */

      /* Testar Destruir Dados */

         else if(strcmp(ComandoTeste , DESTRUIR_DADOS_CMD) == 0)
         {

            numLidos = LER_LerParametros("ii" ,
                               &inxDado, &CondRetEsp);
			
            if(numLidos != 2)
            {
               return TST_CondRetParm;
            } /* if */

			CondRetObtido =
                 DAD_DestruirDados(&vtDado[inxDado]);

            return TST_CompararInt(CondRetEsp , CondRetObtido ,
               "Erro ao destruir dados.");

         } /* fim ativa: Testar Destruir Dados */
		 
      return TST_CondRetNaoConhec;

   } /* fim fun��o: tpca &testar dado */
	
/*****  C�digo das fun��es encapsuladas no m�dulo  *****/

/***********************************************************************
*
*  $FC Fun��o: TDAD - Validar indice de dado
*
***********************************************************************/

   int ValidarInxDado(int inxDado , int Modo)
   {

      if((inxDado <  0)
        || (inxDado >= DIM_VT_DADO))
      {
         return FALSE;
      } /* if */
         
      if(Modo == VAZIO)
      {
         if(vtDado[inxDado] != 0)
         {
            return FALSE;
         } /* if */
      } /* if */
	  else
      {
         if(vtDado[inxDado] == 0)
         {
            return FALSE;
         } /* if */
      } /* if */
         
      return TRUE;

   } /* Fim fun��o: TDAD - Validar indice de dado */

/********** Fim do m�dulo de implementa��o: TDAD Teste Dado **********/

