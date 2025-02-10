#ifndef BBDDST_H
#define BBDDST_H

#define RESET "\033[0m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define GREEN "\033[32m"
#define cpprint std::cout

class BBStack {
    private:
    int* arst;
    int _size;
    public:
    BBStack(int _size);
    ~BBStack();
    void push(int value);
    int pop();
    int back();
    int size();
    void clear();
};

BBStack::BBStack(int _size = 100) {
    arst = new int[_size];
    this->_size = 0;
}

BBStack::~BBStack() {
    delete[] arst;
}

void BBStack::push(int value) {
    arst[_size++] = value;
}

int BBStack::pop() {
    return arst[--_size];
}

int BBStack::back() {
    return arst[_size - 1];
}

int BBStack::size() {
    return _size;
}

void BBStack::clear() {
    _size = 0;
}

#endif