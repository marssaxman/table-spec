// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <cassert>
#include <string>
#include <string_view>

#include "file.h"

File::File(const std::string &path, std::vector<char> &&buffer):
	path(path), buffer(std::move(buffer)) {}

bool File::good() const {
	return !path.empty();
}

std::string_view File::text() {
	return std::string_view(buffer.data(), buffer.size());
}

std::string_view File::get(source::Range loc) {
	assert(loc.good());
	assert(loc.begin < buffer.size() && loc.end <= buffer.size());
	auto ptr = buffer.data() + loc.begin;
	auto len = loc.end - loc.begin;
	return std::string_view(ptr, len);
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
