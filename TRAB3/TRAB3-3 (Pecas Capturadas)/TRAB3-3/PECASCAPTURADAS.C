/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo pe�as capturadas
*
*  Arquivo gerado:              PECASCAPTURADAS.C
*  Letras identificadoras:      BAR
*
*  Projeto: Disciplina INF 1301
*
*  Autores: fmc - Fernanda de Miranda Carvalho
*			mpjv - Marcelo Paulon Juc� Vasconcelos
*			rfss - Renan da Fonte Simas dos Santos
*
*  $HA Hist�rico de evolu��o:
*     Vers�o       Autor          Data         Observa��es
*       1.00   fmc/mpjv/rfss   20/09/2015 In�cio do desenvolvimento
*
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>

#define PECASCAPTURADAS_OWN
#include "PECASCAPTURADAS.H"
#undef PECASCAPTURADAS_OWN

#include "PECA.H"

#include "LISTA.H"

/***********************************************************************
*
*  $TC Tipo de dados: BAR Descritor da pe�a capturadas
*
*
***********************************************************************/

typedef struct BAR_tagPecasCapturadas {

	LIS_tppLista listaPecas;
	/* Lista de pe�as capturadas */

} BAR_tpPecasCapturadas;

/*****  Dados encapsulados no m�dulo  *****/

/***** Prot�tipos das fun��es encapsuladas no m�dulo *****/

void RemoverPeca(void *pPeca);

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: BAR Criar lista de pe�as capturadas
* 
****/
BAR_tpCondRet BAR_CriarListaPecasCapturadas(BAR_tpPecasCapturadas **pPecasCapturadas)
{

	*pPecasCapturadas = (BAR_tpPecasCapturadas *) malloc(sizeof(BAR_tpPecasCapturadas));
	if(*pPecasCapturadas == NULL)
	{
		return BAR_CondRetFaltouMemoria ;
	} /* if */

	(*pPecasCapturadas)->listaPecas = LIS_CriarLista(RemoverPeca);

	return BAR_CondRetOK ;

} /* Fim fun��o: BAR Criar lista de pe�as capturadas */

/***************************************************************************
*
*  Fun��o: BAR Inserir pe�a
*  
****/
BAR_tpCondRet BAR_InserirPeca(BAR_tpPecasCapturadas *pPecasCapturadas, PCA_tpPeca *pPeca)
{
	if(pPecasCapturadas == NULL) 
	{
		return BAR_CondRetListaPecasCapturadasNaoExiste;
	} /* if */
	
	LIS_InserirElementoAntes(pPecasCapturadas->listaPecas, pPeca);
	
	return BAR_CondRetOK;

} /* Fim fun��o: BAR Inserir pe�a */

/***************************************************************************
*
*  Fun��o: BAR Remover pe�a
*  
****/
BAR_tpCondRet BAR_RemoverPeca(BAR_tpPecasCapturadas *pPecasCapturadas, PCA_tpCorPeca CorPeca, PCA_tpPeca **pPeca)
{
	PCA_tpCorPeca CorPecaTemp;
	PCA_tpPeca * pPecaTemp;

	if(pPecasCapturadas == NULL)
	{
		return BAR_CondRetListaPecasCapturadasNaoExiste;
	} /*if*/

	IrInicioLista(pPecasCapturadas->listaPecas);

	do
	{
		pPecaTemp = (PCA_tpPeca *) LIS_ObterValor(pPecasCapturadas->listaPecas);

		PCA_ObterCorPeca(pPecaTemp, &CorPecaTemp);

		if(CorPecaTemp == CorPeca)
		{
			*pPeca = pPecaTemp;
			LIS_ExcluirElemento(pPecasCapturadas->listaPecas);

			return BAR_CondRetOK;
		} /* if */
	} while(LIS_AvancarElementoCorrente(pPecasCapturadas->listaPecas, 1) == LIS_CondRetOK); /* do */

	return BAR_CondRetPecaNaoExiste;

} /* Fim fun��o: BAR Remover pe�a */

/***************************************************************************
*
*  Fun��o: BAR Conta pe�as
*  
****/
BAR_tpCondRet BAR_ContarPecas(BAR_tpPecasCapturadas *pPecasCapturadas, PCA_tpCorPeca CorPeca, int *pContagem)
{
	PCA_tpCorPeca CorPecaTemp;
	PCA_tpPeca *pPecaTemp;

	if(pPecasCapturadas == NULL) 
	{
		return BAR_CondRetListaPecasCapturadasNaoExiste;
	} /* if */

	*pContagem = 0;

	IrInicioLista(pPecasCapturadas->listaPecas);

	if(LIS_ObterValor(pPecasCapturadas->listaPecas) != NULL)
	{
		do
		{
			pPecaTemp = (PCA_tpPeca *) LIS_ObterValor(pPecasCapturadas->listaPecas);

			PCA_ObterCorPeca(pPecaTemp, &CorPecaTemp);

			if(CorPecaTemp == CorPeca)
			{
				(*pContagem)++;
			} /* if */
		} while(LIS_AvancarElementoCorrente(pPecasCapturadas->listaPecas, 1) == LIS_CondRetOK); /* do */
	} /* if */

	return BAR_CondRetOK ;

} /* Fim fun��o: BAR Conta pe�as */

/***************************************************************************
*
*  Fun��o: BAR Destruir lista de pe�as capturadas
*  
****/
BAR_tpCondRet BAR_DestruirListaPecasCapturadas(BAR_tpPecasCapturadas **pPecasCapturadas)
{
	PCA_tpPeca *pPecaTemp;

	if(*pPecasCapturadas == NULL) 
	{
		return BAR_CondRetListaPecasCapturadasNaoExiste;
	} /* if */

	IrInicioLista((*pPecasCapturadas)->listaPecas);

	pPecaTemp = (PCA_tpPeca *) LIS_ObterValor((*pPecasCapturadas)->listaPecas);
	
	while(pPecaTemp != NULL)
	{
		PCA_DestruirPeca(&pPecaTemp);
		
		if(LIS_AvancarElementoCorrente((*pPecasCapturadas)->listaPecas, 1) != PCA_CondRetOK)
		{
			break;
		} /* if */

		pPecaTemp = (PCA_tpPeca *) LIS_ObterValor((*pPecasCapturadas)->listaPecas);
	} /* while */

	free(*pPecasCapturadas);
	*pPecasCapturadas = NULL;

	return BAR_CondRetOK ;

} /* Fim fun��o: BAR Destruir lista de pe�as capturadas */

/*****  C�digo das fun��es encapsuladas no m�dulo  *****/

/***********************************************************************
*
*  $FC Fun��o: Remove pe�a
*
*  $ED Descri��o da fun��o
*     Fun��o chamada ao remover uma pe�a da lista.
*
***********************************************************************/
void RemoverPeca(PCA_tpPeca *pPeca)
{
	return;
}

/********** Fim do m�dulo de implementa��o: M�dulo pe�as capturadas **********/