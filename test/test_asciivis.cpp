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
 * test_asciivis.cpp
 *
 *  Created on: 21 Feb 2020
 *      Author: Tim Spain, t.spain@ucl.ac.uk
 */

#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>

#include <string>
#include <list>
#include <sstream>

#include "../include/asciivis.hpp"

bool test_asciivis_vs_bytearray(const AsciiVis &as, char* tr);

TEST_CASE("Visualise array of strings, compare byte stream", "[Tests]") {
	// C array of C strings
	char const *inchars[] = {"#", "#", "#", "#", "#",
							".", "☺", ".", ".", ".",
							".", ".", ".", ".", ".",
							".", ".", ".", "☻", ".",
							"#", "#", "#", "#", "#"};
	// std::list of std::strings
	std::list<std::string> instrings(inchars, inchars + (sizeof(inchars) / sizeof(*inchars)));

	std::stringstream ss = std::stringstream();
	AsciiVis::visualise_from_iterators(instrings.begin(), instrings.end(), ss, 5, 5);

	// Check the stream byte by byte
	char target_bytes[] = {	'\x23', '\x23', '\x23', '\x23', '\x23', '\x0a',
							'\x2e', '\xe2', '\x98', '\xba', '\x2e', '\x2e', '\x2e', '\x0a',
							'\x2e', '\x2e', '\x2e', '\x2e', '\x2e', '\x0a',
							'\x2e', '\x2e', '\x2e', '\xe2', '\x98', '\xbb', '\x2e', '\x0a',
							'\x23', '\x23', '\x23', '\x23', '\x23', '\x0a'};
	char *tr = target_bytes;
	for (char ch; ss.get(ch); tr++) {
		INFO("The target is " << int(*tr) << " and the value is " << int(ch));
		REQUIRE(int(ch) == int(*tr));
	}
}

TEST_CASE("Add entities, compare byte stream", "[Tests]") {
	int dx = 5;
	int dy = 5;
	AsciiVis vis(dx, dy, "."); // UTF-8 0x2e
	vis.put_obstacle("#", 0, 0, dx, 1);
	vis.put_obstacle("#", 0, dy, dx, -1); //UTF-8 0x23
	vis.put_agent("☺", 1, 1); // UTF-8 0xe298ba
	vis.put_agent("☻", 3, 3); // UTF-8 0xe298bb

	// Check the stream byte by byte
	char target_bytes[] = {	'\x23', '\x23', '\x23', '\x23', '\x23', '\x0a',
							'\x2e', '\xe2', '\x98', '\xba', '\x2e', '\x2e', '\x2e', '\x0a',
							'\x2e', '\x2e', '\x2e', '\x2e', '\x2e', '\x0a',
							'\x2e', '\x2e', '\x2e', '\xe2', '\x98', '\xbb', '\x2e', '\x0a',
							'\x23', '\x23', '\x23', '\x23', '\x23', '\x0a'};

	test_asciivis_vs_bytearray(vis, target_bytes);
}

TEST_CASE("Draw obstacles in every orientation", "[Tests]") {
	int nx = 5;
	int ny = 5;

	char target_bytes[] = {
			'\x2e', '\x2e', '\x2e', '\x2e', '\x2e', '\x0a',
			'\x2e', '\x23', '\x23', '\x23', '\x2e', '\x0a',
			'\x2e', '\x23', '\x23', '\x23', '\x2e', '\x0a',
			'\x2e', '\x23', '\x23', '\x23', '\x2e', '\x0a',
			'\x2e', '\x2e', '\x2e', '\x2e', '\x2e', '\x0a',
	};

	AsciiVis pp(nx, ny, ".");
	pp.put_obstacle("#", 1, 1, 3, 3);
	test_asciivis_vs_bytearray(pp, target_bytes);

	AsciiVis pm(nx, ny, ".");
	pm.put_obstacle("#", 1, 4, 3, -3);
	test_asciivis_vs_bytearray(pm, target_bytes);

	AsciiVis mp(nx, ny, ".");
	mp.put_obstacle("#", 4, 1, -3, 3);
	test_asciivis_vs_bytearray(mp, target_bytes);

	AsciiVis mm(nx, ny, ".");
	mm.put_obstacle("#", 4, 4, -3, -3);
	test_asciivis_vs_bytearray(mm, target_bytes);

}

bool test_asciivis_vs_bytearray(const AsciiVis &as, char* tr) {
	bool is_good = true;

	std::stringstream ss = std::stringstream();
	ss << as;

	for (char ch; ss.get(ch); tr++) {
		INFO("The target is " << int(*tr) << " and the value is " << int(ch));
		is_good = is_good && (int(ch) == int(*tr));
		REQUIRE(is_good);
	}
	return is_good;
}
