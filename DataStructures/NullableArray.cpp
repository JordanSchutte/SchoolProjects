#include <iostream>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cassert>
#include <bitset>

// Set the Nth bit in a given byte.
static void setBit(uint8_t& byte, size_t pos, bool value) {
    byte |= (value << pos);
}

// Get the Nth bit in a given byte.
static bool getBit(uint8_t byte, size_t pos) {
    auto ret = byte & (1 << pos);
    return ret;
}

// Given a vector of bytes and a logical index, set the appropriate bit.
static void setBitLogical(std::vector<uint8_t>& bytes, size_t idx, bool value) {;
    auto& byte = bytes[idx / 8];
    auto pos = idx % 8;
    setBit(byte, pos, value);
}

// Get a bit given a vector of bytes and a logical index.
static bool getBitLogical(const std::vector<uint8_t>& bytes, size_t idx) {
    auto byte = bytes[idx / 8];
    auto pos = idx % 8;
    return getBit(byte, pos);
}

template <class T>
class NullableArray {
public:
    NullableArray(std::vector<T> data, std::vector<uint8_t> nulls, size_t size);
    NullableArray<T> gather(const std::vector<uint32_t>& indices) const;
    size_t size() const;
    std::string toString() const;
private:
    std::vector<T> data_;
    std::vector<uint8_t> nulls_;
    size_t size_;
};

template <class T>
NullableArray<T>::NullableArray(std::vector<T> data, std::vector<uint8_t> nulls,
                                size_t size)
    : data_(std::move(data)), nulls_(std::move(nulls)), size_(size) {

    // Must have enough null bits.
    if ((nulls_.size() * 8) < size_) throw std::exception();

    // Data cannot exceed size.
    if (data_.size() > size) throw std::exception();
}

template <class T>
NullableArray<T>
NullableArray<T>::gather(const std::vector<uint32_t>& indices) const {

    // Set up the pieces of the new NullableArray.
    std::vector<T> data;
    std::vector<uint8_t> nulls;

    // Set up the bytes in the nulls array.
    for (size_t i = 0; i < indices.size() / 8; i++) nulls.push_back(0);
    if (indices.size() - (indices.size() / 8)) nulls.push_back(0);

    // Iterate through the gather map.
    for (uint32_t idx : indices) {

        // Each number in the gather map must be a valid index into this.
        if (idx >= size_) throw new std::exception();

        // If the null bit is 1, then we can use this index.
        const bool isIdxNull = getBitLogical(this->nulls_, idx);
        const size_t nextNewIdx = data.size();

        if (isIdxNull) {
            auto value = this->data_[idx];
            data.push_back(value);
            assert(!getBitLogical(nulls, nextNewIdx));
            setBitLogical(nulls, nextNewIdx, true);

        // Else it's null, so emplace an empty.
        } else {
            auto empty = T();
            data.push_back(std::move(empty));
            assert(!getBitLogical(nulls, nextNewIdx));
        }
    }

    NullableArray<T> ret(std::move(data), std::move(nulls), indices.size());

    assert(ret.size() == indices.size());

    return ret;
}

template <class T>
size_t NullableArray<T>::NullableArray::size() const {
    return size_;
}

// TODO: Relies on unary prefix + to print the <T> out as a number, needs
// template specialization for char instead.
template <class T>
static void stringify(std::stringstream& ss, const std::vector<T>& vec) {
    ss << "{";
    for (int i = 0; i < vec.size()-1; i++) ss << +vec[i] << ", ";
    if (vec.size()) ss << +vec[vec.size()-1];
    ss << "}";
}

template <class T>
std::string NullableArray<T>::toString() const {
    std::stringstream ss;

    ss << "data: ";
    stringify(ss, data_);
    ss << std::endl;

    ss << "nulls: ";
    stringify(ss, nulls_);

    return ss.str();
}

int main(int argc, char** argv) {

    // Set up the test NullableArray...
    std::vector<uint32_t> data = {1, 2, 3, 4};
    std::vector<uint8_t> nulls = {11};

    NullableArray<uint32_t> array(data, nulls, 4);

    std::cout << array.toString() << std::endl;

    std::vector<uint32_t> gatherMap = {0, 2, 0, 3, 1};

    auto out = array.gather(gatherMap);

    std::cout << out.toString() << std::endl;

    return 0;
}
