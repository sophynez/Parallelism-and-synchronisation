#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<unistd.h>
#include<sys/wait.h>
#include <math.h>
#include <stdbool.h>

FILE *f1, *f2, *f;
FILE *t_temp;

int x, y, n;



void fill (int n){

	f = fopen("fa.txt","w");
	if(f==NULL){
        printf("error\n");
        exit(1);
    }

    for(int i=2;i<=n;i++){
	    fprintf(f,"%d ",i);
	}
	fclose(f);
    
}



void p1(){

    f1 = fopen("f1.txt","w");
    //printf("valeur de x=%d \n", x);
    //fscanf(f,"%d",x);
    int multiple= 0;
        int j, prem = 0;

        for (j=x+1; j<=n; j++){
            if (j%x ==0)
            {
                fprintf(f1,"%d ",j);
                
            }
            else if (prem == 0)
            {
                y = j;
                int id = fork();
                if (id == 0){
                   p2(); 
                }
                
                prem = 1;
            }       
        }

        wait(0);

    
    fclose(f1);
exit(0);
}

void p2(){

	f2 = fopen("f2.txt","w");
    int j;

        for (j=y+1; j<=n; j++){
            if (j%y == 0)
            {
                fprintf(f2,"%d ",j);
            }
        }
    fclose(f2);
exit(0);
}

void purge(){
    f = fopen("fa.txt", "r");
    f1 = fopen("f1.txt", "r");
    f2 = fopen("f2.txt", "r");
    FILE *ftemp = fopen("t_temp.txt", "w");
    
    int nf, nf1, nf2;
    
    fscanf(f1, "%d ", &nf1);
    fscanf(f2, "%d ", &nf2);
    while (!feof(f))
    {
        fscanf(f, "%d ", &nf);
        if(nf != nf1 && nf!=nf2) {
            fprintf(ftemp, "%d ", nf);
        }
        if (nf == nf1)
        {
            if (!feof(f1)){
                fscanf(f1, "%d ", &nf1); 
            }
        }
        if (nf == nf2)
        {
            if (!feof(f2)){
            fscanf(f2, "%d ", &nf2);
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
    while(fscanf(ftemp,"%d ",&c)!=EOF){
        int x = c;
        fprintf(f, "%d ", x);
    }

    fclose(ftemp);
    fclose(f);



}



int main (){
	printf("donner valeur\n");
    scanf("%d", &n);
    fill(n);

    int id1, i;

    for (i=0; i<=sqrt(n); i++){ 
        f = fopen("fa.txt","r");

        fscanf(f,"%d ",&x);
        //printf("val de x %d\n",x);

        id1 = fork();
        if (id1 == 0){ p1(); }
        else
        wait(0);
        purge();
	 
    }
    printf("Traitement Fini\n");
}
