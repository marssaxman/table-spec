// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include <optional>
#include <set>
#include <string>
#include <vector>

namespace schema {

struct Column {
	std::string name;
	std::string type;
	bool optional = false;
	bool repeated = false;
	bool unique = false;
	std::string value;
};

struct Key {
	std::set<std::string> columns;
};

struct Table {
	std::string name;
	std::vector<Column> columns;
	std::optional<Key> primary;
	std::vector<Key> keys;
};

struct Schema {
	std::string name;
	std::vector<Table> tables;
};

} // namespace schema

