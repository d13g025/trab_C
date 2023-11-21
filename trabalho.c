#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<locale.h>

//srtok()
/*Elaborar um controle de estoque contendo no menu (swtic case):
-Lançamento de entradas em estoque (struct com descrição_Produto, quantidade, valor_Unit)
-Fazer a baixa/saída de produtos;
-imprimir relatório com posição de estoque (saldo inicia + entradas - saidal = saldo);
-após selecionado cada opção, tem um comando para voltar para o menu
*****talvez conectar a tabela com excel como banco de dados*****
*/
int codigo_geral = 0; //variavel de escopo geral;

void pular_linha (){ //para pular linha
    printf("\n");
}
void limparTela (){
    system("cls");
}
/*-----------------------------------------------------------------------------*/
struct st_produto{ //campo de cadastro de produtos

    int codigo;
    char descricao[30];
    int entradas;
    int saidas;
    float valor_Unit;
}produto[50];

/*-----------------------------------------------------------------------------*/
int cadastro (){ //1 - Cadastro de Produto

   char opcao;

    do{

    codigo_geral += 1;
    produto[codigo_geral].codigo = codigo_geral;
    fflush(stdin);
    printf("Código: %d", produto[codigo_geral].codigo);
    pular_linha ();
    printf("PRODUTO: ");
    fgets(produto[codigo_geral].descricao, 30, stdin);
    //scanf(" [^\n]", produto[codigo_geral].descricao);
    fflush(stdin);

    printf("QUANTIDADE: ");
    scanf("%d", &produto[codigo_geral].entradas);

    printf("VALOR_UNITARIO: R$");
    scanf("%f", &produto[codigo_geral].valor_Unit);

    printf("TOTAL: R$ %.2f", produto[codigo_geral].entradas* produto[codigo_geral].valor_Unit);
    pular_linha();
    fflush(stdin);

    printf("Deseja CADASTRAR outro produto: [S/N]: ");
    scanf("%c", &opcao);
    pular_linha;
    }while(opcao != 'N' && opcao != 'n');
    pular_linha();
}

/*-----------------------------------------------------------------------------*/

void lista_produtos(){

    printf("Lista de Produtos\n");
    for(int i = 1; i <= codigo_geral; i++){
        printf("\t%d  -  %s", produto[i].codigo, produto[i].descricao);
    }
    pular_linha();
}

/*-----------------------------------------------------------------------------*/

int vendas(){ //2 - Realizar Vendas


    int opcao1, saida;
    char opcao;

    lista_produtos();

    do{
    printf("******FATURAMENTO********\n");
    printf("Código:");
    scanf("%d", &opcao1);

         if((produto[opcao1].entradas - produto[opcao1].saidas) > 0){
        printf("Produto: %s", produto[opcao1].descricao);


        printf("Quantidade:");
        scanf("%d", &saida);

        do{
        if ((produto[opcao1].entradas - produto[opcao1].saidas)< saida){
            printf("SALDO INSUFICIENTE!");
            printf("Quantidade:");
            scanf("%d", &saida);
        }
        }while((produto[opcao1].entradas - produto[opcao1].saidas)< saida);

        produto[opcao1].saidas = saida + produto[opcao1].saidas; //atualizando o valor das saídas

        printf("Valor unitario: %.2f\n", produto[opcao1].valor_Unit);
        printf("TOTAL: R$ %.2f\n", saida * produto[opcao1].valor_Unit);

        pular_linha();
        }else{
            printf("Sem saldo para faturamento desse produto");}

    pular_linha();
    fflush(stdin);

      printf("Deseja FATURAR outro produto: [S/N]: ");
    scanf("%c", &opcao);

    }while(opcao != 'N' && opcao1 != 'n');
    pular_linha();
}

int lancarEntradas (){//3 - Lançar Entradas

    lista_produtos();
    int entrada, opcao1;
    char opcao;

    do{

        printf("**********LANÇAMENTO DE ENTRADAS************\n");
        printf("Código: ");
        scanf("%d", &opcao1);

        printf("PRODUTO: ");
        printf("Produto: %s", produto[opcao1].descricao);

        printf("QUANTIDADE: ");
        scanf("%d", &entrada);

        produto[codigo_geral].entradas = opcao1 + produto[codigo_geral].entradas;

        printf("Deseja LANÇAR outro produto: [S/N]: ");
        scanf("%c", &opcao);
    }while(opcao != 'N' && opcao != 'n');
    pular_linha();
}

int consulta(){ //4 - Consultar Estoque


   int opcao1;

   lista_produtos();

   char opcao;

    do{
        printf("**********CONSULTA ESTOQUE************\n");
        printf("Código: ");
        scanf("%d", &opcao1);

        if((produto[opcao1].entradas - produto[opcao1].saidas) > 0){
        printf("PRODUTO: %s", produto[opcao1].descricao);
        fflush(stdin);
        printf("ESTOQUE\n");
        printf("\tEntradas: %d\n", produto[opcao1].entradas);
        printf("\tSaídas: %d\n", produto[opcao1].saidas);
        printf("\tSaldo Final: %d\n", produto[opcao1].entradas - produto[opcao1].saidas);
        printf("TOTAL: R$ %.2f", (produto[opcao1].entradas - produto[opcao1].saidas)*produto[opcao1].valor_Unit);
        pular_linha();
        fflush(stdin);
        printf("Deseja CONSULTAR outro produto: [S/N]: ");
        scanf("%c", &opcao);
        }else{
            printf("Sem saldo de produto");}
    }while(opcao != 'N');
    pular_linha();
}
/*-----------------------------------------------------------------------------*/

void tela (){ //layot menu inicial


    printf(" _____________________________________________\n");
    printf("|=============================================|\n");
    printf("|===================MENU======================|\n");
    printf("| 1 - Cadastro de Produto.....................|\n");
    printf("| 2 - Realizar Vendas.........................|\n");
    printf("| 3 - Lançar Entradas.........................|\n");
    printf("| 4 - Consultar Estoque.......................|\n");
    printf("| 5 - Sair....................................|\n");
    printf("|_____________________________________________|\n");
    printf("QUAL OPERAÇÃO DESEJA REALIZAR:");
}

/*-----------------------------------------------------------------------------*/
int main(){  //ainda só para teste se a função roda
    setlocale(LC_ALL,"Portuguese");  //biblioteca para corrigir os acentos.
    int escolha;

    do{
        tela();
        scanf("%d", &escolha);
        pular_linha();

    switch (escolha){

    case 1:
        cadastro();
        break;
    case 2:
        vendas();
        break;
    case 3:
        lancarEntradas();
        break;
    case 4:
        consulta();
        break;
    case 5:
        printf("Até breve");
        break;
    default:
        printf("OPÇÃO INVÁLIDA");
        break;}
        }while( escolha != 5);
return 0;}
