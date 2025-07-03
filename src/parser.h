// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include "grammar.h"
#include "syntax.h"
#include "error.h"

struct Parser {
	Parser(Lexer &in, Reporter &err);
	syntax::Node::Opt parse();

private:
	syntax::Node::Opt parse(grammar::Precedence);
	Lexer &in;
	Reporter &err;
};

