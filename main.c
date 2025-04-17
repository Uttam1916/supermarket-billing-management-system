#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct{
    int id;
    char category[50];
    char brand[50];
    float price;
    int stock;
} product;

void  LoadItems(const char *filename, product products[], int maxprod){
    
}

void OpenCart(){}
void DisplayProducts(){}
void SearchID(){}
void exits(){
    printf("Thank you for shopping! Please visit us again");
    exit(0);
}
void MainMenu(){
    int choice=100;

    while(choice){
        printf("SuperMarket Billing System\n");
        printf("1. Cart and Billing\n");
        printf("2. Products\n"); 
        printf("3. Search by ID\n");
        printf("4. Exit\n");
        printf("Enter your choice\n");

        scanf("%d",choice);

        switch(choice){
            case(1):
                OpenCart();
                break;
            case(2):
                DisplayProducts();
                break;
            case(3):
                SearchID();
                break;
            case(4):
                exits();
                break;
            default:
                printf("Invalid choice, enter another\n");

        }
    }
}

int main(){
    LoadItems();
    MainMenu();
    return 0;
}