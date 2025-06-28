// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include <string>

#include "file.h"

class Reporter {
public:
	Reporter(File &file);
	void report(source::Location loc, const std::string &);
	void report(source::Range loc, const std::string &);
	bool any() const { return failed; }

protected:
	File &file;
	bool failed = false;
};
