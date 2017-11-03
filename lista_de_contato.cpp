#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/conio.c"
/* Nome do programa: Agenda de Contatos.
   Autor: Gustavo H. N. Santos.
   Data: 21/05/2017.
   Função Global: Armazenar uma lista de contatos em um arquivo, podendo acrescentar numeros quando quiser.
   Linguagem de Implementação: C. */

/* Estrutura */   
typedef struct 
{
	int telefone, dia, mes, ano;
	char nome[180];
}Contato;

/* Funções */
void inserirContato(int n, int nt, Contato *contato, FILE *arq, FILE *arq1);// Passando o FILE arq e arq1 para poder abrir o arquivo dentro da função e escrever os contatos.
																			// Se não houver arquivo criado, dentro da função ele vai criar.
void pesquisar(int nt, char nome[], Contato *contato);
void imprimir (int nt, Contato *contato);
void listaporLetra (char letra, int nt, Contato *contato);
void anvMes (int nt, int mes, Contato *contato);

/* Inicio do MAIN */
int main()
{
	Contato *contato; // struct Contato com a variavel contato em ponteiro.
	int opcao=NULL, n=0, nt=0, mes=0;
	char nome[180], letra;
	//Iniciando os arquivos.
	FILE *arq = fopen("contatos.txt","rb+");
	FILE *arq1 = fopen("nt.txt","rb+");
	//Se não houver arquivo mostra na tela o erro abaixo.
	textcolor(LIGHTGREEN);
	if(arq == NULL && arq1 == NULL) {
		printf( "Nao tem arquivo para ser aberto.\n\n");
	}
	rewind(arq);//Posiciona o cursor de volta ao início do arquivo.
	rewind(arq1);//Posiciona o cursor de volta ao início do arquivo.
	fread(&nt,sizeof(int), 1,arq1); // Lendo os valores do arquivo "nt.txt"

	contato=(Contato *)malloc(nt*sizeof(Contato));// Alocando os contatos já armazenados.
	
	fread(contato,sizeof(Contato), nt,arq);// Lendos os valores do arquivo "Contatos.txt".
	
	//Fechando arquivo, pois ele está lendo no momento.
	fclose(arq);
	fclose(arq1);
	
	//Se houver algum contato existente ele entra na condição abaixo.
	if(nt>0)
		printf("Existem = %d Contatos\n\n", nt);
	else
		printf("\t\t\t!!Nao existe contato adicionado!!\n\n");
	
	//Iniciando o programa
	printf("Iniciando Programa...\n\n");
	system("PAUSE");
	
	do{
		textcolor(YELLOW);
		system("clear || cls");// Limpar a tela sempre que voltar para o menu.
		printf("\tEscolha uma Opcao:\n"); // Inicio do menu de funções.
	   	printf("\t1 - Inserir contatos.\n");
		printf("\t2 - Pesquisar Contato.\n");
		printf("\t3 - Listas de Contatos.\n");
		printf("\t4 - Lista por letra.\n");
		printf("\t5 - Imprimir os aniversariantes do mes.\n");
		printf("\t6 - Remover toda lista de contato.\n");
		printf("\t0 - Sair.\n\n");
		scanf("%d", &opcao);// Gravando o valor da opção escolhida.
		
		switch(opcao){
			case 1:
				// NT = Numeros de Conatos TOTAIS, se for mais que 0 ele faz Realocação de memoria.
				// Se não ele faz a alocação de memoria com MALLOC.
				// Memory Allocation.
				textcolor(LIGHTBLUE);
				printf("Quantos contatos serao inseridos: ");
				scanf("%d", &n); 
				if (nt>0)
		   	   	   	contato=(Contato *)realloc(contato, (n+nt) * sizeof(Contato));// Se houver contato ele soma com o proximo valor,
							 	 	 	 	 	 	 	 	 	 	 	 	 	  // NT + N, N é o valor que acabou de ser adicionado.
							 	 	 	 	 	 	 	 	 	 	 	 	 	  // NT o valor anterior alocado.
				else if(nt==0)
		   	   	   	contato=(Contato *)malloc(n*sizeof(Contato));// Se nt for igual a zero ele faz a alocação para adicionar novos contatos.	
				printf("\n");
				inserirContato(n, nt, contato, arq, arq1); // Função inserir contatos
				nt = nt + n; // Após sair da função ele guarda o valor anterior de n e soma com o anterior dele mesmo.
				system("PAUSE");
				getchar();
				break; 
			case 2:
				textcolor(LIGHTMAGENTA);
				fflush(stdin);
				printf("Digite o Nome desejado: ");
				fgets(nome,180, stdin); // Comparação de nomes
				printf("\n");
				pesquisar(nt, nome, contato); // Função pesquisar contato atraves do nome.
				system("PAUSE");
				getchar();
				break;
			case 3:
				textcolor(RED);
				imprimir(nt, contato);// Imprimir todos os contatos.
	   	   		system("PAUSE");
	   	   		getchar();
   	   			break;
   	   		case 4:
   	   			textcolor(CYAN);
   	   			fflush(stdin);
   	   			printf("Digite a Letra desejada: ");
				scanf("%s", &letra); // Pesquisar por letra.
				printf("\n");
   	   			listaporLetra(letra, nt, contato); // Função pesquisar pela primeira letra do nome.
				system("PAUSE");
				getchar();
				break;
  	   		case 5:
  	   			textcolor(MAGENTA);
  	   			printf("Digite o numero do Mes: ");
				scanf("%d", &mes); // Pesquisar o aniversariante do mês.
				printf("\n");
   	   			anvMes(nt, mes, contato);// Função Aniversariante do mês.
				system("PAUSE");
				getchar();
				break;
			case 6:
				textcolor(LIGHTRED);
				printf(" \t!!Removendo!!\n\n ");
				remove("Contatos.txt"); // remove o arquivo.
				remove("nt.txt");// remove o arquivo.
				free(contato); //apaga da memoria todos os contatos.
				nt = nt - nt; //Limpa os numeros totais.	
				n = n - n;
				printf(" \t\t!!Removido!!\n\n ");
				printf(" \t\t!!NT = %d!!\n\n ", nt);
				system("PAUSE");
				getchar();
				break;
			case 0:
                printf("Saindo do sistema.");// value 0, programa finalizado.
                free(contato);
                break;	
			default:	
				textcolor(RED);
				printf("Codigo invalido!\n");
				break;	
		}			
    }while(opcao);
	return 0;
}

/* Codigo das Funções */

void inserirContato(int n,int nt, Contato *contato, FILE *arq, FILE *arq1)
{
	int i, rt=0;
	// Criando e abrindo o arquivo caso não tenha.
	arq = fopen("contatos.txt","wb+");
	arq1 = fopen("nt.txt","wb+");
	
	for(i=nt; i<(nt+n); i++) // Escrevendo na estrutura Contato
	{
		
		fflush(stdin);
		textcolor(GREEN);
		printf("Digite o nome: ");
		textcolor(YELLOW);
		fgets(contato[i].nome,180, stdin);
		printf("\n");
		
		textcolor(GREEN);
		printf("Digite o numero de telefone: ");
		textcolor(YELLOW);
		scanf("%d", &contato[i].telefone);
		printf("\n");
		
		textcolor(GREEN);
		printf("Digite o data de nascimento: \n");
		printf("Dia: ");
		textcolor(YELLOW);
		scanf("%d", &contato[i].dia);
		printf("\n");
		
		textcolor(GREEN);
		printf("Mes: ");
		textcolor(YELLOW);
		scanf("%d", &contato[i].mes);
		printf("\n");
		
		textcolor(GREEN);
		printf("E Ano: ");
		textcolor(YELLOW);
		scanf("%d", &contato[i].ano);
		printf("\n");
	}
	
	rt= nt + n;// Usando uma variavel local para guardar a soma do nt.
	
	rewind(arq);// Posiciona o cursor de volta ao início do arquivo.
	fwrite(contato,sizeof(Contato), rt,arq); // Escrevendo no arquivo aberto no nome "Contato.txt"
	fclose(arq);// Fechando arquivo.
	
	rewind(arq1);// Posiciona o cursor de volta ao início do arquivo.
	fwrite(&rt,sizeof(int), 1, arq1);
	fclose(arq1);// Fechando arquivo.
}

void pesquisar(int nt, char nome[], Contato *contato) // Aqui vai pesquisar por nome na agenda de contatos
{
	int i, cont=0;
	strupr(nome);// Quando o nome entra na função coloco o nome todo como Maiusculo,
				// Para facilitar na hora de fazer a comparação de strings.
				
	for (i=0; i<nt; i++)
	{
		strupr(contato[i].nome);// Colocando todos os nomes do contato em Maiusculo para fazer a comparação.
		if (strcmp (contato[i].nome, nome) == 0) // strcmp comparando duas strings, se for igual a 0
												// 	 quer dizer que são iguais.
		{
			printf("\tNome: %s\n", contato[i].nome);// imprime o nome
			printf("\tTelefone: %d\n", contato[i].telefone);// telefone
			printf("\tData de Nascimento: %d/%d/%d\n\n", contato[i].dia, contato[i].mes, contato[i].ano);// e data
			cont++;
		}
	}	
	if(cont==0)
	{
		printf("Contato nao encontrado\n\n");
		cont=0;
	}
}

void imprimir (int nt, Contato *contato) // aqui imprime todos os contatos
{
	int i;
	
	for (i=0; i<nt; i++)
	{
		printf("\tNome: %s\n", contato[i].nome);
		printf("\tTelefone: %d\n", contato[i].telefone);
		printf("\tData de Nascimento: %d/%d/%d\n", contato[i].dia, contato[i].mes, contato[i].ano);
		printf("\n");
	}
}

void listaporLetra (char letra, int nt, Contato *contato)// Aqui imprime todos os nomes com a inicial com a Letra desejada
{
	int i, cont=0;
	char aux;
	
	for (i=0; i<nt; i++)
	{
		// Verifica as letras de 'a' A 'z' e se for minusculo ele passa o contato para nome minusculo.
		if ((letra >= 'a') && (letra <= 'z'))
		{
			strlwr(contato[i].nome);// Passando o contato para Minusculo.
			aux = contato[i].nome[0]; // Salvando a primeira letra em uma variavel local auxiliar.
			if (aux==letra)
			{
				printf("Nome: %s\n", contato[i].nome);
				printf("Telefone: %d\n", contato[i].telefone);
				printf("Data de Nascimento: %d/%d/%d\n\n", contato[i].dia, contato[i].mes, contato[i].ano);	
				cont++;
			}
				
		}	
		// Verifica as letras de 'A' a 'Z' e se for maiusculo ele passa o contato para nome maiusculo.
		else if ((letra >= 'A') && (letra <= 'Z'))
		{
			strupr(contato[i].nome);// Passando o contato para Maiusculo.
			aux = contato[i].nome[0];// Salvando a primeira letra em uma variavel local auxiliar.
			if (aux==letra)
			{
				printf("Nome: %s\n", contato[i].nome);
				printf("Telefone: %d\n", contato[i].telefone);
				printf("Data de Nascimento: %d/%d/%d\n\n", contato[i].dia, contato[i].mes, contato[i].ano);	
				cont++;
			}	
		}
	}
	if(cont==0)
	{
		printf("Contato nao encontrado\n\n");
		cont=0;
	}
}

void anvMes (int nt, int mes, Contato *contato)// Imprime todos os aniversariantes do mes.
{
	int i, cont=0;
	for (i=0; i<nt; i++)
	{
		if (contato[i].mes==mes)
		{

			printf("\tAniversariante do mes eh\n");
			printf("\t\tNome: %s\n", contato[i].nome);
			printf("\t\tData de Nascimento: %d/%d/%d\n\n", contato[i].dia, contato[i].mes, contato[i].ano);
			cont++;
		}
	}
	if(cont==0)
	{
		printf("Contato nao encontrado\n\n");
		cont=0;
	}
}

