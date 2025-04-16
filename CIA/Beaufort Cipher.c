#include <stdio.h>
#include <string.h>
#include <ctype.h>

void beaufortCipher(char *text, char *key) {
    int keyLen = strlen(key);
    for (int i = 0, j = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char t = toupper(text[i]);
            char k = toupper(key[j % keyLen]);

            int c = (k - t + 26) % 26 + 'A';
            text[i] = isupper(text[i]) ? c : tolower(c);
            j++;
        }
    }
}

int main() {
    char message[100];
    char key[100];

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';

    printf("Enter keyword: ");
    scanf("%s", key);

    beaufortCipher(message, key);
    printf("Encrypted: %s\n", message);

    // Use the same function again to decrypt (reciprocal)
    beaufortCipher(message, key);
    printf("Decrypted: %s\n", message);

    return 0;
}
