#ifndef _SMARTPTR_H_
#define _SMARTPTR_H_

template <typename T> class SmartPtr;
template <typename T>
SmartPtr<T> make_SmartPtr(const T& item)
{
	return SmartPtr<T>(item);
}

template <typename T>
class SmartPtr
{
	template <typename T> friend SmartPtr<T> make_SmartPtr(const T& item);
public:
	SmartPtr() :ptr(nullptr), use(new size_t(1)){}
	SmartPtr(const SmartPtr& item) :ptr(item.ptr), use(item.use){ ++*use; }
	SmartPtr& operator= (const SmartPtr& item)
	{
		++*item.use;
		destroy();
		ptr = item.ptr;
		use = item.use;
		return *this;
	}
	T& operator* ()
	{
		if (ptr)
			return *ptr;
		else
			throw std::runtime_error("unhandled pointer");
	}
	const T& operator* () const
	{
		if (ptr)
			return *ptr;
		else
			throw std::runtime_error("unhandled pointer");
	}
	T* operator-> ()
	{
		if (ptr)
			return ptr;
		else
			throw std::runtime_error("access unhandled pointer");
	}
	const T* operator-> () const
	{
		if (ptr)
			return ptr;
		else
			throw std::runtime_error("access unhandled pointer");
	}

	~SmartPtr() { destroy(); }
private:
	SmartPtr(const T& item) :ptr(new T(item)), use(new size_t(1)) {}
	T* ptr;
	size_t* use;
	void destroy()
	{
		if (--*use == 0)
		{
			delete ptr;
			delete use;
		}
	}
};




#endif