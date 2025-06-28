// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <iostream>

#include "source.h"

namespace source {

Range operator+(Range a, Range b) {
	auto begin = std::min(a.begin, b.begin);
	auto end = std::max(a.end, b.end);
	return Range(begin, end);
}

Reader::Reader(const std::vector<char> &buffer)
    : buf(buffer.begin()), pos(buffer.begin()), end(buffer.end()) {}

std::string Reader::get(Range r) {
	return std::string(buf + r.begin, buf + r.end);
}

} // namespace source

