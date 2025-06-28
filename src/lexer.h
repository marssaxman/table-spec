// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include <optional>
#include <vector>

#include "error.h"
#include "reader.h"
#include "source.h"
#include "token.h"

class Lexer {
public:
	Lexer(Reader &, Reporter &);
	bool eof() const { return in.eof(); }
	bool good() const { return in.good(); }
	Token peek();
	void next();
	Token take();
	bool match(Token::Type);
	std::string get(source::Range loc) { return in.get(loc); }

private:
	Token ident(source::Location begin);
	Token number(source::Location begin);
	void error(const source::Location &, const std::string &);
	void begin_token();
	bool skip_spaces();
	bool skip_comments();
	void line_comment();
	void block_comment();
	Token tok(Token::Type type, source::Location begin);

	Reader &in;
	Reporter &err;

	std::optional<Reader> forward;
};

