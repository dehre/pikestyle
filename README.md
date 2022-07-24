# Pikestyle

I found [Notes on Programming in C](http://doc.cat-v.org/bell_labs/pikestyle) - aka *pikestyle* - is a very interesting read.  
The section on *Complexity* is perhaps the most interesting one:

> Most programs are too complicated - that is, more complex than they need to be to solve their problems efficiently.  Why? Mostly it's because of bad design, but I will skip that issue here because it's a big one.  But programs are often complicated at the microscopic level, and that is something I can address here.
>
> &nbsp;&nbsp;&nbsp;&nbsp;**Rule 1.**  You can't tell where a program is going to spend its time.  Bottlenecks occur in surprising places, so don't try to second guess and put in a speed hack until you've proven that's where the bottleneck is.
>
> &nbsp;&nbsp;&nbsp;&nbsp;**Rule 2.**  Measure.  Don't tune for speed until you've measured, and even then don't unless one part of the code overwhelms the rest.
>
> &nbsp;&nbsp;&nbsp;&nbsp;**Rule 3.**  Fancy algorithms are slow when n is small, and n is usually small.  Fancy algorithms have big constants. Until you know that n is frequently going to be big, don't get fancy.  (Even if n does get big, use Rule 2 first.)   For example, binary trees are always faster than splay trees for workaday problems.
>
> &nbsp;&nbsp;&nbsp;&nbsp;**Rule 4.**  Fancy algorithms are buggier than simple ones, and they're much harder to implement.  Use simple algorithms as well as simple data structures.
>
> &nbsp;&nbsp;&nbsp;&nbsp;The following data structures are a complete list for almost all practical programs:
>
> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;array  
> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;linked list  
> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;hash table  
> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;binary tree  
>
> &nbsp;&nbsp;&nbsp;&nbsp;Of course, you must also be prepared to collect these into compound data structures.  For instance, a symbol table might be implemented as a hash table containing linked lists of arrays of characters.
>
> &nbsp;&nbsp;&nbsp;&nbsp;**Rule 5.**  Data dominates.  If you've chosen the right data structures and organized things well, the algorithms will almost always be self-evident.  Data structures, not algorithms, are central to programming.  (See The Mythical Man-Month: Essays on Software Engineering by F. P. Brooks, page 102.)
>
> &nbsp;&nbsp;&nbsp;&nbsp;**Rule 6.**  There is no Rule 6.

<br/>

Rob Pike states that those four data structures are enough for almost all practical purposes, to which I agree.

In that spirit, I decided implement them from scratch in C, along with a few useful algorithms for sorting arrays (`selection sort` and `quicksort`)
and searching through them efficiently (`binary search`).

*NOTE:* arrays are built-ins in C, so I went for [vectors](https://en.cppreference.com/w/cpp/container/vector), a contiguous growable array type allocated on the heap.

## Time Complexity

The time complexities for each data structure:  

|   Data Structure   | Avg Access | Avg Search | Avg Insertion | Avg Deletion | Worst Access | Worst Search | Worst Insertion | Worst Deletion |
|:------------------:|:----------:|:----------:|:-------------:|:------------:|:------------:|:------------:|:---------------:|:--------------:|
|       Vector       |    O(1)    |    O(n)    |      O(1)     |     O(1)     |     O(1)     |     O(n)     |       O(1)      |      O(1)      |
| Doubly Linked List |    O(n)    |    O(n)    |      O(1)     |     O(1)     |     O(n)     |     O(n)     |       O(1)      |      O(1)      |
|     Hash Table     |      /     |    O(1)    |      O(1)     |     O(1)     |       /      |     O(n)     |       O(n)      |      O(n)      |
| Binary Search Tree |  O(log(n)) |  O(log(n)) |   O(log(n))   |   O(log(n))  |     O(n)     |     O(n)     |       O(n)      |      O(n)      |

The time complexities for the sorting algorithms:  

|    Algorithm   |     Avg     |  Worst |
|:--------------:|:-----------:|:------:|
| Selection Sort |    O(n^2)   | O(n^2) |
|    Quicksort   | O(n*log(n)) | O(n^2) |


*NOTE:* the time complexity for searching through a sorted vector drops down to `O(log(n))` if `binary search` is used.

## Sparse Notes

**Simplicity & Readability**

First and most important note, this repo isn't meant to be used as a library!  
It aims at showcasing how the data structures and algorithms can be implemented in the most simple and readable way,
and can be used as reference for more robust implementations, that also deal with failed memory allocations and generic data types.

**Generics**

C doesn't provide generics ([actually it does, but...](https://jameshfisher.com/2017/08/19/c-generic/) that's not what I was looking for).  
The most common approach is heavily based on macros, but it harms readability.  
For this reason, types in this project have been hardcoded.  

```c
typedef int BSTItem;

struct BSTNode
{
    BSTItem item;
    struct BSTNode *left;
    struct BSTNode *right;
};
```

**Error Handling**

Still in pursue of readability, error handling has been in part neglected.  
Adding error handling would have meant either giving functions an odd signature (e.g. have the function [return an error code and pass in a pointer to a location to return the result](https://stackoverflow.com/questions/291828/what-is-the-best-way-to-return-an-error-from-a-function-when-im-already-returni)) or taking [the `errno` approach](https://www.youtube.com/watch?v=IZiUT-ipnj0).

That said, the functions deal gracefully with the most common API misuses (e.g. adding an item to a non-existent binary search tree returns immediately) and sometimes call `assert` on less-obvious issues.  
Memory allocations, instead, aren't checked for failure.

**Testing**

[GoogleTest](https://google.github.io/googletest/) has been used as testing and mocking framework.  
It's a C++ library, but it doesn't require special C++ jargon for simple assertions.

Unfortunately, I came to partially regret this decision.  
The problem I stumbled upon is with mocking.  
When you pass a function pointer as argument, such as:

```c
void vec_traverse(const struct Vec *vec, void (*fn)(VecItem item));
```

it's difficult to mock `fn` with C++ and GoogleTest, because the former [requires](https://isocpp.org/wiki/faq/pointers-to-members#memfnptr-vs-fnptr) a [static method](https://isocpp.org/wiki/faq/pointers-to-members#fnptr-vs-memfnptr-types), and the latter doesn't provide an easy way of mocking it.

I ended up with [tracking the number of calls to `fn` by incrementing a `static` variable](https://github.com/dehre/pikestyle/blob/main/tests/vec_tests.cc#L134), but that wasn't very beautiful.  
I will evaluate the libraries suggested here for future projects: https://interrupt.memfault.com/blog/unit-test-mocking#cc-mocking-libraries

**Hash Tables & collisions**

There are a lot of different types and a ton of different optimizations you can do on Hash Tables, but usually they're described as
an array of linked lists, used for handling collisions, indexed by a hash function.  
Linked lists, however, tend to be relatively [slow](https://baptiste-wicht.com/posts/2012/11/cpp-benchmark-vector-vs-list.html); plus, given the lack of generics in C, they would require a specialized implementation where each item is a `struct {const char* key; int value}`.

For dealing with collisions, I chose *linear probing* instead, which is simpler, faster, and requires only an array/vector.  
In short, if we're trying to insert an item into the array but the slot isn't empty, we search for the next empty one and insert the item there.

**Hash Tables, again**

A couple of notes more:

1. The keys have been chosen to be of type `const char *`, which assumes the strings are stored in read-only memory and doesn't require
   dealing with variables whose lifetime is possibly shorter than the lifetime of the Hash Table itself.   

2. This Hash Table implementation doesn't resize according to its load factor: the underlying array is of fixed size, and when it's full,
   it simply doesn't allow new items to be inserted anymore.

**Balancing the Binary Search Tree**

The overall performance of a BST degrades from `O(log(n))` to `O(n)` when not balanced.  
The approach that fn `bst_balance` takes to re-balance the tree is quite straightforward:

1. collect the tree's items into a Vector in ascending order
2. starting from the middle of the Vector (which becomes the new root), recursively create a new balanced tree
3. deallocate the Vector and the old BST
