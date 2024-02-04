#include <stdio.h>
#include <stdlib.h>

struct foodNode {
    struct foodNode *prev;
    struct foodNode *next;
    char itemName[50]; 
    float price;
};

struct foodNode *head;

void addFoodItem();
void removeFoodItem();
void displayMenu();
void searchItem();
void mainMenu();

int main() {
    int choice = 0;

    while (choice != 6) {
        mainMenu();
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addFoodItem();
                break;
            case 2:
                removeFoodItem();
                break;
            case 3:
                displayMenu();
                break;
            case 4:
                searchItem();
                break;
            case 5:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Please enter a valid choice.\n");
        }
    }

    return 0;
}

void mainMenu() {
    printf("\n*********Food Ordering System*********\n");
    printf("Choose one option from the following list ...\n");
    printf("===============================================\n");
    printf("1. Add Food Item\n");
    printf("2. Remove Food Item\n");
    printf("3. Display Menu\n");
    printf("4. Search for an Item\n");
    printf("5. Exit\n");
}

void addFoodItem() {
    struct foodNode *ptr;
    ptr = (struct foodNode *)malloc(sizeof(struct foodNode));

    if (ptr == NULL) {
        printf("\nOVERFLOW\n");
    } else {
        printf("\nEnter food item name: ");
        scanf("%s", ptr->itemName);
        printf("Enter price: ");
        scanf("%f", &ptr->price);

        ptr->next = head;
        ptr->prev = NULL;

        if (head != NULL) {
            head->prev = ptr;
        }

        head = ptr;

        printf("\nFood item added to the menu\n");
    }
}

void removeFoodItem() {
    struct foodNode *ptr, *prev;
    char itemName[50];

    if (head == NULL) {
        printf("Menu is empty\n");
        return;
    }

    printf("\nEnter the item name you want to remove: ");
    scanf("%s", itemName);

    ptr = head;
    prev = NULL;
    while (ptr != NULL) {
        if (strcmp(ptr->itemName, itemName) == 0) {
            if (prev == NULL) {
            
                head = ptr->next;
                if (head != NULL) {
                    head->prev = NULL;
                }
            } else {
                prev->next = ptr->next;
                if (ptr->next != NULL) {
                    ptr->next->prev = prev;
                }
            }
           free(ptr); 
            printf("Item removed from the menu\n");
            return;
        }

        prev = ptr;
        ptr = ptr->next;
    }

    printf("Item not found\n");
}


void displayMenu() {
    struct foodNode *ptr;
    ptr = head;

    if (ptr == NULL) {
        printf("Menu is empty\n");
    } else {
        printf("\n************ Menu ************\n");
        while (ptr != NULL) {
            printf("%s - %.2f\n", ptr->itemName, ptr->price);
            ptr = ptr->next;
        }
    }
}

void searchItem() {
    struct foodNode *ptr;
    char itemName[50];
    int flag = 1;

    ptr = head;

    if (ptr == NULL) {
        printf("\nMenu is empty\n");
    } else {
        printf("\nEnter the item name you want to search: ");
        scanf("%s", itemName);

        while (ptr != NULL) {
            if (strcmp(ptr->itemName, itemName) == 0) {
                printf("Item found - %s (%.2f)\n", ptr->itemName, ptr->price);
                flag = 0;
                break;
            }
            ptr = ptr->next;
        }

        if (flag == 1) {
            printf("Item not found\n");
        }
    }
}

