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
	Component::Vec items;

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

	Token last = in.take();
	if (last.type != Token::eof) {
		err.report(last.loc, "Unexpected input token");
	}

	source::Location end = items.empty()? begin: items.back()->loc.end;
	return Root::make(source::Range(begin, end), std::move(items));
}

} // namespace parser
