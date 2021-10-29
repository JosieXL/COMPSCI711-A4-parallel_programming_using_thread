// NewMakeApp.cpp : This is the cpp file that used to build exe file and do similar but simpler thing as make.exe
// Author: Josie Li
// ID Number: 455398598
// UPI: xli556
// Update date: 6th September 2021

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <regex>
#include <thread>
#include <mutex>

using namespace std;

vector<string> isContainSub(vector<string> strVec, vector<string> substring);
mutex mtx;


vector<vector<string>> getAccess(vector<vector<vector<string>>> targetDependency, string dependString, vector<vector<string>> commandPrintAll, vector<vector<string>> command) {
    for (int j = 1; j < targetDependency.size(); j++) {
        if (targetDependency[j][0][0] == dependString) {
            vector<string> dependency = isContainSub(targetDependency[j][1], { ".o", ".obj", ".lib", ".so", ".a", ".dll" });
            if (dependency.size() != 0) {
                // Make sure the command for library is also included
                for (int e = 1; e < command.size(); e++) {
                    if (command[e][0] == targetDependency[j][0][0]) {
                        commandPrintAll.push_back({ command[e].begin() + 1, command[e].end() });
                    }
                }
                for (int k = 0; k < dependency.size(); k++) {
                    commandPrintAll = getAccess(targetDependency, dependency[k], commandPrintAll, command);
                }
            }
            else {
                for (int e = 1; e < command.size(); e++) {
                    if (command[e][0] == targetDependency[j][0][0]) {
                        commandPrintAll.push_back({ command[e].begin() + 1, command[e].end() });
                    }
                }
            }
        }
    }
    return commandPrintAll;
}

vector<string> isContainSub(vector<string> strVec, vector<string> substring) {
    vector<string> result;
    for (int i = 0; i < strVec.size(); i++) {
        for (int j = 0; j < substring.size(); j++) {
            if (strVec[i].find(substring[j]) != strVec[i].npos) {
                result.push_back(strVec[i]);
            }
        }
    }
    return result;
}

bool isContain(vector<string> strVec, vector<string> substring) {
    for (int i = 0; i < strVec.size(); i++) {
        for (int j = 0; j < substring.size(); j++) {
            if (strVec[i].find(substring[j]) != strVec[i].npos) {
                return true;
            }
        }
    }
    return false;
}

void stringSplitByString(const string& str, const string& split, vector<string>& result) {
    if (str == "") return;
    string strs = str + split;
    int position = strs.find(split);
    int step = split.size();
    while (position != strs.npos) { // if strs cannot find the split
        string temp = strs.substr(0, position);
        result.push_back(temp);
        strs = strs.substr(position + step, strs.size());
        position = strs.find(split);
    }
}

void print_command(vector<string> command) {
    //mutex mtx;
    mtx.lock();
    for (int k = 0; k < command.size(); k++) {
        cout << command[k] << endl;
        system(command[k].c_str());
    }
    mtx.unlock();
}

int main(int argc, char *argv[])
{
    vector<vector<vector<string>>> targetDependency;
    vector<vector<string>> middle, command, commandPrintAll, commandSub, commandSubn;
    vector<string> firstSplit, secondSplit;
    string inputLine, target;
    ifstream input_file;

    regex str_targetDependency("[a-zA-Z0-9_-]+\\.[a-zA-Z]+\\:(\\s[a-zA-Z0-9_-]+\\.[a-zA-Z]+)+\\n");
    regex str_command("\\tg\\+\\+(\\s-[a-zA-Z]+(\\s[a-zA-Z0-9_-]+\\.[a-zA-Z]+)+)+\\n");
    
    if (argc == 1) {
        string file = "Makefile";
        input_file.open(file);
        bool isOpen = true;
        if (input_file.fail()) {
            isOpen = false;
            //cout << "No required " << file << endl;
            input_file.close();
        }
        if (isOpen == false) {
            string file = "makefile";
            input_file.open(file);
            isOpen = true;
            if (input_file.fail()) {
                isOpen = false;
                //cout << "No required " << file << endl;
                input_file.close();
            }
        }
        if (isOpen == false) {
            cout << "No required Makefile/makefile" << endl;
        }
    }
    else if ((argc == 3)) {
        string file = argv[2];
        input_file.open(file);
        if (input_file.fail()) {
            cout << "Error opening " << file << endl;
            input_file.close();
        }
    }
    
    while (getline(input_file, inputLine)) {
        //Using getline will return the string one index before the new line character, so to match the syntax need to add the new line character.
        inputLine = inputLine + "\n"; 
        bool matchTD = regex_match(inputLine, str_targetDependency);
        bool matchCo = regex_match(inputLine, str_command);
        if ((matchTD == false) && (matchCo == false)) {
            cout << "Wrong syntax in makefile!" << endl;
            return 1;
        }
        if (inputLine == "" || inputLine[0] == '#') {
            continue;
        }
        inputLine = inputLine.substr(0, inputLine.size() - 1);
        if (inputLine[0] != '\t') {
            stringSplitByString(inputLine, ": ", firstSplit); //firstSplit = [a.out, main.o queue.o]
            stringSplitByString(firstSplit[1], " ", secondSplit); //secondSplit = [main.o, queue.o]
            target = firstSplit[0];
            middle.push_back({ target });
            command.push_back({ target }); //also put target into command
            middle.push_back(secondSplit);
            targetDependency.push_back(middle);
        }
        else if (inputLine[0] == '\t') {
            inputLine = inputLine.substr(1, inputLine.size());
            for (int i = 0; i < command.size(); i++) {
                if (command[i][0] == target) {
                    command[i].push_back(inputLine);
                }
            }
        }
        firstSplit.clear();
        secondSplit.clear();
        middle.clear();
    }
    // close the file stream
    input_file.close();
    
    /*
    Example targetDependency = { {{"a.out"},{"lib1.lib"}}, {{"main.o"},{"main.cpp", "queue.h"}}, {{"queue.o"},{"queue.cpp", "queue.h"}},{{"lib1.lib"},{"main.o","queue.o"}} };
    Example command = { {"a.out", "g++ -o a.out lib1.lib", "flex ..."}, {"main.o", "g++ -o main.o -c main.cpp"}, {"queue.o", "g++ -o queue.o -c queue.cpp"}, {"lib1.lib", "g++ -a lib1.lib -o queue.o main.o"} };
    */
    
    for (int i = 0; i < targetDependency[0][1].size(); i++) {
        commandPrintAll = getAccess(targetDependency, targetDependency[0][1][i], commandPrintAll, command);
    }
    
    for (int i = 0; i < commandPrintAll.size(); i++) {
        if (isContain(commandPrintAll[i], { ".lib", ".so", ".a", ".dll" }) == true) {
            commandSub.push_back(commandPrintAll[i]);
        }
        else {
            commandSubn.push_back(commandPrintAll[i]);
        }
    }
    
    vector<thread> threadsO;
    if (commandSubn.size() > 0) {
        for (int i = 0; i < commandSubn.size(); i++) {
            threadsO.push_back(thread(print_command, commandSubn[i]));
        }
    }
    for (auto& th : threadsO) th.join();
    
    vector<thread> threads1;
    if (commandSub.size() > 0) {
        for (int i = 0; i < commandSub.size(); i++) {
            threads1.push_back(thread(print_command, commandSub[i]));
        }
    }
    for (auto& th : threads1) th.join();

    /*
    * The following codes are the same code as above but with no thread on it.
    * Because some of the version issue, cannot build the cpp file to exe with thread 
    * and mutex inside, so if want to use CMD to test Makefile with name other than 
    * "Makefile" or "makefile", you may need to use the below codes instead of the
    * above codes with thread and mutex.

    if (commandSubn.size() > 0) {
        for (int i = 0; i < commandSubn.size(); i++) {
            for (int j = 0; j < commandSubn[i].size(); j++) {
                cout << commandSubn[i][j] << endl;
                system(commandSubn[i][j].c_str());
            }
        }
    }
    
    if (commandSub.size() > 0) {
        for (int i = 0; i < commandSub.size(); i++) {
            for (int j = 0; j < commandSub[i].size(); j++) {
                cout << commandSub[i][j] << endl;
                system(commandSub[i][j].c_str());
            }
        }
    }
    */

    cout << command[0][1] << endl;
    system(command[0][1].c_str());

    return 0;
}
