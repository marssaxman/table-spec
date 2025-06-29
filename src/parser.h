// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include "syntax.h"
#include "error.h"
#include "token.h"

class Parser {
using Node = syntax::Node;
public:
	Parser(Lexer &in, Reporter &err);
	Node::Opt parse();

private:
	Node::Opt term();
	Node::Opt list();
	Node::Opt commas();
	Node::Opt semicolons();
	Node::Opt expression();
	template <typename T> Node::Opt group(Token, int endch);
	Node::Opt parens(Token);
	Node::Opt brackets(Token);
	Node::Opt braces(Token);
	Lexer &in;
	Reporter &err;
};

