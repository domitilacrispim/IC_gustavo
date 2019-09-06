#include<bits/stdc++.h>
#include <dirent.h>

int main (){
	double Tempo[10];
system("g++ js.cpp -o b");
		
	for( int i=0; i<10;i++){
//	printf("????%d??????", i+1);
	clock_t Ticks[2];
    DIR *dir, *dir2;    
 struct dirent *lsdir, *lsdi2;
 char pasta[100], aux[2000];
  dir = opendir("/home/domitila/Documentos/icomp/TEXAS_42_LEON3/");	

    int g=0; 		
    char seq[10000], mds=0;  
    while ( ( lsdir = readdir(dir) ) != NULL )
    { aux[0]='\0';
	
	 strcpy(pasta,lsdir->d_name);
	if(pasta[0]=='I' || pasta[0]=='D'){
		strcat(aux, "./b.out ");
		strcat(aux, pasta);		
		Ticks[0] = clock();
		system(aux);
	    	Ticks[1] = clock();
			
		 Tempo[i] = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;	
			
		
   
	 }
	}
	//printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
	system("g++ hu.c");
	system("./a.out");
	//printf("___________________________________________________");
	}
for( int i=0; i<10;i++) printf("%lf\n", Tempo[i]);
}


