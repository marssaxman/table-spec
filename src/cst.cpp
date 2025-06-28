// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include "cst.h"

namespace cst {

List::List(Node::Ptr value) : Node(Kind::List), value(std::move(value)) {}

Leaf::Leaf(Kind kind, Loc loc) : Node(kind), loc(loc) {}

Keyword::Keyword(Loc loc, int id) : Leaf(Kind::Keyword, loc), id(id) {}

Ident::Ident(Loc loc) : Leaf(Kind::Ident, loc) {}

Number::Number(Loc loc) : Leaf(Kind::Number, loc) {}

Symbol::Symbol(Loc loc, int ch) : Leaf(Kind::Symbol, loc), ch(ch) {}

Semicolon::Semicolon(Node::Opt value)
    : Node(Kind::Semicolon), value(std::move(value)) {}

Comma::Comma(Node::Opt value) : Node(Kind::Comma), value(std::move(value)) {}

Group::Group(Kind kind, Loc loc, Opt body)
    : Node(kind), loc(loc), body(std::move(body)) {}

Parens::Parens(Loc loc, Opt body) : Group(Kind::Parens, loc, std::move(body)) {}

Brackets::Brackets(Loc loc, Opt body)
    : Group(Kind::Brackets, loc, std::move(body)) {}

Braces::Braces(Loc loc, Opt body) : Group(Kind::Braces, loc, std::move(body)) {}

} // namespace cst
