PyFlavor
========

Bring Python flavor to C++

Compilation
===========
compiler must support C++14 (g++-4.8+)
```sh
$ ./configure && make
```
Documentation
=============

Core language
-------------

* **list comprehension**
```C++
// C++14
auto v1 = {1, 2, 3, 4, 5};
auto v2 = v1 | [](int i) { return i+1; }; // lazy, nothing happened yet
auto v2 = transformed(v1, [](int i) { return i+1; }); // same as |, also lazy
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

to be implemented
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
* enumerate
* filter / ifilter
* format
* getattr
* input
* iter
* list
* map
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


