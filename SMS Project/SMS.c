#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Stock {
    int id;
    char name[50];
    int quantity;
    float price;
};

// Function declarations
void addStock();
void viewStock();
void searchStock();
void updateStock();
void deleteStock();

FILE *file;

int main() {
    int choice;
    while (1) {
        printf("\n----- Stock Management System -----\n");
        printf("1. Add Stock\n");
        printf("2. Update Stock\n");
        printf("3. Delete Stock\n");
        printf("4. Search Stock\n");
        printf("5. View All Stock\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStock(); break;
            case 2: updateStock(); break;
            case 3: deleteStock(); break;
            case 4: searchStock(); break;
            case 5: viewStock(); break;
            case 6: exit(0);
            default: printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}

void addStock() {
    struct Stock s;
    file = fopen("stock.txt", "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    printf("Enter Item ID: ");
    scanf("%d", &s.id);
    printf("Enter Item Name: ");
    scanf(" %[^\n]%*c", s.name);
    printf("Enter Quantity: ");
    scanf("%d", &s.quantity);
    printf("Enter Price: ");
    scanf("%f", &s.price);

    fprintf(file, "%d %s %d \t\t%.2f\n", s.id, s.name, s.quantity, s.price);
    fclose(file);
    printf("Record Added Successfully!\n");
}

void viewStock() {
    struct Stock s;
    file = fopen("stock.txt", "r");
    if (file == NULL) {
        printf("No records found!\n");
        return;
    }
    printf("\nID\tName\tQuantity\tPrice\n");
    while (fscanf(file, "%d %s %d %f", &s.id, s.name, &s.quantity, &s.price) != EOF) {
        printf("%d\t%s\t%d\t%.2f\n", s.id, s.name, s.quantity, s.price);
    }
    fclose(file);
}

void searchStock() {
    struct Stock s;
    int id, found = 0;
    printf("Enter Item ID to search: ");
    scanf("%d", &id);
    file = fopen("stock.txt", "r");
    if (file == NULL) {
        printf("No records found!\n");
        return;
    }
    while (fscanf(file, "%d %s %d %f", &s.id, s.name, &s.quantity, &s.price) != EOF) {
        if (s.id == id) {
            printf("Record Found:\nID: %d\nName: %s\nQuantity: %d\nPrice: %.2f\n", s.id, s.name, s.quantity, s.price);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Record not found!\n");
    }
    fclose(file);
}

void updateStock() {
    struct Stock s;
    int id, found = 0;
    FILE *temp;
    printf("Enter Item ID to update: ");
    scanf("%d", &id);

    file = fopen("stock.txt", "r");
    temp = fopen("temp.txt", "w");
    if (file == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    while (fscanf(file, "%d %s %d %f", &s.id, s.name, &s.quantity, &s.price) != EOF) {
        if (s.id == id) {
            printf("Enter New Name: ");
            scanf(" %[^\n]%*c", s.name);
            printf("Enter New Quantity: ");
            scanf("%d", &s.quantity);
            printf("Enter New Price: ");
            scanf("%f", &s.price);
            found = 1;
        }
        fprintf(temp, "%d %s %d \t%.2f\n", s.id, s.name, s.quantity, s.price);
    }

    fclose(file);
    fclose(temp);

    remove("stock.txt");
    rename("temp.txt", "stock.txt");

    if (found) {
        printf("Record Updated Successfully!\n");
    } else {
        printf("Record not found!\n");
    }
}

void deleteStock() {
    struct Stock s;
    int id, found = 0;
    FILE *temp;
    printf("Enter Item ID to delete: ");
    scanf("%d", &id);

    file = fopen("stock.txt", "r");
    temp = fopen("temp.txt", "w");
    if (file == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    while (fscanf(file, "%d %s %d %f", &s.id, s.name, &s.quantity, &s.price) != EOF) {
        if (s.id == id) {
            found = 1;
            continue; // Skip writing this record
        }
        fprintf(temp, "%d %s %d \t%.2f\n", s.id, s.name, s.quantity, s.price);
    }

    fclose(file);
    fclose(temp);

    remove("stock.txt");
    rename("temp.txt", "stock.txt");

    if (found) {
        printf("Record Deleted Successfully!\n");
    } else {
        printf("Record not found!\n");
    }
}

