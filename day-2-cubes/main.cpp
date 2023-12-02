#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
using namespace std;

const int MAXRED = 12;
const int MAXGREEN = 13;
const int MAXBLUE = 14;

int find_space_char(string word) {
    for (int i=0; i<size(word); i++)
        if (word[i] == ' ')
            return i;
    return 0;
}

int find_comma_char(string word) {
    for (int i=0; i<size(word); i++)
        if (word[i] == ',' or word[i] == ';')
            return 1;
    return 0;
}

int check_bag_cubes(int num, string color) {
    if (color == "red") {
        if (num > MAXRED)
            return 0;
    } else if (color == "green") {
        if (num > MAXGREEN)
            return 0;
    } else if (color == "blue") {
        if (num > MAXBLUE)
            return 0;
    }
    return 1;
}

int analyze_game(string line, int lsize) {
    int tbeg = 0, tend = 0; /* token begin/end */
    string word = "";
    int i = 0;
    int gameid = 0;
    int current_cubes = 0;
    string current_color = "";
    int lread = 0;

    for (char letter : line) {
        lread++;
        i++;
        word += letter;
        if (letter == ':') {
            tbeg = find_space_char(word);
            tend = i-tbeg-1;
            gameid = stoi(word.substr(tbeg, tend));
            word = "";
            i = 0;
        } else if (letter == ',' or letter == ';' or lread == lsize) {
            tbeg = find_space_char(word)+1;
            word = word.substr(tbeg, size(word));
            tend = find_space_char(word);
            current_cubes = stoi(word.substr(tbeg-1, tend));
            tbeg = find_space_char(word)+1;
            word = word.substr(tbeg);
            if (find_comma_char(word))
                current_color = word.substr(0, size(word)-1);
            else
                current_color = word.substr(0, size(word));
            word = "";
            i = 0;
            if (not check_bag_cubes(current_cubes, current_color))
                return 0;
        }
    }   
    return gameid;
}

void update_cubes_minimum(int num, string color, int *red, int *green, int *blue) {
    if (color == "red") {
        if (num > *red)
            *red = num;
    } else if (color == "green") {
        if (num > *green)
            *green = num;
    } else if (color == "blue") {
        if (num > *blue)
            *blue = num;
    }
}

int analyze_game_minimum(string line, int lsize) {
    int tbeg = 0, tend = 0; /* token begin/end */
    string word = "";
    int i = 0;
    int gameid = 0;
    int current_cubes = 0;
    string current_color = "";
    int lread = 0;
    int maxred = 0, maxgreen = 0, maxblue = 0;

    for (char letter : line) {
        lread++;
        i++;
        word += letter;
        if (letter == ':') {
            tbeg = find_space_char(word);
            tend = i-tbeg-1;
            gameid = stoi(word.substr(tbeg, tend));
            word = "";
            i = 0;
        } else if (letter == ',' or letter == ';' or lread == lsize) {
            tbeg = find_space_char(word)+1;
            word = word.substr(tbeg, size(word));
            tend = find_space_char(word);
            current_cubes = stoi(word.substr(tbeg-1, tend));
            tbeg = find_space_char(word)+1;
            word = word.substr(tbeg);
            if (find_comma_char(word))
                current_color = word.substr(0, size(word)-1);
            else
                current_color = word.substr(0, size(word));
            word = "";
            i = 0;
            update_cubes_minimum(current_cubes, 
                                 current_color,
                                 &maxred, &maxgreen, &maxblue);
        }
    }   
    return maxred*maxgreen*maxblue;
}

int main() {   
    ifstream file("input");
    file.is_open();
    string line;
    int sum_ids = 0;
    int sum_pws = 0;

    while (getline(file, line)) {
        sum_ids += analyze_game(line, size(line)); 
        sum_pws += analyze_game_minimum(line, size(line)); 
    }

    cout << "The sum of the ids where the game is possible: " << sum_ids << endl;
    cout << "The sum of the powers of the minimum number of cubes in each game is: " << sum_pws << endl;

    file.close();
 
    return 0;
}
