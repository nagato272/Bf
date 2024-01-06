#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#if __unix__		// non esistono in amente windows )=
	extern void _exit(register int);
	#include <sys/types.h>
	#include <unistd.h>
#else
	#error, "operative system not unix-like"
#endif


#ifndef checker
	#define checker(x, msg) 			\
		if(x){ 					\
			perror(msg);			\
			_exit(EXIT_FAILURE);		\
		}
#else
	#error, "macro checker already defined"
#endif


#if defined(checker) // verra usato in futuro
	typedef struct{
		#define MAX 30000
		char nastro[MAX];
	}machine;
#endif



int main(int argc, char *argv[], char *envp[]){
	checker(argc != 1, "errore nel passaggio degli argomenti al programma");

	FILE *input = fopen("./test.txt", "r");
	checker(input == NULL, "file not found");
	
	// ottengo la lunghezza max del file
	unsigned long int numberOFInstruction = 0; 
	char character;
	while((character = fgetc(input)) != EOF){
		printf("%c", character);		// verifico che i caratteri vengano presi correttamente
		numberOFInstruction++;
	}

	#ifndef SIZEFILE
		// dopo aver ottenuto la len del file creo una macro che verrà usato come buffer del vettore che conterra tutte le instruzioni
		#define SIZEFILE numberOFInstruction
	#endif

	char instFile[SIZEFILE];

	// inserisco char x char nel vettore,ho provato con fgets ma non funziona comunque
	for(int i = 0; (instFile[i] = fgetc(input)) != EOF; i++)
		;


	printf("lunghezza del vettore: %ld", strlen(instFile)); 		// output sbagliato
	printf("\nlunghezza del file in input :%ld", SIZEFILE); 		// output corretto (rappresenta la lunghezza del file)

	return EXIT_SUCCESS;
}



