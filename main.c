/*

TDE de Programa��o de Computadores

Integrantes do Grupo:
Augusto Emanuel Batista Novaes Santos - 6107754
Guilherme Marques Tavares  - 9379212
Pablo Luis dos Santos Alves - 8553028
Gabriel dos Santos Bello Botelho - 1829450
Felipe Bruno Costa da Silva - 3351768


Para entrar no debug mode, basta abrir o main.exe com CMD usando o comando: main.exe -debug
Debug mode est� aqui podemos verificar se o programa as lendo o algoritmo de maneira correta

C�digo testado usando GCC e G++ no Windows 10 e apenas GCC no Puppy Linux
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Verifica se o sistema operacional � windows
#if defined(_WIN32) || defined(_WIN64)
	#include <Windows.h>
#endif

//Tamanho maximo de linhas validas do database
#define MAX_SIZE_OF_DATABASE = 1347;
//Tamanho minimo de linhas validas do database
#define MIN_SIZE_OF_DATABASE = 0;

//Carrega os dados do database para o struct principal(db)
void LerArquivo();

//Mostra o menu da op��o 1 e executa todos suas fun��es
void Option1();

//Mostra o menu da op��o 2 e executa todos suas fun��es
void Option2();

//Usando o algoritmo de Insertion Sort (tem certeza que � insertion? :) <- Olhar psicopata)
void ParaDecrescente();

//Mostra o menu principal e retorna a op��o selecionada pelo usuario
int MainMenu();

//Mostra os dados. Essa fun��o � somente usada em DEBUG MODE.
void ListarDados();

//Limpa a tela
void Clrscr();

_Bool debugMode = 0;


//Struct de dados do Database
typedef struct
{
	int CODMUN7;
	int ANO;
	char NOME[30];
	int CV_SCR1;
} dados;


dados db[1347]; //Dados Principais
dados dbDec[1347]; //Dados decrescentes

int main(int argc, char **argv) {

	debugMode = 1;

	LerArquivo();
	memcpy(dbDec, db, sizeof(db));
	ParaDecrescente();
	
	while (1) {
		int op = MainMenu();
		switch (op) {
			case 1:
				Option1();
				break;
			case 2:
				Option2();
				break;
			case 3:
				return 0;	
		}

		if (debugMode) {
			if (op == 4) {
				ListarDados();
			}
		}
	}
	return 0;
}

char nome[15];

void Option1() {
	typedef struct {
		char nome[30];
		int cv1;
	} resultados;

	resultados r[5];

	int ano, start, end;
	Clrscr();
	printf("Digite o ano: ");
	scanf("%d", &ano);

	if (ano >= 2016 && ano <= 2018) {
		int c = 0;
		for (int i = 0; i < 1347; i++) {
			if (c < 5) {
				if (dbDec[i].ANO == ano) {
					strcpy(r[c].nome, dbDec[i].NOME);
					r[c].cv1 = dbDec[i].CV_SCR1;
					printf("%s %d\n", dbDec[i].NOME, dbDec[i].CV_SCR1);
					c++;
				}
			}
		}
		getchar();
		printf("Deseja salvar esse resultado (S/N)?\n ");
		char op;
		scanf("%c", &op);
		if (op == 'S') {
			sprintf(nome, "%d", ano);
			strcat(nome, ".csv");

			FILE* arquivo;
			arquivo = fopen(nome, "w+");
			fprintf(arquivo, "\"Nome\", \"CV_SCR1\"\n");
			for (int i = 0; i < 5; i++) {
				fprintf(arquivo, "\"%s\", \"%d\"\n", r[i].nome, r[i].cv1);
			}
			fclose(arquivo);
			printf("Resultado salvo no arquivo %d.csv\n", ano);
		}
	}
	else {
		printf("Ano Invalido\n");
	}

	printf("Digite [ENTER] para retornar ao menu anterior");
	//Aguardar o ENTER
	getchar();
	char enter = 0;
	while (enter != '\r' && enter != '\n') { enter = getchar(); }
}

void Option2() {
	typedef struct {
		int cv1[3];
		char nome[30];
	}resultados;

	resultados r;

	int codigo;
	Clrscr();
	printf("Digite o codigo: ");
	scanf("%d", &codigo);

	int finders = 0;

	//Buscar dados no database
	for (int c = 2016; c <= 2018; c++) {
		for (int i = 0; i < 1347; i++) {
			if (db[i].ANO == c && db[i].CODMUN7 == codigo) {
				if (c == 2016) {
					strcpy(r.nome, db[i].NOME);
					printf("%s\n", r.nome);
				}
				r.cv1[2018 - c] = db[i].CV_SCR1;
				printf("%d = %d\n", c, db[i].CV_SCR1);
				finders++;
				break;			
			}
		}
	}

	//Verificar se dados foram encontrados, caso encontrados, perguntar se deseja salvar-los
	{
		if (finders > 0) {
			getchar();
			printf("Deseja salvar esse resultado (S/N)?\n ");
			char op;
			scanf("%c", &op);
			if (op == 'S') {
				sprintf(nome, "%d", codigo);
				strcat(nome, ".csv");

				FILE* arquivo;
				arquivo = fopen(nome, "w+");
				fprintf(arquivo, "\"Ano\", \"CV_SCR1\"\n");
				for (int i = 2; i >= 0; i--) {
					fprintf(arquivo, "\"%d\", \"%d\"\n", 2018 - i, r.cv1[i]);
				}
				fclose(arquivo);
				printf("Resultado salvo no arquivo %d.csv\n", codigo);
			}
		}
		else {
			printf("Codigo invalido\n");
		}
	}

	printf("Digite [ENTER] para retornar ao menu anterior");
	//Aguardar o ENTER
	getchar();
	char enter = 0;
	while (enter != '\r' && enter != '\n') { enter = getchar(); }
}

void ParaDecrescente() {
	for (int i = 0; i < 1346; i++) {
		int k = i;
		while (k >= 0) {
			if (dbDec[k].CV_SCR1 < dbDec[k + 1].CV_SCR1) {
				dados buffer = dbDec[k];
				dbDec[k] = dbDec[k + 1];
				dbDec[k + 1] = buffer;
			}
			k--;
		}
	}
}

int MainMenu() {
	system("cls");
	int op;

	if (debugMode)
		printf("DEBUG MODE\n");

	printf("*************************************************\n");
	printf("* Pesquisa vacinas cidades do Norte do Brasil ***\n");
	printf("*************************************************\n");
	printf("1-Pesquisa por ano\n");
	printf("2-Pesquisa por codigo da cidade\n");
	printf("3-Sair\n");
	if (debugMode) {
		printf("4- Listar todos os dados\n");
	}
	printf("Digite uma opcao: ");
	scanf("%d", &op);

	return op;
}

void ListarDados() {
	Clrscr();

	printf("Qual listagem?\n1- Lista Principal\n2- Lista Decrescente\n");
	int op;
	scanf("%d", &op);

	printf("COD7     NOME                           ANO  CV1 ENDERECO DE MEMORIA FISICA\n");
	if (op == 1) {
		for (int i = 0; i < 1347; i++) {
			printf("%d %-30s %d %d 0x%p\n", db[i].CODMUN7, db[i].NOME, db[i].ANO, db[i].CV_SCR1, &db[i]);
		}
	}
	else {
		for (int i = 0; i < 1347; i++) {
			printf("%d %-30s %d %d 0x%p\n", dbDec[i].CODMUN7, dbDec[i].NOME, dbDec[i].ANO, dbDec[i].CV_SCR1, &dbDec[i]);
		}
	}
	getchar();
	getchar();
}

void LerArquivo() {
	FILE* arquivo;
	arquivo = fopen("database.csv", "r"); //Abre o arquivo para leitura
	char buff[1024];
	fgets(buff, 1024, arquivo); //Usado para ignorar o cabe�alho

	for (int c = 0; c < 1347; c++) {

		fgets(buff, 1024, arquivo); //Le a linha

		strtok(buff, "\"");
		strtok(NULL, "\""); //Dado n�o necessario
		char* codigo7 = 0;
		codigo7 = strtok(NULL, "\""); //Dado CODMUN7
		strtok(NULL, "\""); //Dado n�o necessario
		strtok(NULL, "\""); //Dado n�o necessario
		strtok(NULL, "\""); //Dado n�o necessario
		char* ano = strtok(NULL, "\""); //Dado ANO
		strtok(NULL, "\"");
		char* nome = strtok(NULL, "\""); //Dado NOME
		strtok(NULL, "\"");
		char* CV1 = strtok(NULL, "\""); //Dado CV1
		strtok(NULL, "\""); //Dado n�o necessario

		//Carrega os dados para struct principal (db)
		{
			int code7;
			int anoI;
			int cv1;
			sscanf(codigo7, "%d", &code7);
			sscanf(ano, "%d", &anoI);
			sscanf(CV1, "%d", &cv1);
			db[c].CODMUN7 = code7;
			db[c].ANO = anoI;
			db[c].CV_SCR1 = cv1;
			for (int i = 0; i < strlen(nome); i++) {
				db[c].NOME[i] = nome[i];
			}
		}
	}
}

void Clrscr() {

	//Para limpar a tela � necessario a verifica��o do sistema operacional, sistemas MS-DOS/WIN e UNIX/LINUX n�o possuem o mesmo comando para limpar a tela.

#if defined(_WIN32) || defined(_WIN64)
	system("cls");
#endif
#if defined(__linux__) || defined(__unix__)
	system("clear");
#endif
}