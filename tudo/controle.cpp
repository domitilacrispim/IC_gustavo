
#include<bits/stdc++.h>
#include <stdlib.h> 
#include <unistd.h>

#include <dirent.h>

int main (){
	system("g++ js.cpp ");
	char aux[1000], in='a';
	aux[0]='\0';
	char currDir[10000];
	char DSE_PATH[10000];
	if (getcwd(currDir, sizeof(currDir)) == NULL){
		printf("DSE: Falha ao obter o diretorio corrente.\n\n");
		return -1;
	}
	for( int i=0; i<10;i++){
		DIR *dir, *dir2; 
		struct dirent *lsdir, *lsdi2;
		char pasta[100], aux[2000];
		dir = opendir("/home/lcbio-200/Benchmarks/TEXAS_42_LEON3/");	
		int g=0;
		char seq[10000], mds=0;  
		while ( ( lsdir = readdir(dir) ) != NULL ){ 
			aux[0]='\0'; DSE_PATH[0]='\0';
			strcpy(pasta,lsdir->d_name);
			if(pasta[0]=='I' || pasta[0]=='D'){
				strcat(aux, "./a.out ");
				strcat(aux, pasta);		
				system(aux);
			 }
			 strcpy(DSE_PATH,"/home/lcbio-200/Benchmarks/TEXAS_42_LEON3/");
			strcat ( DSE_PATH, pasta);
			chdir(DSE_PATH);
			strcpy(aux,"\0");
			strcat(aux, " larad -compiler=llvm371 -target=leon3 -algo=list -nsteps=1 -seqlen=128 -nexec=1 ./\0");
			strcat ( aux, pasta);
			strcat ( aux, ".c > relatorio_grafo_extendido");
			strcat ( aux, pasta);
			printf("%s\n\n", aux); 	
			system(aux);
			chdir(currDir);
		}
	}
}
