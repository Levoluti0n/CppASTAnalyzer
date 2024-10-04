#include <iostream>
#include <string>

class Example {
public:
    void showMessage() {
        std::cout << "Hello, World!" << std::endl;
    }

    int add(int a, int b) {
        return a + b;
    }

private:
    int secretNumber = 42;
};

class Spec{
public:
    void showMessage() {
        std::cout << "Bye, World!" << std::endl;
    }

    int subtract(int a, int b) {
        return a - b;
    }

private:
    int secretNumber = 42;
};

int main() {
    Example example;
    example.showMessage();

    int result = example.add(5, 3);
    std::cout << "The result of addition is: " << result << std::endl;

    return 0;
}
