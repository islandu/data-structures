//
// islandu/
//   data-structures/
//     doublylinkedlist.cpp
//
// Daniel Thompson, 2020
//

#include <iostream>
#include <stdexcept>

template <typename T>
class DoublyLinkedList {

private:

  // Internal node structure
  struct Node {
    T item;
    Node *prev, *next;
    Node( const T item );
  };

  // Private data members
  Node *head, *tail;

  // Private functions
  Node* indexToNode( const int index ); // Retrieves node pointer from index

public:

  // Iterator classes
  class iterator {
  private:
    Node *node;
  public:
    iterator( Node *node );
    iterator operator++();
    iterator operator++( int );
    iterator operator--();
    iterator operator--( int );
    T& operator*();
    bool operator==( iterator other );
    bool operator!=( iterator other );
  };

  class reverse_iterator {
  private:
    Node *node;
  public:
    reverse_iterator( Node *node );
    reverse_iterator operator++();
    reverse_iterator operator++( int );
    reverse_iterator operator--();
    reverse_iterator operator--( int );
    T& operator*();
    bool operator==( reverse_iterator other );
    bool operator!=( reverse_iterator other );
  };

  // Constructors/destructor
  DoublyLinkedList();
  DoublyLinkedList( const DoublyLinkedList &src ); // Deep copy
  ~DoublyLinkedList();

  // Member functions
  void appendItem( const T item );
  void deleteItem( const int index );
  void insertItem( const int index, const T item );
  size_t size() const;

  // Iterator-retrieval functions
  iterator begin();
  iterator end();
  reverse_iterator rbegin();
  reverse_iterator rend();

  // Operators
  T& operator[]( const int index );
  DoublyLinkedList& operator=( const DoublyLinkedList &src ); // Shallow copy
};

// DoublyLinkedList<T> private functions

template <typename T>
DoublyLinkedList<T>::Node::Node( const T item ) : item( item )
{
  this->prev = NULL;
  this->next = NULL;
}

template <typename T>
typename DoublyLinkedList<T>::Node*
DoublyLinkedList<T>::indexToNode( const int index )
{
  DoublyLinkedList<T>::Node *pos=NULL;

  // Positive index
  if ( index >= 0 )
  {
    pos = this->head;

    for ( int i=0; i < index; ++i )
    {
      if ( !pos )
        throw std::invalid_argument( "index out of range" );

      pos = pos->next;
    }
  }
  // Negative index (e.g., -1: last, -2: second to last)
  else
  {
    pos = this->tail;

    for ( int i=-1; i > index; --i )
    {
      if ( !pos )
        throw std::invalid_argument( "index out of range" );

      pos = pos->prev;
    }
  }

  return pos;
}

// DoublyLinkedList<T>::iterator functions

template <typename T>
DoublyLinkedList<T>::iterator::iterator( Node *node ) : node( node ) {}

template <typename T>
typename DoublyLinkedList<T>::iterator
DoublyLinkedList<T>::iterator::operator++()
{
  this->node = node->next;
  return *this;
}

template <typename T>
typename DoublyLinkedList<T>::iterator
DoublyLinkedList<T>::iterator::operator++( int )
{
  this->node = node->next;
  return *this;
}

template <typename T>
typename DoublyLinkedList<T>::iterator
DoublyLinkedList<T>::iterator::operator--()
{
  this->node = node->prev;
  return *this;
}

template <typename T>
typename DoublyLinkedList<T>::iterator
DoublyLinkedList<T>::iterator::operator--( int )
{
  this->node = node->prev;
  return *this;
}

template <typename T>
T& DoublyLinkedList<T>::iterator::operator*()
{
  return this->node->item;
}

template <typename T>
bool DoublyLinkedList<T>::iterator::operator==(
  DoublyLinkedList<T>::iterator other
)
{
  return this->node == other.node;
}

template <typename T>
bool DoublyLinkedList<T>::iterator::operator!=(
  DoublyLinkedList<T>::iterator other
)
{
  return this->node != other.node;
}

// DoublyLinkedList<T>::reverse_iterator functions

template <typename T>
DoublyLinkedList<T>::reverse_iterator::reverse_iterator( Node *node ) :
node( node ) {}

template <typename T>
typename DoublyLinkedList<T>::reverse_iterator
DoublyLinkedList<T>::reverse_iterator::operator++()
{
  this->node = node->prev;
  return *this;
}

template <typename T>
typename DoublyLinkedList<T>::reverse_iterator
DoublyLinkedList<T>::reverse_iterator::operator++( int )
{
  this->node = node->prev;
  return *this;
}

template <typename T>
typename DoublyLinkedList<T>::reverse_iterator
DoublyLinkedList<T>::reverse_iterator::operator--()
{
  this->node = node->next;
  return *this;
}

template <typename T>
typename DoublyLinkedList<T>::reverse_iterator
DoublyLinkedList<T>::reverse_iterator::operator--( int )
{
  this->node = node->next;
  return *this;
}

template <typename T>
T& DoublyLinkedList<T>::reverse_iterator::operator*()
{
  return this->node->item;
}

template <typename T>
bool DoublyLinkedList<T>::reverse_iterator::operator==(
  DoublyLinkedList<T>::reverse_iterator other
)
{
  return this->node == other.node;
}

template <typename T>
bool
DoublyLinkedList<T>::reverse_iterator::operator!=(
  DoublyLinkedList<T>::reverse_iterator other
)
{
  return this->node != other.node;
}

// DoublyLinkedList<T> constructors/destructor

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList()
{
  this->head = NULL;
  this->tail = NULL;
}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList( const DoublyLinkedList<T> &src )
{
  DoublyLinkedList<T>::Node *pos = src.head;

  // Creates new list from source contents (deep copy)
  while ( pos )
  {
    this->appendItem( pos->item );
    pos = pos->next;
  }
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
  DoublyLinkedList<T>::Node *pos, *tmp=NULL;
  pos = this->head;

  // Freeing memory held by nodes
  while ( pos )
  {
    tmp = pos->next;
    delete pos;
    pos = tmp;
  }
}

// DoublyLinkedList<T> member functions

template <typename T>
void DoublyLinkedList<T>::appendItem( const T item )
{
  if ( !(this->head) )
  {
    // First node, both head and tail of list
    this->head = new Node( item );
    this->tail = this->head;
  }
  else
  {
    DoublyLinkedList<T>::Node *tmp = this->tail;
    // New node is now the tail
    this->tail = new Node( item );
    // Linking new node to old tail
    tmp->next = this->tail;
    this->tail->prev = tmp;
  }
}

template <typename T>
void DoublyLinkedList<T>::deleteItem( const int index )
{
  DoublyLinkedList<T>::Node* pos = this->indexToNode( index );

  // If deleting head, second node becomes new head
  if ( pos == this->head )
    this->head = pos->next;
  // If deleting node with a follower, link follower to previous node
  if ( pos->next )
    pos->next->prev = pos->prev;
  // If deleting node with a previous node, link previous to follower
  if ( pos->prev )
    pos->prev->next = pos->next;

  delete pos;
}

template <typename T>
void DoublyLinkedList<T>::insertItem( const int index, const T item )
{
  DoublyLinkedList<T>::Node *newNode, *pos;
  newNode = new DoublyLinkedList<T>::Node( item );
  pos = this->indexToNode( index );

  // If inserting at index 0, update head pointer
  if ( pos == this->head )
    this->head = newNode;
  // If insertion position has previous node, link it to the new node
  if ( pos->prev )
    pos->prev->next = newNode;
  // Set linkage for new node and displaced node
  newNode->prev = pos->prev;
  newNode->next = pos;
  pos->prev = newNode;
}

template <typename T>
size_t DoublyLinkedList<T>::size() const
{
  size_t result=0;
  DoublyLinkedList<T>::Node *pos = this->head;

  while ( pos )
  {
    ++result;
    pos = pos->next;
  }

  return result;
}

// DoublyLinkedList<T> iterator-retrieval functions

template <typename T>
typename DoublyLinkedList<T>::iterator DoublyLinkedList<T>::begin()
{
  DoublyLinkedList<T>::iterator result( this->head );
  return result;
}

template <typename T>
typename DoublyLinkedList<T>::iterator DoublyLinkedList<T>::end()
{
  DoublyLinkedList<T>::iterator result( this->tail->next );
  return result;
}

template <typename T>
typename DoublyLinkedList<T>::reverse_iterator DoublyLinkedList<T>::rbegin()
{
  DoublyLinkedList<T>::reverse_iterator result( this->tail );
  return result;
}

template <typename T>
typename DoublyLinkedList<T>::reverse_iterator DoublyLinkedList<T>::rend()
{
  DoublyLinkedList<T>::reverse_iterator result( this->head->prev );
  return result;
}

// DoublyLinkedList<T> operators

template <typename T>
T& DoublyLinkedList<T>::operator[]( const int index )
{
  DoublyLinkedList<T>::Node *pos = this->indexToNode( index );
  return pos->item;
}

template <typename T>
DoublyLinkedList<T>&
DoublyLinkedList<T>::operator=( const DoublyLinkedList<T> & src )
{
  this->head = src.head;
  this->tail = src.tail;
}

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
