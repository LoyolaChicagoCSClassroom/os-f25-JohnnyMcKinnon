/*

***PROJECT PROPOSAL***
Contact Book in alphabetical order(using an array of  LinkedLists)


1. Introduction:
End goal of project-create a Contact Book that stores and manages contact information
in an alphabetically ordered array of linked lists. This project will exemplify practical
usage of data structures, specifically an array of linked lists, and will provide a
functional program for managing contacts efficiently. User will be able to
add, search, update, and delete contacts while maintaining alphabetical order.

2. Problem Statement:
Many people struggle to organize and quickly access large lists of contacts.
Traditional arrays or unsorted lists can make searching, inserting, and deleting contacts
inefficient. By using an array of linked lists, we can maintain an organized structure
while allowing efficient insertion and deletion operations. This approach demonstrates
the practical use of linked lists and reinforces understanding of dynamic data structures.

3. Proposed Solution:
The project will implement a Contact Book using an array of linked lists.
Each node contains:
1-Name
2-Phone number
3-Email address
4-Optional notes(such as address, occupation, or any other information the user deems
important.)
Each linked list will maintain contacts in alphabetical order by name(Undecided if it will
be first name or last name basis. Leaning towards last name for an evenly distributed
array of linked lists).

The program will support:
1-Add Contact: Insert a new contact in the correct alphabetical position.
2-Search Contact: Find a contact by name efficiently by traversing the list
by first selecting the linked list corresponding to the initial letter, then traversing
3-Update Contact: Modify details of an existing contact.
4-Delete Contact: Remove a contact while maintaining alphabetical order.
5-Display Contacts: Print all contacts in alphabetical order.
The solution will be implemented in C, using dynamic memory allocation for linked list
nodes. User interaction will be through the terminal(originally for Ubuntu).
The project will include a feature to display all contacts stored in the contact book.
The program will traverse the linked list and present each contact’s information in
alphabetical order, allowing the user to view all entries efficiently.

4. End Goal:
The end goal of this project is a fully functional terminal-based Contact Book application
with well-documented source code and appropriate comments. The primary operations,
such as adding, searching, updating, and deleting contacts, have a time complexity of
O(k), where k is the number of contacts sharing the same initial letter. The only
operation with a less efficient time complexity is displaying the full contact list,
which requires O(n) time, where n is the total number of contacts.

*/


// ***CODE***
#include <stdio.h>
#include <stdlib.h>

//Start here
