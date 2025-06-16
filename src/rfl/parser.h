// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include <map>
#include <string>

#include "rfl/cst.h"
#include "rfl/lexer.h"
#include "rfl/reporter.h"

namespace rfl {
namespace parser {

class Parser {
public:
	Parser(lexer::Lexer &in, Reporter &err,
	       const std::map<std::string, unsigned> &keywords);
	cst::Node::Opt parse();

private:
	cst::Node::Opt parse_ident(lexer::Token);
	cst::Node::Opt parse_term();
	cst::Node::Opt parse_list();
	cst::Node::Opt parse_commas();
	cst::Node::Opt parse_semicolons();
	cst::Node::Opt parse_exp();
	template <typename T> cst::Node::Opt parse_group(lexer::Token, int endch);
	cst::Node::Opt parse_parens(lexer::Token);
	cst::Node::Opt parse_brackets(lexer::Token);
	cst::Node::Opt parse_braces(lexer::Token);
	lexer::Lexer &in;
	Reporter &err;
	const std::map<std::string, unsigned> &keywords;
};

} // namespace parser
} // namespace rfl
