#include<stdio.h>  
#include<stdlib.h>  
#include<string.h> 

struct foodNode   
{  
    char itemName[50];
    float price;
    struct foodNode *next;   
};

struct foodNode *head;

void beginsert();   
void lastinsert();  
void begin_delete();  
void last_delete();  
void search();  
void display();  
void mainMenu();

void main()  
{  
    int choice = 0;  
    while (choice != 7)   
    {  
        mainMenu(); 
        printf("\nEnter your choice: ");         
        scanf("%d", &choice);  

        switch (choice)  
        {  
            case 1:  
                beginsert();      
                break;  
            case 2:  
                lastinsert();         
                break;  
            case 3:  
                begin_delete();       
                break;  
            case 4:  
                last_delete();        
                break;  
            case 5:  
                search();         
                break;  
            case 6:  
                display();        
                break;
            case 7:
                printf("\nExiting the program\n");
                break;
            default:  
                printf("Please enter a valid choice..\n");  
        }  
    }  
}


void mainMenu() {
    printf("\n*********Food Ordering System*********\n");  
    printf("Choose one option from the following list ...\n");  
    printf("===============================================\n");  
    printf("1. Insert at the beginning\n");
    printf("2. Insert at the end\n");
    printf("3. Delete from the beginning\n");
    printf("4. Delete from the end\n");
    printf("5. Search for a food item\n");
    printf("6. Show the food menu\n");
    printf("7. Exit\n");
}

void beginsert()  
{  
    struct foodNode *ptr;   
    ptr = (struct foodNode *)malloc(sizeof(struct foodNode));  
    if(ptr == NULL)  
    {  
        printf("\nOVERFLOW\n");  
    }  
    else   
    {  
        printf("\nEnter the food item name: ");  
        scanf("%s", ptr->itemName);  
        printf("Enter the price: ");  
        scanf("%f", &ptr->price);  

        ptr->next = head;  
        head = ptr;  

        printf("\nFood item inserted\n");  
    }  
}  

void lastinsert()  
{  
    struct foodNode *ptr, *temp;   
    ptr = (struct foodNode *)malloc(sizeof(struct foodNode));  
    if(ptr == NULL)  
    {  
        printf("\nOVERFLOW\n");  
    }  
    else  
    {  
        printf("\nEnter the food item name: ");  
        scanf("%s", ptr->itemName);  
        printf("Enter the price: ");  
        scanf("%f", &ptr->price);  

        if(head == NULL)  
        {  
            head = ptr;  
            ptr->next = NULL;    
        }  
        else  
        {  
            temp = head;  
            while(temp->next != NULL)  
            {  
                temp = temp->next;  
            }  
            temp->next = ptr;   
            ptr->next = NULL;  
        }  
          
        printf("\nFood item inserted\n");  
    }  
}  

void begin_delete()  
{  
    struct foodNode *ptr;   
    if(head == NULL)  
    {  
        printf("\nUNDERFLOW\n");    
    }  
    else if(head->next == NULL)  
    {  
        free(head);  
        head = NULL;  
        printf("\nFood item deleted\n");  
    }  
    else  
    {   
        ptr = head;   
        while(ptr->next != NULL)  
            ptr = ptr->next;   
        ptr->next = head->next;  
        free(head);  
        head = ptr->next;  
        printf("\nFood item deleted\n");  
    }  
}  

void last_delete()  
{  
    struct foodNode *ptr, *preptr;  
    if(head == NULL)  
    {  
        printf("\nUNDERFLOW\n");  
    }  
    else if(head->next == NULL)  
    {  
        free(head);  
        head = NULL;  
        printf("\nFood item deleted\n");  
    }  
    else  
    {  
        ptr = head;  
        while(ptr->next != NULL)  
        {  
            preptr = ptr;  
            ptr = ptr->next;  
        }  
        preptr->next = NULL;  
        free(ptr);  
        printf("\nFood item deleted\n");  
    }  
}  

void search()  
{  
    struct foodNode *ptr;  
    char searchItem[50];  
    int flag = 0;  

    if(head == NULL)  
    {  
        printf("\nMenu is empty\n");  
    }  
    else  
    {   
        printf("\nEnter the food item name you want to search: ");   
        scanf("%s", searchItem);  

        ptr = head;  
        while(ptr != NULL)  
        {  
            if(strcmp(ptr->itemName, searchItem) == 0)  
            {  
                printf("Food item found - %s (%.2f)\n", ptr->itemName, ptr->price);  
                flag = 1;  
                break;  
            }   
            ptr = ptr->next;  
        }  

        if(flag == 0)  
        {  
            printf("Food item not found\n");  
        }  
    }     
}

void display()  
{  
    struct foodNode *ptr;  
    ptr = head;  

    if(head == NULL)  
    {  
        printf("\nMenu is empty\n");  
    }     
    else  
    {  
        printf("\n************ Food Menu ************\n");  
        while(ptr != NULL)  
        {  
            printf("%s - %.2f\n", ptr->itemName, ptr->price);  
            ptr = ptr->next;  
        }  
    }  
}

