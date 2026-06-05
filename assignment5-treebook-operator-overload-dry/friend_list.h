#include <string>
#include <iostream>
#include <vector>

class FriendList
{
public:
    // FriendList();
    // ~FriendList();
    // FriendList(const FriendList& other);
    // FriendList& operator=(FriendList other);

    // // disabled like in part 2
    // FriendList(FriendList&& other) = delete;
    // FriendList& operator=(FriendList&& other) = delete;

    void add_friend(const std::string& name);
    void set_friend(size_t index, const std::string& name);
    size_t size() const;
    std::string get_friend(size_t index) const;

    friend std::ostream& operator<<(std::ostream& os, const FriendList& friendList);
private:
    // std::string* _friends;
    // size_t _size;
    // size_t _capacity;
    std::vector<std::string> _friends;

    // void swap(FriendList& other) noexcept;
};