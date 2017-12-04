 #include <time.h>
#include <stdlib.h>

void resetRand(){
    srand((unsigned)time(NULL));
}

int aleatorio(int n){
    return rand() % n +1;

}
