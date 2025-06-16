// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include "rfl/rfl.h"
#include "rfl/lexer.h"
#include "rfl/parser.h"
#include "rfl/reporter.h"
#include "rfl/source.h"

namespace rfl {

Frontend::Frontend(const Config &config) : config(config) {
	for (size_t i = 0; i < config.keywords.size(); ++i) {
		keywords[config.keywords[i]] = i;
	}
}

cst::Node::Opt Frontend::run(const std::vector<char> &input, Reporter &err) {
	source::Reader r(input);
	lexer::Lexer l(r, err);
	parser::Parser p(l, err, keywords);
	return p.parse();
}

} // namespace rfl
