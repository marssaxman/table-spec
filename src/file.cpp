// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <string>

#include "file.h"

std::string File::get(rfl::source::Range loc) {
	// TODO: return the given range of bytes as a string
	return std::string();
}

std::pair<unsigned, unsigned> File::line_and_column(rfl::source::Location loc) {
	// TODO: compute line number and column offset
	return std::pair<unsigned, unsigned>();
}
