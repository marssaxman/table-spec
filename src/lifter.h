// Copyright 2025 Mars Saxman
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include <vector>

#include "rfl/cst.h"
#include "rfl/reporter.h"
#include "schema.h"

std::vector<schema::Schema> lift(rfl::cst::Node::Ptr, rfl::Reporter &err);
