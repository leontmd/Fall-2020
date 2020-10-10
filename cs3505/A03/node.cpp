/* This node class is used to build linked lists for the
 * string_set class.
 *
 * Peter Jensen
 * September 18, 2020
 */

#include "node.h"

// By default, functions are not in a namespace.  They are not in any
// class.  Symbols defined here are globally available.  We need to
// qualify our function names so that you are definining our 
// cs3505::node class functions.
//
// Note that you can also use the namespace cs3505 { } block, this 
// would eliminate one level of name qualification.  The 
// 'using' statement will not help in this situation.  
// 
// Qualify it as shown here for functions: 
//      cs3505::node::functionname, etc.

/*******************************************************
 * node member function definitions
 ***************************************************** */

// Students will decide how to implement the constructor, 
// destructor, and any helper methods.
cs3505::node::node(std::string d, int width) : next(width, NULL)
{
    this->data = d;
}

cs3505::node::~node()
{
    std::vector<node*>().swap(this->next);
}