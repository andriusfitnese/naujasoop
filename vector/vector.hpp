#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>
#include <memory>
#include <initializer_list>
#include <iterator>
#include <algorithm>
#include <stdexcept>
#include <utility>
#include <ostream>

template<typename T, typename Allocator = std::allocator<T>>
class Vector {

public:
	using value_type = T;
	using allocator_type = Allocator;
	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;
	using reference = T&;
	using const_reference = const T&;
	using pointer = typename std::allocator_traits<allocator_type>::pointer;
	using const_pointer = typename std::allocator_traits<allocator_type>::const_pointer;
	using iterator = T*;
	using const_iterator = const T*;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	//---------------------------------------------------------------------------------------------- konstruktoriai

	Vector() noexcept(std::is_nothrow_default_constructible<Alloc>::value) // default
		: allocator_(), data_(nullptr), size_(0), capacity_(0) {
	}

	explicit Vector(size_type count, const T& value, const Allocator& alloc = Allocator())  // count
		: alloc_(alloc), size_(count), cap_(count)
	{
		data_ = std::allocator_traits<Allocator>::allocate(alloc_, cap_);
		for (size_type i = 0; i < size_; ++i)
			std::allocator_traits<Allocator>::construct(alloc_, data_ + i, value);
	}


	template <typename InputIt, //range 
		typename = std::enable_if_t<!std::is_integral<InputIt>::value>>  // ne enable_if, kadangi butu dviprasmiskumas jei vartotojas duotu 2 int
		Vector(InputIt first, InputIt last, const Allocator& alloc = Allocator())
		: alloc_(alloc)
	{
		size_ = cap_ = std::distance(first, last);
		data_ = std::allocator_traits<Allocator>::allocate(alloc_, cap_);
		size_type i = 0;
		for (InputIt it = first; it != last; ++it, ++i)
			std::allocator_traits<Allocator>::construct(alloc_, data_ + i, *it);
	}

	Vector(const Vector& other) //kopijavimo
		: size_(other.size_), capacity_(other.capacity_), allocator_(other.allocator_) {
		data_ = allocator_traits::allocate(allocator_, capacity_);
		for (size_type i = 0; i < size_; ++i) {
			allocator_traits::construct(allocator_, data_ + i, other.data_[i]);
		}
	}

	Vector(Vector&& other) noexcept //kelimo
		: data_(other.data_), size_(other.size_), capacity_(other.capacity_),
		allocator_(std::move(other.allocator_)) {
		other.data_ = nullptr;
		other.size_ = 0;
		other.capacity_ = 0;
	}

	Vector(std::initializer_list<T> init) //list inicializacija
		: size_(init.size()), capacity_(init.size()), allocator_() {
		data_ = allocator_traits::allocate(allocator_, capacity_);
		std::uninitialized_copy(init.begin(), init.end(), data_);
	}

	~Vector() { //destruktorius
		clear();
		if (data_) {
			allocator_traits::deallocate(allocator_, data_, capacity_);
		}
	}


	//---------------------------------------------------------------------------------------------- priskyrimo operatoriai

	Vector& operator=(const Vector& other) { //kopijavimo
		if (this != &other) {
			Vector tmp(other);
			swap(tmp);
		}
		return *this;
	}

	Vector& operator=(Vector&& other) noexcept { //kelimo
		if (this != &other) {
			clear();
			if (data_) {
				allocator_traits::deallocate(allocator_, data_, capacity_);
			}

			data_ = other.data_;
			size_ = other.size_;
			capacity_ = other.capacity_;
			allocator_ = std::move(other.allocator_);

			other.data_ = nullptr;
			other.size_ = 0;
			other.capacity_ = 0;
		}
		return *this;
	}
	//---------------------------------------------------------------------------------------------- iteratoriai

	iterator begin() noexcept { return data_; }
	const_iterator begin() const noexcept { return data_; }
	const_iterator cbegin() const noexcept { return data_; }

	iterator end() noexcept { return data_ + size_; }
	const_iterator end() const noexcept { return data_ + size_; }
	const_iterator cend() const noexcept { return data_ + size_; }

	reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
	const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
	const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(end()); }

	reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
	const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }
	const_reverse_iterator crend() const noexcept { return const_reverse_iterator(begin()); }

	//---------------------------------------------------------------------------------------------- capacity

	bool empty() const noexcept { return size_ == 0; }
	size_type size() const noexcept { return size_; }
	size_type capacity() const noexcept { return cap_; }

	void reserve(size_type new_cap) {
		if (new_cap <= cap_) return;
		pointer newdata = alloc_.allocate(new_cap);
		for (size_type i = 0;i < size_;++i){
			std::allocator_traits<Allocator>::construct(allocator_, newdata + i,
				std::move_if_noexcept(data[i]));
		std::allocator_traits<Allocator>::destroy(allocator_, data_ + i);
	}
	if (data_)alloc_.deallocate(data_, cap_);
	data_ = newdata;
	cap_ = new_cap;
}
	void shrink_to_fit() {
		if (size_ == capacity_) return; 

		pointer new_data = std::allocator_traits<Allocator>::allocate(alloc_, size_);
		size_type i = 0;

		try {
			for (; i < size_; ++i) {
				std::allocator_traits<Allocator>::construct(
					alloc_, new_data + i,
					std::move_if_noexcept(data_[i])
				);
			}
		}
		catch (...) {
			for (size_type j = 0; j < i; ++j)
				std::allocator_traits<Allocator>::destroy(alloc_, new_data + j);
			std::allocator_traits<Allocator>::deallocate(alloc_, new_data, size_);
			throw;
		}
		clear();
		if (data_) {
			std::allocator_traits<Allocator>::deallocate(alloc_, data_, capacity_);
		}

		data_ = new_data;
		capacity_ = size_;
	}

	//---------------------------------------------------------------------------------------------- modifiers


	void clear() noexcept {
		for (size_type i = 0; i < size_; ++i) {
			std::allocator_traits<Allocator>::destroy(alloc_, data_ + i);
		}
		size_ = 0;
	}


	void push_back(const T& value) {
		if (size_ == capacity_) {
			reserve(capacity_ ? capacity_ * 2 : 1);
		}
		std::allocator_traits<Allocator>::construct(
			alloc_, data_ + size_, value
		);
		++size_;
	}

	void push_back(T&& value) {
		if (size_ == capacity_) {
			reserve(capacity_ ? capacity_ * 2 : 1);
		}
		std::allocator_traits<Allocator>::construct(
			alloc_, data_ + size_, std::move(value)
		);
		++size_;
	}


	template <class... Args>
	reference emplace_back(Args&&... args) {
		if (size_ == capacity_) {
			reserve(capacity_ ? capacity_ * 2 : 1);
		}
		std::allocator_traits<Allocator>::construct(
			alloc_, data_ + size_, std::forward<Args>(args)...
		);
		return *(data_ + size_++);
	}

	template<class... Args>
	iterator emplace(const_iterator pos, Args&&... args) {
		size_type idx = pos - data_;
		if (size_ == capacity_) {
			reserve(capacity_ ? capacity_ * 2 : 1);
		}
		for (size_type i = size_; i > idx; --i) {
			std::allocator_traits<Allocator>::construct(
				alloc_, data_ + i,
				std::move_if_noexcept(data_[i - 1])
			);
			std::allocator_traits<Allocator>::destroy(alloc_, data_ + i - 1);
		}
		std::allocator_traits<Allocator>::construct(
			alloc_, data_ + idx, std::forward<Args>(args)...
		);
		++size_;
		return data_ + idx;
	}

	void pop_back() noexcept {
		if (size_ > 0) {
			--size_;
			std::allocator_traits<Allocator>::destroy(alloc_, data_ + size_);
		}
	}

	void resize(size_type count, const T& value = T()) {
		if (count < size_) {
			for (size_type i = count; i < size_; ++i) {
				std::allocator_traits<Allocator>::destroy(alloc_, data_ + i);
			}
			size_ = count;
		}
		else if (count > size_) {
			if (count > capacity_) reserve(count);
			size_type i = size_;
			try {
				for (; i < count; ++i) {
					std::allocator_traits<Allocator>::construct(
						alloc_, data_ + i, value
					);
				}
			}
			catch (...) {
				for (size_type j = size_; j < i; ++j) {
					std::allocator_traits<Allocator>::destroy(alloc_, data_ + j);
				}
				throw;
			}
			size_ = count;
		}
	}

	void swap(Vector& other) noexcept(
		std::is_nothrow_swappable<Allocator>::value &&
		noexcept(std::swap(data_, other.data_))
		) {
		using std::swap;
		swap(data_, other.data_);
		swap(size_, other.size_);
		swap(capacity_, other.capacity_);
		swap(alloc_, other.alloc_);
	}

private:
	Allocator allocator_;
	pointer data_;
	size_type size_;
	size_type capacity_;
	

};


#endif