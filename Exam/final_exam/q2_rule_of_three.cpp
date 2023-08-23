#include <iostream>

struct Chair {
    double sitHeight;
    double seatWidth;
    bool hasBack;
};

class DynamicChair {
    Chair* data;

public:
    DynamicChair(Chair d) : data(new Chair(d)) {}

    const Chair& operator*() const { return *data; }
    Chair& operator*() { return *data; }

    DynamicChair& operator=(const Chair& d) {
        *data = d;
        return *this;
    }

    ~DynamicChair() {
        delete this->data;
        this->data = nullptr;
    }

    DynamicChair(const DynamicChair& source) : data(nullptr) {
        this->data = source.data;
    }

    DynamicChair& operator=(const DynamicChair& rhs) {
        this->data = rhs.data;
        return *this;
    }
};