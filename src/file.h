// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include <string>
#include <vector>

#include "source.h"

struct File {
	std::string get(source::Range);
	std::pair<unsigned, unsigned> line_and_column(source::Location);
	std::string path;
	std::vector<char> buffer;
};
