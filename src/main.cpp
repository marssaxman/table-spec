// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <vector>

#include "error.h"
#include "file.h"
#include "lexer.h"
#include "parser.h"
#include "source.h"

File read(const std::string &path) {
	std::ifstream file(path, std::ios::binary | std::ios::ate);
	std::streamsize size = file.tellg();
	file.seekg(0, std::ios::beg);
	if (file.fail()) {
		std::cerr << "cannot open " << path << std::endl;
		return File();
	}

	std::vector<char> buffer(size);
	if (file.read(buffer.data(), size)) {
		return File(path, std::move(buffer));
	} else {
		std::cerr << "failed to read " << path << std::endl;
		return File();
	}
}

int compile(const std::string &path) {
	File file = read(path);
	if (!file.good()) {
		return EXIT_FAILURE;
	}
	Reporter err(file);

	Reader r(file.text());
	Lexer l(r, err);
	Parser p(l, err);
	auto root = p.parse();

	if (root) {
	}

	return err.any() ? EXIT_FAILURE : EXIT_SUCCESS;
}

int main(int argc, const char *argv[]) {
	if (argc <= 1) {
		std::cerr << argv[0] << ": no input files" << std::endl;
		return EXIT_FAILURE;
	}
	bool fail = false;
	for (int i = 1; i < argc; ++i) {
		fail |= compile(argv[i]) != EXIT_SUCCESS;
	}
	return fail ? EXIT_FAILURE : EXIT_SUCCESS;
}
