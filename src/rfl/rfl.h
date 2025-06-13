// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include <map>
#include <string>
#include <vector>

#include "rfl/cst.h"
#include "rfl/reporter.h"
#include "rfl/source.h"

namespace rfl {

struct Config {
	std::vector<std::string> keywords;
};

struct Frontend {
	Frontend(const Config &);
	cst::Node::Opt run(const std::vector<char> &source, Reporter &err);
private:
	Config config;
	std::map<std::string, unsigned> keywords;
};

} // namespace rfl
