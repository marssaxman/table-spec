// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <iostream>

#include "source.h"

namespace source {

std::string File::get(Range loc) {
	// TODO: return the given range of bytes as a string
	return std::string();
}

std::pair<unsigned, unsigned> File::line_and_column(Location loc) {
	// TODO: compute line number and column offset
	return std::pair<unsigned, unsigned>();
}

Reader::Reader(const std::vector<char> &buffer):
	buf(buffer.begin()),
	pos(buffer.begin()),
	end(buffer.end()) {}

} // namespace source
