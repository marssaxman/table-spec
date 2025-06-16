// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include <string>

#include "file.h"
#include "rfl/reporter.h"

class Reporter : public rfl::Reporter {
public:
	Reporter(File &file);
	void report(rfl::source::Location loc, const std::string &) override;
	void report(rfl::source::Range loc, const std::string &) override;
	bool any() const { return failed; }

protected:
	File &file;
	bool failed = false;
};
