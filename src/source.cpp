// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <iostream>

#include "source.h"

namespace source {

Reader::Reader(const std::vector<char> &buffer):
	buf(buffer.begin()),
	pos(buffer.begin()),
	end(buffer.end()) {}

} // namespace source
