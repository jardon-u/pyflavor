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
auto v1 = {1, 2, 3, 4, 5};
auto v2 = v1 | [](int i) { return i+1; }; // v2 is a "range", nothing happened yet
auto v2 = transformed(v1, [](int i) { return i+1; }); // equivalent
```
```Python
v1 = [1, 2, 3, 4, 5] 
v2 = (i+1 for i in v1)
```

Built-in
--------

https://docs.python.org/2/library/functions.html#all

to be implemented
* all
* any
* enumerate
* filter
* format
* getattr
* input
* iter
* list
* map
* max
* min
* **open [WIP]**
```C++
for (auto& line : open("file.txt"))
      ...
```
```Python
for line in open("file.txt"):
      ...
```
* **print [WIP]**
```C++
print("Fifty =", 50);
```
```Python
print("Fifty =", 50)
```
* range / xrange
* reduce
* slice / islice
* sorted
* sum
* zip / izip
