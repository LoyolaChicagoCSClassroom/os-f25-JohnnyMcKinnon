#include "page.h"
#include <stddef.h>

#define TOTAL_PAGES 128
#define PAGE_SIZE (2 * 1024 * 1024) // 2 MB per page

static struct ppage physical_page_array[TOTAL_PAGES];
static struct ppage *free_list = NULL;

void init_pfa_list(void) {
    for (int i = 0; i < TOTAL_PAGES; ++i) {
        physical_page_array[i].physical_addr = (void *)(i * PAGE_SIZE);
        physical_page_array[i].next = (i < TOTAL_PAGES - 1) ? &physical_page_array[i + 1] : NULL;
        physical_page_array[i].prev = (i > 0) ? &physical_page_array[i - 1] : NULL;
    }
    free_list = &physical_page_array[0];
}

struct ppage *allocate_physical_pages(unsigned int npages) {
    struct ppage *head = NULL;
    struct ppage *tail = NULL;

    for (unsigned int i = 0; i < npages; ++i) {
        if (free_list == NULL) return NULL;

        struct ppage *page = free_list;
        free_list = free_list->next;
        if (free_list)
            free_list->prev = NULL;

        page->next = NULL;
        page->prev = NULL;

        if (head == NULL) {
            head = tail = page;
        } else {
            tail->next = page;
            page->prev = tail;
            tail = page;
        }
    }

    return head;
}

void free_physical_pages(struct ppage *ppage_list) {
    if (ppage_list == NULL) return;

    struct ppage *last = ppage_list;
    while (last->next != NULL) {
        last = last->next;
    }

    last->next = free_list;
    if (free_list)
        free_list->prev = last;

    free_list = ppage_list;
    ppage_list->prev = NULL;
}

