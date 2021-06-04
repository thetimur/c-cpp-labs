#include <iostream>
#include <employees.h>

int main() {
    EmployeesArray arr;

    std::string command;
    while (std::cin >> command) {
        if (command[0] == 'e') {
            break;
        } else if (command == "list") {
            std::cout << arr;
        } else if (command[0] == 'a') {
            Employee *cur = Employee::create_from_istream(std::cin);
            arr.add(cur);
        } else if (command[0] == 'l') {
            std::string filename;
            std::cin >> filename;

            std::ifstream fin;
            fin.open(filename, std::ios::binary);

            fin >> arr;
            fin.close();
        } else if (command[0] == 's') {
            std::string filename;
            std::cin >> filename;

            std::ofstream fout;
            fout.open(filename, std::ios::binary);

            fout << arr;
            fout.close();
        } else {
            std::cout << "Unknown command!\n";
        }
    }
    return 0;
}