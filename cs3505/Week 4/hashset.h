#include <string>
#include "node.h"

#ifndef HASHSET_H
#define HASHSET_H

namespace cs3505
{
  class hashset
  {
    // Default is private.

    node **table;

    int capacity; // array size
    int size;     // element count

  public:

    hashset(int capacity = 100);
    hashset(const hashset & other);
    ~hashset();

    hashset & operator= (const hashset & other);  // hashset x, y, z;  x = y = z;

    void add      (const std::string & s);
    void remove   (const std::string & s);
    bool contains (const std::string & s) const;
    int  get_size () const;

  private:
    int hash (const std::string & s) const;
    void clean();
  };
}

#endif
