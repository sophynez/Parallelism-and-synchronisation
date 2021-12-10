#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<unistd.h>
#include<sys/wait.h>
#include <math.h>
#include <stdbool.h>

FILE *f1, *f2, *f;
FILE *t_temp;

int n;
int premier1,premier2;



void fill (int n){
    printf("Remlissage du fichier\n");
	f = fopen("fa.txt","w");
	if(f==NULL){
        printf("error\n");
        exit(1);
    }

    for(int i=2;i<=n;i++){
	    fprintf(f,"%d\n",i);
	}
	fclose(f);
    
}



void p1(){
    printf("---------Début de P1\n");
    f1 = fopen("f1.txt","w");
    int i=2;
    int j, prem = 0;

    f = fopen("fa.txt", "r");
    int p;
    while (fscanf(f,"%d",&p)!=EOF){
        if (p % premier1 == 0 && p > premier1){
            fprintf(f1,"%d\n",p);
            printf("%d-- ",p);
        }
        else{
            if (prem == 0 && p > premier1){
                premier2 = p;
                int id = fork();
                if (id == 0){
                    p2();
                }
                prem = 1;
            }
        }
        }
    fclose(f);
    wait(0);  
    exit(0);
    
}

void p2(){
    printf("------------Début de P2\n");
    f  = fopen("fa.txt","r");
	f2 = fopen("f2.txt","w");
    int p;  

    while (fscanf(f,"%d",&p)!=EOF){
        if (p % premier2 == 0 && p > premier2){
            fprintf(f2,"%d\n",p);
            printf("%d-- ",p);
        }
    }
    fclose(f);
    fclose(f2);
    exit(0);
}

void purge(){
    printf("---Début purge\n");
    f = fopen("fa.txt", "r");
    f1 = fopen("f1.txt", "r");
    f2 = fopen("f2.txt", "r");
    FILE *ftemp = fopen("t_temp.txt", "w");
    int nf, nf1, nf2;
    
    fscanf(f1, "%d ", &nf1);
    fscanf(f2, "%d ", &nf2);
    int x = nf1/2;
    int y = nf2/2;
    while (fscanf(f, "%d", &nf) != EOF){  
        if(nf != nf1 && nf!=nf2) {
            fprintf(ftemp, "%d\n", nf);
        }
        if (nf >= nf1)
        {
            if (!feof(f1)){
                fscanf(f1, "%d", &nf1); 
            }
        }
        if (nf >= nf2 )
        {
            if (!feof(f2)){
            fscanf(f2, "%d", &nf2);
            }
             
        }
    }
    fclose(f);
    fclose(ftemp);
                
    fclose(f1);
    fclose(f2);

    f = fopen("fa.txt","w");
	    if (f == NULL) {printf("ERROR\n"); exit(1);}

    ftemp = fopen("t_temp.txt", "r");
	    if (ftemp == NULL) {printf("ERROR\n"); exit(1);}
	int c;
    while(fscanf(ftemp,"%d",&c)!=EOF){
        fprintf(f, "%d\n",c);
    }

    fclose(ftemp);
    fclose(f);


    // affectation de la prochaine valeur de premier1
    f = fopen("fa.txt","r");
    int p;

    while (fscanf(f,"%d",&p)!=EOF){
        if (p>x && p>y){
            premier1 = p;
            break;
        }
    }
    fclose(f);
}



int main (){
    printf("Début du programme\n");
	printf("---Donner valeur\n");
    scanf("%d", &n);
    fill(n);
    
    int s, s1, s2;

    int id1, i;
    premier1 = 2;

    while (premier1 <=(int)sqrt(n)){ 
        
        id1 = fork();
        if (id1 == 0){
            printf("------Création P1\n");
             p1(); 
        }
        wait(0);
        purge();


    }
    printf("Traitement Fini\n");
}
