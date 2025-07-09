// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include <string>
#include <string_view>
#include <vector>

#include "source.h"

struct File {
	File() {}
	File(const std::string &path, std::vector<char> &&buffer);
	bool good() const;
	std::string_view text();
	std::string_view get(source::Range);
	std::pair<unsigned, unsigned> line_and_column(source::Location);
	const std::string path;
private:
	std::vector<char> buffer;
};
