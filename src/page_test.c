#include <stdio.h>
#include "page.h"

// Simple function to count pages in a linked list
int count_pages(struct ppage *list) {
    int count = 0;
    while (list != NULL) {
        count++;
        list = list->next;
    }
    return count;
}

void run_page_allocator_tests() {
    printf("Running page allocator tests...\n");
    //initialize
    init_pfa_list();
    int free_count = count_pages(free_physical_pages);
    printf("[Init] Free pages after init: %d (expected 128)\n", free_count);

    //Test1-ask for 10 pages
    struct ppage *alloc_list = allocate_physical_pages(10);
    int alloc_count = count_pages(alloc_list);
    free_count = count_pages(free_physical_pages);
    printf("[Alloc] Allocated pages: %d (expected 10)\n", alloc_count);
    printf("[Alloc] Free pages after alloc: %d (expected 118)\n", free_count);

    //Test2-release unused pages
    free_physical_pages(alloc_list);
    alloc_list = NULL;
    free_count = count_pages(free_physical_pages);
    printf("[Free] Free pages after freeing: %d (expected 128)\n", free_count);

    //Test3-ask for excess pages
    alloc_list = allocate_physical_pages(200);
    alloc_count = count_pages(alloc_list);
    printf("[OverAlloc] Allocated pages: %d (expected 128)\n", alloc_count);
    free_count = count_pages(free_physical_pages);
    printf("[OverAlloc] Free pages after over-alloc: %d (expected 0)\n", free_count);
}//run_page_allocator_tests 

int main() {
    run_page_allocator_tests();
    return 0;
}//main
//Chat GPT was indeed conslted with for testing code
