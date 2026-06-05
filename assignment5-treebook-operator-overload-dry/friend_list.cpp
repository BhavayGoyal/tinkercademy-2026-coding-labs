#include <utility>
#include <stdexcept>
#include "friend_list.h"

// FriendList::FriendList() : _friends(nullptr), _size(0), _capacity(0) {}

// FriendList::~FriendList() {
//     delete[] _friends;
// }

// FriendList::FriendList(const FriendList& other) : _size(other._size), _capacity(other._capacity) {
//     _friends = new std::string[_capacity];
//     for (size_t i = 0; i < _size; ++i) {
//         _friends[i] = other._friends[i];
//     }
// }

// void FriendList::swap(FriendList& other) noexcept {
//     std::swap(_friends, other._friends);
//     std::swap(_size, other._size);
//     std::swap(_capacity, other._capacity);
// }

// FriendList& FriendList::operator=(FriendList other) {
//     swap(other);
//     return *this;
// }

void FriendList::add_friend(const std::string& name) {
    // if (_size == _capacity) {
    //     _capacity = _capacity == 0 ? 1 : 2 * _capacity + 1;
    //     std::string* new_friends = new std::string[_capacity];
    //     for (size_t i = 0; i < _size; ++i) {
    //         new_friends[i] = _friends[i];
    //     }
    //     delete[] _friends;
    //     _friends = new_friends;
    // }
    // _friends[_size++] = name;
    _friends.push_back(name);
}

void FriendList::set_friend(size_t index, const std::string& name) {
    // if (index >= _size) throw std::out_of_range("Index out of range");
    if (index >= _friends.size()) throw std::out_of_range("Index out of range");
    _friends[index] = name;
}

// size_t FriendList::size() const { return _size; }
size_t FriendList::size() const { return _friends.size(); }

std::string FriendList::get_friend(size_t index) const {
    // if (index >= _size) throw std::out_of_range("Index out of range");
    if (index >= _friends.size()) throw std::out_of_range("Index out of range");
    return _friends[index];
}

std::ostream& operator<<(std::ostream& os, const FriendList& fl) {
    os << "[";
    for (size_t i = 0; i < fl._friends.size(); ++i) {
        os << fl._friends[i] << (i < fl._friends.size() - 1 ? ", " : "");
    }
    os << "]";
    return os;
}