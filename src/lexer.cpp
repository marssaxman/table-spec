// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <cctype>

#include "lexer.h"

namespace lexer {

Lexer::Lexer(source::Reader &in, error::Reporter &err):
	in(in),
	err(err) {}

Token Lexer::peek() {
	auto start = in;
	auto out = take();
	forward = in;
	in = start;
	return out;
}

void Lexer::next() {
	if (forward) {
		in = forward.value();
		forward.reset();
	} else {
		(void)take();
	}
}

Token Lexer::take() {
	if (in.eof()) return tok(Token::eof, in.loc());
	begin_token();
	source::Location begin = in.loc();
	int ch = in.take();
	if (isalpha(ch)) return ident(begin);
	if (isdigit(ch)) return number(begin);
	return tok(Token::Type(ch), begin);
}

bool Lexer::match(Token::Type tk) {
	return (tk == peek().type)? next(), true: false;
}

Token Lexer::ident(source::Location begin) {
	int ch {};
	do {
		ch = in.take();
	} while (isalnum(ch) || '_' == ch);
	in.back();
	return tok(Token::ident, begin);
}

Token Lexer::number(source::Location begin) {
	int ch {};
	do {
		ch = in.take();
	} while (isalnum(ch) || '.' == ch);
	in.back();
	return tok(Token::number, begin);
}

void Lexer::error(const source::Location &loc, const std::string &message) {
	err.report(loc, message);
}

void Lexer::begin_token() {
	while (in.good() && (skip_spaces() || skip_comments()));
}

bool Lexer::skip_spaces() {
	bool found = false;
	for (int ch = in.peek(); isspace(ch); ch = in.peek()) {
		in.next();
		found = true;
	}
	return found;
}

bool Lexer::skip_comments() {
	if (in.match('/')) {
		if (in.match('/')) {
			line_comment();
			return true;
		}
		if (in.match('*')) {
			block_comment();
			return true;
		}
		in.back();
	}
	return false;
}

void Lexer::line_comment() {
	for (int ch = in.take(); ch != '\n' && in.good(); ch = in.take());
}

void Lexer::block_comment() {
	auto begin = in.loc();
	for (int ch = in.take(); in.good(); ch = in.take()) {
		if (ch == '*' && in.match('/')) return;
		if (ch == '/' && in.match('*')) block_comment();
	}
	error(begin, "non-terminated block comment");
}

Token Lexer::tok(Token::Type type, source::Location begin) {
	auto loc = source::Range(begin, in.loc());
	return Token{.type = type, .loc = loc};
}

} // namespace lexer
