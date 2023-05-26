#include <ios>

namespace std
{
	ios_base::~ios_base()
	{
		// calls callbacks
		// deallocate memory
	}

	ios_base::fmtflags ios_base::flags() const
	{
		return _fmtflags;
	}

	ios_base::fmtflags ios_base::flags(fmtflags fmtfl)
	{
		ios_base::fmtflags tmp_flags = _fmtflags;
		_fmtflags = fmtfl;
		return tmp_flags;
	}

	ios_base::fmtflags ios_base::setf(fmtflags fmtfl)
	{
		ios_base::fmtflags tmp_flags = _fmtflags;
		_fmtflags |= fmtfl;
		return tmp_flags;
	}

	ios_base::fmtflags ios_base::setf(fmtflags fmtfl, fmtflags mask)
	{
		ios_base::fmtflags tmp_flags = _fmtflags;
		_fmtflags = (_fmtflags & ~mask) | (fmtfl & mask);
		return tmp_flags;
	}

	void ios_base::unsetf(fmtflags mask)
	{
		_fmtflags &= ~mask;
	}

	streamsize ios_base::precision() const
	{
		return _precision;
	}

	streamsize ios_base::precision(streamsize new_precision)
	{
		streamsize tmp_precision = _precision;
		_precision = new_precision;
		return tmp_precision;
	}

	streamsize ios_base::width() const
	{
		return _width;
	}

	streamsize ios_base::width(streamsize new_width)
	{
		streamsize tmp_width = _width;
		_width = new_width;
		return tmp_width;
	}
}