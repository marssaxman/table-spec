// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include <cstdint>

#include "source.h"
#include "syntax.h"
#include "token.h"

namespace grammar {

enum Precedence : uint32_t;
using syntax::Node;

struct Prefix {
	Prefix(Precedence);
	Precedence prec{};
	virtual Node::Ptr make(source::Range, Node::Ptr&&) const = 0;
	static const Prefix* match(Token);
};

struct Infix {
	Infix(Precedence);
	Infix(Precedence left, Precedence right);
	Precedence left{};
	Precedence right{};
	virtual Node::Ptr make(Node::Ptr&& l, source::Range tk, Node::Ptr&& r) const = 0;
	static const Infix* match(Token tk);
};

struct Postfix {
	Postfix(Precedence);
	Precedence prec{};
	virtual Node::Ptr make(Node::Ptr&& val, source::Range tk) const = 0;
	static const Postfix* match(Token tk);
};

} // namespace grammar

