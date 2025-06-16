// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include <memory>
#include <string>
#include <vector>

namespace ast {

struct Node {
	virtual ~Node() = default;
	const enum Kind {
		Ident,
		Number,
		Subscript,
		Column,
		Table,
		Schema,
		Root,
	} kind;
	using Ptr = std::unique_ptr<Node>;
	using Opt = std::optional<Ptr>;
	using Vec = std::vector<Ptr>;

protected:
	Node(Kind kind) : kind(kind) {}
} :

    struct Expression : public Node {
};

struct Ident : public Expression {
	std::string value;
};

struct Number : public Expression {
	std::string value;
};

struct Subscript : public Expression {
	Expression::Ptr base;
	Expression::Ptr arg;
};

struct Column : public Node {
	std::string name;
	Expression::Ptr type;
	Expressin::Opt value;
};

struct Table : public Node {
	std::string name;
	Column::Vec columns;
};

struct Schema : public Node {
	std::string name;
	Table::Vec tables;
};

struct Root : public Node {
	Schema::Vec schemas;
};

} // namespace ast
