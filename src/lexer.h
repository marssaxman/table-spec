// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include <optional>
#include <vector>

#include "error.h"
#include "source.h"

namespace lexer {

struct Token {
	enum Type : int32_t {
		eof = 0,
		ident = -1,
		number = -2,
		proc = -3,
		query = -4,
		schema = -5,
		table = -6,
		comma = ',',
		semicolon = ';',
	} type;
	source::Range loc;
};

class Lexer {
public:
	Lexer(source::Reader &, Reporter &);
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

	source::Reader &in;
	Reporter &err;

	std::optional<source::Reader> forward;
};

} // namespace lexer

