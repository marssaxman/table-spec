# table-spec
Domain-specific language for table & query schemas, yielding includable C++
code implementing a bespoke in-memory, non-persistent database engine.

This is an experiment in its early stages.

# What is this for?

As my usage of C++ has evolved over the years, I have increasingly found myself
building little ad-hoc databases out of simple structs and standard containers.
As with any repetitive task, I'd like to automate this away: instead of writing
implementations for the constraints and queries involved, I'd like to declare
the tables and queries, then let the machine generate all the busywork needed
for validation and efficient access.

While it might be possible to do this all within C++ using some kind of nested
template wizardry, that doesn't sound like it would be any fun to write or
maintain. Instead, I'm following after `tablegen` from the LLVM project and
writing a little tool which will parse a schema file and emit C++ source code.
