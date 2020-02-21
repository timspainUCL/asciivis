/*
 * asciivis.hpp
 *
 *  Created on: 21 Feb 2020
 *      Author: tim
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
	AsciiVis(int line_length, int n_lines, std::string bg_character);

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

	// Put a single character in a location
	void put_agent(std::string, double, double);

	// Put an obstacle of defined size at a point
	void put_obstacle(std::string, double, double, double, double);

	friend std::ostream& operator <<(std::ostream &os, const AsciiVis &as);
};




#endif /* INCLUDE_ASCIIVIS_HPP_ */
