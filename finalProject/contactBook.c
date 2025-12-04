// Johnny McKinnon
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 26   // A-Z


typedef struct Contact {
    char name[50];
    char phone[20];
    char email[50];
    char notes[100];
    struct Contact* next;
} Contact; //struct Contact

Contact* contactBook[SIZE];

// Manual uppercase only converter
char toUpperManual(char c) {
    if (c >= 'a' && c <= 'z')
        return c - 32;   // ASCII difference
    return c;
}

// Converter for first letter --> array index
int getIndex(char c) {
    c = toUpperManual(c);
    if (c < 'A' || c > 'Z') return -1;
    return c - 'A';
}

//new node
Contact* createContact(char name[], char phone[], char email[], char notes[]) {
    Contact* newC = malloc(sizeof(Contact));
    strcpy(newC->name, name);
    strcpy(newC->phone, phone);
    strcpy(newC->email, email);
    strcpy(newC->notes, notes);
    newC->next = NULL;
    return newC;
}

//Must insert in alphabetical order
void addContactManual(char name[], char phone[], char email[], char notes[]) {

    int index = getIndex(name[0]);
    if (index == -1) {
        printf("Invalid name.\n");
        return;
    }

    Contact* newC = createContact(name, phone, email, notes);

    Contact* curr = contactBook[index];
    Contact* prev = NULL;

    while (curr != NULL && strcmp(newC->name, curr->name) > 0) {
        prev = curr;
        curr = curr->next;
    }

    if (prev == NULL) {
        newC->next = contactBook[index];
        contactBook[index] = newC;
    } else {
        prev->next = newC;
        newC->next = curr;
    }
}

// Add contact interactively(through terminal commands)
void addContact() {
    char name[50], phone[20], email[50], notes[100];

    printf("Enter name: ");
    fgets(name, 50, stdin); name[strcspn(name, "\n")] = 0;

    printf("Enter phone: ");
    fgets(phone, 20, stdin); phone[strcspn(phone, "\n")] = 0;

    printf("Enter email: ");
    fgets(email, 50, stdin); email[strcspn(email, "\n")] = 0;

    printf("Enter notes: ");
    fgets(notes, 100, stdin); notes[strcspn(notes, "\n")] = 0;

    addContactManual(name, phone, email, notes);

    printf("Contact added.\n");
}

// Search by name
Contact* searchContact(char name[]) {
    int index = getIndex(name[0]);
    if (index == -1) return NULL;

    Contact* curr = contactBook[index];

    while (curr != NULL) {
        if (strcmp(curr->name, name) == 0)
            return curr;
        curr = curr->next;
    }

    return NULL;
}

// Update contact
void updateContact() {
    char name[50];
    printf("Enter name to update: ");
    fgets(name, 50, stdin); name[strcspn(name, "\n")] = 0;

    Contact* c = searchContact(name);

    if (c == NULL) {
        printf("Contact not found.\n");
        return;
    }

    printf("Enter new phone: ");
    fgets(c->phone, 20, stdin); c->phone[strcspn(c->phone, "\n")] = 0;

    printf("Enter new email: ");
    fgets(c->email, 50, stdin); c->email[strcspn(c->email, "\n")] = 0;

    printf("Enter new notes: ");
    fgets(c->notes, 100, stdin); c->notes[strcspn(c->notes, "\n")] = 0;

    printf("Contact updated.\n");
}

// Delete contact
void deleteContact() {
    char name[50];
    printf("Enter name to delete: ");
    fgets(name, 50, stdin); name[strcspn(name, "\n")] = 0;

    int index = getIndex(name[0]);
    if (index == -1) {
        printf("Invalid name.\n");
        return;
    }

    Contact* curr = contactBook[index];
    Contact* prev = NULL;

    while (curr != NULL && strcmp(curr->name, name) != 0) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) {
        printf("Contact not found.\n");
        return;
    }

    if (prev == NULL)
        contactBook[index] = curr->next;
    else
        prev->next = curr->next;

    free(curr);
    printf("Contact deleted.\n");
}

// Display all contacts
void displayContacts() {
    for (int i = 0; i < SIZE; i++) {
        Contact* curr = contactBook[i];
        while (curr != NULL) {
            printf("\nName: %s\nPhone: %s\nEmail: %s\nNotes: %s\n",
                   curr->name, curr->phone, curr->email, curr->notes);
            curr = curr->next;
        }
    }
}

// Menu
void menu() {
    int choice;
    char temp[10];

    while (1) {
        printf("\n1. Add Contact\n");
        printf("2. Update Contact\n");
        printf("3. Delete Contact\n");
        printf("4. Display All Contacts\n");
        printf("5. Exit\n");
        printf("Choice: ");

        fgets(temp, 10, stdin);
        choice = atoi(temp);

        switch (choice) {
            case 1: addContact(); break;
            case 2: updateContact(); break;
            case 3: deleteContact(); break;
            case 4: displayContacts(); break;
            case 5: exit(0);
            default: printf("Invalid choice.\n");
        }
    }
}
