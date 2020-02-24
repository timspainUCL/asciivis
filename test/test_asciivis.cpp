/*
 * test_asciivis.cpp
 *
 *  Created on: 21 Feb 2020
 *      Author: tim
 */

#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>

#include <string>
#include <list>
#include <sstream>

#include "../include/asciivis.hpp"

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

	std::stringstream ss = std::stringstream();
	ss << vis;

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


