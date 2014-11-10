#ifndef _CHECKEDPTR_H_
#define _CHECKEDPTR_H_
#include <exception>

template <typename T>
class CheckedPtr
{
public:
	CheckedPtr(T *b, T *e) :beg(b), end(e), curr(b),sz(e-b+1){}
	CheckedPtr& operator++()
	{
		if (curr == end)
			throw std::out_of_range("out of range");
		else
			++curr;

		return *this;
	}
	CheckedPtr& operator--()
	{
		if (curr == beg)
			throw std::out_of_range("out of range");
		else
			--curr;
		return *this;
	}
	CheckedPtr operator++(int)
	{
		CheckedPtr ret(*this);
		++*this;
		return ret;
	}
	CheckedPtr operator--(int)
	{
		CheckedPtr ret(*this);
		--*this;
		return ret;
	}
	T operator* () const
	{
		if (curr == end)
			throw std::out_of_range("out of range");
		
		return *curr;
	}
	T& operator[] (size_t i) const
	{
		if (i >= sz)
			throw std::out_of_range("out of range");
		return *(beg + i);
	}
	size_t size() const;
	template <typename T>
	friend bool operator== (const CheckedPtr<T>& lhs, const CheckedPtr<T>& rhs);
	template <typename T>
	friend bool operator!= (const CheckedPtr<T>& lhs, const CheckedPtr<T>& rhs);
	template <typename T>
	friend bool operator< (const CheckedPtr<T>& lhs, const CheckedPtr<T>& rhs);
	template <typename T>
	friend bool operator> (const CheckedPtr<T>& lhs, const CheckedPtr<T>& rhs);

	CheckedPtr operator+ (size_t offset) const;
	CheckedPtr operator- (size_t offset) const;
private:
	size_t sz;
	T *beg;
	T *end;
	T *curr;

	void set_curr(T *current) { curr = current; }
};

template <typename T>
size_t CheckedPtr<T>::size() const
{
	return sz;
}

template <typename T>
bool operator== (const CheckedPtr<T>& lhs, const CheckedPtr<T>& rhs)
{
	return lhs.beg == rhs.beg && lhs.end == rhs.end && lhs.curr == rhs.curr;
}

template <typename T>
bool operator!= (const CheckedPtr<T>& lhs, const CheckedPtr<T>& rhs)
{
	return !(lhs == rhs);
}

template <typename T>
bool operator< (const CheckedPtr<T>& lhs, const CheckedPtr<T>& rhs)
{
	return lhs.beg == rhs.beg && lhs.end == rhs.end && lhs.curr < rhs.curr;
}

template <typename T>
bool operator> (const CheckedPtr<T>& lhs, const CheckedPtr<T>& rhs)
{
	return lhs.beg == rhs.beg && lhs.end == rhs.end && lhs.curr > rhs.curr;
}

template <typename T>
CheckedPtr<T> CheckedPtr<T>::operator+ (size_t offset) const
{
	if (curr - beg + offset >= sz)
		throw std::out_of_range("out of range");
	CheckedPtr<T> ret(beg, end);
	ret.set_curr(curr + offset);
	return ret;
}

template <typename T>
CheckedPtr<T> CheckedPtr<T>::operator- (size_t offset) const
{
	if (curr - beg < offset)
		throw std::out_of_range("out of range");
	CheckedPtr<T> ret(beg, end);
	ret.set_curr(curr);
	return ret;
}


#endif