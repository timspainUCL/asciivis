/*
 * Copyright 2020 University College London
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 */


/*
 * asciivis.hpp
 *
 *	Header file for AsciiVis, a class for static ASCII-art style
 *	visualisation using UTF-8.
 *
 *	The visualisation works on a field line_length by n_lines in
 *	size. Positions are given in floating point values, and can take
 *	any value in the range (0, line_length) in x and (0, n_lines) in
 *	y. The output grid square (i, j) covers the input coordinates:
 *
 *	(i.0, j.0)------(i+1.0, j.0)
 *		 |              |
 *		 |              |
 *		 |              |
 *		 |  (i.5, j.5)  |
 *		 |              |
 *		 |              |
 *		 |              |
 *	(i.0, j+1.0)--(i+1.0, j+1.0)
 *
 *  Created on: 21 Feb 2020
 *      Author: Tim Spain, t.spain@ucl.ac.uk
 */

#include <ostream>

#include <vector>
#include <string>

#ifndef INCLUDE_ASCIIVIS_HPP_
#define INCLUDE_ASCIIVIS_HPP_

class AsciiVis {
private:
	int line_length;
	int n_lines;

	std::string bg_character;
	std::vector<std::string> characters;

public:
	/*
	 * Constructor
	 * int line_length: length of the line in symbols
	 * int n_lines: number of lines of text in the field
	 * std::string: the default character for the background. Please
	 * 		supply a string that results in a complete UTF-8
	 * 		character, otherwise behaviour is undefined, and will
	 * 		probably look bad.
	 */
	AsciiVis(int line_length, int n_lines, std::string bg_character);

	/*
	 * Constructor
	 * int line_length: length of the line in symbols
	 * int n_lines: number of lines of text in the field
	 *
	 * This constructor uses space " " as a background character.
	 */
	AsciiVis(int line_length, int n_lines);

	template<typename I>
	static void visualise_from_iterators(I begin, I end, std::ostream &os, int line_length, int n_lines) {
		int column_count = 0;
		int line_count = 0;

		I iter = begin;
		while(iter != end && line_count < n_lines) {
			os << *iter;
			iter++;
			column_count++;
			if (column_count >= line_length) {
				os << std::endl;
				column_count = 0;
				line_count++;
			}
		}
	};

	/*
	 * Put a single character in a location
	 *
	 * std::string symbol: the character to placed.  Please
	 * 		supply a string that results in a complete UTF-8
	 * 		character, otherwise behaviour is undefined, and will
	 * 		probably look bad.
	 * 	double x: position of the symbol along the line, starting
	 * 		from 0
	 * 	double y: line number to place the symbol, starting from 0
	 */
	void put_agent(std::string symbol, double x, double y);

	/*
	 * Put an obstacle of defined size at a point. Fills an area with
	 * copies of a single symbol. Any output grid square even partly
	 * covered by the area will be filled with the selected
	 * character.
	 *
	 * std::string symbol: the character to placed.  Please
	 * 		supply a string that results in a complete UTF-8
	 * 		character, otherwise behaviour is undefined, and will
	 * 		probably look bad.
	 * double x0
	 * double y0: define one corner of the area to be filled
	 * double length
	 * double height: define the size of the area to be filled. Can
	 * 		be negative to define an area by a corner other than the
	 * 		top left.
	 */
	void put_obstacle(std::string symbol, double x0, double y0, double length, double height);

	/*
	 * Output the defined field to a std::stream. Ends with a line break.
	 *
	 * std::ostream &os: stream to output the ascii-art visualisation to
	 * const AsciiVis &as: field to be visualised
	 */
	friend std::ostream& operator <<(std::ostream &os, const AsciiVis &as);
};

#endif /* INCLUDE_ASCIIVIS_HPP_ */
