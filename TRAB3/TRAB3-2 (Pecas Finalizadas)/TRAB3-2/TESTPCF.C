/***************************************************************************
*  $MCI M�dulo de implementa��o: TPCF Teste lista de pe�as finalizadas
*
*  Arquivo gerado:              TestPCF.c
*  Letras identificadoras:      TPCA
*
*  Projeto: Disciplina INF 1301

*  Autores: fmc - Fernanda de Miranda Carvalho
*			mpjv - Marcelo Paulon Juc� Vasconcelos
*			rfss - Renan da Fonte Simas dos Santos
*
*  $HA Hist�rico de evolu��o:
*     Vers�o       Autor          Data         Observa��es
*       1.00   fmc/mpjv/rfss   17/09/2015 In�cio do desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "PECASFINALIZADAS.h"

static const char RESET_PECAS_FINALIZADAS_CMD				[] = "=resetteste";
static const char CRIAR_LISTA_PECAS_FINALIZADAS_CMD			[] = "=criarlistapecasfinalizadas";
static const char INSERIR_PECA_CMD							[] = "=inserirpeca";
static const char CONTAR_PECAS_CMD							[] = "=contarpecas";
static const char DESTRUIR_LISTA_PECAS_FINALIZADAS_CMD      [] = "=destruirlistapecasfinalizadas";

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_PECAS_FINALIZADAS 10
#define DIM_VALOR   100

PCF_tpPecasFinalizadas  *vtPecasFinalizadas[DIM_VT_PECAS_FINALIZADAS];

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

   static int ValidarInxPecasFinalizadas(int inxPecasFinalizadas , int Modo);

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TPCF &Testar Pe�as Finalizadas
*
*  $ED Descri��o da fun��o
*     Podem ser criadas at� 10 listas de pe�as finalizadas, identificadas pelos �ndices 0 a 10
*
*     Comandos dispon�veis:
*
*     =resetteste
*           - anula o vetor de Lista de Pe�as Finalizadas.
*     =criarlistapecasfinalizadas				inxPeca		CondRetEsp
*	  =inserirpeca								inxPeca		CorPeca		CondRetEsp
*     =contarpecas								inxPeca		CorPeca		ValorEsp	CondRetEsp
*     =destruirlistapecasfinalizadas			inxPeca		CondRetEsp
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando(char * ComandoTeste)
   {

      int inxPecasFinalizadas  = -1 ,
          numLidos   = -1 ,
		  ContagemTemp,
		  ValorEsp,
          CondRetEsp = -1,
		  CorPecasFinalizadasEsp = -1;

	  PCF_tpCondRet CondRetObtido   = PCF_CondRetOK;
      PCF_tpCondRet CondRetEsperado = PCF_CondRetOK;
		/* inicializa para qualquer coisa */

      int i;
	  
	  PCA_tpCorPeca CorPeca;

	  PCA_tpPeca *pPecaTemp;

      /* Efetuar reset de teste de lista de pe�as finalizadas */

         if(strcmp(ComandoTeste , RESET_PECAS_FINALIZADAS_CMD) == 0)
         {

            for(i = 0; i < DIM_VT_PECAS_FINALIZADAS; i++)
			{
			   CondRetObtido = PCF_DestruirListaPecasFinalizadas(&vtPecasFinalizadas[i]);
               vtPecasFinalizadas[i] = NULL;
            } /* for */

			return TST_CompararInt(CondRetEsperado , CondRetObtido ,
                                    "Retorno errado ao destruir lista de pecas finalizadas.");

         } /* fim ativa: Efetuar reset de teste de lista de pe�as finalizadas */

      /* Testar Criar Lista de Pe�as Finalizadas */

         else if(strcmp(ComandoTeste , CRIAR_LISTA_PECAS_FINALIZADAS_CMD) == 0)
         {

            numLidos = LER_LerParametros("ii" ,
                       &inxPecasFinalizadas, &CondRetEsp);

            if((numLidos != 2)
              || (! ValidarInxPecasFinalizadas(inxPecasFinalizadas , VAZIO)))
            {
               return TST_CondRetParm;
            } /* if */

            CondRetObtido =
                 PCF_CriarListaPecasFinalizadas(&vtPecasFinalizadas[inxPecasFinalizadas]);

            return TST_CompararInt(CondRetEsp , CondRetObtido ,
               "Erro em ponteiro de nova lista de pe�as finalizadas.");

         } /* fim ativa: Testar Criar Pe�a */

		 /* Testar Inserir Pe�a */

		 else if (strcmp(ComandoTeste, INSERIR_PECA_CMD) == 0)
         {
			 numLidos = LER_LerParametros("iii" ,
                               &inxPecasFinalizadas, &CorPeca, &CondRetEsp);

            if(numLidos != 3)
            {
               return TST_CondRetParm;
            } /* if */
			
			PCA_CriarPeca(&pPecaTemp, CorPeca);
			
			CondRetObtido =
				PCF_InserirPeca(vtPecasFinalizadas[inxPecasFinalizadas], pPecaTemp);

            if(TST_CompararInt(CondRetEsp , CondRetObtido ,
               "Erro ao inserir pe�a.") == TST_CondRetErro)
			{
				return TST_CondRetErro;
			} /* if */

			return TST_CondRetOK;
         } /* fim ativa: Testar Inserir Pe�a */

      /* Testar Destruir Lista de Pe�as Finalizadas */

		 else if (strcmp(ComandoTeste, DESTRUIR_LISTA_PECAS_FINALIZADAS_CMD) == 0)
		 {

			 numLidos = LER_LerParametros("ii",
				 &inxPecasFinalizadas, &CondRetEsp);

			 if (numLidos != 2)
			 {
				 return TST_CondRetParm;
			 } /* if */

			 CondRetObtido =
				 PCF_DestruirListaPecasFinalizadas(&vtPecasFinalizadas[inxPecasFinalizadas]);

			 return TST_CompararInt(CondRetEsp, CondRetObtido,
				 "Erro ao destruir lista de pecas finalizadas.");

		 } /* fim ativa: Testar Destruir Lista de Pe�as Finalizadas */

	 /* Testar Contar Pe�as */

		 else if (strcmp(ComandoTeste, CONTAR_PECAS_CMD) == 0)
		 {

			 numLidos = LER_LerParametros("iiii",
				 &inxPecasFinalizadas, &CorPeca, &ValorEsp, &CondRetEsp);

			 if (numLidos != 4)
			 {
				 return TST_CondRetParm;
			 } /* if */

			 CondRetObtido =
				 PCF_ContarPecas(vtPecasFinalizadas[inxPecasFinalizadas], CorPeca, &ContagemTemp);

			 if (CondRetObtido == PCF_CondRetOK && CondRetEsp == PCF_CondRetOK)
			 {
				 return TST_CompararInt(ValorEsp, ContagemTemp,
					 "Erro ao contar peca - contagem incorreta.");
			 } /* if */

			 return TST_CompararInt(CondRetEsp, CondRetObtido,
				 "Erro ao contar peca.");

		 } /* fim ativa: Testar Contar Pe�as */
		 
      return TST_CondRetNaoConhec;

   } /* fim fun��o: tpcf &testar lista de pe�as finalizadas */



/*****  C�digo das fun��es encapsuladas no m�dulo  *****/

/***********************************************************************
*
*  $FC Fun��o: TPCA - Validar indice de pe�a
*
***********************************************************************/

   int ValidarInxPecasFinalizadas(int inxPecasFinalizadas , int Modo)
   {

      if((inxPecasFinalizadas <  0)
		  || (inxPecasFinalizadas >= DIM_VT_PECAS_FINALIZADAS))
      {
         return FALSE;
      } /* if */
         
      if(Modo == VAZIO)
      {
         if(vtPecasFinalizadas[inxPecasFinalizadas] != 0)
         {
            return FALSE;
         } /* if */
      } /* if */
	  else
      {
         if(vtPecasFinalizadas[inxPecasFinalizadas] == 0)
         {
            return FALSE;
         } /* if */
      } /* if */
         
      return TRUE;

   } /* Fim fun��o: TPCA - Validar indice de pe�a */

/********** Fim do m�dulo de implementa��o: TPCA Teste Pe�a **********/

