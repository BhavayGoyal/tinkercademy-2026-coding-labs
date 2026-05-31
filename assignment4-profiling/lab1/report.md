# Intro Profiling Lab Report

## 1. Optimizations Made

- TODO

## 2. Methodology Walkthrough

Include before/after evidence from:

- `time`
- `perf stat`
- FlameGraph
- Callgrind/KCachegrind
- Valgrind leak summary

## 3. Correctness Evidence

Include:

- `make test`
- Final normal run output
- Checksum comparison before and after optimization

## 4. Conceptual Questions

Answer Q1.1 through Q6.1 from the README.

**Q1.1:** `real` is wall-clock elapsed time, while `user` + `sys` is CPU time spent in user mode and kernel mode. They usually differ for 2 reasons.
  - wall-clock (real) time keeps ticking during waiting (I/O, scheduling, preemption), making `real` larger
  - Multiple threads running simultaneously on multiple cores can make CPU time exceed wall-clock (real) time because CPU time will be total time taken on all cores combined, while real time is the total wall-clock time.

Here in this question, we ran it on just one core using taskset -c 0, so 2nd option is ruled out so in our case real time is bigger than user+sys because of waiting (I/O, scheduling, preemption) etc.


<!-- **Q1.1:** `real` is wall-clock elapsed time, while `user` + `sys` is CPU time spent in user mode and kernel mode. They usually differ for 2 reasons.
  - wall-clock (real) time keeps ticking during waiting (I/O, scheduling, preemption), making `real` larger
  - Multiple threads running simultaneously on multiple cores can make CPU time exceed wall-clock (real) time because CPU time will be total time taken on all cores combined, while real time is the total wall-clock time.
  
Here in this question, we ran it on just one core using taskset -c 0, so 2nd option is ruled out so in our case real time is bigger than user+sys because of waiting (I/O, scheduling, preemption) etc. -->