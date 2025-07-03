// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <memory>

#include "grammar.h"
#include "lexer.h"
#include "parser.h"
#include "source.h"
#include "token.h"

Parser::Parser(Lexer &in, Reporter &err) : in(in), err(err) {}

/*

we're going to do a pratt parser
this will be an expression language
syntax blocks will be made of prefixes and subscripts

so we'll do this:

syntax::Node parse(min_bp = 0) {
	// prefix operators
	if (binding = prefix_op_token(lexer.peek()) {
		exp = make_op_node(lexer.next(), parse(binding.right));
	} else {
		exp = term();
	}
	do {
		tk = lexer.peek();
		// postfix operators
		if (binding = postfix_op_token(tk)) {
			if (binding.left < min_bp) break;
			lexer.next();
			// handle suffix groups here?
			exp = make_op_node(tk, exp);
			continue;
		}
		// infix operators
		binding = infix_op_token(tk);
		if (binding.left < min_bp) break;
		lexer.next();
		rhs = parse(binding.rght);
		exp = make_op_node(tk, exp, rhs);
	}
	
	return exp;
}

*/

syntax::Node::Opt Parser::parse(grammar::Precedence min_prec) {
	return std::nullopt;
}

syntax::Node::Opt Parser::parse() {
	auto out = parse(0);
	Token tk = in.take();
	if (tk.type != Token::eof) {
		err.report(tk.loc, "Unexpected token at end of file");
	}
	return out;
}

