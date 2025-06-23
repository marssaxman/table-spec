// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include <memory>
#include <string>
#include <vector>

/*

block decl: type, name, contents

column decl: name, type, opt-value

expression: term opt-subscript

subscript: '(' expression-list ')'

*/



namespace ast {

class BlockDecl {
	BlockDecl() = default;
public:
	virtual ~BlockDecl() = default;
	const enum Kind {
		Schema,
		Table,
	};
	using Ptr = std::unique_ptr<Node>;
	using Opt = std::optional<Ptr>;
	using Vec = std::vector<Ptr>;
};


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
	Expression::Opt value;
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

} // namespace ast
