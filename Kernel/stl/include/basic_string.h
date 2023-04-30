#pragma once

#include <char_traits.h>
#include <cstring>
#include <iterator>
#include <memory>

namespace std
{
	template <
		typename CharType,
		typename CharTraits = char_traits<CharType>,
		typename Allocator = std::allocator<CharType>
	>
	class basic_string
	{
	public:
		using traits_type		= CharTraits;
		using value_type		= CharType;
		using allocator_type	= Allocator;
		using size_type			= allocator_traits<Allocator>::size_type;
		using difference_type	= allocator_traits<Allocator>::difference_type;
		using reference			= value_type&;
		using const_reference	= value_type const&;
		using pointer			= allocator_traits<Allocator>::pointer;
		using const_pointer		= allocator_traits<Allocator>::const_pointer;
		using iterator			= default_iterator<pointer>;
		using const_iterator	= default_iterator<const_pointer>;

#pragma region Members
		inline constexpr basic_string() noexcept(noexcept(allocator_type()))
			: basic_string(allocator_type()) {}

		inline constexpr basic_string(allocator_type const& alloc) noexcept
		{
			_alloc = alloc;
			_data = _alloc.allocate(1);
			_data[0] = 0;
			_size = 0;
			_capacity = 0;
		}

		inline constexpr basic_string(size_type count, value_type ch, allocator_type const& alloc = allocator_type())
		{
			_alloc = alloc;
			_data = _alloc.allocate(count + 1);
			_size = count;
			_capacity = count;

			for (size_type i = 0; i < count; ++i)
			{
				_data[i] = ch;
			}

			_data[count] = 0;
		}

		inline constexpr basic_string(basic_string const& other)			
		{
			_alloc = other._alloc;
			_data = other._data;
			_size = other._size;
			_capacity = other._capacity;
		}

		inline constexpr basic_string(const value_type* string, allocator_type const& alloc = allocator_type())
		{
			_alloc = alloc;

			for (_size = _capacity = 0; string[_size]; _size++, _capacity++);

			_data = _alloc.allocate(_size + 1);
			memcpy(_data, string, _size);
			_data[_size + 1] = 0;
		}

		inline constexpr allocator_type get_allocator() const noexcept { return _alloc; }
#pragma endregion

#pragma region Operators
	public:
		inline constexpr basic_string& operator+=(const char* other)
		{
			size_type other_size = 0;
			for (size_type i = 0; other[i]; ++i, ++other_size);

			if (_size + other_size <= _capacity)
			{
				for (size_type i = 0; i < other_size; ++i)
				{
					_data[_size + i] = other[i];
				}

				_size += other_size;
				_data[_size] = 0;

				return *this;
			}

			pointer new_data = _alloc.allocate(_size + other_size + 1);
			memcpy(new_data, _data, _size);
			memcpy(new_data + _size, other, other_size);
			new_data[_size + other_size] = 0;

			_alloc.deallocate(_data, _capacity);
			_data = new_data;
			_capacity = _size + other_size;
			_size = _capacity;

			return *this;
		}
#pragma endregion

#pragma region Element Access
	public:
		inline constexpr value_type* c_str() const noexcept { return _data; }
#pragma endregion

	private:
		Allocator _alloc;
		size_type _size;
		size_type _capacity;
		pointer _data;
	};
}