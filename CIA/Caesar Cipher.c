#include <stdio.h>
#include <ctype.h>
#include <string.h>

void caesarEncrypt(char *text, int key) {
    for (int i = 0; text[i] != '\0'; i++) {
        char ch = text[i];
        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            text[i] = (ch - base + key) % 26 + base;
        }
    }
}

void caesarDecrypt(char *text, int key) {
    caesarEncrypt(text, 26 - (key % 26));
}

int main() {
    char message[100];
    int key;

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';  // remove newline

    printf("Enter Caesar key (0-25): ");
    scanf("%d", &key);

    caesarEncrypt(message, key);
    printf("Encrypted: %s\n", message);

    caesarDecrypt(message, key);
    printf("Decrypted: %s\n", message);

    return 0;
}
