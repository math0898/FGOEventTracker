#include <iostream>
#include <fstream>
#include "color_codes.hpp"

using namespace std;

/**
 * @brief Utility method to print out the current collection counts.
 * 
 * @param data The data to print to the console.
 */
void status (long* data) {
    cout << endl;
    cout << C_WHITE << "---- Currently Remaining ----" << endl;
    cout << C_GOLD << "Dry Firewood: " << C_RESET << data[0] << endl;
    cout << C_GREEN << "Fresh Vegetables: " << C_RESET << data[1] << endl;
    cout << C_RED << "Mini Chainsaws: " << C_RESET << data[2] << endl; 
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
    cout << C_GOLD <<  "    Dry Firewood: " << C_RESET << (data[0] * 0.899) << endl;
    cout << C_GREEN << "Fresh Vegetables: " << C_RESET << (data[1] * 0.866) << endl;
    cout << C_RED <<   "  Mini Chainsaws: " << C_RESET << (data[2] * 0.868) << endl;
    cout << C_WHITE << "           Total: " << C_RESET << (data[0] * 0.899) + (data[1] * 0.866) + (data[2] * 0.868) << endl;
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
    *file << "wood: " << data[0] << endl;
    *file << "veggies: " << data[1] << endl;
    *file << "saws: " << data[2] << endl;

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
        if (temp == "wood:") index = 0;
        else if (temp == "veggies:") index = 1;
        else if (temp == "saws:") index = 2;
        *file >> temp;
        data[index] = atoi(temp.c_str());
    }

    file->close();
    delete(file);
}

int main () {

    long* data = new long[3]{ 0 }; // WOOD VEGGIES SAWS
    load(data);

    string input;
    while (input != "exit") {
        status(data);
        cout << endl << C_GRAY << "> " << C_RESET ;
        cin >> input;
        if (input == "set") {
            string sel;
            cin >> sel;
            int index = 0;
            if (sel == "veggies") index = 1;
            else if (sel == "saws") index = 2;
            cin >> sel;
            data[index] = atoi(sel.c_str());
        } else if (input == "run") {
            string t1, t2;
            cout << C_GOLD << "Wood " << C_GRAY << "(Count/Bonus): " << C_RESET;
            cin >> t1;
            cin >> t2;
            data[0] -= atoi(t1.c_str()) * (3 + atoi(t2.c_str()));
            cout << C_GREEN << "Veggies " << C_GRAY << "(Count/Bonus): " << C_RESET;
            cin >> t1;
            cin >> t2;
            data[1] -= atoi(t1.c_str()) * (3 + atoi(t2.c_str()));
            cout << C_RED << "Saws " << C_GRAY << "(Count/Bonus): " << C_RESET;
            cin >> t1;
            cin >> t2;
            data[2] -= atoi(t1.c_str()) * (3 + atoi(t2.c_str()));
        } else if (input == "ap") ap(data);
    }

    save(data);
    cout << endl;
    delete(data);
    return 0;
}
