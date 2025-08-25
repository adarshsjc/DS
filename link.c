#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int coeff;
    int exp;
    struct Node* next;
} Node;

Node* createNode(int coeff, int exp) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = NULL;
    return newNode;
}

void append(Node** head, int coeff, int exp) {
    Node* newNode = createNode(coeff, exp);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* temp = *head;
        while (temp->next)
            temp = temp->next;
        temp->next = newNode;
    }
}

void display(Node* head) {
    if (head == NULL) {
        printf("0\n");
        return;
    }
    Node* temp = head;
    while (temp) {
        printf("%dx^%d", temp->coeff, temp->exp);
        if (temp->next && temp->next->coeff >= 0)
            printf(" + ");
        temp = temp->next;
    }
    printf("\n");
}

Node* addPolynomials(Node* poly1, Node* poly2) {
    Node* result = NULL;
    while (poly1 && poly2) {
        if (poly1->exp == poly2->exp) {
            int sum = poly1->coeff + poly2->coeff;
            if (sum != 0)
                append(&result, sum, poly1->exp);
            poly1 = poly1->next;
            poly2 = poly2->next;
        } else if (poly1->exp > poly2->exp) {
            append(&result, poly1->coeff, poly1->exp);
            poly1 = poly1->next;
        } else {
            append(&result, poly2->coeff, poly2->exp);
            poly2 = poly2->next;
        }
    }
    while (poly1) {
        append(&result, poly1->coeff, poly1->exp);
        poly1 = poly1->next;
    }
    while (poly2) {
        append(&result, poly2->coeff, poly2->exp);
        poly2 = poly2->next;
    }
    return result;
}

void inputPolynomial(Node** poly) {
    int n, coeff, exp;
    printf("Enter number of terms: ");
    scanf("%d", &n);

    printf("Enter terms in descending order of exponents:\n");
    for (int i = 0; i < n; i++) {
        printf("Coefficient and exponent: ");
        scanf("%d %d", &coeff, &exp);
        append(poly, coeff, exp);
    }
}

int main() {
    Node* poly1 = NULL;
    Node* poly2 = NULL;
    Node* sum = NULL;

    printf("Input Polynomial 1:\n");
    inputPolynomial(&poly1);

    printf("Input Polynomial 2:\n");
    inputPolynomial(&poly2);

    printf("\nPolynomial 1: ");
    display(poly1);

    printf("Polynomial 2: ");
    display(poly2);

    sum = addPolynomials(poly1, poly2);

    printf("Sum: ");
    display(sum);

    // Memory cleanup is recommended but omitted here for brevity

    return 0;
}

