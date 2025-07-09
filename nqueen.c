#include <stdio.h>
#include <stdlib.h>

void printSolution(int **board, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

int isSafe(int **board, int row, int col, int n) {
    int i, j;

    // Check this row on left side
    for (i = 0; i < col; i++)
        if (board[row][i])
            return 0;

    // Check upper diagonal on left side
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return 0;

    // Check lower diagonal on left side
    for (i = row, j = col; j >= 0 && i < n; i++, j--)
        if (board[i][j])
            return 0;

    return 1;
}

int solveNQUtil(int **board, int col, int n) {
    if (col >= n)
        return 1;

    for (int i = 0; i < n; i++) {
        if (isSafe(board, i, col, n)) {
            board[i][col] = 1;

            if (solveNQUtil(board, col + 1, n))
                return 1;

            board[i][col] = 0; // BACKTRACK
        }
    }

    return 0;
}

void solveNQ(int n) {
    int **board = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        board[i] = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++)
            board[i][j] = 0;
    }

    if (solveNQUtil(board, 0, n) == 0) {
        printf("Solution does not exist");
        return;
    }

    printSolution(board, n);

    for (int i = 0; i < n; i++) {
        free(board[i]);
    }
    free(board);
}

int main() {
    int n;
    printf("Enter the number of queens (N): ");
    scanf("%d", &n);
    solveNQ(n);
    return 0;
}