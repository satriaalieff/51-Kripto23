#include <iostream>
using namespace std;

string encrypt(int key, char str[])
{
    char temp;
    for (int i = 0; str[i] != '\0'; i++)
    {
        temp = str[i]; 
        if (temp >= 'a' && temp <= 'z'){
            temp = temp + key;

            if (temp > 'z'){
                temp = temp - 'z' + 'a' - 1;   
            }
            str[i] = temp;  
        }
        else if (temp >= 'A' && temp <= 'Z') {
            temp = temp + key;

            if (temp > 'Z') {
                temp = temp - 'Z' + 'A' - 1;
            }

            str[i] = temp;
        }
    }
    cout << "Encrypted Text : " << str << endl;
}

string decrypt(int key, char str[]) {
    char temp;
    for (int i = 0; str[i] != '\0'; i++) {
        temp = str[i];
        if (temp >= 'a' && temp <= 'z') {
            temp = temp - key;  

            if (temp > 'z') {
                temp = temp - 'z' + 'a' - 1;
            }
            str[i] = temp;
        }
        else if (temp >= 'A' && temp <= 'Z') {
            temp = temp - key;

            if (temp > 'Z') {
                temp = temp - 'Z' + 'A' - 1;
            }
            str[i] = temp;
        }
    }
    cout << "Decrypted Text : " << str << endl;
}

int main() {
    int key;
    int x;
    char str[99];

    do {
        cout << "Choose :\n";
        cout << "1. Encrypt\n";
        cout << "2. Decrypt\n";
        cout << "3. Exit\n";
        cin >> x;

        switch (x) {
            case 1:
                cout << "Input Plain Text : ";
                cin.ignore(100, '\n');
                cin.getline(str, sizeof(str));

                cout << "Input Key : ";
                cin >> key;

                encrypt(key, str);
                cout << endl;

                break;
            case 2:
                cout << "Input Plain Text : ";
                cin.ignore(100, '\n');
                cin.getline(str, sizeof(str));

                cout << "Input Key : ";
                cin >> key;

                decrypt(key, str);
                cout << endl;

                break;
            default:
                break;
            }
    } while (x != 3);
}