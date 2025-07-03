// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include "grammar.h"

#include <memory>
#include <unordered_map>
#include <utility>

namespace grammar {

using std::unique_ptr;
using std::unordered_map;

Prefix::Prefix(Precedence p): prec(p) {}

template<typename T>
struct Prefixer : public Prefix {
	Node::Ptr make(source::Range tk, Node::Ptr&& value) override {
		return std::make_unique<T>(tk, std::move(value));
	}
};

Infix::Infix(Precedence l, Precedence r): left(l), right(r) {}

template<typename T>
struct Infixer : public Infix {
	Node::Ptr make(Node::Ptr&& l, source::Range tk, Node::Ptr&& r) override {
		return std::make_unique<T>(std::move(l), tk, std::move(r));
	}
};

Postfix::Postfix(Precedence p): prec(p) {}

template <typename T>
struct Postfixer : public Postfix {
	Node::Ptr make(Node::Ptr&& value, source::Range tk) override {
		return std::make_unique<T>(std::move(value), tk);
	}
};

const Prefix* Prefix::match(Token tk) {
	static const unordered_map<Token::Type, unique_ptr<Prefix>> ops = {
	};
	auto iter = ops.find(tk.type);
	if (iter != ops.end()) {
		return iter->second.get();
	} else {
		return nullptr;
	}
}

const Infix* Infix::match(Token tk) {
	static const unordered_map<Token::Type, unique_ptr<Infix>> ops = {
	};
	auto iter = ops.find(tk.type);
	if (iter != ops.end()) {
		return iter->second.get();
	} else {
		return nullptr;
	}
}

const Postfix* Postfix::match(Token tk) {
	static const unordered_map<Token::Type, unique_ptr<Postfix>> ops = {
	};
	auto iter = ops.find(tk.type);
	if (iter != ops.end()) {
		return iter->second.get();
	} else {
		return nullptr;
	}
}

} // namespace grammar
