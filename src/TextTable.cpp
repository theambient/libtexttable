//
//  TextTable.cpp
//  libtexttable
//
//  Created by Ruslan Mullakhmetov on 13 Mar 2013.
//

#include <algorithm>
#include <numeric>
#include <iostream>
#include <iomanip>
#include "TextTable.h"

TextTable::TextTable( size_t colnum, size_t margin )
{
	_columns_num = colnum;
	_margin = margin;
}

std::ostream & operator<<(std::ostream& os, const TextTable & tt )
{
	std::vector<size_t> colwidth(tt._columns_num);
	
	std::fill( colwidth.begin(), colwidth.end(), 0 );
	
	for( const auto & row : tt._rows )
	{
		if( row.size() != tt._columns_num )
		{
			throw std::runtime_error("invalid numer of columns in row: provided 5, " + std::to_string(tt._columns_num) + " required");
		}
		
		for(size_t i=0; i<row.size(); ++i )
		{
			colwidth[i] = std::max( colwidth[i], row[i].size() );
		}
	}
	
	std::string margin_str(tt._margin, ' ');
	
	auto table_width = std::accumulate(colwidth.begin(), colwidth.end(), 0) + (1 + 2 * tt._margin) * tt._columns_num + 1;
	
	os << TextTable::Delimiter(table_width) << std::endl;
	
	bool first_row = true;
	
	for( const auto & row : tt._rows )
	{
		os << '|';
		
		for(size_t i=0; i<row.size(); ++i )
		{
			os << margin_str << std::setw((int) colwidth[i]) << row[i] << margin_str << '|';
		}
		
		os << std::endl;
		
		if( first_row )
		{
			first_row = false;
			os << TextTable::Delimiter(table_width) << std::endl;
		}
	}
	
	os << TextTable::Delimiter(table_width);
	
	
	return os;
	
}


void TextTable::add_row(Row row)
{
	_rows.emplace_back(row);
}


