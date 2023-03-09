#include <iostream>
#include <fstream>
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
    // cout << endl;
    // cout << C_WHITE << "---- Currently Remaining ----" << endl;
    // cout << C_GOLD << "Mugs: " << C_RESET << data[0] << endl;
    // cout << C_GREEN << "Keychains: " << C_RESET << data[1] << endl;
    // cout << C_RED << "Plushies: " << C_RESET << data[2] << endl; 
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
    cout << C_GOLD <<  "     Mugs: " << C_RESET << (data[0] * 0.909) << endl;
    cout << C_GREEN << "Keychains: " << C_RESET << (data[1] * 0.849) << endl;
    cout << C_RED <<   " Plushies: " << C_RESET << (data[2] * 0.873) << endl;
    cout << C_WHITE << "    Total: " << C_RESET << (data[0] * 0.909) + (data[1] * 0.849) + (data[2] * 0.873) << endl;
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

int main () {

    long* data = new long[3]{ 0 }; // MUGS KEYCHAINS PLUSHIES
    Event* currentEvent = nullptr;
    int linesToClear = 0;
    load(data);

    string input;
    while (input != "exit") {
        status(data, currentEvent);
        cout << C_GRAY << "> " << C_RESET ;
        cin >> input;
        if (input == "set") {
            string sel;
            cin >> sel;
            int index = 0;
            if (sel == "keychains") index = 1;
            else if (sel == "plushies") index = 2;
            cin >> sel;
            data[index] = atoi(sel.c_str());
        } else if (input == "run") {
            string t1, t2;
            cout << C_GOLD << "Mugs " << C_GRAY << "(Count/Bonus): " << C_RESET;
            cin >> t1;
            cin >> t2;
            data[0] -= atoi(t1.c_str()) * (3 + atoi(t2.c_str()));
            cout << C_GREEN << "Keychains " << C_GRAY << "(Count/Bonus): " << C_RESET;
            cin >> t1;
            cin >> t2;
            data[1] -= atoi(t1.c_str()) * (3 + atoi(t2.c_str()));
            cout << C_RED << "Plushies " << C_GRAY << "(Count/Bonus): " << C_RESET;
            cin >> t1;
            cin >> t2;
            data[2] -= atoi(t1.c_str()) * (3 + atoi(t2.c_str()));
        } else if (input == "ap") ap(data);
    }

    save(data);
    cout << endl;
    delete[](data);
    return 0;
}
