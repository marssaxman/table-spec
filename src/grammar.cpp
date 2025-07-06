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

using std::make_unique;
using std::unique_ptr;
using std::unordered_map;

enum Precedence : uint32_t {
	ROOT = 0,
	DECLARATION = 2,
};

Prefix::Prefix(Precedence p): prec(p) {}

template<typename T>
struct Prefixer : public Prefix {
	using Prefix::Prefix;
	Node::Ptr make(source::Range tk, Node::Ptr&& value) const override {
		return make_unique<T>(tk, std::move(value));
	}
};

Infix::Infix(Precedence x): left(x), right(x) {}

Infix::Infix(Precedence l, Precedence r): left(l), right(r) {}

template<typename T>
struct Infixer : public Infix {
	using Infix::Infix;
	Node::Ptr make(Node::Ptr&& l, source::Range tk, Node::Ptr&& r) const override {
		return make_unique<T>(std::move(l), tk, std::move(r));
	}
};

Postfix::Postfix(Precedence p): prec(p) {}

template <typename T>
struct Postfixer : public Postfix {
	using Postfix::Postfix;
	Node::Ptr make(Node::Ptr&& value, source::Range tk) const override {
		return make_unique<T>(std::move(value), tk);
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
	static const unordered_map<Token::Type, const Infix*> ops = {
		{Token::colon, new Infixer<syntax::Declaration>(DECLARATION)},
	};
	auto iter = ops.find(tk.type);
	if (iter != ops.end()) {
		return iter->second;
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
