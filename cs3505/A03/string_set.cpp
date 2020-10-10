/* A 'string set' is defined as a set of strings stored
 * in sorted order in a drop list.  See the class video
 * for details.
 *
 * For lists that do not exceed 2 ^ (max_width + 1)
 * elements, the add, remove, and contains functions are 
 * O(lg size) on average.  The operator= and get_elements 
 * functions are O(size).   
 * 
 * Peter Jensen
 * September 18, 2020
 */

#include "string_set.h"
#include <iostream>  // For debugging, if needed.

namespace cs3505
{
  /*******************************************************
   * string_set member function definitions
   ***************************************************** */
  
  /** Constructor:  The parameter indicates the maximum
    * width of the next pointers in the drop list nodes.
    */
  string_set::string_set(int max_width)
  {
    this->max_width = max_width;
    this->size = 0;
    head = new node("",max_width);
  }

  
  /** Copy constructor:  Initialize this set
    * to contain exactly the same elements as
    * another set.
    */
  string_set::string_set (const string_set & other)
  {
    // TODO:  Complete this constructor
    head = NULL;
    *this = other;
  }

  /** Destructor:  Release any memory allocated
    * for this object.
    */
  string_set::~string_set()
  {
    // TODO:  Complete this destructor to correctly deallocate 
    // any heap-allocated memory for this object.    
    clean();
  }

  cs3505::string_set & cs3505::string_set::operator= (const string_set & other)
  {
    //  Avoid self alignment
    if(this == &other) return *this;
    clean();
    this->max_width = other.max_width;
    this->head = new node("", max_width);
    this->size = other.size;

    node* cur = other.head->next[0];
    while(cur != NULL)
    {
      this->add(cur->data);
      cur = cur->next[0];
    }

    return *this;
  }

  int string_set::get_size() const
  {
    return this->size;
  }

  void string_set::add(const std::string & target)
  {
    node* curr = head;

    std::vector<node*> prior(max_width, NULL);

    int longest_width = 0;

    node* temp = head->next[longest_width];
    while(temp != NULL)
    {
      ++longest_width;
      temp = head->next[longest_width];
    }

    for (int i = longest_width; i >= 0; i--) 
    { 
        while (curr->next[i] != NULL && curr->next[i]->data < target)
        {
          curr = curr->next[i]; 
        } 
        prior[i] = curr; 
    }

    curr = curr->next[0];

    if (curr == NULL || curr->data != target) 
    { 
        int random_width = randomWidth(); 
  
        if (random_width > longest_width) 
        { 
            for (int i=longest_width+1;i<random_width+1;i++) 
                prior[i] = head; 
  
            longest_width = random_width; 
        } 
  
        node* n = new node(target, random_width); 

        for (int i=0;i<=random_width;i++) 
        { 
            n->next[i] = prior[i]->next[i]; 
            prior[i]->next[i] = n; 
        } 
    }  
  }

  void string_set::remove(const std::string & target)
  {
    node* curr = head;
    std::vector<node*> prior(max_width, NULL);

    int longest_width = 0;

    node* temp = head->next[longest_width];
    while(temp != NULL)
    {
      ++longest_width;
      temp = head->next[longest_width];
    }

    for(int i = longest_width; i >= 0; i--) 
    { 
        while(curr->next[i] != NULL  && curr->next[i]->data < target) 
        {
          curr = curr->next[i]; 
        }
        prior[i] = curr; 
    } 

    curr = curr->next[0]; 
  
    if(curr != NULL and curr->data == target) 
    { 
        for(int i=0;i<=longest_width;i++) 
        { 
            if(prior[i]->next[i] != curr) { break; }
            prior[i]->next[i] = curr->next[i]; 
        } 
    } 
  }

  bool string_set::contains(const std::string & target) const
  {
    node* curr = head; 
  
    int longest_width = 0;

    node* temp = head->next[longest_width];
    while(temp != NULL)
    {
      ++longest_width;
      temp = head->next[longest_width];
    }

    for(int i = longest_width; i >= 0; i--) 
    { 
        while(curr->next[i] && curr->next[i]->data < target) 
        {
          curr = curr->next[i]; 
        }      
    } 
    curr = curr->next[0]; 
  
    if(curr and curr->data == target)  {return true;}

    return false;
  }

  std::vector<std::string> string_set::get_elements()
  {
    std::vector<std::string> answer;

    node* curr = head->next[0];
    while(curr != NULL)
    {
      answer.push_back(curr->data);
      curr = curr->next[0];
    }

    return answer;
  }

  // Additional public and private helper function definitions needed
  int string_set::randomWidth()
  {
    float percentage = (float)rand()/RAND_MAX;
    int width = 0;
    while(percentage < 0.5 && width < max_width)
    {
      ++width;
      percentage = (float)rand()/RAND_MAX;
    }
    return width;
  }

  void string_set::clean()
  {
    node* cur = head;
    while(cur != NULL)
    {
      node *temp = cur;
      cur = cur->next[0];
      delete temp;
    }
  }
}
