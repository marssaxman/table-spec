# table-spec
Domain-specific language for table & query schemas, yielding includable C++
code implementing a bespoke in-memory, non-persistent database engine.

This is an experiment in its early stages.

## What is this for?

Wouldn't it be convenient if one could declare relational data structures
inside one's C++ programs? I often find myself building little ad-hoc databases
out of simple structs and standard containers. Instead of doing this by hand,
I'd like to use a tool which would generate all the busywork necessary for
efficient access and consistent state.

While it might be possible using some kind of nested template wizardry, that
doesn't sound like any fun to write or maintain. Instead, following the example
of `tablegen` from the LLVM project, this tool compiles a schema DSL into C++
source code.

## Usage

To build, simply `make`, then look for `bin/table-spec`.

Invoke `table-spec <FILE>` to process a schema file.


