// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <iostream>

int main(int argc, const char *argv[])
{
	if (argc <= 1) {
		std::cerr << argv[0] << ": no input files" << std::endl;
		return EXIT_FAILURE;
	}
	bool fail = false;
	for (int i = 1; i < argc; ++i) {
		(void)argv[i];
	}
	return fail? EXIT_FAILURE: EXIT_SUCCESS;
}
