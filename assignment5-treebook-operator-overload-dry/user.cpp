#include "user.h"

/**
 * Creates a new User with the given name and no friends.
 */
User::User(const std::string& name) : _name(name) {}

/**
 * Adds a friend to this User's list of friends.
 * @param name The name of the friend to add.
 */
void User::add_friend(const std::string& name) { _friends.add_friend(name); }

/**
 * Returns the name of this User.
 */
std::string User::get_name() const { return _name; }

/**
 * Returns the number of friends this User has.
 */
size_t User::size() const { return _friends.size(); }

/**
 * Sets the friend at the given index to the given name.
 * @param index The index of the friend to set.
 * @param name The name to set the friend to.
 */
void User::set_friend(size_t index, const std::string& name) { _friends.set_friend(index, name); }

// FORMAT - User(name=Alice, friends=[Bob, Charlie])
std::ostream& operator<<(std::ostream& os, const User &user) {
  os << "User(name=" << user._name << ", friends=" << user._friends << ")";
  return os;
}

// no longer needed since we are using FriendList which has its own copy constructor and assignment operator
// User::~User() {
//   delete[] _friends;
// }

// void User::swap(User& other) noexcept {
//   std::swap(_name, other._name);
//   std::swap(_friends, other._friends);
//   std::swap(_size, other._size);
//   std::swap(_capacity, other._capacity);
// }

// User::User(const User& user) : _name(user._name), _size(user._size), _capacity(user._capacity) {
//   _friends = new std::string[_capacity];
//   for (int i = 0; i < _size; ++i) {
//     _friends[i] = user._friends[i];
//   }
// }

// User& User::operator=(User user) {
//   swap(user);
//   return *this;
// }