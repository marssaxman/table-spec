// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <iostream>

#include "error.h"

Reporter::Reporter(File &file):
	file(file) {}

void Reporter::report(rfl::source::Location loc, const std::string &message) {
	std::cerr << file.path << ": " << message << std::endl;
	failed = true;
}

void Reporter::report(rfl::source::Range loc, const std::string &message) {
	std::cerr << file.path << ": " << message << std::endl;
	failed = true;
}

