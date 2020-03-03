#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <time.h>
#include <dirent.h>

#define tampop 100

int tami=10;
typedef struct no{
	char nome[35];
	double *vizinho; //ARESTAS
	double total=0;
	int inicial=0;
}no;

typedef struct Grafo{
	int qtd_ver;
	no *vertices;
}Grafo;

Grafo cria_grafo( Grafo G, int qd_v){
	G.qtd_ver=qd_v;
	G.vertices=(no*)malloc(sizeof(no)*(qd_v));
	for(int i=0; i<qd_v; i++){
		G.vertices[i].vizinho = (double*)malloc(sizeof(double)*(qd_v));
		memset(	G.vertices[i].vizinho, 0, sizeof(G.vertices[i].vizinho));
	}
	return G;
}

typedef struct individuo {
	char passos[161][50];
	int n_passos;
	double fitness;
}individuo;

typedef struct populacao{
	individuo pop[100];
	int ger;
}populacao;


individuo gera_ind( individuo id, int num_inic, Grafo g, int max){
	tami+=10;
	if(tami>161) tami=10;
	int tam=1, aux, aux1, ind=0;
	while(max>0){
		num_inic=rand()%161;
		strcpy(id.passos[tam],g.vertices[num_inic].nome); // aleatorio 	
		max--;
		tam++;
	}
	return id;
}
populacao gera_pop(populacao p, Grafo g, int maxi){

	int  random=rand()%161, max, aux_t, aux_s, min, pass=0, ind=0, random_v, passo;
	for(int ind=0; ind<tampop; ind++){
			random=rand()%161; // comeca com indice aleatorio
			max=tami;
			max++;
			p.pop[ind].n_passos=max;
			max--;
			strcpy(p.pop[ind].passos[pass],g.vertices[random].nome);
			p.pop[ind]=gera_ind(p.pop[ind], random, g, max);
			random=rand()%161;
	}
	p.ger=0;
	return p;
}



int main (int argc,  char *argv[ ] ){

	Grafo g;
	int tam, i=0, max=0, min, bal=0;
	char nom[50], cat[100], nom_p[50], car;
	populacao p;
	FILE *arq, *arq2;
	DIR *dir;
    	struct dirent *lsdir;
	strcpy(nom_p, argv[1]);
	//printf("%s\n", nom_p); return 0;
	dir = opendir("/home/lcbio-200/Domitila/Sequencias_TI");	// caminho de onde estao salvos os passos
	arq = fopen ("resultado1", "rt");
	fscanf (arq, "%d", &tam); //return 0;//printf("%d", tam);
	g=cria_grafo(g, tam+1);

	while(i<tam){
		fscanf (arq, "%s", nom);
		if(nom==NULL) break;
		strcpy(g.vertices[i].nome,nom);
		//printf("%s\n", g.vertices[i].nome);
		g.vertices[i].vizinho=(double*) malloc (45*sizeof (double));
		i++;
	}
	srand(time(0));

	fclose(arq);
	p=gera_pop(p,g, max);

	bzero(cat, 100); // limpa a variavel cat
	arq = fopen("/opt/lara-tools/larad/algorithms/list/dse_algo.lara","r+");
	arq2 = fopen("/opt/lara-tools/larad/algorithms/list/dse_algo2.lara","w+");
	while(1){
		fscanf(arq,"%c", &car);
		if(car=='['){
			bal++;
		}
		//printf("%c", car );
		if(bal==2){
			break;
		}
	}
	printf("\n" );
	for(int i=0; i<100; i++){
		if(i!=0) printf( ", ");
		printf( "[ ");
		for(int j=0; j<p.pop[i].n_passos; j++){
			if(j!=0) printf( ", ");
			printf( "\"%s\"", p.pop[i].passos[j]);
		}

		printf( "]\n ");
	}
	int verdade=0;
	while(fscanf(arq,"%c", &car )!=EOF){
		if(car=='[') verdade++;
		if(car==']') verdade--;
		//if(verdade<0)
		//	printf("%c", car );

	}
	//rename("/opt/lara-tools/larad/algorithms/list/dse_algo2.lara", "/opt/lara-tools/larad/algorithms/list/dse_algo.lara");
}
