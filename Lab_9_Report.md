# Laboratory Work 9 - Final Report
**Topic:** Structure of Binary Executable Files and Reverse Engineering
**Student:** [Your Name Here]

## Objective
To demonstrate the ability to compile a C++ program into a binary executable, inspect its contents, and perform data patching using reverse engineering techniques (HEX editing).

## Step 1: Source Code and Compilation
We started with a standard C++ program (`hello.cpp`) that prints a message to the console.
```cpp
#include <iostream>

int main() {
    std::cout << "Hello, World!";
    return 0;
}
```

This code was compiled into an ELF binary executable named `hello`.
When executing the original binary, the output is:
```
$ ./hello
Hello, World!
```

## Step 2: Binary Patching (HEX Editing)
Instead of using a visual HEX editor, we directly modified the raw binary data, locating the string `"Hello, World!"` which is stored in the `.rodata` (read-only data) section of the binary.

> **Note on String Lengths:** The original string `"Hello, World!"` is exactly 13 characters long. To prevent corrupting the binary, the replacement string must also be exactly 13 characters. Therefore, we replaced it with `"Hacked World!"`.

## Step 3: Verification
After saving the patched binary, we ran the program again to verify the data patching was successful without needing to recompile the source code.

**Final Output:**
```
$ ./hello
Hacked World!
```

## Conclusion
By modifying the `.rodata` section of the compiled binary, we successfully changed the program's output without altering the original C++ source code. This demonstrates that string literals are stored in plain text within executable files and can be manipulated if the replacement data perfectly aligns with the original memory allocation.
