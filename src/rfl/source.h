// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include <algorithm>
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

namespace rfl {
namespace source {

using Location = uint32_t;

struct Range {
	Range() = default;
	Range(Location x) : begin(x), end(x) {}
	Range(Location b, Location e) : begin(b), end(e) {}
	Location begin{};
	Location end{};
	bool good() const { return end > begin; }
};
Range operator+(Range a, Range b);

class Reader {
public:
	Reader(const std::vector<char> &buffer);
	bool eof() const { return pos == end; }
	bool good() const { return pos < end; }
	char peek() const { return eof() ? 0 : *pos; }
	void next() { eof() ? (void)pad++ : (void)pos++; }
	char take() { return eof() ? (pad++, 0) : *pos++; }
	bool match(int ch) { return (ch == peek()) ? (next(), true) : false; }
	void back() { pad ? (void)pad-- : (void)pos--; }
	Location loc() const { return Location(pos - buf); }
	std::string get(Range);

private:
	std::vector<char>::const_iterator buf;
	std::vector<char>::const_iterator pos;
	std::vector<char>::const_iterator end;
	unsigned pad = 0;
};

} // namespace source
} // namespace rfl
