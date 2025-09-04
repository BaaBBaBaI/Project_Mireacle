#include <iostream>

struct oneWayList
{
    int data;
    oneWayList* next;

};

void print_list(oneWayList* head) {
    oneWayList* tempo = head;
    while (tempo != nullptr) {
        std::cout << tempo->data << " ";
        tempo = tempo->next;
    }
    std::cout << "NULL" << std::endl;
}

int main() {
    oneWayList* maximka = new oneWayList();
    maximka->data = 10;
    maximka->next = new oneWayList;
    maximka->next->data = 12;
    maximka->next->next = new oneWayList;
    maximka->next->next->data = 30;
    print_list(maximka);
}

/* есть несколько операций:
    обход т т т
    вставка в начало 1 1 1
    вставка в конец т 1 1
    произвольная вставка т т т
    удаление из начала 1 1 1
    удаление из конца т 1 т
    удаление по указателю т 1 т 
    поиск т т т*/