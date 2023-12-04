#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

int main() {
    ifstream file("input");
    string line;
    string lines[3] = {"", "", ""};
    bool firstrun = true;

    if (!file.is_open())
        cout << "Unable to open file" << endl;

    while (getline(file, line)) {
        i = i%3;
        lines[i] = line;
        if (i == 2)
            firstrun = false;
        if (not firstrun) {
            for (int j=0; j<line.size(); j++)
                if (isdigit(lines[1][j])
        }
        i++;
    }

    file.close();

    return 0;
}

