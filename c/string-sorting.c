// return true if a > b, false otherwise
int lexicographic_sort(const char* a, const char* b) {
    while (*a){
        if (*a < *b)
            return 0;
        else if (*a > *b)
            return 1;
        else{ // next char
            a++;
            b++;
        }
    }
    return 0; // equal strings
}

// return true if a < b, false otherwise
int lexicographic_sort_reverse(const char* a, const char* b) {
    return !lexicographic_sort(a, b);
}

// return true if a > b, false otherwise
int sort_by_number_of_distinct_characters(const char* a, const char* b) {
    const char* a_ptr = a, * b_ptr = b;
    int ac = 0, bc = 0;
    #define buffer 256

    int r[buffer] = {0};
    int p[buffer] = {0};
    
    while (*a){
        r[*a] = 1;
        a++;
    }
    while (*b){
        p[*b] = 1;
        b++;
    }

    for (int i = 0; i <= buffer; i++) {
        if (r[i] == 1)
            ac++;
        if (p[i] == 1)
            bc++;
    }

    if (ac > bc)
        return 1;
    else if (ac < bc)
        return 0;
    else // equal sizes
        return lexicographic_sort(a_ptr, b_ptr);
}

// return true if a > b, false otherwise
int sort_by_length(const char* a, const char* b) {
    const char* a_ptr = a, * b_ptr = b;
    int ac = 0, bc = 0;

    while (*a){
        a++;
        ac++;
    }
    while (*b){
        b++;
        bc++;
    }

    if (ac > bc)
        return 1;
    else if (ac < bc)
        return 0;
    else // equal sizes
        return lexicographic_sort(a_ptr, b_ptr);
}

void string_sort(char** arr, const int len, int (*cmp_func)(const char* a, const char* b)) {
    for (int j = 0; j < (len - 1); j++) {
        for (int i = 0; i < (len - 1); i++) {
            if ((*cmp_func)(arr[i], arr[i + 1])) {
                // return true if a > b, so swap
                char* temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
            }
        }
    }
}