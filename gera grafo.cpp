#include<stdio.h> 
#include<string.h>
#include<stdlib.h>
#include <time.h>
#include <dirent.h>

#define tampop 100

int tami=10;
typedef struct no{
	char nome[30];
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
	//printf ("%d\n",max);
	while(max>0){	
		//printf("%d", g.vertices[num_inic].total);
		if( (int)g.vertices[num_inic].total<1) { num_inic=rand()%161;
				continue;
		 }
		if((int)g.vertices[num_inic].total>0){
			aux=rand()%(int)g.vertices[num_inic].total;
			//aux++;
			//puts("MIMIM");
		}	
		
		strcpy(id.passos[tam],g.vertices[(int)g.vertices[num_inic].vizinho[aux]].nome);
		max--;
		tam++;
		//printf("%s",g.vertices[(int)g.vertices[num_inic].vizinho[aux]].nome);
				
		num_inic=g.vertices[num_inic].vizinho[aux];
	}
	return id;
}
populacao gera_pop(populacao p, Grafo g, int maxi){
	
	int  random=rand()%161, max, aux_t, aux_s, min, pass=0, ind=0, random_v, passo;
	
   	
	for(int ind=0; ind<tampop; ind++){
		if(g.vertices[random].total==0){
			random=rand()%161; 
			ind--;
		}		
		else {
			max=tami;
			max++;
			p.pop[ind].n_passos=max;
			max--;
			strcpy(p.pop[ind].passos[pass],g.vertices[random].nome);
			//printf("%s\n", p.pop[ind].passos[pass]);		
			//printf("%d\n", random);	
			p.pop[ind]=gera_ind(p.pop[ind], random, g, max); 
			random=rand()%161;
		}
	}
	p.ger=0;
	return p;
}


int main (){
	
	Grafo g;
	int tam, i=0, max=0, min;
	char nom[50], cat[100];
	populacao p;
	FILE *arq;
	DIR *dir;
    	struct dirent *lsdir;
	dir = opendir("/home/estagio/IC/Sequencias_TI");	// caminho de onde estao salvos os passos
	arq = fopen ("resultado1", "rt");
	fscanf (arq, "%d", &tam); //printf("%d", tam);
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
	while ( ( lsdir = readdir(dir) ) != NULL ){
		//printf("ROAR");
		
        	if (lsdir->d_name[0]!='.'){
			i=-1;
			min=0;
			int numes[200], ct=0;
 			bzero(cat, 100); // limpa a variavel cat
			strcat(cat, "Sequencias_TI/"); // concatena valores em cat
			strcat(cat, lsdir->d_name);
			fclose(arq);
			arq = fopen (cat, "rt"); 
			while(fscanf(arq, "%s", nom)!=EOF){
				min++; //printf("%s", nom); //return 0;
				nom[strlen(nom)-1]='\0';
				for( int ji=0; ji<161; ji++){
					//printf("%s !!! %s\n", g.vertices[ji].nome, nom);
										
					if(strcmp(g.vertices[ji].nome, nom)==0){
						//printf("%s %s\n", g.vertices[ji].nome, nom);
						if(i==-1){
							g.vertices[ji].inicial++;
							numes[ct]=ji;
							ct++;
							i=ji; break;
							}	
						else {
							for(int io=0; io<ct; io++){
								printf("%d\n", (int)g.vertices[i].total);
								g.vertices[numes[io]].vizinho[(int)g.vertices[numes[io]].total]=ji;
								g.vertices[numes[io]].total++;	
								//printf("%d\n", i);
								//printf("%s %s\n", nom, g.vertices[io].nome);	
									 //break;				
							}
							numes[ct]=ji;
							ct++;
						}	
						break;		
					}
					
				}
				
			
				
			} return 0; 	
			if(min>max) max=min;
		
		}
		//printf("%d\n",rand()%161);
			
			
    	}
	closedir(dir); 
	for( int ji=0; ji<161; ji++){
		printf("%d",g.vertices[i].vizinho[(int)g.vertices[i].total]);
	}
	p=gera_pop(p,g, max);
	for ( int j=0; j<100; j++){
		for (int mimi=0; mimi<p.pop[j].n_passos; mimi++){
			if(mimi!=0) printf(", ");
			printf("%s", p.pop[j].passos[mimi]);
			
			
		}
		puts("");
	}
}
