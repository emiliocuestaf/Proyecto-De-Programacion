#include <stdio.h>

int caracola (int a, int b, int carraca[2]){
    carraca[0] = a*b;
    carraca[1] = a+b;
    
    return 1;
}

int main(){
    int quetal[2];
    quetal[1] = 5;
    quetal[0] = 10;
    caracola(2,3, quetal);
    printf("%d %d", quetal[0], quetal[1]);
    printf("%c", '░');
    return 1;
}