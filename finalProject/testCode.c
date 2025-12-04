int main() {
    // Initialize list
    for (int i = 0; i < SIZE; i++)
        contactBook[i] = NULL;

    // Test code
    addContactManual("Eric Spencer", "708-2543", "eric@example.com", "Friend");
    addContactManual("Mo Jaber", "708-3254", "momen@example.com", "Work");
    addContactManual("Ella Jankeki", "708-4325", "ella@example.com", "Friend");
    addContactManual("Mary Drocsid", "708-5432", "amanda@example.com", "Neighbor");

    printf("Testing contacts inserted.\n");
    displayContacts();
    menu();
}
