// CENTRO UNIVERSIT�RIO DOS GUARARAPES - UNIFG
// T�cnicas de Programa��o
// Lista de Revis�o A2-N2
// Autores:
// Grupo 01:
//	Alequissandra Rayane Farias Santos Silva - 202000574
//	Beatriz Lira Martins - 2020002049
//	Matheus Barros Cris�stomo - 202058447
//	Paloma Corr�a Alves - 202000716
//	Vinicius Rodrigues Cardoso Silva - 202000632 
//	Thulio Mateus de Oliveira Queiroz - 202003804
// 
// APS:
// Programa de envio de mensagens pela intranet de uma empresa atrav�s de login.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Registro que representa os dados de login e senha de usu�rio.
typedef struct{
    char login[10];
    char senha[10];
} usuarios;

// Registro que representa os dados de mensagem.
typedef struct{
	char ip[15];
	char assunto[50];
	char msg[100];
} mensagens;

// Declara um global ponteiro para o arquivo.
FILE *pusuarios;

FILE *pmensagens;

// Vari�veis globais auxiliares validar usu�rios.
usuarios usuario_aux;

// Vari�veis globais auxiliares adicionar mensagens.
mensagens mensagem_aux;

// Procedimento que imprime uma linha no terminal.
void linha() {
	int i;
	for (i = 1; i <= 80; i++) {
		printf("_");
	}
	printf("\n");
}

//---------------------------------------------------------------------------

// PARTE MENU!!!

int menu(){
	int opcao;
	
	printf("\n\n### MENU ###");
	printf("\n\n1. Enviar mensagem");
	printf("\n2. Listar mensagens enviadas");
	printf("\n3. Apagar arquivo de mensagens enviadas");
	printf("\n0. Sair");
	printf("\nEscolha uma opcao: ");
	scanf("%d", &opcao);
	fflush(stdin);
	
	return opcao;
}

//---------------------------------------------------------------------------

// PARTE MENSAGEM!!!

void abre_arquivo_mensagens(){
	// Abre o arquivo em forma de leitura.
	pmensagens = fopen("mensagens.dat", "r+b");
	// Caso o arquivo n�o exista, ele � criado.
	if (pmensagens == NULL) {
		pmensagens = fopen("mensagens.dat", "w+b");
	}
}

// void enviar(struct mensagem vetor_msg[], struct mensagem dado, int posicao)
// Procedimento que cria a mensagem dentro do arquivo
void enviar() {
	int resp;
	
	do {
			
		printf("\n\nEnviar Mensagem\n\n");
		printf("\nIP: ");
		scanf("%s", mensagem_aux.ip);
		fflush(stdin);
		
		printf("\nAssunto: ");
		fgets(mensagem_aux.assunto, 50, stdin);
		fflush(stdin);
		
		printf("\nMensagem: ");
		fgets(mensagem_aux.msg, 100, stdin);
		fflush(stdin);
		
		// coloca o leitor no inicio do arquivo
		fseek(pmensagens, 0, SEEK_END);
		
		// escreve o registro da mensagem_aux no arquivo
		fwrite(&mensagem_aux, sizeof(mensagens), 1, pmensagens);
		printf("\n\nMensagem cadastrada com sucesso!\n\n");
		
		printf("\nDeseja cadastrar outra Mensagem (1-Sim/0-Nao)? ");
		scanf("%d", &resp);
		fflush(stdin);
		
	} while(resp == 1);

}

// void listar(struct mensagem vetor_msg[], int tamanho)
// Fun��o que lista todas mensagens do arquivo
void listar() {
	
	printf("\n\nListagem de Mensagens\n\n\n");
	linha();
	
	rewind(pmensagens);
	fread(&mensagem_aux, sizeof(mensagens), 1, pmensagens);
	
	// percorre todo o arquivo at� chegar no fim
	while(feof(pmensagens) == 0) {
		// verifica se o registro tem dados
		if (mensagem_aux.msg != 0){
			printf("\nIP: %-20s\n", mensagem_aux.ip);
			printf("\nAssunto: %-20s\n", mensagem_aux.assunto);
			printf("Mensagem: %-20s\n", mensagem_aux.msg);	
		}
		// l� mais um registro
		fread(&mensagem_aux, sizeof(mensagens), 1, pmensagens);
	}		
	
	linha();
	printf("\n\n\nDigite qualquer tecla para voltar ao menu...");
	getchar();
}	

// void apagar(char *mensagens.dat)
// Fun��o que apaga o arquivo de mensagens.
void apagar(){
	fclose(pmensagens);
	printf("\n\nARQUIVO DE MENSAGEM APAGADO!\n\n");
	remove("mensagens.dat");
}

//---------------------------------------------------------------------------

// PARTE USUARIO!!!

// Procedimento que abre um arquivo.
void abre_arquivo_usuarios() {
	// Abre o arquivo em forma d leitura.
	pusuarios = fopen("usuarios.dat", "r+b");
}

// Fun��o que verifica se o usuario � v�lido
int valida_login(char *log) {
	int p = 0;
	
	// Retorna leitor do arquivo para o in�cio do arquivo
	rewind(pusuarios);
	// Faz a leitura do primeiro registro do arquivo
	fread(&usuario_aux, sizeof(usuarios), 1, pusuarios);
	
	// Enquanto n�o chegar ao fim do arquivo fa�a
	while (feof(pusuarios) == 0) {
		
		// Se login passado for igual do usuario_aux
		if (strcmp(usuario_aux.login, log) == 0) {
				return p; // Retorna a posi��o do usuario no arquivo
		} else {
			// L� o pr�ximo registro
			fread(&usuario_aux, sizeof(usuarios), 1, pusuarios);
			p++; // Incrementa a posi��o lida do arquivo
		}
	}
	// Retorna -1 caso o usuario n�o seja encontrado
	return -1; 
}

// Fun��o que verifica se a senha est� correta
int valida_senha(char *senha) {
	int p = 0;
	
	if (strcmp(usuario_aux.senha, senha) == 0){
	// Retorna 0 caso a senha esteja correta
		return 0;
	} else {
	// Retorna -1 caso a senha esteja incorreta	
		return -1;
	}
}

int finalizar(){
	printf("Aperte qualquer tecla para continuar...");
	getchar();
	
	return 0;
}

// Procedimento que pede para o usu�rio digitar o numero de login a ser procurado.
void loginSenha() {
	char logcon[10], senhacon[10];
	int resp, op;
	
	do{
	printf("\nLogin: ");
	scanf("%s", logcon);
	fflush(stdin);
	
		if (valida_login(logcon) != -1){
		
			printf("Senha: ");
			scanf("%s", senhacon);
			fflush(stdin);
			
			if (valida_senha(senhacon) == 0) {
				printf("Usuario logado com sucesso!");
				op = menu();
				
				while (op != 0){
					switch(op){
						case 1:
							enviar();	
						break;
							
						case 2:
							printf("\nLISTA DE MENSAGENS ENVIADAS");
							listar();
							
						break;
						
						case 3:
							apagar();
							abre_arquivo_mensagens();
						break;
						
						case 0: 
							fclose(pusuarios);
							fclose(pmensagens);
						break;
						
						default:
							printf("\n\n\nOpcao invalida!");
							printf("\n\nDigite qualquer tecla para continuar...");
							getchar();
						break;	
					}
					op = menu();	
				}
			break;
			} else {
				printf("Senha invalida!\n\n");
			}
		} else {
			printf("Usuario nao encontrado\n\n");
		}
	
		printf("\n\nDeseja repetir o login (1-Sim/0-Nao)? "); 
		scanf("%d", &resp);
		fflush(stdin);		
	}while(resp == 1);
	
}

//---------------------------------------------------------------------------

// FUN��O PRINCIPAL!!!

int main(int argc, char *argv[]) {
	int op;
	
	abre_arquivo_usuarios();
	abre_arquivo_mensagens();
	
	printf("\n\nPROGRAMA DE MENSAGENS\n\n");
	
	loginSenha();
	
	return 0;
}
