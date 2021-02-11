# Benchmarking sorting algorithms
Benchmarked using Google benchmark library [link](https://github.com/google/benchmark).
Used sorts:

-std::sort

-quicksort custom

-quicksort, with bubble sort when array<=64

-quicksort, finding median for every partition && bubble sort <=64


```
Run on (8 X 3600 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x4)
  L1 Instruction 32 KiB (x4)
  L2 Unified 256 KiB (x4)
  L3 Unified 6144 KiB (x1)
Load Average: 1.33, 1.47, 1.50
-----------------------------------------------------------------------------
Benchmark                                   Time             CPU   Iterations
-----------------------------------------------------------------------------
BM_std_sort/2097152_mean                  794 ms          794 ms           50
BM_std_sort/2097152_median                793 ms          793 ms           50
BM_std_sort/2097152_stddev               5.86 ms         5.81 ms           50
BM_quicksort/2097152_mean                 781 ms          781 ms           50
BM_quicksort/2097152_median               775 ms          775 ms           50
BM_quicksort/2097152_stddev              26.8 ms         26.8 ms           50
BM_quickBubble_sort/2097152_mean          626 ms          626 ms           50
BM_quickBubble_sort/2097152_median        620 ms          620 ms           50
BM_quickBubble_sort/2097152_stddev       29.8 ms         29.8 ms           50
BM_quicksort_median/2097152_mean         2051 ms         2051 ms           50
BM_quicksort_median/2097152_median       2043 ms         2043 ms           50
BM_quicksort_median/2097152_stddev       62.2 ms         62.2 ms           50
```
