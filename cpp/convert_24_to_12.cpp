#include <iostream>
#include <string>
using namespace std;

int main() {
    string inputTime;
    cout << "Enter time (hh:mm) in 24-hour notation (for example, 12:56): ";
    cin >> inputTime;

    size_t found = inputTime.find(':');

    if (found == string::npos) {
        cout << "Invalid Input, : not found\n";
        return -1;
    }

    int hour = stoi(inputTime.substr(0, found)), minute = stoi(inputTime.substr(found+1));
    if ( (hour < 0 || hour > 23) || ( minute < 0 || minute > 59)) {
        cout << "Invalid input wrong hour/minute\n";
        return -1;
    }

    if (hour == 0) {
        hour = 12;
    }

    if (hour <= 11) {
        cout << hour << ":" << minute << " AM\n"; 
    } else if (hour == 12) {
        cout << hour << ":" << minute << " PM\n"; 
    } else {
        cout << hour % 12 << ":" << minute << " PM\n";
    }
    return 0;
}