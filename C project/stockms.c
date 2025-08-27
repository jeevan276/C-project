#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store product details
typedef struct {
    int id;
    char name[50];
    int quantity;
    float price;
} Product;

// Function declarations
void addStock();
void searchStock();
void deleteStock();
void displayStock();

int main() {
    int choice;

    do {
        printf("\n===== Stock Management System =====\n");
        printf("1. Add Stock\n");
        printf("2. Search Stock\n");
        printf("3. Delete Stock\n");
        printf("4. Display Stock\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStock(); break;
            case 2: searchStock(); break;
            case 3: deleteStock(); break;
            case 4: displayStock(); break;
            case 5: printf("Exiting the program... Thank you!\n"); break;
            default: printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

// Function to add a new product
void addStock() {
    Product p;
    FILE *fp = fopen("stock.dat", "ab"); // Open file in append mode

    if (!fp) {
        printf("Error: Could not open file.\n");
        return;
    }

    printf("\nEnter Product ID: ");
    scanf("%d", &p.id);
    printf("Enter Product Name: ");
    scanf("%s", p.name);
    printf("Enter Quantity: ");
    scanf("%d", &p.quantity);
    printf("Enter Price: ");
    scanf("%f", &p.price);

    fwrite(&p, sizeof(Product), 1, fp);
    fclose(fp);

    printf("Product added successfully!\n");
}

// Function to search for a product by ID
void searchStock() {
    int id, found = 0;
    Product p;
    FILE *fp = fopen("stock.dat", "rb");

    if (!fp) {
        printf("No stock data available.\n");
        return;
    }

    printf("\nEnter Product ID to search: ");
    scanf("%d", &id);

    while (fread(&p, sizeof(Product), 1, fp)) {
        if (p.id == id) {
            printf("\nProduct Found:\n");
            printf("ID: %d\nName: %s\nQuantity: %d\nPrice: %.2f\n", p.id, p.name, p.quantity, p.price);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Product not found.\n");
    }

    fclose(fp);
}

// Function to delete a product by ID
void deleteStock() {
    int id, found = 0;
    Product p;
    FILE *fp = fopen("stock.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if (!fp || !temp) {
        printf("Error: Could not open file.\n");
        return;
    }

    printf("\nEnter Product ID to delete: ");
    scanf("%d", &id);

    while (fread(&p, sizeof(Product), 1, fp)) {
        if (p.id != id) {
            fwrite(&p, sizeof(Product), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("stock.dat");
    rename("temp.dat", "stock.dat");

    if (found) {
        printf("Product deleted successfully!\n");
    } else {
        printf("Product not found.\n");
    }
}

// Function to display all products
void displayStock() {
    Product p;
    FILE *fp = fopen("stock.dat", "rb");

    if (!fp) {
        printf("No stock data available.\n");
        return;
    }

    printf("\n===== Stock List =====\n");
    printf("%-10s %-20s %-10s %-10s\n", "ID", "Name", "Quantity", "Price");

    while (fread(&p, sizeof(Product), 1, fp)) {
        printf("%-10d %-20s %-10d %-10.2f\n", p.id, p.name, p.quantity, p.price);
    }

    fclose(fp);
}

