template <typename T> 
class Container { public:
virtual ~Container() {}
virtual int size() const = 0;
virtual bool empty() const { return size() == 0; } 
virtual void clear() = 0;
};