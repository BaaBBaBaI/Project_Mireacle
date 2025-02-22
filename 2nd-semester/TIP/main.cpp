#include "rt1.hpp"

int main() {
    triangle mama(1, 2, 4);

    // mama.set(1, 2, 4);
    mama.show();
    std::cout << mama.perimeter() << std::endl; 

    return 0;
}