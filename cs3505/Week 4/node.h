#include <string>

#ifndef NODE_H
#define NODE_H

namespace cs3505
{
  class node
  {
    friend class hashset;

  private:
    node(const std::string & data);
    ~node();

    std::string data;
    node        *next;
  };
}

#endif
