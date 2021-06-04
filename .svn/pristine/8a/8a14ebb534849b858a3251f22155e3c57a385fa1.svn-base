#include "matrix.h"
#include <vector>

int main() {

    std::vector<Matrix> storage(10, Matrix(0, 0));
    std::string command;

    while (std::cin >> command) {
        if (command == "exit") {
            break;
        } else if (command[0] == 'l') {
            std::string reg, filename;
            std::cin >> reg >> filename;

            try {
                Matrix nw = Matrix(0, 0);
                nw.load(filename);
                storage[reg[1] - '0'] = nw;
            } catch (MatrixException &e) {
                std::cout << e.what() << std::endl;
            }
        } else if (command[0] == 'e') {
            try {
                std::string reg;
                std::cin >> reg;

                int x, y;
                std::cin >> x >> y;

                std::cout << storage[reg[1] - '0'].get(x, y) << std::endl;
            } catch (MatrixException &e) {
                std::cout << e.what() << std::endl;
            }
        } else if (command[0] == 'a') {
            try {
                std::string reg1, reg2;
                std::cin >> reg1 >> reg2;

                storage[reg1[1] - '0'] += storage[reg2[1] - '0'];
            } catch (MatrixException &e) {
                std::cout << e.what() << std::endl;
            }
        } else if (command[0] == 'p') {
            std::string reg;
            std::cin >> reg;

            storage[reg[1] - '0'].print();
        } else if (command[0] == 'm') {
            try {
                std::string reg1, reg2;
                std::cin >> reg1 >> reg2;

                storage[reg1[1] - '0'] *= storage[reg2[1] - '0'];
            } catch (MatrixException &e) {
                std::cout << e.what() << std::endl;
            }
        } else {
            std::cout << "Unknown command\n";
        }
    }
    return 0;
}