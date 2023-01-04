#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
typedef struct {
    int capacity; //max size
    int front; //preceding index of the first data
    int rear; //index of the last data
    int* elements;
}Queue;
//Queue function prototype
Queue* createQueue(int MAX_SIZE);
Queue* deleteQueue(Queue* queue_p);
bool isEmpty(Queue* queue_p);
bool isFull(Queue* queue_p);
void enqueue(Queue* queue_p, int element);
int dequeue(Queue* queue_p);
void show(Queue* queue_p);
//main
int main(void){
    Queue* queue1;
    int MAX_SIZE;
    printf("Enter capacity of queue(circular queue wastes one space)> ");
    scanf("%d", &MAX_SIZE);
    queue1 = createQueue(MAX_SIZE);
    printf("capacity%d front%d rear%d empty?%d full?%d\n", queue1->capacity, queue1->front,queue1->rear,isEmpty(queue1), isFull(queue1));
    //test
    char status;
    char trash;
    do {
        printf("Enter command(e:Enqueue d:Dequeue x:Exit)> ");
        //clear buffer
        do {
            scanf("%c", &trash);
        } while (trash != '\n');
        
        do {
            scanf("%c", &status);
        } while (!isalpha(status));
        switch (status) {
            case 'e':
                printf("Enter an integer> ");
                int number;
                scanf("%d", &number);
                enqueue(queue1, number);
                show(queue1);
                printf("(front%d rear%d capacity%d)\n", queue1->front, queue1->rear, queue1->capacity);
                break;
            case 'd':
                if (!isEmpty(queue1)) {
                    printf("%d\n", dequeue(queue1));
                }
                show(queue1);
                printf("(front%d rear%d capacity%d)\n", queue1->front, queue1->rear, queue1->capacity);
                break;
            default:
                break;
        }
        printf("--------------------------------------------------------\n");
    } while (status != 'x');
    queue1 = deleteQueue(queue1);
    free(queue1);
    printf("queue1 deleted\n");
    return 0;
}
//function implementation
Queue* createQueue(int MAX_SIZE) {
    Queue* temp = (Queue*)malloc(sizeof(Queue));
    temp->capacity = MAX_SIZE;
    temp->front = 0;
    temp->rear = 0;
    temp->elements = (int*)malloc(temp->capacity*sizeof(int));
    return temp;
}
Queue* deleteQueue(Queue* queue_p) {
    free(queue_p->elements);
    free(queue_p);
    return NULL;
}
bool isEmpty(Queue* queue_p) {
    return queue_p->front == queue_p->rear;
}
bool isFull(Queue* queue_p) {
    return queue_p->front == (queue_p->rear+1) % queue_p->capacity;
}
void enqueue(Queue* queue_p, int element) {
    if (isFull(queue_p)){
        printf("Queue is full\n");
        return;
    }else{
        queue_p->rear=(queue_p->rear+1)%queue_p->capacity;
        queue_p->elements[queue_p->rear] = element;
    }
}
int dequeue(Queue* queue_p) {
    if (isEmpty(queue_p)) {
        printf("Queue is empty\n");
        return 0;
    }else{
        queue_p->front=(queue_p->front+1)%queue_p->capacity;
        return queue_p->elements[queue_p->front];
    }
}
void show(Queue* queue_p) {
    printf("Queue: ");
    if (isEmpty(queue_p)) {
        printf("empty\n");
    }else{
        //calculate size
        int size = queue_p->rear - queue_p->front;
        if (size<0){
            //front is bigger than rear
            size += queue_p->capacity;
        }
        //print queue
        for (int i=0; i<size; i++){
            int idx = (queue_p->front+1+i) % queue_p->capacity;
            printf("%d ", queue_p->elements[idx]);
        }
        printf("\n");
    }
}
