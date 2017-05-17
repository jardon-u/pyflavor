PyFlavor
========

Bring Python flavor to C++

Compilation
===========
compiler must support C++14 (g++-4.8+ / clang 4.0)
```sh
$ ./configure && make
```
Documentation
=============

Core language features
----------------------

* **list comprehension**
```C++
// C++14
auto v1 = {1, 2, 3, 4, 5};
auto v2 = v1 | [](int i) { return i+1; }; // lazy, see also map and imap
```
```Python
# Python
v1 = [1, 2, 3, 4, 5]
v2 = (i+1 for i in v1)
```

* slicing [?]

Built-in
--------

https://docs.python.org/2/library/functions.html#all

* **all, any [,none]**
```C++
// C++
auto v = {3, 4, 5};
all(v | [](int i) { return i > 2; })
any(v | f)
```
```Python
# Python3
all(i > 2 for i in v1)
any(f(i) for i in v1)
```
* **enumerate**
```C++
// C++
auto v = {"1", "2", "3"};
for (auto t : enumerate(v)) {
    ... std::get<0>(t); // idx
    ... std::get<1>(t); // value
}
```
```Python
# Python
v = ["1", "2", "3"]
for t in enumerate(v):
    ... t[0], t[1] // idx, value
```
* **filter / ifilter**
```C++
// C++
auto v = {"1", "2", "3"};
for (auto t : enumerate(v)) {
    ... std::get<0>(t); // idx
    ... std::get<1>(t); // value
}
```
```Python
# Python
v = ["1", "2", "3"]
for t in enumerate(v):
    ... t[0], t[1] // idx, value
```
* format
* getattr
* input
* iter
* list
```C++
// C++
auto v = {1, 2, 3};
auto v1 = v | [](int i) {return i+1}; // lazy
std::vector<int> v2 = list(v1);       // concrete
```
```Python
# Python
v1 = (i+1 for i in [1, 2, 3]) // lazy
v2 = list(v1)                 // concrete
```
* **map / imap**
```C++
// C++14
auto v = {1, 2, 3, 4, 5};
auto v1 = map([](int i) { return i+1; }, v);  // -> new vector
auto v2 = imap([](int i) { return i+1; }, v); // -> generator
// map ~= list(imap)
```
```Python
# Python
v = [1, 2, 3, 4, 5]
v1 = map(lambda x: x+1, v)
# ... or v1 = [i+1 for i in v]
v2 = (i+1 for i in v) # != itertools.imap(..., v) that actually consumes v
```
* max
* min
* **open**
```C++
// C++
for (auto& line : open("file.txt"))
      ...
```
```Python
# Python
for line in open("file.txt"):
      ...
```
* **print**
```C++
// C++
print("Fifty =", 50);
```
```Python
# Python3
print("Fifty =", 50)
```
* range / xrange
* **reduce**
```C++
// C++
reduce([](string a, string b) { return a + b; }, s)
```
```Python
# Python
reduce(lambda x,y: x + y, ["1","2","3"])
```
* slice / islice
* sorted
* sum
* zip / izip
```C++
// C++
vector<int>    v = {1, 2, 3};
vector<string> w = {"3", "2", "1"};
for (auto t : zip(v, w)) {
    ... std::get<0>(t); // == v[i]
    ... std::get<1>(t); // == w[i]
}
```
```Python
# Python3
v = {1, 2, 3}
w = {"3", "2", "1"}
for t in zip(vw):
    t[1], t[2]
```

Itertools
---------

* chain
* compress
* dropwhile
* groupby
* tee
* takewhile
* iziplongest

* product
* permutations
* combinations
* combinations_with_replacement

More-itertools
-----

* chunked
* collate
* consumer
