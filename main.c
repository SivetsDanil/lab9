#include <math.h>
#include <stdio.h>
#include <string.h>
#include "table.h"
#include <windows.h>


void swap(Table* t, int i, int j) {
    if (i == j) return;
    float k = t->keys[i];
    t->keys[i] = t->keys[j];
    t->keys[j] = k;
    char tmp[TEXT_LEN];
    strcpy(tmp, t->texts[i]);
    strcpy(t->texts[i], t->texts[j]);
    strcpy(t->texts[j], tmp);
}

void down(Table* t, int root, int last) {
    while (1) {
        int left  = 2 * root + 1;
        int right = 2 * root + 2;
        if (left > last)
            break;
        int largest = left;
        if (right <= last && t->keys[right] > t->keys[left])
            largest = right;
        if (t->keys[root] >= t->keys[largest])
            break;
        swap(t, root, largest);
        root = largest;
    }
}
void sort(Table* t) {
    for (int i = t->n / 2 - 1; i >= 0; i--)
        down(t, i, t->n - 1);
    for (int last = t->n - 1; last > 0; last--) {
        swap(t, 0, last);
        down(t, 0, last - 1);
    }
}

int binary_search(Table* t, float key) {
    int l, r, mid;
    l = 0;
    r = t->n -1;
    while (l <= r) {
        mid = l + (r - l) / 2;
        if (fabsf(t->keys[mid] - key) < EPS) {
            return mid;
        }
        if (t->keys[mid] < key) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return -1;
}

int main(void) {
    SetConsoleOutputCP(65001);
    FILE* test1 = fopen("../test_sorted.txt", "r");
    FILE* test2 = fopen("../test_reversed.txt", "r");
    FILE* test3 = fopen("../test_random.txt", "r");
    FILE* test = test3;
    int n;
    fscanf(test, "%d", &n);
    Table t;
    float key;
    t.n = 0;
    for (int i = 0; i < n; i++) {
        fscanf(test, "%f %[^\n]", &t.keys[t.n], t.texts[t.n]);
        t.n++;
    }
    printf("-----------------before sort-----------------------\n");

    for (int i = 0; i < t.n; i++) {
        printf("%g %s\n", t.keys[i], t.texts[i]);
    }
    printf("-----------------after sort-----------------------\n");

    sort(&t);
    for (int i = 0; i < t.n; i++) {
        printf("%g %s\n", t.keys[i], t.texts[i]);
    }
    printf("------------------test search----------------------\n");
    int n1;
    int f;
    fscanf(test, "%d", &n1);
    for (int i = 0; i < n1; i++) {
        fscanf(test, "%f", &key);
        printf("%g \n", key);
        f = binary_search(&t, key);
        if (f == -1) {
            printf("Not found");
        }
        else {
            printf("%s\n", t.texts[f]);
        }
    }
    return 0;
}
