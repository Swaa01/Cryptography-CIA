#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

// Pad text with 'X' to fill the grid completely
void padText(char *text, int totalLen) {
    int len = strlen(text);
    for (int i = len; i < totalLen; i++) {
        text[i] = 'X'; // Padding character
    }
    text[totalLen] = '\0';
}

void encryptRoute(char *text, int rows, int cols, char *cipher) {
    int len = strlen(text);
    int totalLen = rows * cols;
    padText(text, totalLen);

    char grid[rows][cols];
    int k = 0;

    // Fill grid row-wise
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            grid[i][j] = text[k++];

    // Read grid column-wise to encrypt
    k = 0;
    for (int j = 0; j < cols; j++)
        for (int i = 0; i < rows; i++)
            cipher[k++] = grid[i][j];

    cipher[k] = '\0';
}

void decryptRoute(char *cipher, int rows, int cols, char *result) {
    int len = strlen(cipher);
    char grid[rows][cols];
    int k = 0;

    // Fill grid column-wise
    for (int j = 0; j < cols; j++)
        for (int i = 0; i < rows; i++)
            grid[i][j] = cipher[k++];

    // Read grid row-wise to get original message
    k = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result[k++] = grid[i][j];

    result[k] = '\0';
}

int main() {
    char text[200], encrypted[200], decrypted[200];
    int rows, cols;

    printf("Enter the message (uppercase letters only): ");
    scanf("%s", text);

    // Convert to uppercase
    for (int i = 0; text[i]; i++)
        text[i] = toupper(text[i]);

    printf("Enter number of rows and columns (e.g., 3 4): ");
    scanf("%d %d", &rows, &cols);

    encryptRoute(text, rows, cols, encrypted);
    printf("Encrypted: %s\n", encrypted);

    decryptRoute(encrypted, rows, cols, decrypted);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}
