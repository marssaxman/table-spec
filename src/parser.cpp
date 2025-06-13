// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <iostream>

#include "lexer.h"
#include "parser.h"

namespace parser {

using lexer::Token;
using namespace cst;

Parser::Parser(lexer::Lexer &in, error::Reporter &err):
	in(in),
	err(err) {}

Node::Opt Parser::parse_term() {
	Node::Opt out;
	auto tk = in.peek();
	switch ((int)tk.type) {
		case Token::eof:
		case ')':
		case ']':
		case '}':
		case ';':
		case ',':
			break;
		case '(':
			return parse_parens(tk);
		case '[':
			return parse_brackets(tk);
		case '{':
			return parse_braces(tk);
		case Token::ident:
			out = std::make_unique<Ident>(tk.loc);
			break;
		case Token::number:
			out = std::make_unique<Number>(tk.loc);
			break;
		default:
			out = std::make_unique<Operator>(tk.loc, tk.type);
	}
	if (out.has_value()) {
		in.next();
	}
	return out;
}

Node::Opt Parser::parse_list() {
	Node::Opt out = parse_term();
	if (out) {
		Node::Opt *chain = &out;
		while (auto term = parse_term()) {
			auto link = std::make_unique<List>(std::move(chain->value()));
			link->next = std::move(term);
			auto next = &link->next;
			*chain = std::move(link);
			chain = next;
		}
	}
	return out;
}

Node::Opt Parser::parse_commas() {
	Node::Opt out;
	Node::Opt *chain = &out;
	while (in.good()) {
		auto list = parse_list();
		if (in.match(Token::comma)) {
			auto link = std::make_unique<Comma>(std::move(list));
			auto next = &link->next;
			*chain = std::move(link);
			chain = next;
		} else {
			*chain = std::move(list);
			break;
		}
	}
	return out;
}

Node::Opt Parser::parse_semicolons() {
	Node::Opt out;
	Node::Opt *chain = &out;
	while (in.good()) {
		auto commas = parse_commas();
		if (in.match(Token::semicolon)) {
			auto link = std::make_unique<Semicolon>(std::move(commas));
			auto next = &link->next;
			*chain = std::move(link);
			chain = next;
		} else {
			*chain = std::move(commas);
			break;
		}
	}
	return out;
}

Node::Opt Parser::parse_exp() {
	return parse_semicolons();
}

template<typename T>
cst::Node::Opt Parser::parse_group(lexer::Token tk, int endch) {
	auto begin = tk.loc;
	in.next();
	auto body = parse_exp();
	tk = in.peek();
	if (endch == tk.type) {
		in.next();
	} else {
		err.report(tk.loc, "Expected '" + std::string(1, endch) + "' here");
	}
	return std::make_unique<T>(begin + tk.loc, std::move(body));
}

Node::Opt Parser::parse_parens(Token tk) {
	return parse_group<Parens>(tk, ')');
}

Node::Opt Parser::parse_brackets(Token tk) {
	return parse_group<Brackets>(tk, ']');
}

Node::Opt Parser::parse_braces(Token tk) {
	return parse_group<Braces>(tk, '}');
}

Node::Opt Parser::parse() {
	auto out = parse_exp();
	lexer::Token tk = in.take();
	if (tk.type != lexer::Token::eof) {
		err.report(tk.loc, "Unexpected token at end of file");
	}
	return out;
}

} // namespace parser
