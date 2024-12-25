#include "consoleUtil.h"
#include <Windows.h>
using std::string;
using std::cout;
using std::cin;

void printSpacerL() {
    cout << "-------------------------------------------------------------------------\n";
}

void printSpacerS() {
    cout << "########\n";
}

void printSpacerGap(int x) {
    for (x; x > 0; --x) {
        cout << '\n';
    }
}

string promptUserInputString(string prompt) {
    printSpacerGap(6);
    printSpacerL();
    string response;
    cout << prompt << ": ";
    cin >> response;
    cin.clear();
    cin.ignore(100000000000, '\n');
    printSpacerL();
    return response;
}

int promptUserInputInt(string prompt) {
    printSpacerL();
    int response;
    cout << prompt << ": ";
    cin >> response;
    cin.clear();
    cin.ignore(100000000000, '\n');
    printSpacerL();
    return response;
}

void printToConsole(string s) {
    cout << s << '\n';
}

void pause(double milliseconds) {
    //std::system("pause");
    Sleep(milliseconds);
}

void pause() {
    std::system("pause");
}