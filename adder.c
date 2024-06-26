#include <stdio.h>
void carryLookaheadAdder(int A[], int B[], int *S, int *Cout) {
    int P[4], G[4], C[5];

    // Generate P and G signals
    for (int i = 0; i < 4; i++) {
        P[i] = A[i] ^ B[i];
        G[i] = A[i] & B[i];
    }

    // Generate C signals
    C[0] = G[0] | (P[0] & 0); // Cin = 0
    C[1] = G[1] | (P[1] & C[0]);
    C[2] = G[2] | (P[2] & (G[1] | (P[1] & C[0])));
    C[3] = G[3] | (P[3] & (G[2] | (P[2] & (G[1] | (P[1] & C[0])))));
    C[4] = P[3] & G[2] & G[1] & G[0];

    // Generate Sum and Cout
    *S = P[0] ^ C[0];
    for (int i = 1; i < 4; i++) {
        *S |= (P[i] ^ C[i]) << i;
    }
    *Cout = C[3] | C[4];
}

int main() {
    int A[4], B[4];
    int S;
    int Cout;

    // Take user input for binary numbers A and B
    printf("Enter a 4-bit binary number A (enter digits from right to left): ");
    for (int i = 3; i >= 0; i--) {
        scanf("%1d", &A[i]);
    }

    printf("Enter another 4-bit binary number B (enter digits from right to left): ");
    for (int i = 3; i >= 0; i--) {
        scanf("%1d", &B[i]);
    }

    carryLookaheadAdder(A, B, &S, &Cout);

    printf("Sum: %d%d%d%d\n", (S >> 3) & 1, (S >> 2) & 1, (S >> 1) & 1, S & 1);
    printf("Cout: %d\n", Cout);

    return 0;
}
