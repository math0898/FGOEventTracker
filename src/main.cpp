#include <iostream>
#include <fstream>
#include <vector>
#include "color_codes.hpp"
#include "event.hpp"

#define HUMAN_BRONZE "Mugs"
#define HUMAN_SILVER "Keychains"
#define HUMAN_GOLD "Plushies"

using namespace std;

/**
 * @brief Utility method to print out the current collection counts.
 * 
 * @param data The data to print to the console.
 * @param event The currently loaded event.
 */
void status (long* data, Event* event) {
    cout << C_GRAY << " ---- Current Event: ";
    if (event == nullptr) cout << " No Event Loaded";
    else cout << event->getDisplayname();
    cout << " ---- " << endl;
    cout << C_MAGENTA << HUMAN_BRONZE << " (" << data[0] << ") ";
    cout << C_WHITE << HUMAN_SILVER << " (" << data[1] << ") ";
    cout << C_GOLD << HUMAN_GOLD << " (" << data[2] << ") ";
}

/**
 * @brief Utility method to print out the current ap usage counts.
 * 
 * @param data The data to print to the console.
 */
void ap (long* data) {
    cout << endl;
    cout << C_WHITE << "     ---- Remaining AP Costs ----     " << endl;
    cout << C_GRAY <<  "(Assumes optimal single farming nodes)" << endl;
    cout << C_MAGENTA <<  "     Mugs: " << C_RESET << (data[0] * 0.909) / 3.0 << endl;
    cout << C_WHITE << "Keychains: " << C_RESET << (data[1] * 0.849) / 3.0 << endl;
    cout << C_GOLD <<   " Plushies: " << C_RESET << (data[2] * 0.873) / 3.0 << endl;
    cout << C_GREEN << "    Total: " << C_RESET << (data[0] * 0.909) / 3.0 + (data[1] * 0.849) / 3.0 + (data[2] * 0.873) / 3.0 << endl;
    
    cout << endl;
    cout << C_GRAY <<  "(Assumes optimal multiple farming node)" << endl;
    double* rates = new double[3]{ 1.451, 1.412, 1.387 };
    cout << C_MAGENTA <<  "     Mugs: " << C_RESET << (data[0] * rates[0]) / 3.0 << endl;
    cout << C_WHITE << "Keychains: " << C_RESET << (data[1] * rates[1]) / 3.0 << endl;
    cout << C_GOLD <<   " Plushies: " << C_RESET << (data[2] * rates[2]) / 3.0 << endl;
    int runs = 0;
    for (int i = 0; i < 3; i++) {
        int t = 0;
        for (; data[i] - (t * rates[i] * 40) > 0; t++);
        if (t > runs) runs = t;
    }
    delete[](rates);

    cout << C_GREEN << "    Total: " << C_RESET << runs * 40 << " (" << runs << " runs)" << endl;
}

/**
 * @brief Saves data to a local file.
 * 
 * @param data The long array to pull the data from.
 */
void save (long* data) {
    fstream* file = new fstream();
    file->open("data.yml", ios::out);

    file->clear();
    *file << "mugs: " << data[0] << endl;
    *file << "keychains: " << data[1] << endl;
    *file << "plushies: " << data[2] << endl;

    file->close();
    delete(file);
}

/**
 * @brief Loads data from a local file.
 * 
 * @param data The long array to dump the data to.
 */
void load (long* data) {

    fstream* file = new fstream();
    file->open("data.yml", ios::in);
    if (!file->is_open()) {
        save(new long[3]{ 0 });
        file->open("data.yml", ios::in);
    }

    string temp("c");
    int index = 0;

    while (!file->eof() && temp != "") {
        *file >> temp;
        if (temp == "mugs:") index = 0;
        else if (temp == "keychains:") index = 1;
        else if (temp == "plushies:") index = 2;
        *file >> temp;
        data[index] = atoi(temp.c_str());
    }

    file->close();
    delete(file);
}

int c_strLength (char* str, int length) {
    for (int i = 0; i < length; i++) if (str[i] == (char) NULL) return i + 1;
    return length;
}

vector<string> argsFromString (string str) {
    vector<string> v = vector<string>();
    int j = 0;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == ' ') {
            v.push_back(str.substr(j, i - j));
            j = i + 1;
        } else if (i == str.size() - 1) v.push_back(str.substr(j, i - j  + 1));
    }
    return v;
}

int main () {

    long* data = new long[3]{ 0 }; // MUGS KEYCHAINS PLUSHIES
    Event* currentEvent = nullptr;
    int linesToClear = 0;
    load(data);

    string input;
    char* buffer = new char[256]{ ' ' };
    while (input != "exit") {
        for (int i = 0; i < 3; i++) if (data[i] < 0) data[i] = 0;
        status(data, currentEvent);
        cout << C_GRAY << "> " << C_RESET;
        cin.getline(buffer, 256);
        input = string(buffer, c_strLength(buffer, 256) - 1); // -1 to remove trailing newline
        vector<string> args = argsFromString(input);
        if (args[0] == "prisms") {
            cout << "Hello world!" << endl;
            string sel;
            long days = 0;
            long target = 0;
            long current = 0;
            const long AP_PER_APPLE = 137;
            const float AP_PER_PRISM = 3.333;
            cout << C_YELLOW << "Days: ";
            cin >> sel;
            days = atoi(sel.c_str()) - 1;
            cout << CURSOR_UP << ERASE_IN_LINE << C_WHITE << "Current: ";
            cin >> sel;
            current = atoi(sel.c_str());
            cout << CURSOR_UP << ERASE_IN_LINE << C_GREEN << "Target: ";
            cin >> sel;
            target = atoi(sel.c_str());
            cout << CURSOR_UP << ERASE_IN_LINE << C_GRAY << "Have: " << current << "/" << target << " (" << ((float) current ) / ((float) target) * 100.0 << ")" << endl;
            const long PASSIVE_AP = (days * 24 * 60) / 5; // 24 hours, 60 minutes, 1 AP : 5 minutes
            const double NEEDED_AP = (target - current - (days * 30)) * AP_PER_PRISM;
            cout << C_GRAY << "Passive AP: " << PASSIVE_AP << endl;
            cout << C_GRAY << "Needed AP: " << NEEDED_AP << endl;
            if (PASSIVE_AP > NEEDED_AP) cout << C_GRAY << "Use: " << (NEEDED_AP / PASSIVE_AP) * 100.0<< "\% of AP" << endl;
            else cout << C_GRAY << "Deficit: " << (NEEDED_AP - PASSIVE_AP) / AP_PER_APPLE << " Apples" << endl;
        } else if (args[0] == "set") {
            string sel;
            cin >> sel;
            int index = 0;
            if (sel == "keychains") index = 1;
            else if (sel == "plushies") index = 2;
            cin >> sel;
            data[index] = atoi(sel.c_str());
        } else if (args[0] == "run") {
            char* buffer = new char[16]{ ' ' };
            cout << C_MAGENTA << "Mugs " << C_GRAY << "(Count/Bonus): " << C_RESET;
            cin.getline(buffer, 16);
            vector<string> t = argsFromString(buffer);
            data[0] -= atoi(t[0].c_str()) * (3 + atoi(t[1].c_str()));
            cout << CURSOR_UP << ERASE_IN_LINE << C_WHITE << "Keychains " << C_GRAY << "(Count/Bonus): " << C_RESET;
            cin.getline(buffer, 16);
            t = argsFromString(buffer);
            data[1] -= atoi(t[0].c_str()) * (3 + atoi(t[1].c_str()));
            cout << CURSOR_UP << ERASE_IN_LINE << C_GOLD << "Plushies " << C_GRAY << "(Count/Bonus): " << C_RESET;
            cin.getline(buffer, 16);
            t = argsFromString(buffer);
            data[2] -= atoi(t[0].c_str()) * (3 + atoi(t[1].c_str()));
            cout << CURSOR_UP << ERASE_IN_LINE;
        } else if (args[0] == "ap") ap(data);
    }

    save(data);
    cout << endl;
    delete[](data);
    return 0;
}
