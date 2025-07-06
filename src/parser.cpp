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

syntax::Node::Ptr Parser::term(Token tk) {
	switch (tk.type) {
	case Token::ident:
		return std::make_unique<syntax::Ident>(tk.loc, in.get(tk.loc));
	case Token::number:
		return std::make_unique<syntax::Number>(tk.loc, in.get(tk.loc));
	default:
		err.report(tk.loc, "Unexpected token");
		return std::make_unique<syntax::Error>(tk.loc);
	}
}

syntax::Node::Ptr Parser::parse(grammar::Precedence min_prec) {
	syntax::Node::Ptr exp;
	Token tk = in.take();
	if (auto op = grammar::Prefix::match(tk)) {
		exp = op->make(tk.loc, parse(op->prec));
	} else {
		exp = term(tk);
	}
	while (tk.type != Token::eof) {
		tk = in.peek();
		if (auto op = grammar::Postfix::match(tk)) {
			if (op->prec < min_prec) break;
			in.next();
			exp = op->make(std::move(exp), tk.loc);
			continue;
		}
		auto op = grammar::Infix::match(tk);
		if (op->left < min_prec) break;
		in.next();
		exp = op->make(std::move(exp), tk.loc, parse(op->right));
	}
	return exp;
}

syntax::Node::Opt Parser::parse() {
	auto out = parse(grammar::Precedence{});
	Token tk = in.take();
	if (tk.type != Token::eof) {
		err.report(tk.loc, "Unexpected token at end of file");
	}
	return out;
}

