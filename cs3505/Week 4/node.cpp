#include <string>
#include "node.h"

// TODO - qualify and complete the constructor.

cs3505::node::node(const std::string & s)
  : data(s), next(NULL)
{
  //  this->data = s;
  //  this->next = NULL;
}


// TODO - qualify and complete the destructor.

cs3505::node::~node()
{
  // Recursively delete children

  if ((*this).next != NULL)
  {
    // Assume -all- nodes are on the heap, delete the next one.
    delete this->next;
  }

  // Invalidate the next pointer for safety.

  next = NULL;
}
