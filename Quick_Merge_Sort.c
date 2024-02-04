#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Food {
    char name[50];
    double price;
};

// generate random food data with numerical prices
void generateRandomFood(struct Food array[], int size) {
    const char *foodNames[] = {"Burger", "Pizza", "Salad", "Pasta", "Sushi", "IceCream", "Fries", "Sandwich", "Steak", "Soup"};

    for (int i = 0; i < size; i++) {
        strcpy(array[i].name, foodNames[i]);
        array[i].price = ((double)rand() / RAND_MAX) * 100.0 + 50.0; 
    }
}

// Function to write food data to a file
void writeFoodToFile(struct Food array[], int size, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; i++) {
        fprintf(file, "%s %.2lf\n", array[i].name, array[i].price);
    }

    fclose(file);
}

// Function to read food data from a file
void readFoodFromFile(struct Food array[], int size, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; i++) {
        fscanf(file, "%s %lf", array[i].name, &array[i].price);
    }

    fclose(file);
}

// Function to perform Bubble Sort based on food prices
void bubbleSort(struct Food array[], int size) {
    int comparisons = 0;
    int swaps = 0;

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            comparisons++;
            if (array[j].price > array[j + 1].price) {
                // Swap the elements
                struct Food temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
                swaps++;
            }
        }
    }

    printf("Bubble Sort: Comparisons = %d, Swaps = %d\n", comparisons, swaps);
}

// Function to perform Merge Sort based on food prices
void merge(struct Food array[], int left, int mid, int right, int *comparisons, int *dataTransfers) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    struct Food leftArray[n1], rightArray[n2];

    // Copy data to temporary arrays leftArray[] and rightArray[]
    for (i = 0; i < n1; i++)
        leftArray[i] = array[left + i];
    for (j = 0; j < n2; j++)
        rightArray[j] = array[mid + 1 + j];

    // Merge the temporary arrays back into array[left..right]
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        (*comparisons)++;
        if (leftArray[i].price <= rightArray[j].price) {
            array[k] = leftArray[i];
            i++;
        } else {
            array[k] = rightArray[j];
            j++;
            (*dataTransfers)++;
        }
        k++;
    }

    // Copy the remaining elements of leftArray[], if there are any
    while (i < n1) {
        array[k] = leftArray[i];
        i++;
        k++;
        (*dataTransfers)++;
    }

    // Copy the remaining elements of rightArray[], if there are any
    while (j < n2) {
        array[k] = rightArray[j];
        j++;
        k++;
        (*dataTransfers)++;
    }
}

void mergeSort(struct Food array[], int left, int right, int *comparisons, int *dataTransfers) {
    if (left < right) {
        // Same as (left+right)/2, but avoids overflow for large left and right
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(array, left, mid, comparisons, dataTransfers);
        mergeSort(array, mid + 1, right, comparisons, dataTransfers);

        // Merge the sorted halves
        merge(array, left, mid, right, comparisons, dataTransfers);
    }
}

// Function to partition the array for quicksort
int partition(struct Food array[], int low, int high, int *comparisons, int *dataTransfers) {
    double pivot = array[high].price;
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        (*comparisons)++;
        if (array[j].price < pivot) {
            i++;
            // Swap the elements
            struct Food temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            (*dataTransfers)++;
        }
    }

    // Swap the pivot element with the element at (i + 1)
    struct Food temp = array[i + 1];
    array[i + 1] = array[high];
    array[high] = temp;
    (*dataTransfers)++;

    return i + 1;
}

// Function to perform Quicksort based on food prices
void quickSort(struct Food array[], int low, int high, int *comparisons, int *dataTransfers) {
    if (low < high) {
        // Find the partitioning index
        int pi = partition(array, low, high, comparisons, dataTransfers);

        // Recursively sort the elements before and after the partition
        quickSort(array, low, pi - 1, comparisons, dataTransfers);
        quickSort(array, pi + 1, high, comparisons, dataTransfers);
    }
}

// Function to display the menu
void displayMenu(struct Food array[], int size) {
    printf("Menu:\n");
    for (int i = 0; i < size; i++) {
        printf("%s - %.2lf\n", array[i].name, array[i].price);
    }
    printf("\n");
}

int main() {
    const int size = 10;
    struct Food menu[size];

    generateRandomFood(menu, size);

    writeFoodToFile(menu, size, "menu.txt");

    readFoodFromFile(menu, size, "menu.txt");

    printf("Unsorted Menu:\n");
    displayMenu(menu, size);

    // Bubble Sort based on food prices
    bubbleSort(menu, size);
    printf("\nMenu after Bubble Sort:\n");
    displayMenu(menu, size);

    readFoodFromFile(menu, size, "menu.txt");

    // Merge Sort based on food prices
    int comparisonsMerge = 0;
    int dataTransfersMerge = 0;
    mergeSort(menu, 0, size - 1, &comparisonsMerge, &dataTransfersMerge);
    printf("\nMenu after Merge Sort:\n");
    displayMenu(menu, size);
    printf("Merge Sort: Comparisons = %d, Data Transfers = %d\n", comparisonsMerge, dataTransfersMerge);

    // Read food data from the file again to restore unsorted menu
    readFoodFromFile(menu, size, "menu.txt");

    // Quicksort based on food prices
    int comparisonsQuick = 0;
    int dataTransfersQuick = 0;
    quickSort(menu, 0, size - 1, &comparisonsQuick, &dataTransfersQuick);
    printf("\nMenu after Quick Sort:\n");
    displayMenu(menu, size);
    printf("Quick Sort: Comparisons = %d, Data Transfers = %d\n", comparisonsQuick, dataTransfersQuick);

    return 0;
}

