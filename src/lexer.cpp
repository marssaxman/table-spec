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
		in = forward;
		forward.reset();
	} else {
		(void)take();
	}
}

Token Lexer::take() {
	int ch = in.take();
	switch (ch) {
		case '{': return Token::brace_l;
		case '}': return Token::brace_r;
	}
	return Token::eof;
}

bool Lexer::match(Token tk) {
	return (tk == peek())? next(), true: false;
}

void Lexer::error(const source::Location &loc, const std::string &message) {
	err.report(loc, message);
}

void Lexer::begin_token() {
	while (!in.eof() && (skip_spaces() || skip_comments()));
}

bool Lexer::skip_spaces() {
	bool found = false;
	for (int ch = in.peek(); isspace(ch); in.next()) {
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
	for (int ch = in.take(); ch != '\n'; in.next());
}

void Lexer::block_comment() {
	auto begin = in.loc();
	for (int ch = in.take(); !in.eof(); ch = in.take()) {
		if (ch == '*' && in.match('/')) return;
		if (ch == '/' && in.match('*')) block_comment();
	}
	error(begin, "non-terminated block comment");
}

} // namespace lexer
