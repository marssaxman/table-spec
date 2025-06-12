// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "source.h"

namespace ast {

using Loc = source::Range;

template <class T> class Node {
public:
	virtual ~Node() = default;
	using Ptr = std::shared_ptr<T>;
	using Opt = std::optional<Ptr>;
	using Vec = std::vector<Ptr>;
	template<typename... Params>
	static Ptr make(Params&&... args) {
		return std::make_shared<T>(std::forward<Params>(args)...);
	}
	const Loc loc;
protected:
	Node(Loc loc) : loc(loc) {}
};

// Abstract expression base
class Expr : public Node<Expr> {
public:
	enum class Kind {
		Ident,
	};
	const Kind kind;
protected:
	Expr(Loc, Kind);
};

// Abstract component base
class Component : public Node<Component> {
public:
	enum class Kind {
		Schema,
		Table,
	};
	const Kind kind;
protected:
	Component(Loc, Kind);
};

// Expression nodes

class Ident : public Expr {
public:
	Ident(Loc, const std::string &);
	const std::string value;
};

// Component nodes

class Schema : public Component {
public:
	Schema(Loc, Ident::Ptr);
	Ident::Ptr name;
};

class Column : public Node<Column> {
public:
	Column(Loc, Ident::Ptr name, Expr::Ptr type, Expr::Opt val);
	Ident::Ptr name;
	Expr::Ptr type;
	Expr::Opt value;
};

class Table : public Component {
public:
	Table(Loc, Ident::Ptr name, Column::Vec columns);
	Ident::Ptr name;
	Column::Vec columns;
};

// Translation unit

class Root : public Node<Root> {
public:
	Root(Loc, Component::Vec);
	Component::Vec components;
};

} // namespace ast
