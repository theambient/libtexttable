//
//  TextTable.h
//  libtexttable
//
//  Created by Ruslan Mullakhmetov on 13 Mar 2013.
//

#ifndef __libtexttable__TextTable__
#define __libtexttable__TextTable__

#include <string>
#include <vector>
#include <iosfwd>
#include <stdexcept>
#include <initializer_list>

class TextTable
{
public:
	
	typedef std::vector<std::string> Row;

	TextTable(size_t columns_num, size_t margin = 1 );
	
	template<typename Iter>
	void add_row( Iter first, Iter last );
	
	void add_row( Row row );
	
	friend std::ostream & operator<<(std::ostream& os, const TextTable & tt );
private:
	
	class Delimiter
	{
		size_t _width;
		char _symbol;
	public:
		Delimiter(size_t width, char c = '-' ): _width(width), _symbol(c){}
		
		friend std::ostream & operator<<( std::ostream & os, const Delimiter & d )
		{
			for( size_t i=0; i<d._width; ++i )
			{
				os << d._symbol;
			}
			return os;
		}
	};
	
	std::vector<Row> _rows;
	size_t _columns_num;
	size_t _margin;
	
	std::string delimiter(size_t width) const;
};


template<typename Iter>
void TextTable::add_row( Iter first, Iter last )
{
	if( last - first != _columns_num )
	{
		throw std::runtime_error("invalid numer of columns in added row: provided 5, " + std::to_string(_columns_num) + " required");
	}
	
	_rows.emplace_back(first, last);
}


#endif /* defined(__libtexttable__TextTable__) */
