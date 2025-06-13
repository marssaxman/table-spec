// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include <string>

#include "rfl/source.h"

namespace rfl {

struct Reporter {
	virtual ~Reporter() = default;
	virtual void report(source::Location loc, const std::string &message) = 0;
	virtual void report(source::Range loc, const std::string &message) = 0;
};

} // namespace rfl
