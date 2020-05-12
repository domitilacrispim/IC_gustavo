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
	int aparicao=0;
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
//double valor = ((double) rand() * 2) / ( double ) RAND_MAX;


populacao gera_pop(populacao p, Grafo g, int maxi){
	double  aux_s, roleta=0;
	int  random=rand()%161, max=1, tam, min=0, pass=0, ind=0, random_v, passo;
	for(int ind=0; ind<tampop; ind++){
		random=rand()%161; // comeca com indice aleatorio
		pass=rand()%(ind%10*10+10);
		while(pass>tam){
			roleta=0;
			strcpy(p.pop[ind].passos[tam],g.vertices[random].nome);
			tam++;			
			if(g.vertices[random].total==0) break;
			for ( int it=0; it<g.vertices[random].total; it++){
				roleta+=(1/(double)g.vertices[(int)g.vertices[random].vizinho[it]].aparicao);
				printf("%lf ",roleta);
			}
			aux_s = ((double) rand() * 2) / ( double ) RAND_MAX;
			aux_s=aux_s*roleta; 
			printf("%lf\n", aux_s);			
			min=0;
			for ( int it=0; it<g.vertices[random].total; it++){
				printf("%d %d", it, random);
				if(roleta<=aux_s && aux_s<=roleta+(1/(double)g.vertices[(int)g.vertices[random].vizinho[it]].aparicao)){
					printf("%d %d", it, random);
					random=it;
				
					break;
				}
			}	
		}
		p.pop[ind].n_passos=tam;
		tam=0;
	}
	p.ger=0;
	return p;
}



int main (int argc,  char *argv[ ] ){
	
	Grafo g;
	int tam, i=0, ji, max=0, min, bal=0, ju;
	char nom[50], cat[100], nom_p[50], car, dire[100]="\0";
	populacao p;
	FILE *arq, *arq2;	
	arq2 = fopen("/opt/lara-tools/larad/algorithms/list/dse_algo2.lara","w+");
	DIR *dir;
    	struct dirent *lsdir;
	strcpy(nom_p, argv[1]);
	 
	//printf("%s\n", nom_p); return 0;
	dir = opendir("/home/domitila/Documentos/TCC/Sequencias_TI/");	// caminho de onde estao salvos os passos
	arq = fopen ("/home/domitila/Documentos/TCC/Sequencias_TI/resultado1", "rt"); 
	fscanf (arq, "%d", &tam); //return 0;//printf("%d", tam);
	g=cria_grafo(g, tam+1);
	
	while(i<tam){
		fscanf (arq, "%s", nom);
		if(nom==NULL) break;
		strcpy(g.vertices[i].nome,nom);
		g.vertices[i].vizinho=(double*) malloc (45*sizeof (double));
		g.vertices[i].total=0;
		g.vertices[i].aparicao=0;
		i++;
	}
	fclose(arq);

	while ( ( lsdir = readdir(dir) ) != NULL )
    	{
			strcat(	dire,"/home/domitila/Documentos/TCC/Sequencias_TI/");
			strcat(	dire, lsdir->d_name);
			arq = fopen ( dire,"rt");	
			fscanf(arq, "%s", nom);
			nom[strlen(nom)-1]='\0';
		for ( ji=0; ji<tam; ji ++){
			if( strcmp(g.vertices[ji].nome, nom)==0){
				g.vertices[ji].aparicao++;
				break;
			}
		}
		while(fscanf(arq, "%s", nom)!=EOF){
			nom[strlen(nom)-1]='\0';
			for(int jo=0; jo<tam; jo++){
				if(strcmp(g.vertices[jo].nome, nom)==0){

						g.vertices[jo].aparicao++;
						g.vertices[ji].vizinho[(int)g.vertices[ji].total ] = jo;
						g.vertices[ji].total++;
						ji=jo;
					break;
				}
			}
						
		}

		fclose(arq);
		 bzero(dire, 100);		
    	}

	    closedir(dir);
	srand(time(0));
	p=gera_pop(p,g, max);

	bzero(cat, 100); // limpa a variavel cat
	arq = fopen("/opt/lara-tools/larad/algorithms/list/dse_algo.lara","r+");
int aux_col=0;
	while(1){
		fscanf(arq,"%c", &car); 
		fprintf(arq2, "%c", car); 
		if(car=='['){
			aux_col++;	
		}
		if(aux_col==2) break;
	}

	printf("\n" ); 
	for(int i=0; i<100; i++){
		if(i!=0) fprintf( arq2,", ");
		fprintf( arq2, "[ ");
		for(int j=0; j<p.pop[i].n_passos; j++){
			if(j!=0) fprintf( arq2, ", ");
			fprintf( arq2, "\"%s\"", p.pop[i].passos[j]);
		}

		fprintf( arq2, "]\n");
	}

	int verdade=0;
	while(fscanf(arq,"%c", &car )!=EOF){
		if(car=='[') {
			verdade++;	
		}		
		if(car==']') {
			verdade--;	
		}
		
		if(verdade<0){
			verdade=-3;
			fprintf(arq2, "%c", car );
		}
	}
			
	rename("/opt/lara-tools/larad/algorithms/list/dse_algo2.lara", "/opt/lara-tools/larad/algorithms/list/dse_algo.lara");
}
