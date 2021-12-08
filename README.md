## Dependencies

Install Bazel 4 or higher and GNU Parallel.

## Run Instructions

Build the main solver with

```
bazel build //src/solvers:threshold_solve
```

To compile in opt mode, use

```
bazel build //src/solvers:threshold_solve -c opt --copt="-O3" --copt="-ffast-math"
```

Feel free to modify constants in the `src/solvers/threshold_solve.cc` file.

The binary will be located at `bazel-bin/src/solvers/threshold_solve`. It reads
an input from stdin and outputs a solution to stdout. To log, run the binary
with `--alsologtostderr`.

To solve tasks in parallel, build as above and use the `solve.sh` and
`solve_all.sh` scripts located in the root directory. `solve.sh` solves only
the tasks in the `tosolve` file; `solve_all.sh` solves all inputs.


## Merging the results

Use `python3 tools/merge.py inputs outputs... destination` to merge the output
folders, taking the best solution from each folder.

## Checking the results

Use `python3 tools/score.py inputs outputs...` to generate a list of the best
solutions and the folders that they came from.

## Updating tosolve

Copy the query inside query.js and paste it into the developer console on the
leaderboard page.

## Language Server

Run `bazel run @hedron_compile_commands//:refresh_all` to generate a list of
compile commands for your C++ language server.

## Notes

small-77 solved by hand.
medium-69 solved by hand.

