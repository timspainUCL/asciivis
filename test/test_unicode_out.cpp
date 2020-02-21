/*
 * unicode_out.cpp
 *
 *  Created on: 20 Feb 2020
 *      Author: tim
 */

#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>

#include <iostream>

TEST_CASE("How to output emojis?", "[POC]") {
	std::cout << "🙂" << std::endl;
	std::cout << "☺" << std::endl;
}


