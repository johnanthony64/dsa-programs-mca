#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for an order
typedef struct Order {
    char food_name[20];
    char order_details[100];
    struct Order* next;
} Order;

// Structure for a linear queue
typedef struct LinearQueue {
    Order* front;
    Order* rear;
} LinearQueue;

// Structure for a priority queue
typedef struct PriorityQueue {
    Order* front;
} PriorityQueue;

// Structure for a deque
typedef struct Deque {
    Order* front;
    Order* rear;
} Deque;

// Function to create a new order
Order* createOrder(char food_name[20], char order_details[100]) {
    Order* new_order = (Order*)malloc(sizeof(Order));
    strcpy(new_order->food_name, food_name);
    strcpy(new_order->order_details, order_details);
    new_order->next = NULL;

    return new_order;
}

// Function to enqueue an order in a linear queue
void enqueueLinear(LinearQueue* queue, char food_name[20], char order_details[100]) {
    Order* new_order = createOrder(food_name, order_details);

    if (queue->rear == NULL) {
        queue->front = new_order;
        queue->rear = new_order;
    } else {
        queue->rear->next = new_order;
        queue->rear = new_order;
    }

    printf("Order enqueued successfully in the linear queue!\n");
}

// Function to dequeue an order from a linear queue
void dequeueLinear(LinearQueue* queue) {
    if (queue->front == NULL) {
        printf("Linear queue is empty. No order to dequeue.\n");
        return;
    }

    Order* temp = queue->front;
    queue->front = queue->front->next;

    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(temp);
    printf("Order dequeued successfully from the linear queue!\n");
}

// Function to enqueue an order in a priority queue
void enqueuePriority(PriorityQueue* queue, char food_name[20], char order_details[100]) {
    Order* new_order = createOrder(food_name, order_details);

    if (queue->front == NULL) {
        queue->front = new_order;
    } else {
        if (strcmp(new_order->food_name, queue->front->food_name) < 0) {
            new_order->next = queue->front;
            queue->front = new_order;
        } else {
            Order* current = queue->front;
            while (current->next != NULL && strcmp(new_order->food_name, current->next->food_name) >= 0) {
                current = current->next;
            }
            new_order->next = current->next;
            current->next = new_order;
        }
    }

    printf("Order enqueued successfully in the priority queue!\n");
}

// Function to dequeue an order from a priority queue
void dequeuePriority(PriorityQueue* queue) {
    if (queue->front == NULL) {
        printf("Priority queue is empty. No order to dequeue.\n");
        return;
    }

    Order* temp = queue->front;
    queue->front = queue->front->next;

    free(temp);
    printf("Order dequeued successfully from the priority queue!\n");
}

// Function to enqueue an order at the front of a deque
void enqueueFront(Deque* deque, char food_name[20], char order_details[100]) {
    Order* new_order = createOrder(food_name, order_details);

    if (deque->front == NULL) {
        deque->front = new_order;
        deque->rear = new_order;
    } else {
        new_order->next = deque->front;
        deque->front = new_order;
    }

    printf("Order enqueued successfully at the front of the deque!\n");
}

// Function to enqueue an order at the rear of a deque
void enqueueRear(Deque* deque, char food_name[20], char order_details[100]) {
    Order* new_order = createOrder(food_name, order_details);

    if (deque->rear == NULL) {
        deque->front = new_order;
        deque->rear = new_order;
    } else {
        deque->rear->next = new_order;
        deque->rear = new_order;
    }

    printf("Order enqueued successfully at the rear of the deque!\n");
}

// Function to remove an order from the front of a deque
void dequeueFront(Deque* deque) {
    if (deque->front == NULL) {
        printf("Deque is empty. No order to dequeue.\n");
        return;
    }

    Order* temp = deque->front;
    deque->front = deque->front->next;

    free(temp);
    printf("Order dequeued successfully from the front of the deque!\n");
}

// Function to remove an order from the rear of a deque
void dequeueRear(Deque* deque) {
    if (deque->rear == NULL) {
        printf("Deque is empty. No order to dequeue.\n");
        return;
    }

    Order* temp = deque->rear;
    Order* current = deque->front;

    while (current->next != deque->rear) {
        current = current->next;
    }

    deque->rear = current;
    deque->rear->next = NULL;

    free(temp);
    printf("Order dequeued successfully from the rear of the deque!\n");
}

// Function to display the current orders in a queue
void displayQueue(Order* front) {
    if (front == NULL) {
        printf("Queue is empty.\n");
        return;
    }

    Order* current = front;
    printf("Orders in the queue:\n");

    while (current != NULL) {
        printf("Food Name: %s\n", current->food_name);
        printf("Order Details: %s\n", current->order_details);
        printf("------------------------\n");
        current = current->next;
    }
}

int main() {
    LinearQueue linear_queue;
    linear_queue.front = NULL;
    linear_queue.rear = NULL;

    PriorityQueue priority_queue;
    priority_queue.front = NULL;

    Deque deque;
    deque.front = NULL;
    deque.rear = NULL;

    int choice;
    char food_name[20];
    char order_details[100];

    do {
        printf("\n----- Food Ordering System -----\n");
        printf("1. Enqueue in Linear Queue\n");
        printf("2. Dequeue from Linear Queue\n");
        printf("3. Enqueue in Priority Queue\n");
        printf("4. Dequeue from Priority Queue\n");
        printf("5. Enqueue at the Front of Deque\n");
        printf("6. Enqueue at the Rear of Deque\n");
        printf("7. Dequeue from the Front of Deque\n");
        printf("8. Dequeue from the Rear of Deque\n");
        printf("9. Display Orders in a Queue\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the food name: ");
                scanf("%s", food_name);
                printf("Enter the order details: ");
                scanf(" %[^\n]s", order_details);
                enqueueLinear(&linear_queue, food_name, order_details);
                break;
            case 2:
                dequeueLinear(&linear_queue);
                break;
            case 3:
                printf("Enter the food name: ");
                scanf("%s", food_name);
                printf("Enter the order details: ");
                scanf(" %[^\n]s", order_details);
                enqueuePriority(&priority_queue, food_name, order_details);
                break;
            case 4:
                dequeuePriority(&priority_queue);
                break;
            case 5:
                printf("Enter the food name: ");
                scanf("%s", food_name);
                printf("Enter the order details: ");
                scanf(" %[^\n]s", order_details);
                enqueueFront(&deque, food_name, order_details);
                break;
            case 6:
                printf("Enter the food name: ");
                scanf("%s", food_name);
                printf("Enter the order details: ");
                scanf(" %[^\n]s", order_details);
                enqueueRear(&deque, food_name, order_details);
                break;
            case 7:
                dequeueFront(&deque);
                break;
            case 8:
                dequeueRear(&deque);
                break;
            case 9:
                printf("Choose a queue to display:\n");
                printf("1. Linear Queue\n");
                printf("2. Priority Queue\n");
                printf("3. Deque\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);

                switch (choice) {
                    case 1:
                        displayQueue(linear_queue.front);
                        break;
                    case 2:
                        displayQueue(priority_queue.front);
                        break;
                    case 3:
                        displayQueue(deque.front);
                        break;
                    default:
                        printf("Invalid choice.\n");
                        break;
                }
                break;
            case 0:
                printf("Exiting the program. Goodbye!\n");
                break;			
            default:
                printf("Invalid choice.\n");
                break;
        }
    } while (choice != 0);

    return 0;
}

