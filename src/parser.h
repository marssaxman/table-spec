// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include "cst.h"
#include "error.h"
#include "token.h"

class Parser {
public:
	Parser(Lexer &in, Reporter &err);
	cst::Node::Opt parse();

private:
	cst::Node::Opt parse_ident(Token);
	cst::Node::Opt parse_term();
	cst::Node::Opt parse_list();
	cst::Node::Opt parse_commas();
	cst::Node::Opt parse_semicolons();
	cst::Node::Opt parse_exp();
	template <typename T> cst::Node::Opt parse_group(Token, int endch);
	cst::Node::Opt parse_parens(Token);
	cst::Node::Opt parse_brackets(Token);
	cst::Node::Opt parse_braces(Token);
	Lexer &in;
	Reporter &err;
};

