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
		List,
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

// Categories of operators based on position
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
	Group(Kind kind, Ptr&& value);
};

// specific syntax classes

} // namespace syntax
