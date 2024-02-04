#include<stdio.h>  
#include<stdlib.h>  

struct foodNode   
{  
    char itemName[50]; 
    float price;
    struct foodNode *next;   
};

struct foodNode *head;  

void addFoodItem();   
void removeFoodItem();  
void displayMenu();  
void searchItem();  

void main ()  
{  
    int choice = 0;  
    while(choice != 6)   
    {  
        printf("\n\n*********Food Ordering System*********\n");  
        printf("\nChoose one option from the following list ...\n");  
        printf("\n===============================================\n");  
        printf("\n1. Add Food Item\n2. Remove Food Item\n3. Display Menu\n4. Search for an Item\n5. Exit\n");  
        printf("\nEnter your choice?\n");         
        scanf("\n%d", &choice);  

        switch(choice)  
        {  
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
                exit(0);  
                break;  
            default:  
                printf("Please enter a valid choice..");  
        }  
    }  
}  

void addFoodItem()  
{  
    struct foodNode *ptr;  
    ptr = (struct foodNode *) malloc(sizeof(struct foodNode *));  
    if(ptr == NULL)  
    {  
        printf("\nOVERFLOW");  
    }  
    else  
    {  
        printf("\nEnter food item name\n");    
        scanf("%s", ptr->itemName);  
        printf("\nEnter price\n");    
        scanf("%f", &ptr->price);  
        ptr->next = head;  
        head = ptr;  
        printf("\nFood item added to the menu");  
    }  
}  

void removeFoodItem()  
{  
    struct foodNode *ptr, *prev;
    char itemName[50];

    if (head == NULL)  
    {  
        printf("\nMenu is empty\n");  
        return;
    }

    printf("\nEnter the item name you want to remove?\n");   
    scanf("%s", itemName);

    ptr = head;   
    prev = NULL;

    while (ptr != NULL)  
    {  
        if (strcmp(ptr->itemName, itemName) == 0)  
        {  
            
            if (prev == NULL)  
            {
                
                head = ptr->next;
            }
            else  
            {
                prev->next = ptr->next;
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

void displayMenu()  
{  
    struct foodNode *ptr;  
    ptr = head;   
    if(ptr == NULL)  
    {  
        printf("Menu is empty");  
    }  
    else  
    {  
        printf("\n************ Menu ************\n");   
        while (ptr != NULL)  
        {  
            printf("\n%s - %.2f", ptr->itemName, ptr->price);  
            ptr = ptr->next;  
        }  
    }  
}  

void searchItem()  
{  
    struct foodNode *ptr;  
    char itemName[50]; 
    int flag = 1; 

    ptr = head;   
    if(ptr == NULL)  
    {  
        printf("\nMenu is empty\n");  
    }  
    else  
    {   
        printf("\nEnter the item name you want to search?\n");   
        scanf("%s", itemName);  
        
        while (ptr != NULL)  
        {  
            if(strcmp(ptr->itemName, itemName) == 0)  
            {  
                printf("Item found - %s ($%.2f)", ptr->itemName, ptr->price);  
                flag = 0;  
                break;
            }   
            ptr = ptr->next;  
        }  

        if(flag == 1)  
        {  
            printf("Item not found\n");  
        }  
    }     
}


