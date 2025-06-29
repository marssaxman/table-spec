// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include "lexer.h"
#include "parser.h"
#include "token.h"

using namespace syntax;

Parser::Parser(Lexer &in, Reporter &err) : in(in), err(err) {}

Node::Opt Parser::term() {
	Node::Opt out;
	switch ((int)in.peek().type) {
	case Token::eof:
	case ')':
	case ']':
	case '}':
	case ';':
	case ',':
		return out;
	}
	auto tk = in.take();
	switch ((int)tk.type) {
	case '(':
		return parens(tk);
	case '[':
		return brackets(tk);
	case '{':
		return braces(tk);
	case Token::ident:
		return std::make_unique<Ident>(tk.loc);
	case Token::number:
		out = std::make_unique<Number>(tk.loc);
		break;
	default:
		out = std::make_unique<Symbol>(tk.loc, tk.type);
	}
	if (out.has_value()) {
		in.next();
	}
	return out;
}

Node::Opt Parser::list() {
	Node::Opt out = term();
	if (out) {
		Node::Opt *chain = &out;
		while (auto exp = term()) {
			auto link = std::make_unique<List>(std::move(chain->value()));
			link->next = std::move(exp);
			auto next = &link->next;
			*chain = std::move(link);
			chain = next;
		}
	}
	return out;
}

Node::Opt Parser::commas() {
	Node::Opt out;
	Node::Opt *chain = &out;
	while (in.good()) {
		auto exp = list();
		if (in.match(Token::comma)) {
			auto link = std::make_unique<Comma>(std::move(exp));
			auto next = &link->next;
			*chain = std::move(link);
			chain = next;
		} else {
			*chain = std::move(exp);
			break;
		}
	}
	return out;
}

Node::Opt Parser::semicolons() {
	Node::Opt out;
	Node::Opt *chain = &out;
	while (in.good()) {
		auto exp = commas();
		if (in.match(Token::semicolon)) {
			auto link = std::make_unique<Semicolon>(std::move(exp));
			auto next = &link->next;
			*chain = std::move(link);
			chain = next;
		} else {
			*chain = std::move(exp);
			break;
		}
	}
	return out;
}

Node::Opt Parser::expression() { return semicolons(); }

template <typename T>
Node::Opt Parser::group(Token tk, int endch) {
	auto begin = tk.loc;
	in.next();
	auto body = expression();
	tk = in.peek();
	if (endch == tk.type) {
		in.next();
	} else {
		err.report(tk.loc, "Expected '" + std::string(1, endch) + "' here");
	}
	return std::make_unique<T>(begin + tk.loc, std::move(body));
}

Node::Opt Parser::parens(Token tk) {
	return group<Parens>(tk, ')');
}

Node::Opt Parser::brackets(Token tk) {
	return group<Brackets>(tk, ']');
}

Node::Opt Parser::braces(Token tk) {
	return group<Braces>(tk, '}');
}

Node::Opt Parser::parse() {
	auto out = expression();
	Token tk = in.take();
	if (tk.type != Token::eof) {
		err.report(tk.loc, "Unexpected token at end of file");
	}
	return out;
}

