// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include <string>

#include "source.h"

namespace error {

class Reporter {
public:
	Reporter(source::File &file);
	void report(source::Location loc, const std::string &message);
	void report(source::Range loc, const std::string &message);
	bool any() const { return failed; }
protected:
	source::File &file;
	bool failed = false;
};

} // namespace error
