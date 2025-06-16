// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include "raise.h"

using namespace rfl;

class Engine {
public:
	Engine(Reporter &err);
	std::vector<schema::Schema> schemas;
	void run(cst::Node *);

protected:
	cst::Node *parse_schema(cst::Node *);

private:
	Reporter &err;
};

Engine::Engine(Reporter &err) : err(err) {}

void Engine::run(cst::Node *n) {
	while (n) {
		n = parse_schema(n);
	}
}

cst::Node *Engine::parse_schema(cst::Node *) {
	// TODO
	return nullptr;
}

std::vector<schema::Schema> raise(cst::Node::Ptr root, Reporter &err) {
	Engine engine(err);
	engine.run(root.get());
	return engine.schemas;
}
