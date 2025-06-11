// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <lexer.h>

namespace lexer {

Lexer::Lexer(source::Reader &in, error::Reporter &err):
	in(in),
	err(err) {}

Token Lexer::peek() {
	return Token::eof;
}

Token Lexer::take() {
	return Token::eof;
}

bool Lexer::match(Token tk) {
	return tk == Token::eof;
}

source::Range Lexer::loc() const {
	return source::Range{};
}

} // namespace lexer
