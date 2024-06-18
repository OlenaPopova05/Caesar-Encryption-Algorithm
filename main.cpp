#include <iostream>
#include <dlfcn.h>
using namespace std;

int main() {
    int choice, key;
    string text;

    void* handle = dlopen("/Users/olenapopova/Documents/GitHub/Caesar-Encryption-Algorithm/caesar_atgorithm.dylib", RTLD_LAZY);
    if (!handle) {
        cerr << "Error: " << dlerror() << endl;
        return 1;
    }

    typedef string (*encrypt_func)(const string&, int);
    encrypt_func encryption = (encrypt_func) dlsym(handle, "encryption");
    if (!encryption) {
        cerr << "Error: " << dlerror() << endl;
        dlclose(handle);
        return 1;
    }

    typedef string (*decrypt_func)(const string&, int);
    decrypt_func decryption = (decrypt_func) dlsym(handle, "decryption");
    if (!decryption) {
        cerr << "Error: " << dlerror() << endl;
        dlclose(handle);
        return 1;
    }

    while (true) {
        cout << "Do you want to (1) Encrypt or (2) Decrypt? ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter the text: ";
            cin.ignore(); // ignore the newline character left in the input buffer
            getline(cin, text);
            cout << "Enter the key: ";
            cin >> key;

            string encrypted_text = encryption(text, key);
            cout << "Encrypted text: " << encrypted_text << endl;
        } else if (choice == 2) {
            cout << "Enter the text: ";
            cin.ignore(); // ignore the newline character left in the input buffer
            getline(cin, text);
            cout << "Enter the key: ";
            cin >> key;

            string decrypted_text = decryption(text, key);
            cout << "Decrypted text: " << decrypted_text << endl;
        } else {
            cout << "Invalid choice. Please try again." << endl;
            continue;
        }

        cout << "Do you want to continue? (y/n) ";
        char response;
        cin >> response;

        if (response == 'n') {
            break;
        }
    }

    dlclose(handle);

    return 0;
}