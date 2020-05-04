
#include<bits/stdc++.h>
#include <stdlib.h> 
#include <unistd.h>

#include <dirent.h>

int main (){
	char in='a', palavra[1111], aux[2000];
	aux[0]='\0';
	FILE *arq, *arq2;
	arq=fopen("/home/lcbio-200/Domitila/relatorio_grafo_extendido.csv", "a+");
	char currDir[10000];
	char DSE_PATH[10000];
	DIR *dir, *dir2; 
	struct dirent *lsdir, *lsdi2;
	char pasta[100];
	dir = opendir("/home/lcbio-200/Benchmarks/TEXAS_42_LEON3/");	
	int g=0, flag=0, Problematic=0;
	char seq[10000], mds=0;  
	while ( ( lsdir = readdir(dir) ) != NULL ){ 		
		strcat(pasta,lsdir->d_name); flag=0;
		if(pasta[0]=='I' || pasta[0]=='D'){
			Problematic=0;
			fprintf(arq, "%s ," , pasta);		
			strcpy(DSE_PATH,"/home/lcbio-200/Benchmarks/TEXAS_42_LEON3/");
			strcat ( DSE_PATH, pasta);
			strcat ( DSE_PATH, "/relatorio_grafo_extendido");
			strcat ( DSE_PATH, pasta);
			arq2 = fopen(DSE_PATH, "r"); 
			while(fscanf(arq2, "%s", palavra)!=EOF){ 
				if(strcmp("Problematic", palavra)==0) Problematic++;
				if(strcmp(palavra, "Latency")==0){
					fscanf(arq2, "%s", palavra);
					fscanf(arq2, "%s", palavra);
					fprintf(arq, " %s ,", palavra);
					flag=1;
				}
				if(flag==1){
					if(palavra[0]=='-' and palavra[1]=='O'){
						while(fscanf(arq2, "%s", palavra)){
							if(palavra[0]==':') break;
						}
						fscanf(arq2, "%s", palavra);
						fprintf(arq, " %s ,", palavra);
							
					}
								
				}
				
			}
			fprintf(arq,"%d	\n", Problematic);
			fclose(arq2);
			
		}
		pasta[0]='\0';
	}
	
}
