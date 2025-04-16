#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to find modular inverse of determinant
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return -1;
}

// Function to encrypt two letters using 2x2 Hill Cipher
void hillEncrypt(char *text, int key[2][2]) {
    int pt[2], ct[2];
    for (int i = 0; i < strlen(text); i += 2) {
        pt[0] = toupper(text[i]) - 'A';
        pt[1] = toupper(text[i + 1]) - 'A';

        ct[0] = (key[0][0]*pt[0] + key[0][1]*pt[1]) % 26;
        ct[1] = (key[1][0]*pt[0] + key[1][1]*pt[1]) % 26;

        text[i] = ct[0] + 'A';
        text[i + 1] = ct[1] + 'A';
    }
}

// Function to decrypt using inverse key matrix
void hillDecrypt(char *text, int key[2][2]) {
    int det = key[0][0]*key[1][1] - key[0][1]*key[1][0];
    det = (det % 26 + 26) % 26;
    int invDet = modInverse(det, 26);
    if (invDet == -1) {
        printf("Key matrix not invertible under mod 26\n");
        return;
    }

    int invKey[2][2];
    invKey[0][0] =  key[1][1] * invDet % 26;
    invKey[0][1] = -key[0][1] * invDet % 26;
    invKey[1][0] = -key[1][0] * invDet % 26;
    invKey[1][1] =  key[0][0] * invDet % 26;

    // Make sure all values are positive mod 26
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            invKey[i][j] = (invKey[i][j] + 26) % 26;

    int ct[2], pt[2];
    for (int i = 0; i < strlen(text); i += 2) {
        ct[0] = toupper(text[i]) - 'A';
        ct[1] = toupper(text[i + 1]) - 'A';

        pt[0] = (invKey[0][0]*ct[0] + invKey[0][1]*ct[1]) % 26;
        pt[1] = (invKey[1][0]*ct[0] + invKey[1][1]*ct[1]) % 26;

        text[i] = pt[0] + 'A';
        text[i + 1] = pt[1] + 'A';
    }
}

int main() {
    char message[100];
    int key[2][2];

    printf("Enter even-length message (uppercase letters only): ");
    scanf("%s", message);

    if (strlen(message) % 2 != 0) {
        printf("Message length must be even for 2x2 Hill Cipher.\n");
        return 1;
    }

    printf("Enter 2x2 key matrix (integers mod 26):\n");
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            scanf("%d", &key[i][j]);

    hillEncrypt(message, key);
    printf("Encrypted: %s\n", message);

    hillDecrypt(message, key);
    printf("Decrypted: %s\n", message);

    return 0;
}
