#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// 構造体の定義
typedef struct {
    char name[64];
    char email[64];
    int age;
    char gender[64];
} Contact;

// 関数宣言
void addContact(Contact* c, int* count);
void displayContacts(const Contact* contacts, int count);
void saveContacts(const Contact* contacts, int count);
void loadContacts(Contact* contacts, int* count);
void searchContacts(const Contact* contacts, int count);
int menu();

// メイン関数
int main() {
    Contact contacts[64];
    int count = 0;

    int choice;
    do {
        choice = menu();
        switch (choice) {
        case 1:
            addContact(contacts, &count);
            break;
        case 2:
            displayContacts(contacts, count);
            break;
        case 3:
            saveContacts(contacts, count);
            break;
        case 4:
            loadContacts(contacts, &count);
            break;
        case 5:
            searchContacts(contacts, count);
            break;
        }
    } while (choice != 0);

    return 0;
}

// メニュー表示関数
int menu() {
    int choice;
    printf("1: Add Contact\n");
    printf("2: Display Contacts\n");
    printf("3: Save Contacts\n");
    printf("4: Load Contacts\n");
    printf("5: Search Contacts\n");
    printf("0: Exit\n");
    printf("Enter your choice: ");
    printf("\n");
    scanf("%d", &choice);
    return choice;
}

// 連絡先追加関数
void addContact(Contact* contacts, int* count) {
    if (*count >= 64) {
        printf("Contact list is full!\n");
        return;
    }

    Contact newContact;
    printf("Enter name: ");
    scanf("%s", newContact.name);
    printf("Enter email: ");
    scanf("%s", newContact.email);
    printf("Enter age: ");
    scanf("%d", &newContact.age);
    printf("Enter gender(M or F): ");
    scanf("%s", newContact.gender);

    contacts[*count] = newContact;
    (*count)++;
}

// 連絡先表示関数
void displayContacts(const Contact* contacts, int count) {
    printf("Contacts:\n");
    for (int i = 0; i < count; i++) {
        printf("Name: %s, Email: %s, Age: %d, Gender: %s\n", contacts[i].name, contacts[i].email, contacts[i].age, contacts[i].gender);
    }

}

// 連絡先保存関数
void saveContacts(const Contact* contacts, int count) {
    FILE* file = fopen("contacts.dat", "wb");
    if (file == NULL) {
        printf("Unable to open file for writing.\n");
        return;
    }

    fwrite(contacts, sizeof(Contact), count, file);
    fclose(file);
    printf("Contacts saved.\n");
}

// 連絡先読み込み関数
void loadContacts(Contact* contacts, int* count) {
    FILE* file = fopen("contacts.dat", "rb");
    if (file == NULL) {
        printf("Unable to open file for reading.\n");
        return;
    }

    *count = fread(contacts, sizeof(Contact), 50, file);
    fclose(file);
    printf("Contacts loaded.\n");
}

 // 小文字変換関数
void toLowerString(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}


 // 連絡先検索関数
void searchContacts(const Contact* contacts, int count) {
    char searchName[64];
    printf("Enter name to search: ");
    scanf("%s", searchName);
    toLowerString(searchName); //検索名を小文字に変換する

    int found = 0;
    for (int i = 0; i < count; i++) {

        char contactName[64];
        strcpy(contactName, contacts[i].name);
        toLowerString(contactName); //連絡先内の名前を小文字に変換
        

        if (strcmp(contactName, searchName) == 0) {
            printf("Contact found: Name: %s, Email: %s, Age: %d\n", contacts[i].name, contacts[i].email, contacts[i].age, contacts[i].gender);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Contact not found. \n");
    }
}