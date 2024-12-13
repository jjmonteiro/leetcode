#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int id;
    int pages;
} book_t;

typedef struct {
    book_t* book;
    int total_books_in_shelf;
} shelf_t;

typedef struct {
    shelf_t* shelf;
    int total_books_in_library;
} library_t;

int main() {
    srand(time(NULL));

    int num_books = (rand() % 50) + 1; // Total number of books to allocate
    int num_shelves = (rand() % 10) + 1; // Ensure at least 1 shelf

    library_t mylibrary = { .shelf = NULL, .total_books_in_library = 0 };

    // Allocate memory for shelves
    mylibrary.shelf = (shelf_t*)calloc(num_shelves, sizeof(shelf_t));
    if (mylibrary.shelf == NULL) {
        perror("Failed to allocate memory for shelves");
        return 1;
    }

    printf("\nINSERTING %d BOOKS INTO %d SHELVES\n\n", num_books, num_shelves);

    mylibrary.total_books_in_library = num_books;

    for (int i = 0; i < num_books; i++) {
        int pages = (rand() % 100) + 1; // Ensure at least 1 page
        int shelf = rand() % num_shelves;
        shelf_t* current_shelf = &mylibrary.shelf[shelf];

        // Dynamically allocate or expand the memory for books in the shelf
        int new_size = (current_shelf->total_books_in_shelf + 1) * sizeof(book_t);
        book_t* new_books = (book_t*)realloc(current_shelf->book, new_size);
        if (new_books == NULL) {
            perror("Failed to reallocate memory for books");
            return 1;
        }
        current_shelf->book = new_books;

        // Add the new book
        current_shelf->book[current_shelf->total_books_in_shelf].id = i;
        current_shelf->book[current_shelf->total_books_in_shelf].pages = pages;
        current_shelf->total_books_in_shelf++;
        printf("book: %02d, pages: %02d, shelf: %d\n", i, pages, shelf);
    }

    printf("\nLIBRARY SHELVES\n\n");

    for (int i = 0; i < num_shelves; i++) {
        printf("shelf: %d, books: %02d\n", i, mylibrary.shelf[i].total_books_in_shelf);

        for (int j = 0; j < mylibrary.shelf[i].total_books_in_shelf; j++) {
            printf("\tbook: %02d, pages: %02d\n", mylibrary.shelf[i].book[j].id, mylibrary.shelf[i].book[j].pages);
        }
    }

    // Free allocated memory
    for (int i = 0; i < num_shelves; i++) {
        free(mylibrary.shelf[i].book);
    }
    free(mylibrary.shelf);

    return 0;
}
