#include <iostream>
#include <vector>
#include <string>
#include <cassert>

class IntList {
private:
    int* head_;
    int* tail_;
    size_t size_;
public:
    IntList();
    IntList(const std::vector<int>& vec);
    ~IntList();

    void insertAtHead(int x);
    void insertAtTail(int x);
    bool contains(int x) const;
    size_t size() const;
    void reverse();
    int removeAtHead();
    int removeAtTail();
    std::vector<int> toVector() const;
    void sorted();
    std::string toString() const;

};

IntList::IntList() {

}

IntList::IntList(const std::vector<int>& vec) {

}

IntList::~IntList() {

}

void IntList::insertAtHead(int x) {
    return;
}

void IntList::insertAtTail(int x) {
    return;
}

bool IntList::contains(int x) const {
    return false;
}

size_t IntList::size() const {
    return 0;
}

void IntList::reverse() {
    return;
}

int IntList::removeAtHead() {
    return 0;
}

int IntList::removeAtTail() {
    return 0;
}

std::vector<int> IntList::toVector() const {
    std::vector<int> ret;
    return ret;
}

void IntList::sorted() {
    return;
}

std::string IntList::toString() const {
    return "";
}

void test1() {
    IntList list;
    const int hi = 8;
    for (int i = 0; i < hi; i++) list.insertAtTail(i);
    assert(list.size() == 8);
    assert(list.toString() == "{1, 2, 3, 4, 5, 6, 7, 8}");
    std::vector<int> vec = list.toVector();
    assert(vec.size() == list.size());
    list.reverse();
    assert(list.size() == 8);
    assert(list.toString() == "{8, 7, 6, 5, 4, 3, 2, 1}");
    for (int x : vec) assert(list.contains(x));
    for (int x : vec) {
        int y = list.removeAtTail();
        assert(x == y);
    }
    assert(list.size() == 0);
    list = IntList(vec);
    list.reverse();
    for (int i = vec.size(); i >= 0; i--) {
        int x = vec[i];
        assert(list.contains(x));
        assert(list.removeAtTail() == x);
    }
    assert(list.size() == 0);
}

int main() {
    test1();
    return 0;
}
