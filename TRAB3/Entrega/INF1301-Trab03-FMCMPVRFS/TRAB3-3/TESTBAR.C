/***************************************************************************
*  $MCI M�dulo de implementa��o: TBAR Teste lista de pe�as capturadas
*
*  Arquivo gerado:              TestBAR.c
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

#include    "PECASCAPTURADAS.h"

static const char RESET_PECAS_CAPTURADAS_CMD				[] = "=resetteste";
static const char CRIAR_LISTA_PECAS_CAPTURADAS_CMD			[] = "=criarlistapecascapturadas";
static const char INSERIR_PECA_CMD							[] = "=inserirpeca";
static const char REMOVER_PECA_CMD							[] = "=removerpeca";
static const char CONTAR_PECAS_CMD							[] = "=contarpecas";
static const char DESTRUIR_LISTA_PECAS_CAPTURADAS_CMD       [] = "=destruirlistapecascapturadas";

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_PECAS_CAPTURADAS 10
#define DIM_VALOR   100

BAR_tpPecasCapturadas  *vtPecasCapturadas[DIM_VT_PECAS_CAPTURADAS];

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

   static int ValidarInxPecasCapturadas(int inxPecasCapturadas , int Modo);

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TBAR &Testar Pe�as Capturadas
*
*  $ED Descri��o da fun��o
*     Podem ser criadas at� 10 listas de pe�as capturadas, identificadas pelos �ndices 0 a 10
*
*     Comandos dispon�veis:
*
*     =resetteste
*           - anula o vetor de Lista de Pe�as Capturadas.
*     =criarlistapecascapturadas				inxPeca		CondRetEsp
*	  =inserirpeca								inxPeca		CorPeca		CondRetEsp
*	  =removerpeca								inxPeca		CorPeca		CondRetEsp
*     =contarpecas								inxPeca		CorPeca		ValorEsp	CondRetEsp
*     =destruirlistapecascapturadas				inxPeca		CondRetEsp
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando(char * ComandoTeste)
   {

      int inxPecasCapturadas  = -1 ,
          numLidos   = -1 ,
		  ContagemTemp,
		  ValorEsp,
          CondRetEsp = -1,
		  CorPecasCapturadasEsp = -1;

	  BAR_tpCondRet CondRetObtido   = BAR_CondRetOK;
      BAR_tpCondRet CondRetEsperado = BAR_CondRetOK;
		/* inicializa para qualquer coisa */

      int i;
	  
	  PCA_tpCorPeca CorPeca;
	  PCA_tpCorPeca CorPecaEsp;

	  PCA_tpPeca *pPecaTemp;

      /* Efetuar reset de teste de lista de pe�as capturadas */

         if(strcmp(ComandoTeste , RESET_PECAS_CAPTURADAS_CMD) == 0)
         {

            for(i = 0; i < DIM_VT_PECAS_CAPTURADAS; i++)
			{
			   CondRetObtido = BAR_DestruirListaPecasCapturadas(&vtPecasCapturadas[i]);
               vtPecasCapturadas[i] = NULL;
            } /* for */

			return TST_CompararInt(CondRetEsperado , CondRetObtido ,
                                    "Retorno errado ao destruir lista de pecas capturadas.");

         } /* fim ativa: Efetuar reset de teste de lista de pe�as capturadas */

      /* Testar Criar Lista de Pe�as Capturadas */

         else if(strcmp(ComandoTeste , CRIAR_LISTA_PECAS_CAPTURADAS_CMD) == 0)
         {

            numLidos = LER_LerParametros("ii" ,
                       &inxPecasCapturadas, &CondRetEsp);

            if((numLidos != 2)
              || (! ValidarInxPecasCapturadas(inxPecasCapturadas , VAZIO)))
            {
               return TST_CondRetParm;
            } /* if */

            CondRetObtido =
                 BAR_CriarListaPecasCapturadas(&vtPecasCapturadas[inxPecasCapturadas]);

            return TST_CompararInt(CondRetEsp , CondRetObtido ,
               "Erro em ponteiro de nova lista de pe�as capturadas.");

         } /* fim ativa: Testar Criar Pe�a */

		 /* Testar Inserir Pe�a */

		 else if (strcmp(ComandoTeste, INSERIR_PECA_CMD) == 0)
         {
			 numLidos = LER_LerParametros("iii" ,
                               &inxPecasCapturadas, &CorPeca, &CondRetEsp);

            if(numLidos != 3)
            {
               return TST_CondRetParm;
            } /* if */
			
			PCA_CriarPeca(&pPecaTemp, CorPeca);
			
			CondRetObtido =
				BAR_InserirPeca(vtPecasCapturadas[inxPecasCapturadas], pPecaTemp);

            if(TST_CompararInt(CondRetEsp , CondRetObtido ,
               "Erro ao inserir peca.") == TST_CondRetErro)
			{
				return TST_CondRetErro;
			} /* if */

			return TST_CondRetOK;
         } /* fim ativa: Testar Inserir Pe�a */

		 /* Testar Remover Pe�a */

		 else if (strcmp(ComandoTeste, REMOVER_PECA_CMD) == 0)
         {
			 numLidos = LER_LerParametros("iii" ,
                               &inxPecasCapturadas, &CorPeca, &CondRetEsp);

            if(numLidos != 3)
            {
               return TST_CondRetParm;
            } /* if */
						
			CondRetObtido =
				BAR_RemoverPeca(vtPecasCapturadas[inxPecasCapturadas], CorPeca, &pPecaTemp);

			if(CondRetObtido == BAR_CondRetOK && CondRetEsp == BAR_CondRetOK)
			{
				PCA_ObterCorPeca(pPecaTemp, &CorPecaEsp);

				if(CorPecaEsp != CorPeca)
				{
					TST_NotificarFalha("Erro ao remover peca - cor invalida.");
					return TST_CondRetErro;
				} /* if */
			} /* if */

			if(TST_CompararInt(CondRetEsp , CondRetObtido ,
               "Erro ao remover peca.") == TST_CondRetErro)
			{
				return TST_CondRetErro;
			} /* if */

			return TST_CondRetOK;
         } /* fim ativa: Testar Remover Pe�a */

      /* Testar Destruir Lista de Pe�as Capturadas */

		 else if (strcmp(ComandoTeste, DESTRUIR_LISTA_PECAS_CAPTURADAS_CMD) == 0)
		 {

			 numLidos = LER_LerParametros("ii",
				 &inxPecasCapturadas, &CondRetEsp);

			 if (numLidos != 2)
			 {
				 return TST_CondRetParm;
			 } /* if */

			 CondRetObtido =
				 BAR_DestruirListaPecasCapturadas(&vtPecasCapturadas[inxPecasCapturadas]);

			 return TST_CompararInt(CondRetEsp, CondRetObtido,
				 "Erro ao destruir lista de pecas capturadas.");

		 } /* fim ativa: Testar Destruir Lista de Pe�as Capturadas */

	 /* Testar Contar Pe�as */

		 else if (strcmp(ComandoTeste, CONTAR_PECAS_CMD) == 0)
		 {

			 numLidos = LER_LerParametros("iiii",
				 &inxPecasCapturadas, &CorPeca, &ValorEsp, &CondRetEsp);

			 if (numLidos != 4)
			 {
				 return TST_CondRetParm;
			 } /* if */

			 CondRetObtido =
				 BAR_ContarPecas(vtPecasCapturadas[inxPecasCapturadas], CorPeca, &ContagemTemp);

			 if (CondRetObtido == BAR_CondRetOK && CondRetEsp == BAR_CondRetOK)
			 {
				 return TST_CompararInt(ValorEsp, ContagemTemp,
					 "Erro ao contar peca - contagem incorreta.");
			 } /* if */

			 return TST_CompararInt(CondRetEsp, CondRetObtido,
				 "Erro ao contar peca.");

		 } /* fim ativa: Testar Contar Pe�as */
		 
      return TST_CondRetNaoConhec;

   } /* fim fun��o: tbar &testar lista de pe�as capturadas */



/*****  C�digo das fun��es encapsuladas no m�dulo  *****/

/***********************************************************************
*
*  $FC Fun��o: TPCA - Validar indice de pe�a
*
***********************************************************************/

   int ValidarInxPecasCapturadas(int inxPecasCapturadas , int Modo)
   {

      if((inxPecasCapturadas <  0)
		  || (inxPecasCapturadas >= DIM_VT_PECAS_CAPTURADAS))
      {
         return FALSE;
      } /* if */
         
      if(Modo == VAZIO)
      {
         if(vtPecasCapturadas[inxPecasCapturadas] != 0)
         {
            return FALSE;
         } /* if */
      } /* if */
	  else
      {
         if(vtPecasCapturadas[inxPecasCapturadas] == 0)
         {
            return FALSE;
         } /* if */
      } /* if */
         
      return TRUE;

   } /* Fim fun��o: TPCA - Validar indice de pe�a */

/********** Fim do m�dulo de implementa��o: TPCA Teste Pe�a **********/