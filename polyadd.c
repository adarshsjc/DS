#include <stdio.h>

#define MAX_TERMS 10

void inputPoly(int poly[MAX_TERMS][2], int *numTerms) {
    printf("Enter the number of terms in the polynomial: ");
    scanf("%d", numTerms);
   
    for (int i = 0; i < *numTerms; i++) {
        printf("Enter exponent and coefficient for term %d: ", i + 1);
        scanf("%d %d", &poly[i][0], &poly[i][1]);
    }
}

void printPoly(int poly[MAX_TERMS][2], int numTerms) {
    for (int i = 0; i < numTerms; i++) {
        if (poly[i][1] == 0) continue;
        if (i > 0 && poly[i][1] > 0) printf(" + ");
        else if (poly[i][1] < 0) printf(" - ");
       
        if (poly[i][1] < 0 && i > 0)
            printf("%d", -poly[i][1]);
        else
            printf("%d", poly[i][1] < 0 ? -poly[i][1] : poly[i][1]);

        printf("x^%d", poly[i][0]);
    }
    printf("\n");
}

void addPolynomials(int poly1[MAX_TERMS][2], int numTerms1, int poly2[MAX_TERMS][2], int numTerms2, int result[MAX_TERMS][2], int *numResult) {
    int i = 0, j = 0, k = 0;

    while (i < numTerms1 && j < numTerms2) {
        if (poly1[i][0] > poly2[j][0]) {
            result[k][0] = poly1[i][0];
            result[k][1] = poly1[i][1];
            i++;
        } else if (poly1[i][0] < poly2[j][0]) {
            result[k][0] = poly2[j][0];
            result[k][1] = poly2[j][1];
            j++;
        } else {
            int sum = poly1[i][1] + poly2[j][1];
            if (sum != 0) { 
                result[k][0] = poly1[i][0];
                result[k][1] = sum;
                k++;
            }
            i++;
            j++;
            continue; 
        }
        k++;
    }

    while (i < numTerms1) {
        result[k][0] = poly1[i][0];
        result[k][1] = poly1[i][1];
        i++;
        k++;
    }
    while (j < numTerms2) {
        result[k][0] = poly2[j][0];
        result[k][1] = poly2[j][1];
        j++;
        k++;
    }

    *numResult = k;
}

int main() {
    int poly1[MAX_TERMS][2], poly2[MAX_TERMS][2], result[MAX_TERMS][2];
    int numTerms1, numTerms2, numResult;

    printf("Polynomial 1:\n");
    inputPoly(poly1, &numTerms1);

    printf("\nPolynomial 2:\n");
    inputPoly(poly2, &numTerms2);

    addPolynomials(poly1, numTerms1, poly2, numTerms2, result, &numResult);

    printf("\nPolynomial 1: ");
    printPoly(poly1, numTerms1);

    printf("Polynomial 2: ");
    printPoly(poly2, numTerms2);

    printf("Sum of Polynomials: ");
    printPoly(result, numResult);

    return 0;
}