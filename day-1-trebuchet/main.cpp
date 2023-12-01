#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <iterator>
using namespace std;

char numeral_to_digit(string numeral) {
    string spelled[9] = {
        "one", "two", "three",
        "four", "five", "six",
        "seven", "eight", "nine"};

    int size = std::size(numeral);
    for (int i=0; i<10; i++) {
        for (int start=0; start<size; start++) {
            for (int len=3; len<=5 and start+len <= size; len++) {
                if (numeral.substr(start, len) == spelled[i]) {
                    // adding '0' converts int to char
                    return (i+1) + '0';
                }
            }
        }
    } 

    return '0';
}

int find_first_last_numerals(string line) {
    char first = '0', last = '0';
    string numeral = "";
    int found = 0;
    char digit = '0';

    for (auto letter : line) {
        if (not isdigit(letter))
            numeral += letter;
        if (size(numeral) > 2)
            digit = numeral_to_digit(numeral);
        if (digit != '0' or isdigit(letter)) {
            if (found == 0) {
                found++;
                if (digit != '0') {
                    first = digit;
                    last = digit;
                } else {
                    first = letter;
                    last = letter;
                }
            } else if (found > 0) {
                if (digit != '0')
                    last = digit;
                else 
                    last = letter;
            }
        }
        if (digit != '0') {
            numeral = numeral[size(numeral)-1];
            digit = '0';
        }
    }   
    cout << "FIRST " << first << " LAST " << last << endl;
    return ((first - '0') * 10) + last - '0';
}

int find_first_last_digits_only(string line) {
    char first = '0', last = '0';
    int found = 0;

    for (auto letter : line) {
        if (isdigit(letter)) {
            if (found == 0) {
                found++;
                first = letter;
                last = letter;
            } else if (found > 0) {
                last = letter;
            }
        }   
    }

    return ((first - '0') * 10) + last - '0';
}

int main() {
    ifstream file("input");
    file.is_open();
    string line;
    int sum_num = 0, sum_dig = 0;

    while (getline(file, line)) {
        // "1" and "one" are both numerals
        sum_num += find_first_last_numerals(line); 
        // only "1", "2", etc, allowed
        sum_dig += find_first_last_digits_only(line); 
    }

    cout << "The sum of the calibration codes (digits) is: " << sum_dig << endl;
    cout << "The sum of the calibration codes (numerals) is: " << sum_num << endl;

    file.close();
    
    return 0;
}

