// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include "token.h"

#include <unordered_map>

Token Token::from_identifier(const std::string& text, source::Range loc) {
	static const std::unordered_map<std::string, Type> keywords {
	    {"proc", proc},
	    {"query", query},
	    {"schema", schema},
	    {"table", table},
	};
	auto iter = keywords.find(text);
	Token::Type type = (iter != keywords.end())? iter->second: ident;
	return Token{.type = type, .loc = loc};
}
