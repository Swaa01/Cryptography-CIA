#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Encrypt using Rail Fence Cipher
void encryptRailFence(char *text, int depth, char *cipher) {
    int len = strlen(text);
    char rail[depth][len];

    // initialize with '\n'
    for (int i = 0; i < depth; i++)
        for (int j = 0; j < len; j++)
            rail[i][j] = '\n';

    int row = 0, dir = 1;

    for (int i = 0; i < len; i++) {
        rail[row][i] = text[i];

        row += dir;
        if (row == 0 || row == depth - 1)
            dir = -dir;
    }

    int k = 0;
    for (int i = 0; i < depth; i++)
        for (int j = 0; j < len; j++)
            if (rail[i][j] != '\n')
                cipher[k++] = rail[i][j];

    cipher[k] = '\0';
}

// Decrypt using Rail Fence Cipher
void decryptRailFence(char *cipher, int depth, char *result) {
    int len = strlen(cipher);
    char rail[depth][len];

    // initialize with '\n'
    for (int i = 0; i < depth; i++)
        for (int j = 0; j < len; j++)
            rail[i][j] = '\n';

    // Mark positions
    int row = 0, dir = 1;
    for (int i = 0; i < len; i++) {
        rail[row][i] = '*';
        row += dir;
        if (row == 0 || row == depth - 1)
            dir = -dir;
    }

    // Fill the letters
    int k = 0;
    for (int i = 0; i < depth; i++)
        for (int j = 0; j < len; j++)
            if (rail[i][j] == '*')
                rail[i][j] = cipher[k++];

    // Read the result in zigzag
    row = 0; dir = 1;
    for (int i = 0; i < len; i++) {
        result[i] = rail[row][i];
        row += dir;
        if (row == 0 || row == depth - 1)
            dir = -dir;
    }
    result[len] = '\0';
}

int main() {
    char text[200], encrypted[200], decrypted[200];
    int depth;

    printf("Enter the message: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    printf("Enter the depth (number of rails): ");
    scanf("%d", &depth);

    encryptRailFence(text, depth, encrypted);
    printf("Encrypted: %s\n", encrypted);

    decryptRailFence(encrypted, depth, decrypted);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}
