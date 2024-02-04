#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    char name[20];
    int price;
} FoodItem;

int linearSearch(FoodItem arr[], int n, char* key);
int sentinelSearch(FoodItem arr[], int n, char* key);
int binarySearch(FoodItem arr[], int low, int high, char* key);
void bubbleSort(FoodItem arr[], int n);
void insertionSort(FoodItem arr[], int n);
void displayMenu(FoodItem menu[], int size);

int main() {
    FoodItem menu[] = {
        {"Pizza", 150},
        {"Burger", 100},
        {"Fries", 50},
        {"Coke", 30}
    };

    int size = sizeof(menu) / sizeof(FoodItem);

    int choice, comparisons;
    char key[20];

    do {
        printf("\nMenu:\n");
        printf("1. Display Menu\n");
        printf("2. Linear Search\n");
        printf("3. Sentinel Search\n");
        printf("4. Bubble Sort\n");
        printf("5. Insertion Sort\n");
        printf("6. Binary Search\n");
        printf("0. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayMenu(menu, size);
                break;

            case 2:
                printf("Enter item name to search: ");
                scanf("%s", key);
                comparisons = linearSearch(menu, size, key);
                printf("Total comparisons for linear search: %d\n", comparisons);
                break;

            case 3:
                printf("Enter item name to search: ");
                scanf("%s", key);
                comparisons = sentinelSearch(menu, size, key);
                printf("Total comparisons for sentinel search: %d\n", comparisons);
                break;

            case 4:
                bubbleSort(menu, size);
                printf("Menu after Bubble Sort:\n");
                displayMenu(menu, size);
                break;

            case 5:
                insertionSort(menu, size);
                printf("Menu after Insertion Sort:\n");
                displayMenu(menu, size);
                break;

            case 6:
                printf("Enter item name to search: ");
                scanf("%s", key);
                comparisons = binarySearch(menu, 0, size - 1, key);
                printf("Total comparisons for binary search: %d\n", comparisons);
                break;

            case 0:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid option!\n");
        }

    } while (choice != 0);

    return 0;
}

void displayMenu(FoodItem menu[], int size) {
    printf("Food Menu\n");

    for (int i = 0; i < size; i++)
        printf("%s %d\n", menu[i].name, menu[i].price);
}

// Linear search
int linearSearch(FoodItem arr[], int n, char* key) {
    for (int i = 0; i < n; i++) {
        if (strcmp(arr[i].name, key) == 0) {
            printf("Item found at index %d\n", i);
            return i + 1; 
        }
    }
    printf("Item not found\n");
    return n;  
}

// Sentinel search
int sentinelSearch(FoodItem arr[], int n, char* key) {
    int lastPrice = arr[n - 1].price;
    strcpy(arr[n - 1].name, key);

    int i = 0;
    while (strcmp(arr[i].name, key) != 0) {
        i++;
    }

    arr[n - 1].price = lastPrice;

    if (i < n - 1 || strcmp(arr[n - 1].name, key) == 0) {
        printf("Item found at index %d\n", i);
        return i + 1;
    }

    printf("Item not found\n");
    return i + 1;
}

// Binary search
int binarySearch(FoodItem arr[], int low, int high, char* key) {
    int comparisons = 0;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        comparisons++;

        int compareResult = strcmp(arr[mid].name, key);

        if (compareResult == 0) {
            printf("Item found at index %d\n", mid);
            return comparisons;
        }

        if (compareResult < 0) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    printf("Item not found\n");
    return comparisons;
}

// Bubble sort
void bubbleSort(FoodItem arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(arr[j].name, arr[j + 1].name) > 0) {
                FoodItem temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Insertion sort
void insertionSort(FoodItem arr[], int n) {
    int i, j;
    FoodItem key;

    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && strcmp(arr[j].name, key.name) > 0) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }

        arr[j + 1] = key;
    }
}

