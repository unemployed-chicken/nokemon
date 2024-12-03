#include "consoleUtil.h"
using std::string;
using std::cout;
using std::cin;

void printSpacerL() {
    cout << "-------------------------------------------------------------------------\n";
}

void printSpacerS() {
    cout << "########\n";
}

string promptUserInputString(string prompt) {
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