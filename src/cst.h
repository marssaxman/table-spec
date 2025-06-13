// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include <memory>
#include <optional>

#include "source.h"

namespace cst {

using Loc = source::Range;

struct Node {
	virtual ~Node() = default;
	const enum Kind {
		List,
		Ident,
		Number,
		Semicolon,
		Comma,
		Operator,
		Parens,
		Brackets,
		Braces,
	} kind;
	using Ptr = std::unique_ptr<Node>;
	using Opt = std::optional<Ptr>;
protected:
	Node(Kind kind) : kind(kind) {}
};

struct List : public Node {
	List(Node::Ptr value);
	Node::Ptr value;
	Node::Opt next;
};

struct Leaf : public Node {
	Leaf(Kind kind, Loc loc);
	const Loc loc;
};

struct Ident : public Leaf {
	Ident(Loc loc);
};

struct Number : public Leaf {
	Number(Loc loc);
};

struct Semicolon : public Node {
	Semicolon(Node::Opt value);
	Node::Opt value;
	Node::Opt next;
};

struct Comma : public Node {
	Comma(Node::Opt value);
	Node::Opt value;
	Node::Opt next;
};

struct Operator : public Leaf {
	Operator(Loc loc, int ch);
	const int ch;
};

struct Group : public Node {
	Group(Kind kind, Loc loc, Opt body);
	const Loc loc;
	Opt body;
};

struct Parens : public Group {
	Parens(Loc loc, Opt body);
};

struct Brackets : public Group {
	Brackets(Loc loc, Opt body);
};

struct Braces : public Group {
	Braces(Loc loc, Opt body);
};

} // namespace cst

