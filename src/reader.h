// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include <string_view>

#include "source.h"

class Reader {
public:
	Reader(std::string_view buffer);
	bool eof() const { return pos == end; }
	bool good() const { return pos < end; }
	char peek() const { return eof() ? 0 : *pos; }
	void next() { eof() ? (void)pad++ : (void)pos++; }
	char take() { return eof() ? (pad++, 0) : *pos++; }
	bool match(int ch) { return (ch == peek()) ? (next(), true) : false; }
	void back() { pad ? (void)pad-- : (void)pos--; }
	source::Location loc() const { return source::Location(pos - buf.begin()); }
	std::string_view get(source::Range);

private:
	std::string_view buf;
	std::string_view::const_iterator pos;
	std::string_view::const_iterator end;
	unsigned pad = 0;
};

