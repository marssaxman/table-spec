// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <utility>

#include "syntax.h"

namespace syntax {

Term::Term(Kind kind, Loc loc):
	Node(kind, loc) {}

Prefix::Prefix(Kind kind, Loc loc, Node::Ptr &&value):
	Node(kind, loc + value->loc), value(std::move(value)) {}

Infix::Infix(Kind kind, Ptr&& lhs, Loc loc, Ptr&& rhs):
	Node(kind, lhs->loc + loc + rhs->loc),
	lhs(std::move(lhs)), rhs(std::move(rhs)) {}

Postfix::Postfix(Kind kind, Ptr&& value, Loc):
	Node(kind, value->loc + loc), value(std::move(value)) {}

Group::Group(Kind kind, Loc open, Ptr&& value, Loc close):
	Node(kind, open + value->loc + close), value(std::move(value)) {}

Error::Error(Loc loc):
	Node(Kind::Error, loc) {}

Ident::Ident(Loc loc, std::string text):
	Term(Kind::Ident, loc), text(text) {}

Number::Number(Loc loc, std::string text):
	Term(Kind::Number, loc), text(text) {}

Declaration::Declaration(Ptr &&lhs, Loc loc, Ptr&& rhs):
	Infix(Kind::Declaration, std::move(lhs), loc, std::move(rhs)) {}


} // namespace syntax
