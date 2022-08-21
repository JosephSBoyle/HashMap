# HashMap

_HashMap_ is an implementation of a [hash map](https://en.wikipedia.org/wiki/Hash_table) of key strings to value strings.

The method for resolving [hash collisions](https://en.wikipedia.org/wiki/Hash_table#Collision_resolution) is _separate chaining_, i.e each bucket (corresponding to a hash _value_) has a corresponding linked list of nodes containing all of the nodes whose keys hash to that value.

![wikipedia](https://upload.wikimedia.org/wikipedia/commons/thumb/d/d0/Hash_table_5_0_1_1_1_1_1_LL.svg/450px-Hash_table_5_0_1_1_1_1_1_LL.svg.png?20090410083356)

A diagram of a hash collision being handled with this approach [1].

## Tests
A set of tests are inlcuded that cover the handling of hash collisions, i.e cases where two different keys have the same hash value and thus need to exist in the same 'bucket'. To run the tests, first compile the project using `make`, then execute `./run`.

## References
1. https://en.wikipedia.org/wiki/Hash_table#Separate_chaining