#ifndef LAB9_TABLE_H
#define LAB9_TABLE_H
#define MAX_N 64
#define TEXT_LEN 256
#define EPS 0.0000001
typedef struct {
    float keys[MAX_N];
    char  texts[MAX_N][TEXT_LEN];
    int   n;
} Table;
#endif //LAB9_TABLE_H
