#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define TAMANHO_VETOR 50
int _vetor[TAMANHO_VETOR];
int _cont = 0;
pthread_mutex_t mutex;

void *CriaVetor(void *argumento){
    for(int i=0;i<TAMANHO_VETOR;i++){
        sleep(1);
        pthread_mutex_lock(&mutex);
        _vetor[i] = rand()%100;
        _cont++;
        printf("Cria [%d] = %d\n",i,_vetor[i]);
        pthread_mutex_unlock(&mutex);        
        
    }  
    pthread_exit(NULL);    
}

void *MostraVetor(void *argumento){
    for(int i=0;i<TAMANHO_VETOR;i++){
        sleep(2);
        pthread_mutex_lock(&mutex);
        printf("Imprimi [%d] = %d\n",i,_vetor[i]);
        pthread_mutex_unlock(&mutex);   
    }    
    pthread_exit(NULL); 
}

void *OrdenaVetor(void *argumento){
    int x, y, aux;
    while(_cont < TAMANHO_VETOR){
		sleep(5);
		pthread_mutex_lock(&mutex);
		for(y = 0 ; y <= TAMANHO_VETOR;y++){
			for(x = 0; x <= _cont - 2; x++){		
				if(_vetor[x] > _vetor[x+1]){
					aux = _vetor[x];
					_vetor[x] = _vetor[x+1];
					_vetor[x+1] = aux;
				}	
			}
		}
		pthread_mutex_unlock(&mutex);
        for(int i = 0;i<TAMANHO_VETOR;i++){
            if(_vetor[i] != 0){
                printf("[%d] ",_vetor[i]);
            }
        }
        printf("\n");
	}
    pthread_exit(NULL); 
}

int main(){
    pthread_mutex_init(&mutex,NULL);
    pthread_t pthCria, pthMostra, pthOrdena;
    void *resp;
    int rstatus;
    
    pthread_create(&pthCria, NULL, CriaVetor, (void *)("abcd"));
    pthread_create(&pthMostra, NULL, MostraVetor, (void *)("abcd"));
    pthread_create(&pthOrdena, NULL, OrdenaVetor, (void *)("abcd"));
    
    pthread_join(pthCria,&resp);
    pthread_join(pthMostra,&resp);
    pthread_join(pthOrdena,&resp);
    pthread_mutex_destroy(&mutex);
}