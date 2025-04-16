#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Function to compute modular inverse of a under mod 26
int modInverse(int a, int m) {
    for (int i = 1; i < m; i++) {
        if ((a * i) % m == 1)
            return i;
    }
    return -1;  // No modular inverse
}

void affineEncrypt(char *text, int a, int b) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            text[i] = (char)((((a * (text[i] - base)) + b) % 26) + base);
        }
    }
}

void affineDecrypt(char *text, int a, int b) {
    int a_inv = modInverse(a, 26);
    if (a_inv == -1) {
        printf("Invalid key: No modular inverse for a = %d under mod 26.\n", a);
        return;
    }
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            int decrypted = (a_inv * ((text[i] - base - b + 26)) % 26);
            text[i] = (char)(decrypted + base);
        }
    }
}

int gcd(int a, int b) {
    while (b) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int main() {
    char message[100];
    int a, b;

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';

    printf("Enter key 'a' (must be coprime with 26): ");
    scanf("%d", &a);
    if (gcd(a, 26) != 1) {
        printf("Invalid key 'a'. It must be coprime with 26.\n");
        return 1;
    }

    printf("Enter key 'b' (0-25): ");
    scanf("%d", &b);

    affineEncrypt(message, a, b);
    printf("Encrypted: %s\n", message);

    affineDecrypt(message, a, b);
    printf("Decrypted: %s\n", message);

    return 0;
}
