//PROGRAMMA IN CUI UN THREAD MANDA DEI COMANDI CASUALMENTE,AD UN ALTRO THREAD DOPO 20 INTERROGAZIONI SI METTE TERMINA ED ESSO FINISCE,SI ASPETTA LA TERMINAZIONE DEL THREAD,SI ELIMINANO I MUTEX E SI ELIMINA IL THREAD//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
void *funzione(void *arg);
//VARIABILE CONDIVISE//
pthread_mutex_t mmutex,tmutex;
char stringa[50];
int i;
int time_to_exit=0;

int main(void){
pthread_t t1;
int res;
int j=0;
char *comandi[]={"AVANTI","INDIETRO","DESTRA","SINISTRA","STOP"};
//1 INIZIALLIZZO I 2 MUTEX//
res=pthread_mutex_init(&mmutex,NULL);
if(res!=0){
perror("ERRORE DURANTE INIZIALIZZAZIONE\n");
exit(1);
}
res=pthread_mutex_init(&tmutex,NULL);
if(res!=0){
perror("ERRORE DURANTE INIZIALIZZAZIONE\n");
exit(1);
}
//2 CREO IL THREAD//
pthread_create(&t1,NULL,funzione,NULL);
//3 BLOCCO IL MUTEX//
pthread_mutex_lock(&tmutex);
srand(i);
//4 FACCIO IL CICLO DEL THREAD PRINCIPALE//
do{
pthread_mutex_lock(&mmutex);
if(i==20){
strcpy(stringa,"TERMINA");
pthread_mutex_unlock(&tmutex);
break;
}
if(i!=0){
printf("La stringa modificata:%s\n",stringa);
}
j=rand()%5;
printf("MANDO UNA STRINGA\n");
strcpy(stringa,comandi[j]);
pthread_mutex_unlock(&tmutex);
}while(1);

pthread_join(t1,NULL);
pthread_mutex_destroy(&tmutex);
pthread_mutex_destroy(&mmutex);
pthread_cancel(t1);
printf("TUTTO E ANDATO CORRETTAMENTE\n");
exit(0);
}

void *funzione(void *arg){
int lun;
do{
pthread_mutex_lock(&tmutex);
if(strncmp(stringa,"TERMINA",7)==0){
pthread_mutex_unlock(&mmutex);
break;
}
lun=strlen(stringa)-1;
printf("Hai inserito la seguente stringa:%s\n",stringa);
printf("LA TUA STRINGA E LUNGA:%d\n",lun);
strcat(stringa,"ESEGUITO");
i++;
pthread_mutex_unlock(&mmutex);
}while(1);
pthread_exit(0);
}
