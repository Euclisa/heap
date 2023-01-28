# Headerless heap
This is headerless heap that doesn't use any cstdlib functions and is written in ANSI C, so you can use it inside OpenCL kernels.
You can use it on integral arrays, but make sure that this library doesn't make any checks regarding heap overflows. Choose appropriate size of your heap before usage.
This library stores size of the heap in the first entry of buffer, so take it into account and choose the size of the buffer by 1 more.
All functions recieve as an argument l-value expression 'ret' that will store exit code of function.