#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void Shellsort(int *v,int tamh, int *com, int *tro){
	
	*com=0,*tro=0;
	int gap,i,j,aux;
	for(gap=tamh/2;gap>0;gap=gap/2){
		for(i=gap;i<tamh;i++){
			aux=v[i];
			*com=*com+1;
			for(j=i;j>=gap && v[j-gap]>aux;j=j-gap){
				*com=*com+1;
				//Copias os valores até achar a sua posição
				v[j]=v[j-gap];
			}
			//Valor movido na sua posição correcta
			if(j!=i){
				//Houve troca se a posição i for dioferente da j
				*tro=*tro+1;	
			}
			v[j]=aux;
		}
	}	
}
void heap_max(int *arr, int n, int i, int *co, int *tr)
{
    int maior = i;
    int e = 2*i + 1;
    int d = 2*i + 2;
 
    // se o filho esquerdo é maior que a raiz
    *co=*co+1;
    if (e < n && arr[e] > arr[maior]){
    	maior = e;
	}
        
 
    // se o filho direito é maior que a raiz
    *co=*co+1;
	if (d < n && arr[d] > arr[maior]){
    	maior = d;
	}
        
 
    // se o maior é filho troca com a raiz
    int tmp , axco=*co,axtr;
    if (maior != i)
    {
    	//Troca
    	tmp=arr[i];
    	arr[i]=arr[maior];
    	arr[maior]=tmp;
    	*tr=*tr+1;
 		axtr=*tr;
 		
        heap_max(arr, n, maior,&axco,&axtr);
    }
}
void heapSort(int *arr, int n, int *com, int *tro)
{
    // criar/construir o heap_max com os elementos do vetor
    int i,o=0,r=0;
    for (i = n / 2 - 1; i >= 0; i--)
        heap_max(arr, n, i,&o,&r);
 
    // extracção de cada elemento do heap
    for (i=n-1; i>=0; i--)
    {
        // Ordenação movendo a raiz para o fim do vetor
        int tp;
        //troca
        tp=arr[0];
        arr[0]=arr[i];
        arr[i]=tp;
 		r=r+1;
        
        heap_max(arr, i, 0,&o,&r);
    }
    *com=o;
    *tro=r;
}

int main(int argc, char *argv[]) {
	//Vetor para 5oo números inteiros
	int vetor[10][500];
	//Vetor auxiliares para ordenação
	int vetorauxshell[10][500],vetorauxheap[10][500];
	//Preencher o vetor de forma aleatória
	int i,j;
	for(i=0;i<10;i++){
		for(j=0;j<500;j++){
			do{
				vetor[i][j] = rand();
				vetorauxshell[i][j]=vetor[i][j];
				vetorauxheap[i][j]=vetor[i][j];
			}while((vetor[i][j]<0) || (vetor[i][j]>1999));
		}
	}
	//Declaração de variáveis ,do tipo clock_t, que vão permitir determinar o tempo gasto na ordenação de cada vetor
	clock_t comeco,fim; 
	//CASO MÉDIO
	printf("\n\t\t\t\t<<<CASO MEDIO>>>\n\n\n");
	//Começamos pelo SHELLSORT
	printf("\t\t\t\t\t\t\tSHELLSORT\n\n\n\n\n");
	//Vetores que irão receber o número de comparações , trocas e o tempo gasto de cada vetor
	int comparacoesShell[10],trocasShell[10];
	double tempoShell[10];
	
	int gap,aux,k=0,tam=500;
	//Ordenação ShellSort, determinação do número de comparações , trocas e o tempo gasto
	while(k<10){
		
		comeco=clock();
		Shellsort(vetorauxshell[k],tam, &comparacoesShell[k], &trocasShell[k]);
		fim=clock();
		tempoShell[k]=1000.0*(double)(fim-comeco)/CLOCKS_PER_SEC;
		k++;
	}	
	
	//Declaração de variáveis que irão determinar o número médio de comparações trocas e o tempo gasto
	float mediacomparacoesShell=0, mediatrocasShell=0,mediatempogasto=0;
	for(i=0;i<10;i++){
		printf("\n_________________________________________________________________________<%d>__________________________________________________________________________________________\n\n\n{ ",i+1);
		for(j=0;j<500;j++){
			if(j!=499){
				printf(" %i ,",vetor[i][j]);	
			}
			else{
				printf(" %i }",vetor[i][j]);	
			}
		}
		printf("\n\n{ ");
		for(j=0;j<500;j++){
			if(j!=499){
				printf(" %i ,",vetorauxshell[i][j]);	
			}
			else{
				printf(" %i }",vetorauxshell[i][j]);	
			}
			
		}
		mediacomparacoesShell=mediacomparacoesShell+comparacoesShell[i];
		mediatrocasShell=mediatrocasShell+trocasShell[i];
		mediatempogasto=mediatempogasto+tempoShell[i];
		printf("\n---Realizaram-se %i comparacoes, %i trocas e o tempo gasto foi de %.3f ms.\n\n",comparacoesShell[i], trocasShell[i], tempoShell[i]);
	}
	
	mediacomparacoesShell=mediacomparacoesShell/10;
	mediatrocasShell=mediatrocasShell/10;
	mediatempogasto=mediatempogasto/10;
	printf("\n\n\t\t\t\t\t\tResultado:\n\n");
	printf("Numero medio de comparacoes:%.3f\nNumero medio de trocas:%.3f\nMedia do tempo gasto para a ordenacao:%.3f ms",mediacomparacoesShell,mediatrocasShell,mediatempogasto);
	
	
	printf("\n\n\n\n\n\n\t\t\t\t\t\t\tHEAPSORT\n\n\n\n\n");
	//Vetores que irão receber o número de comparações , trocas e o tempo gasto de cada vetor
	int comparacoesHeap[10],trocasHeap[10];
	double tempoHeap[10];	
	int n,c,t;
	for(k=0;k<10;k++){
		c=0, t=c;
		comeco=clock();
		heapSort(vetorauxheap[k], tam,&c,&t);
		fim=clock();
		comparacoesHeap[k]=c, trocasHeap[k]=t;
		tempoHeap[k]=1000.0*(double)(fim-comeco)/CLOCKS_PER_SEC;
	}
	float mediacomparacoesheap=0, mediatrocasheap=0,mediatempogastoh=0;
	for(i=0;i<10;i++){
		printf("\n_________________________________________________________________________<%d>__________________________________________________________________________________________\n\n\n{ ",i+1);
		for(j=0;j<500;j++){
			if(j!=499){
				printf(" %i ,",vetor[i][j]);	
			}
			else{
				printf(" %i }",vetor[i][j]);	
			}
		}
		printf("\n\n{ ");
		for(j=0;j<500;j++){
			if(j!=499){
				printf(" %i ,",vetorauxheap[i][j]);	
			}
			else{
				printf(" %i }",vetorauxheap[i][j]);	
			}
			
		}
		mediacomparacoesheap=mediacomparacoesheap+comparacoesHeap[i];
		mediatrocasheap=mediatrocasheap+trocasHeap[i];
		mediatempogastoh=mediatempogastoh+tempoHeap[i];
		printf("\n---Realizaram-se %i comparacoes, %i trocas e o tempo gasto foi de %.3f ms.\n\n",comparacoesHeap[i], trocasHeap[i], tempoHeap[i]);
	}
	mediacomparacoesheap=mediacomparacoesheap/10;
	mediatrocasheap=mediatrocasheap/10;
	mediatempogastoh=mediatempogastoh/10;
	printf("\n\n\t\t\t\t\t\tResultado:\n\n");
	printf("Numero medio de comparacoes:%.3f\nNumero medio de trocas:%.3f\nMedia do tempo gasto para a ordenacao:%.3fms",mediacomparacoesheap,mediatrocasheap,mediatempogastoh);
	
	if(mediacomparacoesheap<mediacomparacoesShell){
		printf("\n\nHEAP SORT e mais eficiente.");
	}
	else printf("\n\nSHELL SORT e mais eficiente.");
	//Declaração de vetores
	int vauxshell[500], vauxheap[500];	
	
	
	//MELHOR CASO 
	printf("\n\n\n\n\n\n\t\t\t\t<<<MELHOR CASO>>>\n\t\t\t\t\t\t\t\tQuando todos estao ordenados por ordem crescente.\n\n\n");
	//Para preencher usamos o segundo vetor da matriz ordenada, para nos facilitar , mas pode ser qualquer um vetor da matriz
	for(j=0;j<500;j++){
		vauxshell[j]=vetorauxheap[2][j];
		vauxheap[j]=vetorauxheap[2][j];	
	}
	int mccompshell=0,mctrcshell=0,mctmpshell=0,mccompheap=0,mctrcheap=0,mctmpheap=0;
	//ORDENAÇÃO PELO SHELL
	comeco=clock();
	Shellsort(vauxshell,tam, &mccompshell, &mctrcshell);
	fim=clock();
	mctmpshell=1000.0*(double)(fim-comeco)/CLOCKS_PER_SEC;
	//ORDENAÇÃO PELO HEAP
	comeco=clock();
	heapSort(vauxheap, tam,&mccompheap,&mctrcheap);
	fim=clock();
	mctmpheap=1000.0*(double)(fim-comeco)/CLOCKS_PER_SEC;
	printf("\n\n");
	printf("\n{");
	
	for(j=0;j<500;j++){
		if(j!=499){
				printf(" %i ,",vauxheap[j]);	
			}
			else{
				printf(" %i }",vauxheap[j]);	
			}	
	}
	printf("\n\n\t\t\t\t\t\tResultado das ordenacoes:");
	printf("\n\tPelo Shell: Realizaram-se %i comparacoes, %i trocas e o tempo gasto foi de %.3f ms.",mccompshell, mctrcshell, mctmpshell);
	printf("\n\tPelo Heap: Realizaram-se %i comparacoes, %i trocas e o tempo gasto foi de %.3f ms.\n",mccompheap, mctrcheap, mctmpheap);
	if(mccompheap<mccompshell){
		printf("\n\nHEAP SORT e mais eficiente.");
	}
	else printf("\n\nSHELL SORT e mais eficiente.");
	
	//PIOR CASO 
	printf("\n\n\n\n\n\n\t\t\t\t<<<<PIOR CASO>>>\n\t\t\t\t\t\t\t\tQuando todos estao ordenados por ordem decrescente.\n\n\n");
	//Para preencher usamos o segundo vetor da matriz ordenada, para nos facilitar , mas pode ser qualquer um
	int u=0;
	printf("\n{");
	for(j=499;j>=0;j--){
		vauxshell[u]=vetorauxheap[2][j];
		 vauxheap[u]=vetorauxheap[2][j];
		 u=u+1;
		if(j!=0){
				printf(" %i ,",vetorauxheap[2][j]);	
			}
			else{
				printf(" %i} ",vetorauxheap[2][j]);	
			}	
	}
	mccompshell=0,mctrcshell=0,mctmpshell=0,mccompheap=0,mctrcheap=0,mctmpheap=0;
	//ORDENAÇÃO PELO SHELL
	comeco=clock();
	Shellsort(vauxshell,tam, &mccompshell, &mctrcshell);
	fim=clock();
	mctmpshell=1000.0*(double)(fim-comeco)/CLOCKS_PER_SEC;
	//ORDENAÇÃO PELO HEAP
	comeco=clock();
	heapSort(vauxheap, tam,&mccompheap,&mctrcheap);
	fim=clock();
	mctmpheap=1000.0*(double)(fim-comeco)/CLOCKS_PER_SEC;
	printf("\n\n");
	printf("\n{");
	
	for(j=0;j<500;j++){
		if(j!=499){
				printf(" %i ,",vauxshell[j]);	
			}
			else{
				printf(" %i }",vauxshell[j]);	
			}	
	}
	printf("\n\n\t\t\t\t\t\tResultado das ordenacoes:");
	printf("\n\tPelo Shell: Realizaram-se %i comparacoes, %i trocas e o tempo gasto foi de %.3f ms.",mccompshell, mctrcshell, mctmpshell);
	printf("\n\tPelo Heap: Realizaram-se %i comparacoes, %i trocas e o tempo gasto foi de %.3f ms.\n",mccompheap, mctrcheap, mctmpheap);
	if(mccompheap<mccompshell){
		printf("\n\nHEAP SORT e mais eficiente.");
	}
	else printf("\n\nSHELL SORT e mais eficiente.");	
	
	return 0;
}

