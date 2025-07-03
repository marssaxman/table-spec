// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include "grammar.h"

namespace grammar {

Prefix::Prefix(Precedence p): prec(p) {}

const Prefix* Prefix::match(Token tk) {
	return nullptr;
}

Infix::Infix(Precedence l, Precedence r): left(l), right(r) {}

const Infix* Infix::match(Token tk) {
	return nullptr;
}

Postfix::Postfix(Precedence p): prec(p) {}

const Postfix* Postfix::match(Token tk) {
	return nullptr;
}

} // namespace grammar
