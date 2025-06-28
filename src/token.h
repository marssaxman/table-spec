// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include <cstdint>

#include "source.h"

struct Token {
	enum Type : int32_t {
		eof = 0,
		ident = -1,
		number = -2,
		proc = -3,
		query = -4,
		schema = -5,
		table = -6,
		comma = ',',
		semicolon = ';',
	} type;
	source::Range loc;
};

