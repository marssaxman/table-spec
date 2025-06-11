// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include <string>
#include <vector>

namespace ast {

struct column {
	std::string name;
	std::string type;
};

struct table {
	std::vector<column> columns;
};

struct schema {
	std::vector<table> tables;
};

} // namespace ast
