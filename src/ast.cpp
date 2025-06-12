// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include "ast.h"

namespace ast {

Expression::Expression(Loc loc, Kind kind):
	Node<Expression>(loc),
	kind(kind) {}

Component::Component(Loc loc, Kind kind):
	Node<Component>(loc),
	kind(kind) {}

Ident::Ident(Loc loc, const std::string &value):
	Expression(loc, Kind::Ident),
	value(value) {}

Schema::Schema(Loc loc, Ident::Ptr name):
	Component(loc, Kind::Schema),
	name(name) {}

Column::Column(Loc loc, Ident::Ptr name):
	Node<Column>(loc),
	name(name) {}

Table::Table(Loc loc, Ident::Ptr name, Column::Vec columns):
	Component(loc, Kind::Table),
	name(name),
	columns(columns) {}

Root::Root(Loc loc, Component::Vec components):
	Node(loc),
	components(components) {}

} // namespace ast
