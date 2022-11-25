#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
    int* ptr;
    ptr=malloc(sizeof(int));
    
    printf("Enter an integer> ");
    scanf("%d",ptr);
    printf("%d\n",*ptr);
    
    free(ptr);
    return 0;
}
