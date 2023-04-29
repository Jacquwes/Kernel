#include <cstdio>
#include <new>

#include <memory_manager.h>

namespace std
{
	/*bad_alloc::bad_alloc(const char* what) noexcept
	{
		m_what = what;
	}

	bad_alloc& bad_alloc::operator=(bad_alloc const& other) noexcept
	{
		m_what = other.m_what;
		return *this;
	}

	const char* bad_alloc::what() const noexcept
	{
		return m_what;
	}

	bad_array_new_length::bad_array_new_length(const char* what) noexcept
	{
		m_what = what;
	}

	bad_array_new_length& bad_array_new_length::operator=(bad_array_new_length const& other) noexcept
	{
		m_what = other.m_what;
		return *this;
	}

	const char* bad_array_new_length::what() const noexcept
	{
		return m_what;
	}*/
}

void* operator new(std::size_t count)
{
	std::printf("operator new(): Allocating %x bytes.\n", count);
	uintptr_t ptr = kernel::memory_manager::instance->allocate(count);

	std::printf("operator new(): Done.\n");
	return reinterpret_cast<void*>(ptr);
}

void* operator new[](std::size_t count)
{
	std::printf("operator new[](): Allocating %x bytes.\n", count);
	uintptr_t ptr = kernel::memory_manager::instance->allocate(count);

	std::printf("operator new[](): Done.\n");
	return reinterpret_cast<void*>(ptr);
}

void operator delete(void* ptr) noexcept
{
}

void operator delete[](void* ptr) noexcept
{
	kernel::memory_manager::instance->deallocate(ptr);
	std::printf("operator delete[](): Deallocated %x.\n", ptr);
}

