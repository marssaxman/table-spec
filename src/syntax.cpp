// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <utility>

#include "syntax.h"

namespace syntax {

Prefix::Prefix(Kind kind, Loc loc, Node::Ptr &&value):
	Node(kind), value(std::move(value)) {}

Infix::Infix(Kind kind, Ptr&& lhs, Loc loc, Ptr&& rhs):
	Node(kind), lhs(std::move(lhs)), rhs(std::move(rhs)) {}

Postfix::Postfix(Kind kind, Ptr&& value, Loc):
	Node(kind), value(std::move(value)) {}

Group::Group(Kind kind, Ptr&& value):
	Node(kind), value(std::move(value)) {}

} // namespace syntax
