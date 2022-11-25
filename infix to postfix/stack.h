#ifndef stack_h
#define stack_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
typedef struct {
    int capacity; //max size of stack
    int top;
    char* elements;
}Stack;
//Stack function prototype
Stack* createStack(int MAX_SIZE);
Stack* deleteStack(Stack* stack_p);
bool isEmpty(Stack* stack_p);
bool isFull(Stack* stack_p);
void doubleCapacity(Stack* stack_p);
void push(Stack* stack_p, char element);
char pop(Stack* stack_p);
char peek(Stack* stack_p);
void show(Stack* stack_p);

#endif /* stack_h */
