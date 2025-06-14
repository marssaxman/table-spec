// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <vector>

#include "error.h"
#include "file.h"
#include "rfl/rfl.h"

int read(const std::string &path, File &out) {
	std::ifstream file(path, std::ios::binary | std::ios::ate);
	std::streamsize size = file.tellg();
	file.seekg(0, std::ios::beg);
	if (file.fail()) {
		std::cerr << "cannot open " << path << std::endl;
		return EXIT_FAILURE;
	}

	std::vector<char> buffer(size);
	if (file.read(buffer.data(), size)) {
		out.path = path;
		out.buffer = std::move(buffer);
		return EXIT_SUCCESS;
	} else {
		std::cerr << "failed to read " << path << std::endl;
		return EXIT_FAILURE;
	}
}

int compile(const std::string &path) {
	File file;
	if (read(path, file)) return EXIT_FAILURE;

	Reporter err(file);
	rfl::Config config;
	config.keywords = {
		"schema",
		"table",
	};
	rfl::Frontend frontend(config);
	auto root = frontend.run(file.buffer, err);

	return err.any() ? EXIT_FAILURE: EXIT_SUCCESS;
}

int main(int argc, const char *argv[])
{
	if (argc <= 1) {
		std::cerr << argv[0] << ": no input files" << std::endl;
		return EXIT_FAILURE;
	}
	bool fail = false;
	for (int i = 1; i < argc; ++i) {
		fail |= compile(argv[i]) != EXIT_SUCCESS;
	}
	return fail? EXIT_FAILURE: EXIT_SUCCESS;
}
