// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include <memory>
#include <optional>

#include "rfl/source.h"

namespace rfl {
namespace cst {

using Loc = source::Range;

struct Node {
	virtual ~Node() = default;
	const enum Kind {
		List,
		Keyword,
		Ident,
		Number,
		Symbol,
		Semicolon,
		Comma,
		Parens,
		Brackets,
		Braces,
	} kind;
	using Ptr = std::unique_ptr<Node>;
	using Opt = std::optional<Ptr>;
protected:
	Node(Kind kind) : kind(kind) {}
};

// Consecutive terms
struct List : public Node {
	List(Node::Ptr value);
	Node::Ptr value;
	Node::Opt next;
};

// Base class for terminal nodes
struct Leaf : public Node {
protected:
	Leaf(Kind kind, Loc loc);
public:
	const Loc loc;
};

// Reserved identifier
struct Keyword : public Leaf {
	Keyword(Loc loc, int id);
	const int id;
};

// Any other identifier
struct Ident : public Leaf {
	Ident(Loc loc);
};

// Numeric literal
struct Number : public Leaf {
	Number(Loc loc);
};

// Punctuation symbol
struct Symbol : public Leaf {
	Symbol(Loc loc, int ch);
	const int ch;
};

// Semicolon-delimited sequence
struct Semicolon : public Node {
	Semicolon(Node::Opt value);
	Node::Opt value;
	Node::Opt next;
};

// Comma-delimited tuple
struct Comma : public Node {
	Comma(Node::Opt value);
	Node::Opt value;
	Node::Opt next;
};

// Base class for subexpression groups
struct Group : public Node {
protected:
	Group(Kind kind, Loc loc, Opt body);
public:
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
} // namespace rfl
