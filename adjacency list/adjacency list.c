#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


//graph
typedef struct Node* Node_ptr;
typedef struct Node {
    int vertex;
    Node_ptr next;
}Node;
Node_ptr NewNode(int vertex);
void InsertNode(Node_ptr vertex, int value);
void Show(Node_ptr* graph, int MAX_VERTICES);
void DFS(Node_ptr* graph, int* visited, int start);
void BFS(Node_ptr* graph, int* visited, int start, int MAX_VERTICES);
void SortList(int* list, int VERTICES_SIZE);

//queue
typedef struct {
    int capacity; //max size
    int front; //preceding index of the first data
    int rear; //index of the last data
    int* elements;
}Queue;
Queue* createQueue(int MAX_SIZE);
Queue* deleteQueue(Queue* queue_p);
bool isEmpty(Queue* queue_p);
bool isFull(Queue* queue_p);
void enqueue(Queue* queue_p, int element);
int dequeue(Queue* queue_p);


int main(void) {
    Node_ptr* graph;
    int MAX_VERTICES;

    //Input the number of vertices
    printf("Enter the number of vertices> ");
    while (scanf("%d", &MAX_VERTICES) != 1 || MAX_VERTICES < 1) {
        //clear buffer
        while (getchar() != '\n');
        printf("Bad input. Enter again.\n");
        printf("Enter the number of vertices> ");
    }
    while (getchar() != '\n');


    //Initialize the graph
    graph = (Node_ptr*)malloc(sizeof(Node_ptr) * MAX_VERTICES);
    for (int i = 0; i < MAX_VERTICES; i++) {
        graph[i] = NewNode(i);
    }


    //input the graph
    for (int i = 0; i < MAX_VERTICES; i++) {
        int VERTICES_SIZE = 0;
        int buffer;
        int* verticesList = (int*)malloc(sizeof(int) * MAX_VERTICES);
        if (!verticesList) {
            exit(1);
        }
        //read vertices
        printf("-----------------------------------------\n");
        printf("Enter vertices that Vertex %d connects to.\n", i);
        printf("vertices' No.(-1 to escape)> ");
        while (VERTICES_SIZE < MAX_VERTICES) {
            while (scanf("%d", &buffer) != 1 || buffer < -1 || buffer >= MAX_VERTICES) {
                //clear buffer
                while (getchar() != '\n');
                printf("Bad input. Enter again.\n");
                printf("Enter vertices' No.(-1 to escape)> ");
            }
            if (buffer == -1) {
                break;
            }
            verticesList[VERTICES_SIZE] = buffer;
            VERTICES_SIZE++;
        }
        while (getchar() != '\n');
        //sort list
        SortList(verticesList, VERTICES_SIZE);
        //insert it into that vertex
        for (int j = 0; j < VERTICES_SIZE; j++) {
            InsertNode(graph[i], verticesList[j]);
        }
        free(verticesList);
    }


    //show the graph
    printf("\n=========== Adjacency Lists ===========\n");
    Show(graph, MAX_VERTICES);


    //depth first search
    int startVertex;
    int* visited = (int*)malloc(sizeof(int) * MAX_VERTICES);
    if (!visited) {
        exit(1);
    }
    for (int i = 0; i < MAX_VERTICES; i++) {
        visited[i] = 0;
    }
    printf("\n========= Depth First Search =========\n");
    printf("Which vertex do you want to start> ");
    while (scanf("%d", &startVertex) != 1 || startVertex < 0 || startVertex >= MAX_VERTICES) {
        //clear buffer
        while (getchar() != '\n');
        printf("Bad input. Enter again.\n");
    }

    printf("DFS: [ ");
    DFS(graph, visited, startVertex);
    //remain vertex
    for (int i = 0; i < MAX_VERTICES; i++) {
        if (!visited[i]) {
            DFS(graph, visited, i);
        }
    }
    printf("]\n");


    //breadth first search
    for (int i = 0; i < MAX_VERTICES; i++) {
        visited[i] = 0;
    }
    printf("\n======== Breadth First Search ========\n");
    printf("Which vertex do you want to start> ");
    while (scanf("%d", &startVertex) != 1 || startVertex < 0 || startVertex >= MAX_VERTICES) {
        //clear buffer
        while (getchar() != '\n');
        printf("Bad input. Enter again.\n");
    }

    printf("BFS: [ ");
    BFS(graph, visited, startVertex, MAX_VERTICES);
    //remain vertex
    for (int i = 0; i < MAX_VERTICES; i++) {
        if (!visited[i]) {
            BFS(graph, visited, i, MAX_VERTICES);
        }
    }
    printf("]\n");


    free(visited);
    free(graph);
    return 0;
}




//graph implementation
Node_ptr NewNode(int vertex) {
    Node_ptr temp = (Node_ptr)(malloc(sizeof(Node)));
    if (!temp) {
        exit(1);
    }
    temp->vertex = vertex;
    temp->next = NULL;
    return temp;
}

void InsertNode(Node_ptr vertex, int value) {
    //create new node
    Node_ptr temp = NewNode(value);
    //the vertex node points to a new node
    temp->next = vertex->next;
    vertex->next = temp;
}

void Show(Node_ptr* graph, int MAX_VERTICES) {
    for (int i = 0; i < MAX_VERTICES; i++) {
        printf("vertex%2d: ", graph[i]->vertex);
        Node_ptr tempVertex = graph[i]->next;
        for (; tempVertex; tempVertex = tempVertex->next) {
            if (!tempVertex) {
                break;
            }
            printf("%-2d ", tempVertex->vertex);
        }
        printf("\n");
    }
}

void DFS(Node_ptr* graph, int* visited, int start) {
    visited[start] = 1;
    printf("%d ", graph[start]->vertex);

    for (Node_ptr temp = graph[start]->next; temp; temp = temp->next) {
        if (!visited[temp->vertex]) {
            DFS(graph, visited, temp->vertex);
        }

    }
}

void BFS(Node_ptr* graph, int* visited, int start, int MAX_VERTICES) {
    Queue* queue = createQueue(MAX_VERTICES * 2);
    visited[start] = 1;
    printf("%d ", graph[start]->vertex);
    enqueue(queue, start);
    while (!isEmpty(queue)) {
        int visiting = dequeue(queue);
        for (Node_ptr temp = graph[visiting]->next; temp; temp = temp->next) {
            if (!visited[temp->vertex]) {
                visited[temp->vertex] = 1;
                printf("%d ", temp->vertex);
                enqueue(queue, temp->vertex);
            }
        }
    }
    deleteQueue(queue);
}

void SortList(int* list, int VERTICES_SIZE) {
    for (int i = 0; i < VERTICES_SIZE; i++) {
        for (int j = i; j < VERTICES_SIZE; j++) {
            if (list[j] > list[i]) {
                int temp = list[j];
                list[j] = list[i];
                list[i] = temp;
            }
        }
    }
}




//queue implementation
Queue* createQueue(int MAX_SIZE) {
    Queue* temp = (Queue*)malloc(sizeof(Queue));
    if (!temp) {
        exit(1);
    }
    temp->capacity = MAX_SIZE;
    temp->front = 0;
    temp->rear = 0;
    temp->elements = (int*)malloc(temp->capacity * sizeof(int));
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
    return queue_p->front == (queue_p->rear + 1) % queue_p->capacity;
}

void enqueue(Queue* queue_p, int element) {
    if (isFull(queue_p)) {
        printf("Queue is full\n");
        return;
    }
    else {
        queue_p->rear = (queue_p->rear + 1) % queue_p->capacity;
        queue_p->elements[queue_p->rear] = element;
    }
}

int dequeue(Queue* queue_p) {
    if (isEmpty(queue_p)) {
        printf("Queue is empty\n");
        return 0;
    }
    else {
        queue_p->front = (queue_p->front + 1) % queue_p->capacity;
        return queue_p->elements[queue_p->front];
    }
}
