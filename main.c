#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_LINE_LENGTH 256
#define MAX_PRODUCTS 100
#define MAX_CART_ITEMS 50

typedef struct{
    int id;
    char category[50];
    char brand[50];
    float price;
    int stock;
} product;

typedef struct{
    product produc;
    int quantity;
} cartitem;

product products[MAX_PRODUCTS];
cartitem cart[MAX_CART_ITEMS];
int totalproducts=0;
int cartsize=0;

int  LoadItems(const char *filename){
    FILE *file=fopen(filename,"r");
    if(!file){
        printf("error loading products");
        exit(0);
    }

    char line[MAX_LINE_LENGTH];
    fgets(line, sizeof(line),file);
    int count=0;

    while(fgets(line, sizeof(line),file)){
        char *token;
        token=strtok(line,",");
        if(token) products[count].id=atoi(token);
        token=strtok(NULL,",");
        if(token) strncpy(products[count].category,token,sizeof(products[count].category)-1);
        token=strtok(NULL,",");
        if(token) strncpy(products[count].brand,token,sizeof(products[count].brand)-1);
        token=strtok(NULL,",");
        if (token) products[count].price=atof(token);
        token=strtok(NULL,",");
        if (token) products[count].stock=atoi(token);
        count++;
    }
    fclose(file);

    return count;
}

void OpenCart(){
    float amt=0.0;
    if(!cart){
        printf("Your cart is empty!\n");
    }
    else{
        printf("\nYour cart:\n");
        for(int i=0;i<cartsize;i++){
            printf("%s | %s | %dx%d\n",cart[i].produc.category,cart[i].produc.brand,cart[i].quantity,cart[i].produc.price);
            float subtotal= cart[i].produc.price * cart[i].quantity;
            amt+=subtotal;
        }
        printf("Total bill= ₹%.2f\n\n",amt);
    }
}

void addtocart(int id, int qty) {
    if (qty <= 0) {
        printf("Quantity must be greater than 0.\n");
        return;
    }

    for (int i = 0; i < totalproducts; i++) {
        if (id == products[i].id) {
            if (products[i].stock >= qty) {

                // Check if product already in cart
                for (int j = 0; j < cartsize; j++) {
                    if (cart[j].produc.id == id) {
                        cart[j].quantity += qty;
                        products[i].stock -= qty;
                        printf("Product quantity added to existing product\n");
                        return;
                    }
                }

                // Check cart size before adding new product
                if (cartsize >= MAX_CART_ITEMS) {
                    printf("Cart is full! Cannot add more products.\n");
                    return;
                }

                // Add product to cart
                cart[cartsize].produc = products[i];
                cart[cartsize].quantity = qty;
                products[i].stock -= qty;
                cartsize++;
                printf("Product added to cart\n\n");
            } else {
                printf("Not enough stock of product — only %d remain\n", products[i].stock);
            }
            return;
        }
    }

    printf("Product not found\n");
}


int noofunicate(char categories[][50]){
    int count=0;
    for(int i=0; i<totalproducts; i++){
        int exists =0;
        for(int j=0; j<count;j++){
            if(strcmp(products[i].category,categories[j])==0){
                exists=1;
                break;
            }
        }
        if(!exists){
            strncpy(categories[count],products[i].category,50);
            count+=1;
        }
        
    }
    return count;
}

void DisplayProducts(){
    char categories[20][50];
    int count=noofunicate(categories);
    
    printf("\n---- Categories ----\n");
    for(int i=0;i<count;i++){
        printf("%d. %s\n",i+1,categories[i]);
    }
    int choice;
    printf("enter your preffered category( 0 to exit):\n");
    scanf("%d",&choice);
    getchar();

    if(choice<=0 || choice>count){
        return;
    }

    char *selected=categories[choice-1];
    printf("\n--- %s Products ---\n",selected);
    printf("ID | Brand | Price | Stock\n");
    for(int i=0; i< totalproducts;i++){
        if(strcmp(products[i].category,selected)==0)
        printf("%d | %s | %f | %d\n",products[i].id,products[i].brand,products[i].price,products[i].stock);
    }

    int id,qty;
    printf("Enter the ID of the product you want to add to your cart( 0 to return):\n");
    scanf("%d",&id);
    if(id<=0){
        return;
    }
    else{
        printf("Enter the quantity of the product you require:\n");
        scanf("%d",&qty);
        addtocart(id,qty);
    }
    }

void SearchID(){
    int id;
    int c=0;
    printf("Enter the ID of the product you want to search:\n");
    scanf("%d",&id);
    for(int i=0;i<totalproducts;i++){
        if(products[i].id==id){
            printf("\n%d | %s | %f | %d\n",products[i].id,products[i].brand,products[i].price,products[i].stock);
            printf("Do you want to purchase this product?(1 for yes and anthing else for no)\n");
            scanf("%d",&c);
            if(c==1){
                int qn;
                printf("Enter the quantity of the product you require:\n");
                scanf("%d",&qn);
                addtocart(products[i].id,qn);
                return;
            }
            else{
                printf("Keep looking!\n");
                return;
            }
        }
        
    }
    printf("Invalid product ID\n");
    return;
    
}

void exits(){
    printf("Thank you for shopping! Please visit us again\n");
    exit(0);
}

void MainMenu(){
    int choice=100;

    while(choice){
        
        printf("\n----SuperMarket Billing System----\n");
        printf("1. Cart and Billing\n");
        printf("2. Products\n"); 
        printf("3. Search by ID\n");
        printf("4. Exit\n");
        printf("Enter your choice:\n");

        scanf("%d",&choice);
        getchar();

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
    totalproducts= LoadItems("products_50.csv");
    MainMenu();

    return 0;
}