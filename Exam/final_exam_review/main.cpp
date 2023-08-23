#include "LinkedList.h"

int main() {
    LinkedList list0 = LinkedList(); // 1, 4, 6, 7, 2, 5
    LinkedList list1 = LinkedList(); // 3, 6, 2, 6, 8, 4

    list0 = list1;

    return 0;
}