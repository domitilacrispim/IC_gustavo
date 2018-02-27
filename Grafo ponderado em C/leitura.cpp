#include<stdio.h>
#include<stdlib.h>
#include <string.h>
typedef struct no{
	char nome[50];
	double *vizinho; //ARESTAS
	double total=0;
}no;


int main (){
	int  contnum=0, result, cont=0, vert1=0, i, vert2=0, conta=1;
	char nom[50];
	int tam;	
	//lendo do arquivo e colocando no grafo *****************************************************************************
	FILE *arq;
	arq = fopen("teste", "rt");
	if(arq==NULL) {
		printf("Nao eh possivel abrir o arquivo!\nMissao abortada.\n"); return 0;
	}	
		
	result = fscanf(arq, "%d", &tam); // o arq se inicia com o numero maximo de passos distindos q podem ser usados		
	no grafo[tam+3];	//''cria'' o grafo 
	
	while(1){
		result = fscanf(arq, "%d", &cont); 
		conta=0;
		if(result==EOF) break;
		//printf("%d!!", cont);
		while(cont--){
			result = fscanf(arq, "%d", &vert2);
			//printf("??%d\n", vert2);
			if(conta==0){
				vert1=vert2;
				conta=1;
			}
			else if(conta==1){
				if(grafo[vert1].total==0){
					grafo[vert1].vizinho=(double*)malloc(sizeof(double)*(tam+1)); 		
					memset(	grafo[vert1].vizinho, 0, sizeof(grafo[vert1].vizinho));
				}
				grafo[vert1].total++; //printf("%lf!! %d\n", grafo[vert1].total, vert1);
				grafo[vert1].vizinho[vert2]++;
				vert1=vert2;
			}
		}
	}
	fclose(arq);
	// montou o grafo *******************************************************************************************
	//essa parte recebe o arquivo com nomes e coloca no grafo !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	FILE *arq1;
	int aux=1;
	arq1 = fopen("nomes", "rt");
	if(arq1==NULL) {
		printf("Nao eh possivel abrir o arquivo!\nMissao abortada.\n"); return 0;
	}		
	while(1){
		result = fscanf(arq1, "%s", nom); 
		if(result==EOF) break;
		strcpy(grafo[aux].nome,nom);
		aux++;	
	}
	fclose(arq1);
	// nomeiou os vertices !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	FILE *arq2 = fopen("resultado", "wt");
	if(arq2==NULL) {
		printf("Nao eh possivel abrir o arquivo!\nMissao abortada.\n"); return 0;
	}	
	// gravando no arquivo &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&	
	fprintf(arq2,"%d\n",tam);  
	for(int y=1; y<=tam; y++){
		fprintf(arq2,"%s\n",grafo[y].nome);  
		// apenas 0 os vertices q nao foram usados pra q nao de problrma ao ler ############################################
		if(grafo[y].total==0){
					grafo[y].vizinho=(double*)malloc(sizeof(double)*(tam+1)); 		
					memset(	grafo[y].vizinho, 0, sizeof(grafo[y].vizinho));
		} 
		// zerados #########################################################################################
		for(int r=1; r<=tam; r++){
			fprintf(arq2," %lf ",grafo[y].vizinho[r]);  
		}
		fprintf(arq2,"\n%lf\n",grafo[y].total );  
	}
	// gravado com sucesso &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
}
