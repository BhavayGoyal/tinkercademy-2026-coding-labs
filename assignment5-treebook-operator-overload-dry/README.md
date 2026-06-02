<p align="center">
  <img src="docs/logo.jpeg" alt="A logo of Treebook, a fictional Stanford-based social media startup" style="width: 300px; height: auto;" />
</p>

# Assignment 4: Treebook

## Overview

The newest Stanford social media startup is Treebook, and you’re a founding member of the team! To get the product off the ground and compete with an unnamed, completely legally unaffiliated app from Harvard, you’ve been assigned the task of implementing user profiles.

For this assignment, you will be implementing parts of a class to allow for operator overloads, as well as to modify some aspects of the special member functions.

There are two files you'll work with for this assignment:

* `user.h` - Contains the declaration for the `User` class that you will extend with special member functions and operators.
* `user.cpp` - Contains the definition of the `User` class.

To download the starter code for this assignment, please see the instructions for [**Getting Started**](../README.md#getting-started) on the course assignments repository.

## Running your code

To run your code, first you'll need to compile it. Open up a terminal (if you are using VSCode, hit <kbd>Ctrl+\`</kbd> or go to **Terminal > New Terminal** at the top). Then make sure that you are in the `assignment4/` directory and run:

```sh
g++ -std=c++20 main.cpp user.cpp -o main
```

Assuming that your code compiles without any compiler errors, you can now do:

```sh
./main
```

which will actually run the `main` function in `main.cpp`.

As you are following the instructions below, we recommend intermittently compiling and running `./main` (which runs every test in `tests/`) to make sure you're on the right track.

> [!NOTE]
>
> ### Note for Windows
>
> On Windows, you may need to compile your code using
>
> ```sh
> g++ -static-libstdc++ -std=c++20 main.cpp user.cpp -o main
> ```
>
> in order to see output. Also, the output executable may be called `main.exe`, in which case you'll run your code with:
>
> ```sh
> ./main.exe
> ```

## Part 1: Viewing Profiles

Take a look at the `user.h` header file. Your coworkers have begun to write a `User` class that will store the name and friends list of each user who joins your social media platform! In order to keep this class super efficient, they have chosen to represent the list of friends as a raw pointer array of `std::string` (kind of like how a `std::vector` stores its elements behind the scenes). Thankfully, they have already written logic for creating a new `User` and for adding friends to an existing `User`'s friend list (`add_friend`), but they've begun to experience some strange issues when working with `User` objects.    

To begin with, there's no easy way to print information about each `User` object to the console, which has made debugging at Treebook difficult. To help your coworkers out, write an `operator<<` method that prints a `User` to a `std::ostream`. **This operator should be declared as a friend function in `user.h` and implemented in `user.cpp`.** For example, a user named `"Alice"` with friends `"Bob"` and `"Charlie"` should give the following output when printed to the console:

```
User(name=Alice, friends=[Bob, Charlie])
```

Note: `operator<<` should not print any newline characters.

> [!IMPORTANT]  
> In your implementation of `operator<<`, you will need to access and loop through the `_friends` private field of the `User` class in order to print out a user's friends. Normally, you cannot access private fields inside of a class in a non-member function—in this case, we can get around this restriction by marking `operator<<` as a **friend function inside of the `User` class.** See the slides for Tuesday's lecture for more information!

## Part 2: Unfriendly Behaviour

With the help of your `operator<<`, your coworkers have been able to make good progress on the social media app. However, they can't quite wrap their head around some seemingly bizzare issues that occur when they try to make copies of `User` objects in memory. Having recently taken CS106L, you suspect that it might have something to do with the special member functions (or the lack thereof) on the `User` class. To fix this issue, we'll implement our own versions of the special member functions (SMFs) for the `User` class, and remove some of the others for which the compiler generated versions are insufficient.

To be specific, you will need to:

1. Implement a destructor for the `User` class. To do so, implement the `~User()` SMF.
2. Make the `User` class copy constructible. To do so, implement the `User(const User& user)` SMF.
3. Make the `User` class copy assignable. To do so, implement the `User& operator=(const User& user)` SMF.
4. Prevent the `User` class from being move constructed. To do so, delete the `User(User&& user)` SMF. 
5. Prevent the `User` class from being move assigned. To do so, delete the `User& operator=(User&& user)` SMF.

In performing these tasks, you are expected to make changes to **both** the `user.h` and `user.cpp` files.

> [!IMPORTANT]  
> In your implementations of points 2 and 3 above, you will need to copy the contents of the `_friends` array. Recall from Thursday's lecture on special member functions that you can copy a pointer array by first allocating memory for a new one (possibly within a member initializer list), and then copying over the elements with a for loop.
> Make sure that you also set the `_size`, `_capacity`, and `_name` of the instance you are changing as well!

## Part 3: DRY pass

Look at the copy constructor and copy assignment you just wrote in Part 2. They almost certainly contain the **same code** — allocate a new array, copy `_size` strings over, copy `_name`, set `_size` and `_capacity`. That's textbook duplication, and it's exactly the kind of thing that goes wrong silently the day someone updates one and forgets the other.

> [!IMPORTANT]
> ### Eliminate the duplication
>
> Refactor so the allocate-and-copy logic appears **once**. Two acceptable approaches — pick one:
>
> 1. **Helper method.** Extract a private member function like `void copy_friends_from(const User& other);`. Both the copy constructor and the copy assignment call it.
> 2. **Copy-and-swap idiom.** Implement a private `void swap(User& other) noexcept` that swaps the four members. Then implement copy assignment as: take the parameter by value (the compiler uses your copy constructor for free), call `swap(*this, other)`, and return `*this`. The temporary's destructor cleans up the old data automatically. This pattern is also exception-safe — look it up if you haven't seen it before.
>
> Re-run `./main` after the refactor. **Every test should still pass** — you haven't changed any behaviour, only structure.

> [!IMPORTANT]
> ##### `short_answer.txt`
> **Q1:** Quote the exact lines or expressions that were duplicated between your Part 2 copy constructor and copy assignment. Which of the two refactors did you choose, and how does it eliminate that duplication? If you chose copy-and-swap, also explain why it is exception-safe.

## Part 4: SRP pass — extract `FriendList`

List every responsibility your `User` class currently has. You should find something like:

- knowing a user's `_name`
- representing a person on the social network
- owning a `std::string*` dynamic array
- growing that array when capacity runs out
- copying that array when a `User` is copied
- releasing that array when a `User` is destroyed
- printing a user (via `operator<<`)

The first two are genuinely `User` concerns. The next four are about *managing a dynamic array of strings* — that's a separate concern that has nothing to do with social networking. **A class that has multiple unrelated reasons to change violates the Single-Responsibility Principle.**

> [!IMPORTANT]
> ### Extract `FriendList`
>
> Create a new class `FriendList` in `friend_list.h` and `friend_list.cpp`. Move into it:
>
> - the `_friends` pointer, `_size`, `_capacity` members
> - the append logic from `add_friend`
> - the destructor, copy constructor, copy assignment that manage the array
> - any helpers needed for iteration or printing
>
> Then rewrite `User` so that:
>
> - It owns a `FriendList _friends;` member **by value** (not pointer).
> - Its `_name` member stays as a `std::string`.
> - `User::add_friend` becomes a one-line delegation to `_friends.add(...)`.
> - **Most of `User`'s SMFs can now be `= default;`** — the work is done by `FriendList`'s SMFs (which `User`'s defaulted SMFs will invoke automatically) and `std::string`'s SMFs.
> - Decide whether the deleted move SMFs from Part 2 still need to be deleted. Document your choice in the short answer below.
> - `operator<<` for `User` prints the name and delegates to `FriendList`'s printing.
>
> The build command grows:
>
> ```sh
> g++ -std=c++20 main.cpp user.cpp friend_list.cpp -o main
> ```
>
> Run the tests again. They should still pass.

> [!IMPORTANT]
> ##### `short_answer.txt`
> **Q2:** List every responsibility the `User` class had at the end of Part 3. Mark which of them belonged to `FriendList`. How did extracting `FriendList` change `User`'s special member functions — which became `= default;`, which disappeared entirely, and which (if any) did you keep hand-written and why?

## Part 5: Always Be Friending

After making changes to the special member functions, you've been able to scale out Treebook across Stanford and word has started to spread at other universities! However, your coworkers and you have found that some common use cases for the `User` class are either inconvenient or impossible given how the class is currently written, and you think you might be able to fix this by implementing some custom operators. 

You will overload two operators for the `User` class. **Please implement both of these operators as member functions** (i.e. declare them inside of the `User` class in `user.h` and provide implementations in `user.cpp`).

### `operator+=`

The `+=` operator will representing adding a user to another user's friend list. This should be symmetric, meaning that adding, for example, Charlie to Alice's friend list should cause Alice to also be in Charlie's list. For example, consider this code:

```cpp
User alice("Alice");
User charlie("Charlie");

alice += charlie;
std::cout << alice << std::endl;
std::cout << charlie << std::endl;

// Expected output:
// User(name=Alice, friends=[Charlie])
// User(name=Charlie, friends=[Alice])
```

The function signature for this operator should be `User& operator+=(User& rhs)`. Note that like the copy-assignment operator, it returns a reference to itself.

### `operator<`

Recall that the `<` operator is required to store users in a `std::set`, as `std::set` is implemented in terms of the comparison operator. Implement `operator<` to compare users alphabetically by name. For example:

```cpp
User alice("Alice");
User charlie("Charlie");

if (alice < charlie)
  std::cout << "Alice is less than Charlie";
else
  std::cout << "Charlie is less than Alice";

// Expected output:
// Alice is less than Charlie
```

The function signature for this operator should be `bool operator<(const User& rhs) const`.

## Part 6: Rule of Zero (optional, brownie points)

This is the punchline of the module. You just wrote, refactored, and split a fair amount of memory-management code. Now watch most of it disappear.

> [!IMPORTANT]
> ### Rewrite `FriendList` using `std::vector`
>
> Open `friend_list.h` / `friend_list.cpp`. Replace the `_friends` / `_size` / `_capacity` trio with a single `std::vector<std::string> _friends;` member.
>
> Now look at the special member functions you wrote on `FriendList`. **Delete every one of them — and don't replace them with `= default;` either.** Just remove the declarations. The compiler will synthesise correct destructors, copy constructors, copy assignments, *and* move SMFs because every member (`std::vector<std::string>`) already manages its own resources correctly.
>
> Do the same for `User`: if it now contains only a `std::string _name;` and a `FriendList _friends;`, you can remove every SMF declaration from it as well — *including* the deleted moves from Part 2. (Why is that suddenly safe? Think about it before you do it.)
>
> Re-run the tests. They should still pass.

This is the **Rule of Zero**: if your class is built only out of types that already follow the Rule of Three/Five correctly, *write no special member functions at all*. The compiler's synthesised versions will be both correct and faster than anything you'd hand-write.

> [!IMPORTANT]
> ##### `short_answer.txt`
> **Q3:** Why does removing every SMF declaration from your `FriendList` and `User` work after Part 6, but would have been a disaster after Part 1? Specifically: in Part 2 you deleted the move SMFs on `User`. Do you still want them deleted now that you've reached Part 6? Argue one way or the other in 2–4 sentences.

## 🚀 Submission Instructions

To run the tests:

```sh
./main                # run all tests
./main <test_name>    # run one named test
```

Commit your changes to the GitHub repository.

Your deliverable should be:

- `user.h`
- `user.cpp`
- `friend_list.h` *(if you completed Part 4)*
- `friend_list.cpp` *(if you completed Part 4)*
- `short_answer.txt`

*Adapted from Stanford CS106L Assignment 5.*
