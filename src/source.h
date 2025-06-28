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

} // namespace source
