//allocator::rebind  一个嵌套的(nested) class template。class rebind<U>拥有唯一成员other，那是一个typedef，代表allocator<U>
//allocator::allocator()  默认构造器
//allocator::allocator(const allocator&)  拷贝构造器
//template <class U>allocator::allocator(const allocator<U>&)  泛化的copy constructor
//allocator::~allocator()  默认析构器
//pointer allocator::address(reference x) const  返回某个对象的地址。算式a.address(x)等同于&x
//const pointer allocator::address(const_reference x) const 返回某个const对象的地址。算式a.address(x)等同于&x
//pointer allocator::allocate(size_type n,const void*=0)  配置空间，足以存储n个T对象。第二参数是个提示。实现上可能会利用它来增进区域性(locality)，或完全忽略之
//void allocator::deallocate(pointer p,size_type n)  归还先前配置的空间
//size_type allocator::max_size() const  返回可成功配置的最大量
//void allocator::construct(pointer p,const T& x)  等同于new(const void*)p T(x)
//void allocator::destroy(pointer p)  等同于p->~T()

#ifndef _ALLOC_
#define _ALLOC_

#include <new>        //for placement new
#include <cstddef>    //for ptrdiff_t,size_t
#include <cstdlib>    //for exit()
#include <climits>    //for UINT_MAX
#include <iostream>   //for cerr

namespace JJ{

template <class T>
inline T* _allocate(ptrdiff_t size,T*){
    set_new_handler(0);
    T* tmp=(T*)(::operator new((size_t)(size* sizeof(T))));
    if(tmp==0){
        cerr<<"out of memory"<<endl;
        exit(1);
    }
    return tmp;
}

template<class T>
inline void _deallocate(T* buffer){
    ::operator delete(buffer);
}

template<class T1,class T2>
inline void _construct(T1* p,const T2& value){
    new(p) T1(value);     //placement new. invoke ctor of T1
}

template<class T>
inline void _destroy(T* ptr){
    ptr->~T();
}

template <class T>
class allocator{
public:
    typedef T            value_type;
    typedef T*           pointer;
    typedef const T*     const_pointer;
    typedef T&           reference;
    typedef const T&     const_reference;
    typedef size_t       size_type;
    typedef ptrdiff_t    difference_type;

    // rebind allocator of type U
    template <class U>
    struct rebind{
        typedef allocator<U> other;
    };

    //hint used for locality. ref.[Austern],p189
    pointer allocate(size_type n,const void* hint=0){
        return _allocate((difference_type)n,(pointer)0);
    }

    void deallocate(pointer p,size_type n){_deallocate(p);}

    void construct(pointer p,const T& value){
        _construct(p,value);
    }

    void destroy(pointer p){_destroy(p);}

    pointer address(reference x){return (pointer)&x;}

    const_pointer const_address(const_reference x){
        return (const_pointer)&x;
    }

    size_type max_size() const{
        return size_type(UINT_MAX/sizeof(T));
    }
};

} //end of namespace JJ

#endif