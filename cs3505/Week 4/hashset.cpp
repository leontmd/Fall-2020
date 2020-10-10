#include <string>
#include "hashset.h"

cs3505::hashset::hashset(int capacity)
{
  // Create a table, clear the sizes.

  table = new node*[capacity];

  this->capacity = capacity;
  this->size = 0;

  // Clear the entries within the table.

  for (int i = 0; i < capacity; i++)
    table[i] = NULL; 
}

cs3505::hashset::hashset(const hashset & other)
{
  table = NULL;
  *this = other;
}

cs3505::hashset::~hashset()
{
  clean();
}

void cs3505::hashset::clean ()
{
  // If the table is non-null, remove all nodes, then delete the table.

  if (table != NULL)
  {
    for (int i = 0; i < capacity; i++)
      if (table[i] != NULL) 
        delete table[i];
    
    delete [] table;
  }

  // Clear variables.

  table = NULL;
  capacity = 0;
  size = 0;
}

cs3505::hashset & cs3505::hashset::operator= (const hashset & other)
{
  // Avoid self assignment.

  if (this == &other)
    return *this;

  // Clean out any existing data

  clean ();
 
  // Copy the other table into this one.

  this->capacity = other.capacity;
  table = new node*[capacity];

  // Clear the entries within the table.

  for (int i = 0; i < capacity; i++)
    table[i] = NULL; 

  // Traverse other hashtable

  for (int i = 0; i < other.capacity; i++)
  {
    node *current = other.table[i];
    while (current != NULL)
    {
      this->add((*current).data);
      current = current->next;
    }
  } 
}


void cs3505::hashset::remove (const std::string & s)
{
  if (!contains(s))
    return;

  int position = hash(s);

  node *prior = NULL;
  node *current = table[position];
  while (current != NULL)
  {
    if (current->data == s)
      break;
    prior = current;
    current = current->next;
  }

  if (prior != NULL)
    prior->next = current->next;
  else
    table[position] = current->next;
 
  current->next = NULL;
  delete current;

  size--; 
}

bool cs3505::hashset::contains (const std::string & s) const
{
  int position = hash(s);

  node *current = table[position];
  while (current != NULL)
  {
    if (current->data == s)
      return true;
    current = current->next;
  }

  return false;
}

void cs3505::hashset::add (const std::string & s)
{
  if (contains(s))
    return;

  int position = hash(s);

  node *temp = table[position];
  table[position] = new node(s);
  table[position]->next = temp;
  size++;
}

int cs3505::hashset::get_size () const
{
  return size;
}

int cs3505::hashset::hash (const std::string & s) const
{
  /** Computes a table index for a given string.
   *   If two strings have the same contents, their
   *   hash code (table index) will be identical.
   * The hash code is guaranteed to be in the
   *   range [0..capacity).
   */  

  // A well-known hash algorithm.  Do not change!!!
  
  long long hash = 0;
  for (int i = 0; i < s.length(); i++)
    hash = ((hash*2237) + s[i]) % capacity;
  
  return static_cast<int>(hash);
}

  
