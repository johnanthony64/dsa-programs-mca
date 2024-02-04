#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 100
#define MAX_ATTRIBUTES 4

struct FoodItem {
    int itemID;
    char name[50];
    float price;
    int quantity;
};

// Insert
void insertFoodItem(struct FoodItem menu[][MAX_ATTRIBUTES], int *numItems) {
	if (*numItems < MAX_ITEMS) {
		struct FoodItem newItem;
		printf("Enter the item ID: ");
        scanf("%d", &newItem.itemID);
        printf("Enter the item name: ");
        scanf("%s", newItem.name);
        printf("Enter the item price: ");
        scanf("%f", &newItem.price);
        printf("Enter the item quantity: ");
        scanf("%d", &newItem.quantity);
         menu[*numItems][0] = newItem;
        (*numItems)++;
         printf("Item added successfully!\n");
    } else {
        printf("Cannot add more items.\n");
    }
}

//Delete
void deleteFoodItem(struct FoodItem menu[][MAX_ATTRIBUTES], int *numItems, int itemID) {
	for (int i = 0; i < *numItems; i++) {
        if (menu[i][0].itemID == itemID) {
            for (int j = i; j < *numItems - 1; j++) {
                menu[j][0] = menu[j + 1][0];
            }
            (*numItems)--;
            printf("Item with ID %d deleted successfully!\n", itemID);
            return;
        }
    }
    printf("Item with ID %d not found.\n", itemID);
}

//  linear search by item name
void searchFoodItem(struct FoodItem menu[][MAX_ATTRIBUTES], int numItems, char itemName[50]) {
   for (int i = 0; i < numItems; i++) {
        if (strcmp(menu[i][0].name, itemName) == 0) {
            printf("Item found:\n");
            printf("Item ID: %d\n", menu[i][0].itemID);
            printf("Item name: %s\n", menu[i][0].name);
            printf("Item price: %.2f\n", menu[i][0].price);
            printf("Item quantity: %d\n", menu[i][0].quantity);
            return;
        }
    }
    printf("Item with name '%s' not found.\n", itemName);
}	
int main() {
    struct FoodItem menu[MAX_ITEMS][MAX_ATTRIBUTES];
    int numItems = 0;

    int choice, itemID;
    char itemName[50];

    while (1) {
        printf("\nFood Ordering System Menu:\n");
        printf("1. Insert a new food item\n");
        printf("2. Delete a food item by ID\n");
        printf("3. Search for a food item by name\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                insertFoodItem(menu, &numItems);
                break;
            case 2:
                printf("Enter the item ID to delete: ");
                scanf("%d", &itemID);
                deleteFoodItem(menu, &numItems, itemID);
                break;
            case 3:
                printf("Enter the item name to search: ");
                scanf("%s", itemName);
                searchFoodItem(menu, numItems, itemName);
                break;
            case 4:
                printf("Exiting the program.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}


