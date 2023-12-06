#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

typedef enum {
    upper,
    current,
    bottom
} line_env;

typedef struct {
    int beg;
    int end;
    bool part;
    int value;
} numpos;

bool isspecial(char symbol) {
    return (symbol == '*' or symbol == '#' or symbol == '@' or
            symbol == '/' or symbol == '+' or symbol == '$' or
            symbol == '%' or symbol == '=' or symbol == '-' or
            symbol == '&');
}

/* check if any num has adjacent symbols below, above, or in the same line */
void check(int pos, line_env where, vector<numpos> &linenums, vector<string> lines) {
    for (auto &i : linenums) {
        if (where == current) {
            if (i.beg-1 >= 0 and isspecial(lines[pos][i.beg-1]))
                i.part = true;
            else if (i.end+1 < lines[pos].size() and
                     isspecial(lines[pos][i.end+1]))
                i.part = true;
        } else if (where == upper) {
            for (int j=i.beg-1; j<=i.end+1; j++)
                if (i.beg-1 >=0 and i.end+1 < lines[pos].size())
                    if (isspecial(lines[pos-1][j]))
                        i.part = true;
        } else if (where == bottom) {
            for (int j=i.beg-1; j<=i.end+1; j++)
                if (i.beg-1 >=0 and i.end+1 < lines[pos].size())
                    if (isspecial(lines[pos+1][j]))
                        i.part = true;
        }
    }
}


/* finds number positions in current line */
void findnums(vector<numpos> &linenums, string line) {
    numpos newpos;
    newpos.part = false;
    newpos.value = 0;
    string snum = "";

    for (int i=0; i<line.size(); i++) {
        if (isdigit(line[i])) {
            newpos.beg = i;
            snum += line[i];
            while (isdigit(line[i])) {
                i++;
                snum += line[i];
            }
            i--;
            newpos.value = stoi(snum);
            newpos.end = i;
            linenums.push_back(newpos);
            snum = "";
        }
    }
}

void sumparts(int &sum, vector<numpos> linenums) {
    for (auto part : linenums) {
        if (part.part) {
//            cout << "NUM: " << part.value << endl;
            sum += part.value;
        }
    }
    cout << endl;
}

void slidein(string line, vector<string> &lines) {
    lines[0] = lines[1];
    lines[1] = lines[2];
    lines[2] = line;
}

int main() {
    ifstream file("input");
    string line;
    vector<string> lines(3, "");
    int envloop=0, ln=-1;
    vector<numpos> linenums;
    int sum = 0;

    if (!file.is_open())
        cout << "Unable to open file" << endl;

    while (getline(file, line)) {
        envloop = envloop%3;
        ln++;
        if (ln < 2) {
            lines[ln] = line;
            if (ln == 1) {
                findnums(linenums, lines[0]);
                check(0, current, linenums, lines);
                check(0, bottom, linenums, lines);
            }

        } else if (ln >= 2 and ln <= 139) {
            if (ln == 2) {
                lines[ln] = line;
            } else {
                slidein(line, lines);
            }
            findnums(linenums, lines[1]);
            check(1, current, linenums, lines);
            check(1, upper, linenums, lines);
            check(1, bottom, linenums, lines);
            if (ln == 139) {
                linenums.clear();
                findnums(linenums, lines[2]);
                check(2, current, linenums, lines);
                check(2, upper, linenums, lines);
            }
        }
        sumparts(sum, linenums);
        linenums.clear();
                /*
                cout << "-----===== LINE " << ln << " =====-----" << endl;
                for (auto part : linenums) {
                    cout << "PART? " << part.part 
                         << " BEG: " << part.beg 
                         << " END: " << part.end << endl;
                }*/
        envloop++;
    }

    cout << "The sum of the part numbers of the engine is: " << sum << endl;

    file.close();

    return 0;
}

