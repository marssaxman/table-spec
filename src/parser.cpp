// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <iostream>

#include "parser.h"

namespace parser {

Parser::Parser(lexer::Lexer &in, error::Reporter &err):
	in(in),
	err(err) {}

ast::Root::Ptr Parser::parse() {
	while (in.good()) {
		std::cout << (int)in.take().type << std::endl;
	}
	return nullptr;
}

} // namespace parser
