// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include <error.h>
#include <source.h>

namespace lexer {

enum class Token : int {
	eof = 0,
};

class Lexer {
public:
	Lexer(source::Reader&, error::Reporter&);
	Token peek();
	Token take();
	bool match(Token);
	source::Range loc() const;
private:
	source::Reader &in;
	error::Reporter &err;
};

} // namespace lexer
