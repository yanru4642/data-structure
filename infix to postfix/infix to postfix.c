//以後Todo:建立一個優先度二維陣列
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "stack.h"
#define MAX 100

bool isValid(char c);
bool isLegal(Stack* stack,char c);

int main(void) {
    Stack* stack = createStack(MAX);
    char readBuffer;
    
    printf("Infix to postfix using stack\n");
    printf("operators: + - * / %% ( )\n");
    printf("operands: single digit integer\n");
    printf("--------------------------------\n");
    printf("Input infix> ");
    int cnt=0;
    do {
        scanf("%c",&readBuffer);
        if(!cnt){
            printf("postfix: ");
            cnt++;
        }
        if(isValid(readBuffer)){
            if(!isdigit(readBuffer)&&!isalpha(readBuffer)){
                if(isEmpty(stack)){
                    push(stack, readBuffer);
                }else{
                    if(readBuffer=='('){
                        push(stack, readBuffer);
                    }else if(readBuffer==')'){
                        while (true) {
                            if(isEmpty(stack)){
                                break;
                            }
                            char temp=pop(stack);
                            if(temp=='('){
                                break;
                            }
                            printf("%c",temp);
                        }
                    }else if(((peek(stack)=='+'||peek(stack)=='-')&&(readBuffer=='*'||readBuffer=='/'||readBuffer=='%'))||peek(stack)=='('){
                        push(stack, readBuffer);
                    }else{
                        do {
                            printf("%c",pop(stack));
                        } while (!isLegal(stack, readBuffer));
                        push(stack, readBuffer);
                    }
                }
            }else{
                printf("%c",readBuffer);
            }
        }
        
    } while (readBuffer!='\n');
    while (!isEmpty(stack)) {
        printf("%c",pop(stack));
    }
    printf("\n");
    
    return 0;
}

bool isValid(char c){
    if(isdigit(c)||isalpha(c)){
        return true;
    }else{
        switch (c) {
            case '+':
            case '-':
            case '*':
            case '/':
            case '%':
            case '(':
            case ')':
                return true;
                break;
            default:
                return false;
                break;
        }
    }
}
bool isLegal(Stack* stack,char c){
    if(c=='+'||c=='-'){
        if(peek(stack)=='+'||peek(stack)=='-'||peek(stack)=='*'||peek(stack)=='/'||peek(stack)=='%'){
            return false;
        }
    }
    return true;
}
