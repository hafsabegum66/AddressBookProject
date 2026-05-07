/*
Project1 : Address-Book
Name: Hafsa Begum
Date : 08-04-2026
Description: Developing a user interface program where user can store thier contact information, also update and delete it.
*/

#include <stdio.h>
#include "contact.h"

int main() {
    int choice,sortChoice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do {
        printf("\nADDRESS BOOK MENU:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
    	printf("6. Save contacts\n");		
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:          
                listContacts(&addressBook, sortChoice);
                break;
            case 6:
                printf("Saving and Exiting...\n");
                saveAndExit(&addressBook);
                break;
            case 7:
                printf("Thank You..,!!\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);
    
       return 0;
}
