// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include <memory>
#include <optional>

#include "source.h"

namespace syntax {

using Loc = source::Range;

struct Node {
	virtual ~Node() = default;
	const enum Kind {
		Error,
		Ident,
		Number,
	} kind;
	const Loc loc;
	using Ptr = std::unique_ptr<Node>;
	using Opt = std::optional<Ptr>;

protected:
	Node(Kind kind, Loc loc) : kind(kind), loc(loc) {}
};

// Categories of operators based on position

struct Term : public Node {
protected:
	Term(Kind kind, Loc);
};

struct Prefix : public Node {
	const Ptr value;
protected:
	Prefix(Kind kind, Loc, Node::Ptr&& value);
};

struct Infix : public Node {
	const Ptr lhs;
	const Ptr rhs;
protected:
	Infix(Kind kind, Ptr&& lhs, Loc loc, Ptr&& rhs);
};

struct Postfix : public Node {
	const Ptr value;
protected:
	Postfix(Kind kind, Ptr&& value, Loc);
};

struct Group : public Node {
	const Ptr value;
protected:
	Group(Kind kind, Loc open, Ptr&& value, Loc close);
};

// specific syntax classes

struct Error : public Node {
	Error(Loc);
};

struct Ident : public Term {
	Ident(Loc, std::string);
	const std::string text;
};

struct Number : public Term {
	Number(Loc, std::string);
	const std::string text;
};

} // namespace syntax
