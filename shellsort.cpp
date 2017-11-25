#include "shellsort.h"
#include <unistd.h>

ShellSort::ShellSort(QObject *parent) : QObject(parent)
{

}

void ShellSort::shellsort(int *vet, int n){
    int h = 1;
    int i, j, chave;

    do{
        h = 3*h + 1;
    }while(h < n);

    do{
        h /= 3;
        for(i = h; i < n; i++){
            chave = vet[i];
            j = i;
            while(j >= h && vet[j - h] > chave){
                vet[j] = vet[j - h];
                j -= h;
            }
                vet[j] = chave;
        }
        emit update();
        usleep(2000);
        //pvet(vet, n); 	//Printa o vetor após cada passo
    }while(h != 1);
}
