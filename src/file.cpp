// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <cassert>
#include <string>

#include "file.h"

std::string File::get(source::Range loc) {
	assert(loc.begin < buffer.size() && loc.end <= buffer.size());
	return std::string(buffer.begin() + loc.begin, buffer.begin() + loc.end);
}

std::pair<unsigned, unsigned> File::line_and_column(source::Location loc) {
	unsigned line = 1;
	unsigned column = 0;
	unsigned size = buffer.size();
	for (unsigned i = 0; i < size; ++i) {
		if (i == loc) {
			return std::make_pair(line, column);
		}
		char ch = buffer[i];
		if ('\n' == ch) {
			line++;
			column = 0;
		} else {
			column++;
		}
	}
	return std::pair<unsigned, unsigned>();
}
