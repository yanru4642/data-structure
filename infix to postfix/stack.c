#include "stack.h"
//Stack function implementation
Stack* createStack(int MAX_SIZE) {
    Stack* stack_p = (Stack*)malloc(sizeof(Stack));
    stack_p->capacity = MAX_SIZE;
    stack_p->top = -1;
    stack_p->elements = (char*)malloc(MAX_SIZE * sizeof(char));
    return stack_p;
}
Stack* deleteStack(Stack* stack_p) {
    free(stack_p->elements);
    free(stack_p);
    return NULL;
}
bool isEmpty(Stack* stack_p) {
    return stack_p->top == -1;
}
bool isFull(Stack* stack_p) {
    return stack_p->top == stack_p->capacity - 1;
}
void doubleCapacity(Stack* stack_p) {
    stack_p->capacity *= 2;
    char* newElements = (char*)malloc(stack_p->capacity * sizeof(char));
    //deep copy
    for (int i = 0; i <= stack_p->top; i++) {
        newElements[i] = stack_p->elements[i];
    }
    free(stack_p->elements);
    stack_p->elements = newElements;
}
void push(Stack* stack_p, char element) {
    if (isFull(stack_p)) {
        printf("stack full! doubling capacity...\n");
        doubleCapacity(stack_p);
    }
    stack_p->top++;
    stack_p->elements[stack_p->top] = element;
    
}
char pop(Stack* stack_p) {
    if (isEmpty(stack_p)) {
        printf("stack is empty!");
        return 0;
    }
    else {
        char element = stack_p->elements[stack_p->top];
        stack_p->top--;
        return element;
    }
}
char peek(Stack* stack_p){
    char element = stack_p->elements[stack_p->top];
    return element;
}
void show(Stack* stack_p) {
    printf("Stack: ");
    if (isEmpty(stack_p)) {
        printf("empty\n");
    }
    else {
        for (int i = 0; i <= stack_p->top; i++) {
            printf("%c ", stack_p->elements[i]);
        }
        printf("\n");
    }
}
