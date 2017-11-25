#include <cstdlib>
#include <cstdio>

void merge(int *A, int p, int q, int r){
        int i, j, k;
        int n1 = q - p +1;
        int n2 = r - q;

        int *L = (int*) malloc(sizeof(int) * (n1 + 1));
        int *R = (int*) malloc(sizeof(int) * (n2 + 1));


        for(i = 0; i < n1; i++){
                L[i] = A[p + i];
        }

        for(j = 0; j < n2; j++, i++){
                R[j] = A[p + i];
        }

        L[n1] = INT_MAX;
        R[n2] = INT_MAX;
        i = 0;
        j = 0;

        for(k = p; k <= r; k++){
                if(L[i] < R[j]){
                        A[k] = L[i];
                        i++;
                }else{
                        A[k] = R[j];
                        j++;
                }
        }
}

void mergeSort(int *A, int p, int r){
        int q;

        if(p < r){
                q = (p + r)/2;
                mergeSort(A, p, q);
                mergeSort(A, q+1, r);
                merge(A, p, q, r);
                //for(i = 0; i <= r; i++)
                  //      printf("%d ", A[i]);
                //printf("\n");
        }

}
