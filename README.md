# Advent of Code 2024
As always, I'm doing Advent of Code this year. This year, I'm doing it in CPP2 (Herb Sutter's C++ experiment). You can find it at https://github.com/hsutter/cppfront but I'm actually using my own version with JohelEGP's module support in place -- https://github.com/threeifbyair/cppfront . I'm using it both to learn and think about safe C++, and to provide some fresh eyes on cppfront. (And boy, do I have OPINIONS.)

You'll also find my Advent 2023 repo growing with CPP2 code as I do the same thing with other puzzles.

If you want to reproduce what I'm doing, I have CMake 3.30 running on Ubuntu 24.10, using a version of Boost 1.87 beta compiled with clang 19 and libc++. (Why Boost 1.87 beta? Because it contains boost::parser, which is really helpful for AoC puzzles.)
