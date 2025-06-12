// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include <optional>

#include "error.h"
#include "source.h"

namespace lexer {

enum class Token : int {
	eof = 0,
	IDENT,
	brace_l, brace_r,
};

class Lexer {
public:
	Lexer(source::Reader&, error::Reporter&);
	Token peek();
	void next();
	Token take();
	bool match(Token);
private:
	void error(const source::Location&, const std::string&);
	void begin_token();
	bool skip_spaces();
	bool skip_comments();
	void line_comment();
	void block_comment();

	source::Reader &in;
	error::Reporter &err;

	std::optional<source::Reader> forward;
};

} // namespace lexer
