// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include <memory>
#include <optional>

#include "source.h"

namespace ast {

template <class T> class Node {
public:
	virtual ~Node() = default;
	using Ptr = std::shared_ptr<T>;
	using Opt = std::optional<Ptr>;

protected:
	Node(source::Range loc) : loc(loc) {}
	source::Range loc = {};
};

class Root : public Node<Root> {
public:
	Root(source::Range);
};

} // namespace ast
