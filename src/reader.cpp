// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <cassert>
#include <iostream>

#include "reader.h"
#include "source.h"

Reader::Reader(std::string_view buf)
    : buf(buf), pos(buf.begin()), end(buf.end()) {}

std::string_view Reader::get(source::Range r) {
	assert(r.good());
	return std::string_view(buf.data() + r.begin, r.end - r.begin);
}

