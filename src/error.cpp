// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <iostream>

#include "error.h"

Reporter::Reporter(File &file) : file(file) {}

void Reporter::report(source::Location loc, const std::string &message) {
	auto lac = file.line_and_column(loc);
	std::cerr << file.path << ":";
	std::cerr << lac.first << ":" << lac.second;
	std::cerr << ": " << message << std::endl;
	failed = true;
}

void Reporter::report(source::Range loc, const std::string &message) {
	auto lac_begin = file.line_and_column(loc.begin);
	auto lac_end = file.line_and_column(loc.end);
	std::cerr << file.path << ":";
	if (lac_begin.first == lac_end.first) {
		std::cerr << lac_begin.first << ":";
		std::cerr << lac_begin.second << "-" << lac_end.second;
	} else {
		std::cerr << lac_begin.first << "-" << lac_end.first;
	}
	std::cerr << ": " << message << std::endl;
	failed = true;
}
