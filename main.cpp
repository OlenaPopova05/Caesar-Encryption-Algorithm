#include <iostream>
#include <dlfcn.h>
using namespace std;

int main() {
    int key;
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

    cout << "Enter the text: ";
    getline(cin, text);
    cout << "Enter the key: ";
    cin >> key;

    string encrypted_text = encryption(text, key);
    cout << "Encrypted text: " << encrypted_text << endl;

    string decrypted_text = decryption(encrypted_text, key);
    cout << "Decrypted text: " << decrypted_text << endl;

    dlclose(handle);

    return 0;
}