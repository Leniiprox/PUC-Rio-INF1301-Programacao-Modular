#if ! defined( LISTA_ )
#define LISTA_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.h
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs,fmc,mpv,rfs
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor            Data           Observa��es
*	  5       fmc,mpv,rfs  27/nov/2015 instrumenta��o / cobertura
*     4       avs          01/fev/2006 criar linguagem script simb�lica
*     3       avs          08/dez/2004 uniformiza��o dos exemplos
*     2       avs          07/jul/2003 unifica��o de todos os m�dulos em um s� projeto
*     1       avs          16/abr/2003 in�cio desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Implementa listas gen�ricas duplamente encadeadas.
*     Podem existir n listas em opera��o simultaneamente.
*     As listas possuem uma cabe�a encapsulando o seu estado.
*
*     Cada lista � homog�nea quanto ao tipo dos dados que armazena.
*     Cada elemento da lista referencia o valor que cont�m.
*
*     Os ponteiros para os dados s�o copiados para elementos da lista.
*        N�o � copiado o valor apontado por estes ponteiros.
*
*     O controle da destrui��o do valor de um elemento a ser exclu�do
*        � realizado por uma fun��o fornecida pelo usu�rio.
*
*     Cada lista referencia uma fun��o que determina como devem ser
*        desalocados os dados nela contidos.
*
*     A fun��o de libera��o dos valores contidos nos elementos deve
*        assegurar a libera��o de todos os espa�os refer�nciados pelo
*        valor contido em um elemento.
*        Esta fun��o � chamada antes de se desalocar um elemento
*        de uma lista.
*        Caso n�o seja necess�rio desalocar o valor referenciado pelo
*        elemento, o ponteiro para a fun��o de libera��o poder� ser NULL .
*        Caso o elemento da lista seja a �nica �ncora do valor referenciado,
*        esta fun��o deve promover a destrui��o (free) desse valor e
*        de todos os dados nele ancorados.
*
***************************************************************************/
 
#if defined( LISTA_OWN )
   #define LISTA_EXT
#else
   #define LISTA_EXT extern
#endif

#ifdef _DEBUG
    #include   "GENERICO.H"
    #include   "CONTA.H"
    #include   "CESPDIN.H"
	#include   "IdTiposEspaco.def"
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma lista */

typedef struct LIS_tagLista * LIS_tppLista ;


/***********************************************************************
*
*  $TC Tipo de dados: LIS Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es da lista
*
***********************************************************************/

   typedef enum {

         LIS_CondRetOK ,
               /* Concluiu corretamente */

         LIS_CondRetListaVazia ,
               /* A lista n�o cont�m elementos */

         LIS_CondRetFimLista ,
               /* Foi atingido o fim de lista */

         LIS_CondRetNaoAchou ,
               /* N�o encontrou o valor procurado */

         LIS_CondRetFaltouMemoria,
               /* Faltou mem�ria ao tentar criar um elemento de lista */

		 LIS_CondRetNaoExiste,
			   /* A lista n�o existe */

		 LIS_CondRetCorrenteIndefinido ,
           /* O elemento corrente n�o foi definido */

		#ifdef _DEBUG
			 LIS_CondRetAcaoDeturpacaoInexistente
			   /* A��o de deturpa��o n�o existe */
		#endif
   } LIS_tpCondRet ;

	/***********************************************************************
	*
	*  $TC Tipo de dados: LIS Modos de deturpa��o
	*
	*
	***********************************************************************/

	#ifdef _DEBUG

	typedef enum {

	   LIS_NaoDeturpa ,
	   /* n�o realiza a��es de deturpa��o */

	   LIS_DeturpaEliminaCorrente ,
	   /* exclui o elemento corrente sem redefinir refer�ncias a ele*/

	   LIS_DeturpaNULLpProx ,
	   /* atribui NULL ao ponteiro para pr�ximo */

	   LIS_DeturpaNULLpAnt ,
	   /* atribui NULL ao ponteiro para anterior */

	   LIS_DeturpaLixopProx ,
	   /* atribui ponteiro para lixo ao ponteiro para pr�ximo */

	   LIS_DeturpaLixopAnt ,
	   /* atribui ponteiro para lixo ao ponteiro para anterior */

	   LIS_DeturpaNULLpValorCorrente ,
	   /* atribui NULL ao ponteiro para o valor do n� corrente */
	   
	   LIS_DeturpaAlteraTipoEstrutura ,
	   /* altera tipo de estrutura da lista */

	   LIS_DeturpaDesencadeiaSemFree ,
	   /* realiza processo de exclus�o mas n�o libera (free) o elemento
	   (vazamento de mem�ria) */
	   	   
	   LIS_DeturpaNULLpCorrente ,
	   /* atribui NULL ao ponteiro corrente */

	   LIS_DeturpaNULLpOrigem ,
	   /* atribui NULL ao ponteiro origem */

	   LIS_DeturpaAumentaNumeroElementos ,
	   /* deturpa o n�mero de elementos, aumentando incorretamente o contador de elementos */

	   LIS_DeturpaNULLpUltimo ,
	   /* atribui NULL ao ponteiro para o �ltimo n� */

	   LIS_DeturpaLixopUltimo ,
	   /* atribui ponteiro para lixo ao ponteiro para o �ltimo n� */

	   LIS_DeturpaLixopCorrente ,
	   /* atribui ponteiro para lixo ao ponteiro para o n� corrente */

	   LIS_DeturpaAlteraTipoNoCorrente ,
	   /* altera tipo de estrutura do n� corrente */

	   LIS_DeturpaAlteraTipoOrigem ,
	   /* altera tipo de estrutura do primeiro n� */

	   LIS_DeturpaAlteraTipoUltimo ,
	   /* altera tipo de estrutura do �ltimo n� */

	   LIS_DeturpaNULLCabeca ,
	   /* atribui NULL ao ponteiro para a cabe�a da lista */

	   LIS_DeturpaNumeroDeElementosNegativo ,
	   /* atribui um valor negativo ao n�mero de elementos da lista */

	   LIS_DeturpaLixopValorCorrente ,
	   /* atribui ponteiro para lixo ao ponteiro para o valor do n� corrente */

	} LIS_tpModosDeturpacao;

	#endif

	/***********************************************************************
	*
	*  $TC Tipo de dados: LIS Condi��es de retorno da verifica��o da lista
	*
	*  $ED Descri��o do tipo
	*     Descreve o que foi avaliado ao executar o VerificarLista
	*
	***********************************************************************/

	#ifdef _DEBUG

	typedef enum {

		LIS_Verificar_ListaInexistente,
		/* A lista passada como par�metro n�o foi criada */

		LIS_Verificar_Cabeca_pPrimeiroNull,
		/* O ponteiro para o primeiro elemento � NULL e outro constituinte
		da cabe�a da lista indica a exist�ncia de algum elemento */

		LIS_Verificar_Cabeca_pUltimoNull,
		/* O ponteiro para o �ltimo elemento � NULL e outro constituinte
		da cabe�a da lista indica exist�ncia de algum elemento */
		
		LIS_Verificar_Cabeca_NumeroDeElementosInvalido,
		/* O n�mero de elementos � assumiu um valor inv�lido ( menor que 0 ) */

		LIS_Verificar_Cabeca_pPrimeiroIncorreto,
		/* O elemento referenciado como primeiro possui um elemento anterior a ele */

		LIS_Verificar_Cabeca_pUltimoIncorreto,
		/* O elemento referenciado como �ltimo possui um elemento ap�s ele */

		LIS_Verificar_Elemento_ErroNoEncadeamento,
		/* A lista n�o est� inteiramente conectada, ou seja, houve altera��o nas refer�ncias
		para o pr�ximo elemento ou para o elemento anterior */

		LIS_Verificar_Elemento_pValorNull,
		/* O ponteiro para o objeto armazenado na lista � NULL */

		LIS_Verificar_Elemento_pValorErro,
		/* O ponteiro para o objeto armazenado na lista aponta para uma regi�o
		inv�lida para o tipo de objeto da lista */

		LIS_Verificar_Cabeca_NumeroDeElementosInconsistente,
		/* O n�mero de elementos difere da quantidade real de elementos */

		LIS_Verificar_Cabeca_pCorrenteInconsistente,
		/* O elemento corrente n�o pertence � lista */

		LIS_Verificar_Elemento_TipoInconsistente,
		/* O tipo do elemento � inv�lido */

		LIS_Verificar_Cabeca_TipoInconsistente,
		/* O tipo da cabe�a � inv�lido */

		LIS_Verificar_Lista_VazamentoDeMemoria,
		/* Houve vazamento de mem�ria */

		LIS_Verificar_ListaValida
		/* N�o foram encontrados problemas estruturais na lista */

	} LIS_tpVerificar ;

	#endif

/***********************************************************************
*
*  $FC Fun��o: LIS  &Criar lista
*
*  $ED Descri��o da fun��o
*     Cria uma lista gen�rica duplamente encadeada.
*     Os poss�veis tipos s�o desconhecidos a priori.
*     A tipagem � implicita.
*     N�o existe identificador de tipo associado � lista.
*
*  $EP Par�metros
*     ExcluirValor  - ponteiro para a fun��o que processa a
*                     exclus�o do valor referenciado pelo elemento
*                     a ser exclu�do.
*                     Ver descri��o do m�dulo.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a lista.
*     Este ponteiro ser� utilizado pelas fun��es que manipulem esta lista.
*
*     Se ocorreu algum erro, por exemplo falta de mem�ria ou dados errados,
*     a fun��o retornar� NULL.
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
***********************************************************************/

   LIS_tppLista LIS_CriarLista(
             void   ( * ExcluirValor ) ( void * pDado ) ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Destruir lista
*
*  $ED Descri��o da fun��o
*     Destr�i a lista fornecida.
*     O par�metro ponteiro para a lista n�o � modificado.
*     Se ocorrer algum erro durante a destrui��o, a lista resultar�
*     estruturalmente incorreta.
*     OBS. n�o existe previs�o para poss�veis falhas de execu��o.
*
*  $FV Valor retornado
*     LIS_CondRetOK    - destruiu sem problemas
*
***********************************************************************/

   void LIS_DestruirLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Esvaziar lista
*
*  $ED Descri��o da fun��o
*     Elimina todos os elementos, sem contudo eliminar a lista
*
*  $EP Par�metros
*     pLista - ponteiro para a lista a ser esvaziada
*
***********************************************************************/

   void LIS_EsvaziarLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Inserir elemento antes
*
*  $ED Descri��o da fun��o
*     Insere novo elemento antes do elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Par�metros
*     pLista - ponteiro para a lista onde deve ser inserido o elemento
*     pValor - ponteiro para o valor do novo elemento
*              Pode ser NULL
*
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetFaltouMemoria
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista pLista ,
                                           void * pValor        ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Inserir elemento ap�s
*
*  $ED Descri��o da fun��o
*     Insere novo elemento ap�s o elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Par�metros
*     Par�metros
*        pLista - ponteiro para a lista onde deve ser inserido o elemento
*        pValor - ponteiro para o valor do novo elemento
*                 Pode ser NULL
*           
*
*  $FV Valor retornado
*     Valor retornado
*        LIS_CondRetOK
*        LIS_CondRetFaltouMemoria
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          void * pValor        )
       ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Excluir elemento
*
*  $ED Descri��o da fun��o
*     Exclui o elemento corrente da lista dada.
*     Se existir o elemento a esquerda do corrente ser� o novo corrente.
*     Se n�o existir e existir o elemento � direita, este se tornar� corrente.
*     Se este tamb�m n�o existir a lista tornou-se vazia.
*
*  $EP Par�metros
*     pLista    - ponteiro para a lista na qual deve excluir.
*
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetListaVazia
*
***********************************************************************/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Obter refer�ncia para o valor contido no elemento
*
*  $ED Descri��o da fun��o
*     Obtem a refer�ncia para o valor contido no elemento corrente da lista
*
*  $EP Par�metros
*     pLista - ponteiro para a lista de onde se quer o valor
*
*  $FV Valor retornado
*     n�o NULL - se o elemento corrente existe
*     NULL     - se a lista estiver vazia
*                Pode retornar NULL se o valor inserido no elemento for NULL.
*
***********************************************************************/

   void * LIS_ObterValor( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Ir para o elemento inicial
*
*  $ED Descri��o da fun��o
*     Torna corrente o primeiro elemento da lista.
*     Faz nada se a lista est� vazia.
*
*  $EP Par�metros
*     pLista - ponteiro para a lista a manipular
*
***********************************************************************/

   void IrInicioLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Ir para o elemento final
*
*  $ED Descri��o da fun��o
*     Torna corrente o elemento final da lista.
*     Faz nada se a lista est� vazia.
*
*  $EP Par�metros
*     pLista - ponteiro para a lista a manipular
*
***********************************************************************/

   void IrFinalLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Avan�ar elemento
*
*  $ED Descri��o da fun��o
*     Avan�a o elemento corrente NumeroDeElementos elementos na lista
*     Se NumeroDeElementos for positivo avan�a em dire��o ao final
*     Se NumeroDeElementos for negativo avan�a em dire��o ao in�cio
*     NumeroDeElementos pode ser maior do que o n�mro de elementos existentes na
*               dire��o desejada
*     Se NumeroDeElementos for zero somente verifica se a lista est� vazia
*
*  $EP Par�metros
*     pLista  - ponteiro para a lista a ser manipulada
*     NumeroDeElementos - o n�mero de elementos a andar
*
*  $FV Valor retornado
*     CondRetOK         - se NumeroDeElementos elementos tiverem sido andados
*     CondRetFimLista   - se encontrou o fim da lista antes de andar NumeroDeElementos
*                         elementos
*     CondRetListaVazia - se a lista est� vazia
*
***********************************************************************/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int NumeroDeElementos ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Procurar elemento contendo valor
*
*  $ED Descri��o da fun��o
*     Procura o elemento que referencia o valor dado.
*     A fun��o compara ponteiro e n�o conte�do apontado.
*
*  $EP Par�metros
*     pLista  - ponteiro para a lista onde procura
*     pValor  - ponteiro para o valor procurado
*               Pode ser NULL
*
*  $FV Valor retornado
*     LIS_CondRetOK  - se encontrou.
*                      O elemento corrente � o primeiro elemento do
*                      elemento corrente inclusive para o fim da lista
*                      e que cont�m o ponteiro procurado
*
*     LIS_CondRetNaoEncontrou - se o ponteiro n�o foi encontrado
*                      O elemento corrente continua o mesmo
*     LIS_CondRetListaVazia   - se a lista estiver vazia
*
***********************************************************************/

   LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista ,
                                    void * pValor        ) ;

/***********************************************************************
*
*  $FC Fun��o: LIS Deturpar Lista
*
*  $ED Descri��o da fun��o
*     Provoca uma determinada falha numa lista.
*     Serve como controle de teste da fun��o LIS_VerificarLista
*
*  $EP Par�metros
*     pLista   - Ponteiro para a cabe�a da lista a ser deturpada
*     acao     - A��o de deturpa��o (ver defini��o de LIS_tpModosDeturpacao)
*
*  $FV Valor retornado
*     LIS_CondRetOk
*     LIS_CondRetListaInexistente
*     LIS_CondRetCorrenteIndefinido - caso n�o se tenha chamado a fun��o
*                                      LIS_AvancarElementoCorrente antes de 
*									   uma a��o que deturpe um elemento da lista
*     LIS_CondRetAcaoDeturpInexistente
*
***********************************************************************/

#ifdef _DEBUG

   LIS_tpCondRet LIS_DeturparLista( LIS_tppLista pLista, LIS_tpModosDeturpacao acao ) ;

#endif

/***********************************************************************
*
*  $FC Fun��o: LIS Verificar Lista
*
*  $ED Descri��o da fun��o
*     Avalia se uma lista est� estruturalmente correta.
*     Retorna o primeiro erro encontrado.
*
*  $EP Par�metros
*     pLista    - Ponteiro para a cabe�a da lista a ser verificada
*
*  $FV Valor retornado
*     Verificar os valores retornados citados anteriormente.
*     Apenas o primeiro erro � retornado.
*     A prioridade de retorno segue a ordem da declara��o, ent�o
*         LIS_Verificar_ListaValida s� � retornado se n�o for 
*         encontrada nenhuma das condi��es de erro anteriores.
*     No caso de erros relativos � elementos, todos os elementos s�o
*         avaliados e, somente ap�s a passagem por todos os elementos,
*         as condi��es seguintes de retorno s�o verificadas.     
*
***********************************************************************/

#ifdef _DEBUG

   LIS_tpVerificar LIS_VerificarLista( LIS_tppLista pLista ) ;

#endif

#undef LISTA_EXT

/********** Fim do m�dulo de defini��o: LIS  Lista duplamente encadeada **********/

#else
#endif
