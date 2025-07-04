// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include "error.h"
#include "grammar.h"
#include "syntax.h"
#include "token.h"

struct Parser {
	Parser(Lexer &in, Reporter &err);
	syntax::Node::Opt parse();

private:
	syntax::Node::Ptr parse(grammar::Precedence);
	syntax::Node::Ptr term(Token tk);
	syntax::Node::Ptr group(Token open, Token::Type close);
	Lexer &in;
	Reporter &err;
};

