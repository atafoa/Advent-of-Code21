//#define __USE_MINGW_ANSI_STDIO 0
#define  _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <sys/time.h>

#define maxSize 200000

int points[maxSize][2]; // {row, col}
int pointsLen = 0;

#define FLIP_ROWS 0 // Along X
#define FLIP_COLS 1 // Along Y

int folds[maxSize][2]; // {Flip along axis, at coordinate}
int foldsLen = 0;

void completeFold(int i) {
    int threshold = folds[i][1];
    for (int p = 0; p < pointsLen; ++p) {
        if (folds[i][0] == FLIP_ROWS) {
            if (points[p][0] >= threshold) points[p][0] = threshold * 2 - points[p][0];
        } else { // FLIP_COLS
            if (points[p][1] >= threshold) points[p][1] = threshold * 2 - points[p][1];
        }
    }
}

int ascPair(const void *pa, const void *pb) { 
    int *a = (int *)pa;
    int *b = (int *)pb;
    if (a[0] == b[0]) return a[1] - b[1];
    else return a[0] - b[0];
}

int countUnique() {
    qsort(points, pointsLen, sizeof(points[0]), ascPair);
    int uniquePts = 0;
    for (int i = 0; i < pointsLen; ++i) {
        if (i > 0 && points[i - 1][0] == points[i][0] && points[i - 1][1] == points[i][1]); // this is a dupe
        else ++uniquePts; // not a dupe, add.
    }
    return uniquePts-1;
}

static inline int max(int a, int b) { return (a > b) ? a : b; }

void printPts() {
    // Find max rows, max cols
    int maxRows = -1, maxCols = -1;
    for (int i = 0; i < pointsLen; ++i) {
        maxRows = max(maxRows, points[i][0]);
        maxCols = max(maxCols, points[i][1]);
    }
    ++maxRows, ++maxCols;
    // # if the point exists, . if it doesn't
    qsort(points, pointsLen, sizeof(points[0]), ascPair);
    int ptr = 0;
    for (int r = 0; r < maxRows; ++r) {
        for (int c = 0; c < maxCols; ++c) {
            if (points[ptr][0] == r && points[ptr][1] == c) {
                putchar('#');
                while (ptr < pointsLen && points[ptr][0] == r && points[ptr][1] == c) ++ptr;
            } else {
                putchar(' ');
            }
        }
        putchar('\n');
    }
}

void testcase() {
    // Complete only 1 fold.
    completeFold(0);
    printf("%d\n", countUnique());
    // Fold the rest
    for (int i = 1; i < foldsLen; ++i) completeFold(i);
    // Let's print out what it says
    printPts();
}

int main() {
   

    // Get input
    freopen("input.txt", "r", stdin);
    char str[maxSize];
    char *first, *second;
    bool findingFolds = false;
    while (!feof(stdin)) {
        scanf("%s", str);
        // Get Coordinates
        if (strcmp(str, "fold")) {
            // Remove comma, assign to 2 strings
            for (int i = 0; str[i] != '\0'; ++i) {
                if (str[i] == ',') {
                    str[i] = '\0';
                    second = &str[i + 1];
                    break;
                }
            }
            first = str;
            // Get coordinates, given in cols, rows. Assign as rows, cols.
            int firstNum = atoi(first);
            int secondNum = atoi(second);
            // Push to array
            points[pointsLen][0] = secondNum;
            points[pointsLen][1] = firstNum;
            ++pointsLen;
        } else {
            // Get folds
            scanf("%s", str); // get "along"
            scanf("%s", str); // get x=num
            if (str[0] == 'x') folds[foldsLen][0] = FLIP_COLS;
            else folds[foldsLen][0] = FLIP_ROWS;
            int num = atoi(&str[2]);
            folds[foldsLen][1] = num;
            ++foldsLen;
        }
    }
    testcase();

    
    return 0;
}