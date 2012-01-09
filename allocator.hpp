#ifndef OBJ_ALLOCATOR_HPP
#define OBJ_ALLOCATOR_HPP

#include <limits>
#include <obj/mpool.hpp>

namespace obj
{
  template <class T> class allocator
  {
  PUBLIC:
	typedef std::size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef T value_type;
    
	template <class U> struct rebind {
      typedef allocator<U> other;
	};

    mPool mpool;
	
  PUBLIC:
	allocator () throw() {}
	allocator (const allocator&) throw() {}
	template <class U> allocator (const allocator<U>&) throw() {}

	~allocator () throw() {}
	
	// メモリを割り当てる
	pointer allocate (size_type num, const_pointer hint = 0) {
      return (pointer)mpool.allocate(num * sizeof(T));
	}
	// コンストラクタを呼ぶ
	void construct (pointer p, const T& value) {
      new ((void*)p) T(value);
	}
	// デストラクタを呼ぶ
	void destroy (pointer p) {
      p->~T();
	}
	// メモリを解放する
	void deallocate (pointer p, size_type num) {
	}
	// アドレスを返す
	pointer address (reference value) const {
      return &value;
    }
	const_pointer address (const_reference value) const {
      return &value;
    }
	// 割当てることができる最大の要素数を返す
	size_type max_size() const throw() {
      return std::numeric_limits<size_t>::max() / sizeof(T);
	}
  };

  template <typename _T1, typename _T2>
  inline bool operator== (const allocator<_T1>&, const allocator<_T2>&) {
    return true;
  }

  template <typename _T1, typename _T2>
  inline bool operator!= (const allocator<_T1>&, const allocator<_T2>&) {
    return false;
  }
}

#endif
