#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Item {
    int id;
    char name[50];
    float price;
    int quantity;
    struct Item* next;
} Item;

Item* inventory = NULL;

// Function prototypes
Item* createItem(int id, char* name, float price, int quantity);
void addItem();
void displayInventory();
Item* findItemById(int id);
void deleteItemById(int id);
void deleteItemQuantity();
void sortInventoryById();
void generateBill();
void printMenu();

// Function to create a new item node
Item* createItem(int id, char* name, float price, int quantity) {
    Item* newItem = (Item*)malloc(sizeof(Item));
    newItem->id = id;
    strcpy(newItem->name, name);
    newItem->price = price;
    newItem->quantity = quantity;
    newItem->next = NULL;
    return newItem;
}

// Function to add an item to the inventory
void addItem() {
    int id, quantity;
    float price;
    char name[50];

    printf("Enter Item ID: ");
    scanf("%d", &id);
    printf("Enter Item Name: ");
    scanf("%s", name);
    printf("Enter Item Price: ");
    scanf("%f", &price);
    printf("Enter Item Quantity: ");
    scanf("%d", &quantity);

    Item* newItem = createItem(id, name, price, quantity);
    newItem->next = inventory;
    inventory = newItem;
    printf("\n");
    printf("Item added successfully!\n");
}

// Function to display the inventory
void displayInventory() {
    if (inventory == NULL) {
        printf("\nThe inventory is empty.\n");
        return;
    }
    printf("\nInventory:\n");
    printf("ID\tName\tPrice\tQuantity\n");
    Item* current = inventory;
    while (current != NULL) {
        printf("%d\t%s\t%.2f\t%d\n", current->id, current->name, current->price, current->quantity);
        current = current->next;
    }
}

// Function to find an item by ID using linear search
Item* findItemById(int id) {
    Item* current = inventory;
    while (current != NULL && current->id != id) {
        current = current->next;
    }
    return current;
}

// Function to delete an item by ID
void deleteItemById(int id) {
    if (inventory == NULL) {
        printf("\n");
        printf("The inventory is empty.\n");
        return;
    }

    Item* current = inventory;
    Item* prev = NULL;

    // Traverse the list to find the item to delete
    while (current != NULL && current->id != id) {
        prev = current;
        current = current->next;
    }

    // Item not found
    if (current == NULL) {
        printf("\n");
        printf("Item with ID %d not found!\n", id);
        return;
    }

    // Item found at the head of the list
    if (prev == NULL) {
        inventory = current->next;
    } else {
        // Item found in the middle or end of the list
        prev->next = current->next;
    }

    free(current);
    printf("\n");
    printf("Item deleted successfully!\n");
}

// Function to delete a specific quantity of an item
void deleteItemQuantity() {
    if (inventory == NULL) {
        printf("\n");
        printf("The inventory is empty.\n");
        return;
    }

    int id, quantity;
    printf("Enter Item ID to delete quantity: ");
    scanf("%d", &id);
    printf("Enter Quantity to delete: ");
    scanf("%d", &quantity);

    Item* item = findItemById(id);
    if (item != NULL) {
        if (quantity <= item->quantity) {
            item->quantity -= quantity;
            printf("\n");
            printf("Deleted %d of %s from inventory. New quantity: %d\n", quantity, item->name, item->quantity);
            if (item->quantity == 0) {
                deleteItemById(id); // Remove the item from the inventory if the quantity is zero
            }
        } else {
            printf("\n");
            printf("Insufficient quantity for item: %s\n", item->name);
        }
    } else {
        printf("\n");
        printf("Item with ID %d not found!\n", id);
    }
}

// Function to sort the inventory by item ID using bubble sort
void sortInventoryById() {
    if (inventory == NULL) {
        printf("\n");
        printf("The inventory is empty.\n");
        return;
    }

    int swapped;
    Item* ptr1;
    Item* lptr = NULL;

    do {
        swapped = 0;
        ptr1 = inventory;

        while (ptr1->next != lptr) {
            if (ptr1->next && ptr1->id > ptr1->next->id) {
                // Swap item data
                int tempId = ptr1->id;
                char tempName[50];
                strcpy(tempName, ptr1->name);
                float tempPrice = ptr1->price;
                int tempQuantity = ptr1->quantity;

                ptr1->id = ptr1->next->id;
                strcpy(ptr1->name, ptr1->next->name);
                ptr1->price = ptr1->next->price;
                ptr1->quantity = ptr1->next->quantity;

                ptr1->next->id = tempId;
                strcpy(ptr1->next->name, tempName);
                ptr1->next->price = tempPrice;
                ptr1->next->quantity = tempQuantity;

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// Function to generate a bill
void generateBill() {
    if (inventory == NULL) {
        printf("\n");
        printf("The inventory is empty.\n");
        return;
    }

    int id, quantity;
    float total = 0.0;
    char choice;

    printf("\nGenerating Bill:\n");
    printf("Enter 'n' when you are done with adding items to the bill.\n");

    do {
        printf("Enter Item ID: ");
        scanf("%d", &id);

        Item* item = findItemById(id);
        if (item != NULL) {
            printf("Enter Quantity: ");
            scanf("%d", &quantity);
            if (quantity <= item->quantity) {
                float cost = quantity * item->price;
                total += cost;
                item->quantity -= quantity;
                printf("Item added to bill: %s, Quantity: %d, Cost: %.2f\n", item->name, quantity, cost);
                if (item->quantity == 0) {
                    deleteItemById(id); // Automatically remove item if quantity is zero
                }
            } else {
                printf("\n");
                printf("Insufficient stock for item: %s\n", item->name);
            }
        } else {
            printf("\n");
            printf("Item with ID %d not found!\n", id);
        }

        printf("Add another item? (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y' || choice == 'Y');

    printf("\nTotal Bill Amount: %.2f\n", total);
}

// Function to print the menu
void printMenu() {
    printf("\n**Grocery Store Billing System**\n");
    printf("\n");
    printf("1. Add Item to Inventory\n");
    printf("2. Display Inventory\n");
    printf("3. Sort Inventory by ID\n");
    printf("4. Generate Bill\n");
    printf("5. Delete Item from Inventory\n");
    printf("6. Delete Specific Quantity of an Item\n");
    printf("7. Exit\n");
    printf("Enter your choice: ");
}

// Main function
int main() {
    int choice;
    while (1) {
        printMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addItem();
                break;
            case 2:
                displayInventory();
                break;
            case 3:
                printf("Inventory sorted successfully!\n");
                sortInventoryById();
                break;
            case 4:
                generateBill();
                break;
            case 5: {
                int id;
                printf("Enter Item ID to delete: ");
                scanf("%d", &id);
                deleteItemById(id);
                break;
            }
            case 6:
                deleteItemQuantity();
                break;
            case 7:
                printf("Thank you for Shopping!\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}