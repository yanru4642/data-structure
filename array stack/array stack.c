#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
typedef struct {
    int capacity; //max size of stack
    int top;
    int* elements;
}Stack;
//Stack function prototype
Stack* createStack(int MAX_SIZE);
Stack* deleteStack(Stack* stack_p);
bool isEmpty(Stack* stack_p);
bool isFull(Stack* stack_p);
void doubleCapacity(Stack* stack_p);
void push(Stack* stack_p, int element);
int pop(Stack* stack_p);
void show(Stack* stack_p);
//main
int main(void) {
    int MAX_SIZE;
    printf("Enter capacity of stack> ");
    scanf("%d", &MAX_SIZE);
    Stack* stack1 = createStack(MAX_SIZE);
    printf("capacity%d top%d empty?%d full?%d\n", stack1->capacity, stack1->top, isEmpty(stack1), isFull(stack1));
    //test stack
    char status;
    char trash;
    do {
        printf("Enter command(i:Push o:Pop x:Exit)> ");
        //clear buffer
        do {
            scanf("%c", &trash);
        } while (trash != '\n');

        do {
            scanf("%c", &status);
        } while (!isalpha(status));
        switch (status) {
        case 'i':
            printf("Enter an integer> ");
            int number;
            scanf("%d", &number);
            push(stack1, number);
            show(stack1);
            printf("(top%d capacity%d)\n", stack1->top, stack1->capacity);
            break;
        case 'o':
            if (!isEmpty(stack1)) {
                printf("%d\n", pop(stack1));
            }
            show(stack1);
            printf("(top%d capacity%d)\n", stack1->top, stack1->capacity);
            break;
        default:
            break;
        }
        printf("--------------------------------------------------------\n");
    } while (status != 'x');
    stack1 = deleteStack(stack1);
    free(stack1);
    printf("stack1 deleted\n");
    return 0;
}
//Stack function implementation
Stack* createStack(int MAX_SIZE) {
    Stack* stack_p = (Stack*)malloc(sizeof(Stack));
    stack_p->capacity = MAX_SIZE;
    stack_p->top = -1;
    stack_p->elements = (int*)malloc(MAX_SIZE * sizeof(int));
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
    int* newElements = (int*)malloc(stack_p->capacity * sizeof(int));
    //deep copy
    for (int i = 0; i <= stack_p->top; i++) {
        newElements[i] = stack_p->elements[i];
    }
    free(stack_p->elements);
    stack_p->elements = newElements;
}
void push(Stack* stack_p, int element) {
    if (isFull(stack_p)) {
        printf("stack full! doubling capacity...\n");
        doubleCapacity(stack_p);
    }
    stack_p->top++;
    stack_p->elements[stack_p->top] = element;

}
int pop(Stack* stack_p) {
    if (isEmpty(stack_p)) {
        printf("stack is empty!");
        return NULL;
    }
    else {
        int element = stack_p->elements[stack_p->top];
        stack_p->top--;
        return element;
    }
}
void show(Stack* stack_p) {
    printf("Stack: ");
    if (isEmpty(stack_p)) {
        printf("empty\n");
    }
    else {
        for (int i = 0; i <= stack_p->top; i++) {
            printf("%d ", stack_p->elements[i]);
        }
        printf("\n");
    }
}