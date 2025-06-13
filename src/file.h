// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include <string>
#include <vector>

#include "rfl/source.h"

struct File {
	std::string get(rfl::source::Range);
	std::pair<unsigned, unsigned> line_and_column(rfl::source::Location);
	std::string path;
	std::vector<char> buffer;
};

