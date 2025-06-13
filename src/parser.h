// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include "cst.h"
#include "error.h"
#include "lexer.h"

namespace parser {

class Parser {
public:
	Parser(lexer::Lexer &in, error::Reporter &err);
	cst::Node::Opt parse();
private:
	cst::Node::Opt parse_term();
	cst::Node::Opt parse_list();
	cst::Node::Opt parse_commas();
	cst::Node::Opt parse_semicolons();
	cst::Node::Opt parse_exp();
	template<typename T>
	cst::Node::Opt parse_group(lexer::Token, int endch);
	cst::Node::Opt parse_parens(lexer::Token);
	cst::Node::Opt parse_brackets(lexer::Token);
	cst::Node::Opt parse_braces(lexer::Token);
	lexer::Lexer &in;
	error::Reporter &err;
};

} // namespace parser
