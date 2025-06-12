// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <iostream>

#include "ast.h"
#include "lexer.h"
#include "parser.h"

namespace parser {

using lexer::Token;
using namespace ast;

Parser::Parser(lexer::Lexer &in, error::Reporter &err):
	in(in),
	err(err) {}

ast::Root::Ptr Parser::parse() {
	Component::Vec components;

	Token tok = in.peek();
	source::Location begin = tok.loc.begin;
	for (bool done = false; in.good() && !done; tok = in.peek()) {
		switch (tok.type) {
			case Token::ident:
			case Token::number:
			case Token::eof:
			default:
				done = true;
		}
	}

	Token last = lexer.take();
	if (last != Token::eof) {
		error(last.loc, "Unexpected input token");
	}

	source::Location end = components.empty()? begin: components.back().loc;
	return Root::make(source::Range(begin, end), std::move(components));
}

} // namespace parser
