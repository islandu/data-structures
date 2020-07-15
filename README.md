# data-structures
Common data structures implemented in C++ as class templates

## DoublyLinkedList\<T\>
This class template implements a doubly linked list with the following key features:
* Forward traversal via `DoublyLinkedList<T>::iterator`
* Backward traversal via `DoublyLinkedList<T>::reverse_iterator`
* Mutable item access via the subscript operator, including access using negative indices (e.g. -1: last item, -2: second-to-last item)
* `appendItem()` function for pushing elements at the end of the list
* `insertItem()` function for inserting an element at a given index
* `deleteItem()` function for deleting an element at a given index

The [source code](doublylinkedlist.cpp) contains the following test function:

```cpp
// Test program
int main()
{
  DoublyLinkedList<int> dll;

  // Populating list
  dll.appendItem( 42 );
  dll.appendItem( 251 );
  dll.appendItem( -131 );
  dll.appendItem( 67 );
  dll.insertItem( 1, -671 );
  dll.insertItem( -2, 12 );

  // Forward traversal with iterator
  std::cout << "List contents (forward traversal): ";

  for ( auto pos = dll.begin(); pos != dll.end(); ++pos )
    std::cout << *pos << ' ';

  std::cout << std::endl;

  // Updating list contents
  dll[0] = -42;
  dll[-2] = 451;
  dll.deleteItem( 1 );

  // Backward traversal with reverse_iterator
  std::cout << "Updated list contents (backward traversal): ";

  for ( auto pos = dll.rbegin(); pos != dll.rend(); ++pos )
    std::cout << *pos << ' ';

  std::cout << std::endl;

  return 0;
}
```

Output of test function:
```
List contents (forward traversal): 42 -671 251 12 -131 67 
Updated list contents (backward traversal): 67 451 12 251 -42
```
