#include <stdio.h>
#include <stdlib.h>

/* allocate matrix */
int **allocateMatrix(int rows, int cols)
{
    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = (int *)malloc(cols * sizeof(int));
    }
    return matrix;
}

void freeMatrix(int **matrix, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

void inputMatrix(int **matrix, int rows, int cols, char name)
{
    printf("Enter the elements for %c (%d x %d):\n", name, rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%c[%d][%d] = ", name, i, j);
            scanf("%d", &matrix[i][j]);
        }
    }
}

void displayMatrix(int **matrix, int rows, int cols, char *title)
{
    printf("%s (%d x %d):\n", title, rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void addMatrices(int **A, int **B, int **sum, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            sum[i][j] = A[i][j] + B[i][j];
        }
    }
}

void multiplyMatrices(int **A, int **B, int **product, int rowsA, int colsA, int colsB)
{
    for (int i = 0; i < rowsA; i++)
    {
        for (int j = 0; j < colsB; j++)
        {
            product[i][j] = 0;
            for (int k = 0; k < colsA; k++)
            {
                product[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main()
{
    int rowsA, colsA, rowsB, colsB;

    printf("Enter the dimension for matrix A (rows cols): ");
    scanf("%d %d", &rowsA, &colsA);

    printf("Enter the dimension for matrix B (rows cols): ");
    scanf("%d %d", &rowsB, &colsB);

    int canAdd = (rowsA == rowsB && colsA == colsB);
    int canMultiply = (colsA == rowsB);

    int **A = allocateMatrix(rowsA, colsA);
    int **B = allocateMatrix(rowsB, colsB);

    int **sum = NULL;
    int **product = NULL;

    inputMatrix(A, rowsA, colsA, 'A');
    inputMatrix(B, rowsB, colsB, 'B');

    if (canAdd)
    {
        sum = allocateMatrix(rowsA, colsA);
        addMatrices(A, B, sum, rowsA, colsA);
        displayMatrix(sum, rowsA, colsA, "Sum of A and B");
    }
    else
    {
        printf("Matrix addition not possible due to dimension mismatch\n");
    }

    if (canMultiply)
    {
        product = allocateMatrix(rowsA, colsB);
        multiplyMatrices(A, B, product, rowsA, colsA, colsB);
        displayMatrix(product, rowsA, colsB, "Product of A and B");
    }
    else
    {
        printf("Matrix multiplication not possible due to dimension mismatch\n");
    }

    freeMatrix(A, rowsA);
    freeMatrix(B, rowsB);
    if (sum)
        freeMatrix(sum, rowsA);
    if (product)
        freeMatrix(product, rowsA);

    return 0;
}