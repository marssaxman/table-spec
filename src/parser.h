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
	cst::Node::Opt term();
	cst::Node::Opt list();
	cst::Node::Opt commas();
	cst::Node::Opt semicolons();
	cst::Node::Opt expression();
	template <typename T> cst::Node::Opt group(Token, int endch);
	cst::Node::Opt parens(Token);
	cst::Node::Opt brackets(Token);
	cst::Node::Opt braces(Token);
	Lexer &in;
	Reporter &err;
};

