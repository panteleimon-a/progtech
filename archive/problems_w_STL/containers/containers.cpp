#include "containers.hpp"
template <typename T>
class dlist: public Container<T> { public:
       // Constructors: default and copy.
dlist();
dlist(const dlist &l);
// Destructor.
~dlist() override;
// Assignment operator.
dlist & operator=(const dlist &l);
// Methods overriden from Container<T>. 
int size() const override;
void clear() override;
// Insert elements.
void push_back(const T &x);
void push_front(const T &x);
// Remove elements.
void pop_front();
void pop_back();
// Inspect elements.
T & front();
T & back();
};
