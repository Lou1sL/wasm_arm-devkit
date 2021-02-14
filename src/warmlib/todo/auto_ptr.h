template<typename element_type>
struct auto_ptr_ref {
    element_type* _M_ptr;
    explicit auto_ptr_ref(element_type* __p): _M_ptr(__p) { }
};

template<typename element_type>
class auto_ptr {

private:
    element_type* _M_ptr;
    
public:
    explicit auto_ptr(element_type* __p = 0) throw() : _M_ptr(__p) { }
    auto_ptr(auto_ptr_ref<element_type> __ref) throw() : _M_ptr(__ref._M_ptr) { }
    auto_ptr(auto_ptr& __a) throw() : _M_ptr(__a.release()) { }
    template<typename tn> auto_ptr(auto_ptr<tn>& __a) throw() : _M_ptr(__a.release()) { }

    auto_ptr& operator=(auto_ptr& __a) throw() { reset(__a.release()); return *this; }
    template<typename tn> auto_ptr& operator=(auto_ptr<tn>& __a) throw() { reset(__a.release()); return *this; }
    auto_ptr& operator=(auto_ptr_ref<element_type> __ref) throw() {
        if (__ref._M_ptr != this->get()) {
            delete _M_ptr;
            _M_ptr = __ref._M_ptr;
        }
        return *this;
    }
    ~auto_ptr() { delete _M_ptr; }
    
    //Dereferencing
    element_type& operator*() const throw() { assert(_M_ptr != 0); return *_M_ptr; }
    element_type* operator->() const throw() { assert(_M_ptr != 0); return _M_ptr; }

    element_type* get() const throw() { return _M_ptr; }
    element_type* release() throw() { element_type* __tmp = _M_ptr; _M_ptr = 0; return __tmp; }
    void reset(element_type* __p = 0) throw() { if (__p != _M_ptr) { delete _M_ptr; _M_ptr = __p; } }
    
    template<typename tn> operator auto_ptr_ref<tn>() throw() { return auto_ptr_ref<tn>(this->release()); }
    template<typename tn> operator auto_ptr<tn>() throw() { return auto_ptr<tn>(this->release()); }
};

template<> 
class auto_ptr<void> {
public:
    typedef void element_type;
};
