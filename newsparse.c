// Program to read two sparse matrices, convert them to compact matrices,
// add them, and display the result and its transpose.

#include <stdio.h>

// Function to read a matrix from user input
void read_matrix(int rows, int cols, int matrix[rows][cols]) {
    printf("\n");
    for (int i=0; i < rows; i++) {
        printf("Enter row-%d: ", i+1);
        for (int j = 0; j < cols; j++) {
            scanf("%d", &matrix[i][j]);
        }   
    }
}

// Function to display a matrix
void display_matrix(int rows, int cols, int matrix[rows][cols]) {
    printf("\n");
    for (int i=0; i < rows; i++) {
        for (int j=0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }   
        printf("\n");
    }
}

// Convert a sparse matrix to its compact (triplet) representation
void to_compact_matrix(int rows, int cols, int matrix[rows][cols], int compact[][3]) {
    compact[0][0] = rows;      // Store total rows
    compact[0][1] = cols;      // Store total columns
    compact[0][2] = 0;         // Initialize count of non-zero elements

    int k=1; // k is index for compact matrix rows
    for (int i=0; i < rows; i++) {
        for (int j=0; j < cols; j++) {
            if (matrix[i][j] == 0) continue; // Skip zero elements
            compact[k][0] = i;               // Row index of non-zero element
            compact[k][1] = j;               // Column index of non-zero element
            compact[k][2] = matrix[i][j];    // Value of non-zero element
            k++;
        } 
    }
    compact[0][2] = k - 1; // Update count of non-zero elements
}

int main() {
    int rows, cols;
    printf("Enter number of rows and columns: ");
    scanf("%d %d", &rows, &cols);
    
    int matrix1[rows][cols]; // First sparse matrix
    int matrix2[rows][cols]; // Second sparse matrix
    
    printf("\nEnter first sparse matrix: ");
    read_matrix(rows, cols, matrix1); // Read first matrix
    printf("\nEnter second sparse matrix: ");
    read_matrix(rows, cols, matrix2); // Read second matrix
    
    printf("\nFirst Sparse Matrix: ");
    display_matrix(rows, cols, matrix1); // Display first matrix
    printf("\nSecond Sparse Matrix: ");
    display_matrix(rows, cols, matrix2); // Display second matrix
    
    int compact1[rows * cols][3]; // Compact representation of first matrix
    int compact2[rows * cols][3]; // Compact representation of second matrix
    
    to_compact_matrix(rows, cols, matrix1, compact1); // Convert first matrix
    to_compact_matrix(rows, cols, matrix2, compact2); // Convert second matrix
    
    printf("\nCompact Matrix 1:");
    display_matrix(compact1[0][2]+1, 3, compact1); // Display compact matrix 1
    printf("\nCompact Matrix 2:");
    display_matrix(compact2[0][2]+1, 3, compact2); // Display compact matrix 2

    int r1 = compact1[0][2]+1; // Number of rows in compact1
    int r2 = compact2[0][2]+1; // Number of rows in compact2
    
    int result[r1+r2-1][3];    // Compact matrix for addition result
    result[0][0] = rows; 
    result[0][1] = cols; 
    result[0][2] = 0;          // Initialize count of non-zero elements

    // Merge the two compact matrices into result (add them)
    int i=1, j=1, k=1;
    while (i<r1 && j<r2) {
        // Compare row and column indices to merge in sorted order
        if ( (compact1[i][0] < compact2[j][0]) || 
                (compact1[i][0] == compact2[j][0] && compact1[i][1] < compact2[j][1]) ) {
            // Add current element from compact1
            result[k][0] = compact1[i][0];
            result[k][1] = compact1[i][1];
            result[k][2] = compact1[i][2];
            k++, i++;
        } 
        else if ((compact1[i][0] > compact2[j][0]) || 
                (compact1[i][0] == compact2[j][0] && compact1[i][1] > compact2[j][1])) {
            // Add current element from compact2
            result[k][0] = compact2[j][0];
            result[k][1] = compact2[j][1];
            result[k][2] = compact2[j][2];
            k++, j++;
        }
        else {
            // If position is same, add values
            if (compact1[i][1] == compact2[j][1]) {
                result[k][0] = compact1[i][0];
                result[k][1] = compact1[i][1];
                result[k][2] = compact1[i][2] + compact2[j][2];
                k++, i++, j++;
            }
        }
    }

    // Copy remaining elements from compact1
    while (i < r1) {
        result[k][0] = compact1[i][0];
        result[k][1] = compact1[i][1];
        result[k][2] = compact1[i][2];
        k++, i++;
    }
    // Copy remaining elements from compact2
    while (j < r2) {
        result[k][0] = compact2[j][0];
        result[k][1] = compact2[j][1];
        result[k][2] = compact2[j][2];
        k++, j++;
    }

    result[0][2] = k - 1; // Update count of non-zero elements in result

    printf("\nResultant Compact Matrix:");
    display_matrix(k, 3, result); // Display the sum compact matrix

    // Find transpose of the resultant compact matrix
    int transposeMat[3][k];
    for (int i=0; i<k; i++) {
        for (int j=0; j<3; j++) {
            transposeMat[j][i] = result[i][j];
        }
    }
    printf("\nTranspose of Resultant Compact Matrix:");
    display_matrix(3, k, transposeMat); // Display transpose
    return 0;
}

// SAMPLE INPUT/OUTPUT
/*
Enter number of rows and columns: 3 3

Enter first sparse matrix: 
Enter row-1: 0 3 0
Enter row-2: 5 2 0
Enter row-3: 0 0 6

Enter second sparse matrix: 
Enter row-1: 1 4 0
Enter row-2: 0 0 0
Enter row-3: 3 0 2

First Sparse Matrix: 
0 3 0 
5 2 0 
0 0 6 

Second Sparse Matrix: 
1 4 0 
0 0 0 
3 0 2 

Compact Matrix 1:
3 3 4 
0 1 3 
1 0 5 
1 1 2 
2 2 6 

Compact Matrix 2:
3 3 4 
0 0 1 
0 1 4 
2 0 3 
2 2 2 

Resultant Compact Matrix:
3 3 6 
0 0 1 
0 1 7 
1 0 5 
1 1 2 
2 0 3 
2 2 8 

Transpose of Resultant Compact Matrix:
3 0 0 1 1 2 2 
3 0 1 0 1 0 2 
6 1 7 5 2 3 8 
*/


////////////////////////////////////////////////////////////////////////////
