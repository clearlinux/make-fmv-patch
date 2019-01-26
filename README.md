
# Make FMV patch generator

The Clear Linux project is currently focusing on applying **function multi-version (FMV)** technology to packages where it is detected that AVX instructions can yield a performance improvement. To solve some of the issues involved with supporting FMV in a full Linux distribution, the project provides a patch generator based on vectorization-candidate detection (using the gcc `-fopt-info-vec` compiler flag). This tool can provide all the FMV patches that a Linux distribution might use.

Although this patch tool was originally designed to be used for Clear Linux OS, the patch generator can be applied to any project built with gcc.

## Example

The following sample code will be used:

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#define MAX 1000000

int a[256], b[256], c[256];

void foo()
{
    int i,x;
    for (x=0; x<MAX; x++)
    {
        for (i=0; i<256; i++)
        {
            a[i] = b[i] + c[i];
        }
     }
}

int main()
{
    foo();
    return 0;
}
```

### 1. Compile the code:
`gcc -O2 -ftree-vectorize -fopt-info-vec  example.c -o example &> log.txt
`

Breaking down the command:
* The `-ftree-vectorize` flag enables vectorization. *Note*: it is enabled by default at `-O3`
* The `-fopt-info-vec` generates a report to stdout providing details of code that the compiler was able to vectorize.
* The `&> log.txt` pipes the output to a file of the same name.

Upon examing the log.txt file (using `cat log.txt`), it can be seen that gcc was able to vectorize parts of the code:
```
example.c:13:13: note: loop vectorized
example.c:13:13: note: loop vectorized
```
### 2. Generate the FMV patch
The patch tool takes the format

`perl make-fmv-patch.pl <buildlog> <sourcecode>`

After checking out the tool from the repository, run the patch tool using `log.txt` as input:

```perl make-fmv-patch.pl log.txt .```

Upon completion, the patch tool will output log confirming that example.c has been patched:

```patching ./example.c @ lines (8)```

The command generates the following example.c.patch patch:
```
--- ./example.c 2019-01-13 00:04:47.646072680 +0000
+++ ./example.c~        2019-01-13 00:04:57.586072680 +0000
@@ -5,6 +5,7 @@

     int a[256], b[256], c[256];

+__attribute__((target_clones("avx2","arch=atom","default")))
     void foo()
     {
         int i,x;
```

If you want to use a differnt target for your code you can create a file targets.conf

For example

```
#if defined(i386__) || defined(__i386__) || defined(_M_IX86) || defined(_M_IX86) || defined(__X86__) || defined(_X86_) || defined(__I86__) || defined(__INTEL__) || defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64) || defined(_M_AMD64)
        __attribute__((target_clones("avx2","arch=haswell","default")))
#endif
```

### 3. Apply the patch
Using the example.c.patch file, apply the patch to example.c:

```patch -p1 < example.c.patch```

The example.c file should have been patched, and look something like:

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#define MAX 1000000

int a[256], b[256], c[256];

__attribute__((target_clones("avx2","arch=atom","default")))
void foo()
{
    int i,x;
    for (x=0; x<MAX; x++)
    {
        for (i=0; i<256; i++)
        {
            a[i] = b[i] + c[i];
        }
     }
}

int main()
{
    foo();
    return 0;
}
```
### 4. Recompile the code

Compile the code again (with FMV syntax having been applied to the code):

```gcc -O2 -ftree-vectorize -fopt-info-vec  example.c -o example```

The console output should contain:
```
example.c:14:13: note: loop vectorized
example.c:14:13: note: loop vectorized
example.c:14:13: note: loop vectorized
```
Voila!

## Requirements

- GCC v6 compiler or newer
- Perl
- Exuberant ctags:
    In order to use `make-fvm-patch.pl` your system will need Exuberant Ctags
    (https://sourceforge.net/projects/ctags/), this is due to the `--c-kinds`
    ctags' flag usage.

## Test examples

The repostory makes available a tests directory. Users can use the tests directory to conduct their own tests and/or share issues with sample code (for easy reproducability).

```bash
    cd tests
    make
    cd ..
```

Once built, follow the steps outlined in the example above:

```bash
    perl make-fmv-patch.pl tests/max-build.log tests/
    perl make-fmv-patch.pl tests/loop-build.log tests/
```
then...
* Apply the patches
* Recompile the code
* Run

## License

This project is licensed under an MIT license. See the `LICENSE` file in this project.

## Further Reading
* Clear Linux: [Use the function multi-version patch generator](https://clearlinux.org/documentation/clear-linux/tutorials/fmv)
