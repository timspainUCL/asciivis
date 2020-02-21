/*
 * asciivis.cpp
 *
 *  Created on: 21 Feb 2020
 *      Author: tim
 */

#include <iostream>
#include <algorithm>

#include "../include/asciivis.hpp"

AsciiVis::AsciiVis(int line_length, int n_lines, std::string bg_character)
: line_length(line_length), n_lines(n_lines), bg_character(bg_character) {
	characters = std::vector<std::string>(line_length*n_lines, bg_character);
}

int round_and_clamp(double x, double mmin, double mmax) {
	return static_cast<int>(std::max(mmin, std::min(mmax, x)));
}

void AsciiVis::put_agent(std::string symbol, double x, double y) {
	// Round and clamp the coordinates
	int line = round_and_clamp(y, 0, n_lines);
	int col = round_and_clamp(x, 0, line_length);
	// Put the string
	characters[line * line_length + col] = symbol;
}

void round_position_extent(double pos, double ext, int min, int max, int &pos_int, int &ext_int) {
	int x1 = round_and_clamp(pos, min, max);
	int x2 = round_and_clamp(pos + ext, min, max);
	pos_int = std::min(x1, x2);
	ext_int = round_and_clamp(std::abs(ext), 1, max);
}

void AsciiVis::put_obstacle(std::string symbol, double x0, double y0, double length, double height) {
	int x1, dx;
	round_position_extent(x0, length, 0, line_length, x1, dx);
	int y1, dy;
	round_position_extent(y0, height, 0, n_lines, y1, dy);

	for (int j = 0; j < dy; j++)
		for (int i = 0; i < dx; i++)
			characters[(j+y1) * line_length + (i+x1)] = symbol;

}

std::ostream& operator <<(std::ostream &os, const AsciiVis &as) {
	as.visualise_from_iterators(as.characters.begin(), as.characters.end(), os, as.line_length, as.n_lines);
	return os;
}
