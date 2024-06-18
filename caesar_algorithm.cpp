#include <iostream>
#include <string>
#include <cctype>
using namespace std;

extern "C" {
    string encryption(string text, int key){
        key = key % 26;
        if (key < 0) {
            key = 26 + key;
        }
        string result = "";
        for (unsigned int i = 0; i < text.length(); i++) {
            char c = text[i];
            if(isupper(c)) {
                int x = c - 'A' + key;
                x = x % 26;
                c = (char) (x + 'A');
            }
            else if (islower(c)){
                int x = c - 'a' + key;
                x = x % 26;
                c = (char) (x + 'a');
            }
            result += c;
        }
        return result;
    }

    string decryption(string text, int key){
        key = key % 26;
        if (key < 0) {
            key = 26 + key;
        }
        string result = "";
        for (unsigned int i = 0; i < text.length(); i++) {
            char c = text[i];
            if(isupper(c)) {
                int x = c - 'A' - key;
                if (x < 0) {
                    x = 26 + x;
                }
                c = (char) (x + 'A');
            }
            else if (islower(c)){
                int x = c - 'a' - key;
                if (x < 0) {
                    x = 26 + x;
                }
                c = (char) (x + 'a');
            }
            result += c;
        }
        return result;
    }
}