# C Project Template

My take on setting up a nice environment for developing **C** (no C++) on MacOS.

## Features
- **CMake**

    Like it or not, it's the [most widely used tool for building C](https://www.jetbrains.com/lp/devecosystem-2021/c).  
    Without reinventing the wheel, I followed the project structure recommended by this [book](https://cliutils.gitlab.io/modern-cmake/chapters/basics/structure.html).

- **googletest**

  Again, [most popular tool](https://www.jetbrains.com/lp/devecosystem-2021/c), so I sticked to it.  
    The setup with CMake was a [breeze](https://google.github.io/googletest/quickstart-cmake.html).  
    Truth being told, the most popular unit-testing framework is "I don't write unit tests for C", followed by "I write unit tests, but I don't use any framework", which [you may decide to believe](https://www.commitstrip.com/en/2017/02/08/where-are-the-tests/?).

- **clang-tidy**

    Static-analysis tool that catches a good amount of mistakes at copmile-time.  
    Unfortunately, it doesn't come preinstalled on Mac, but you can [work it around](#requirements).

- **Sanitizers**

    Address Sanitizer (ASan), Undefined Behaviour Sanitizer (UBSan), and Thread Sanitizer (TSan) for runtime analysis.  
    [Here](https://github.com/google/sanitizers) and [here](https://developer.apple.com/documentation/xcode/diagnosing-memory-thread-and-crash-issues-early) for more info.
    
- **Remote-Containers**

    Thanks to the [VSCode Remote Containers extension](https://code.visualstudio.com/docs/remote/containers), you can try your application in a Docker container running Ubuntu `20.4`.

- **valgrind, strace, ltrace**

    These tools aren't available on Mac, but you can use them inside the Docker container.  
    You may use that Docker image to play around with `gcc` and `gdb` too.

## Requirements

Install these programs on your machine:

- CMake
- Docker
- clang-tidy

PS: To install `clang-tidy`, install `llvm` with Homebrew first, then add this alias to the `.bashrc`:

```sh
alias clang-tidy='/opt/homebrew/opt/llvm/bin/clang-tidy'
```

Then install these VSCode extensions:

- ms-vscode.cpptools
- ms-vscode.cmake-tools
- ms-vscode-remote.remote-containers

## How to use it
  
Everything should work out of the box: building, running, tests, and using the integrated debugger.  
If you're not familiar with the VSCode extension [cmake-tools](https://github.com/microsoft/vscode-cmake-tools),
this [tutorial](https://code.visualstudio.com/docs/cpp/cmake-linux#_select-a-kit) will help you with the first steps.

If you want to develop using the remote container, open the Command Palette and type `Remote-Containers: Reopen in Container` (the Docker daemon should be running already).  
Then delete the `build` directory, and build the project again.

Finally, for strace, ltrace, and valgrind, open the remote container and:

```sh
valgrind path-to-executable
strace path-to-executable
ltrace path-to-executable
gdb path-to-executable
```

## FAQ

### googletest isn't in C

Indeed, but for most use cases [it's all macros](https://github.com/google/googletest/tree/main/googletest/samples) and doesn't look much different from regular C code.

## Others

- A very good list of compiler warnings you may want to add:  
http://fastcompression.blogspot.com/2019/01/compiler-warnings.html

- Here's a tiny program that you can use to try out the Address Sanitizer.  
  Copy it into `apps/main.c`, select the `Asan` [variant](https://github.com/microsoft/vscode-cmake-tools/blob/main/docs/variants.md), build, and run it.

```c
#include <stdlib.h>

int main()
{
    int *x = malloc(10 * sizeof(int));
    free(x);
    return x[5];
}
```
