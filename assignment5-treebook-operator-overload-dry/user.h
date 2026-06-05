/*
 * Assignment 4: TreeBook
 * Adapted by Tinkercademy from Stanford CS106L Assignment 5
 * (originally by Fabio Ibanez, with modifications by Jacob Roberts-Baca).
 */

#pragma once
#include <iostream>
#include <string>
#include "friend_list.h"

class User
{
public:
  User(const std::string& name);
  void add_friend(const std::string& name);
  std::string get_name() const;
  size_t size() const;
  void set_friend(size_t index, const std::string& name);

  /** 
   * STUDENT TODO:
   * Your custom operators and special member functions will go here!
   */
  friend std::ostream& operator<<(std::ostream& os, const User& user);

  ~User() = default;
  User(const User& user) = default;
  User& operator=(const User& user) = default;
  User(User&& user) = delete;
  User& operator=(User&& user) = delete;

  User& operator+=(User& rhs);
  bool operator<(const User& rhs) const;

private:
  std::string _name;
  FriendList _friends;

  // void swap(User& other) noexcept; // no longer needed since we are using FriendList which has its own swap function
};