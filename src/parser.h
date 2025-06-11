// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include "ast.h"
#include "error.h"
#include "lexer.h"

namespace parser {

class Parser {
public:
	Parser(lexer::Lexer &in, error::Reporter &err);
	ast::Root::Ptr parse();
private:
	lexer::Lexer &in;
	error::Reporter &err;
};

} // namespace parser
