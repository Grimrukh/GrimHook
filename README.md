# Firelink

Firelink is a C++ project for building DLLs that hook into running Windows applications and provide pointer and memory
manipulation features (like Cheat Engine). This project is intended for educational or modding purposes and should not 
be used to cheat in online games or other malicious activities.

Of course, the real value of Firelink is the `BaseHook` subclasses that target FromSoftware games. Currently, only
***Dark Souls: Remastered*** (`FirelinkDSR`) and ***Elden Ring*** (`FirelinkER`) are supported. These hook subclasses,
like similar projects by @JKAnderson (TKGP) and myself in C# and Python, automatically expose known valuable memory 
addresses in the running game application (a la Cheat Engine). You can create a simple native DLL that creates a hook
when the DLL is loaded by searching for the game process, or by assuming that the DLL is being loaded *into* the game
process as a plugin (e.g. via `dinput8.dll` sideloading).

---

## Features
- **FirelinkCore**: Core utilities and memory manipulation functions, centered around `ManagedProcess`.
- **FirelinkDSR**: Extensions and hooks specific to ***Dark Souls: Remastered***, centered around `DSRHook`.
- **FirelinkER**: Extensions and hooks specific to ***Elden Ring***, centered around `ERHook`.
  - Bonus: includes a complete C++ implementation of the `MSB` format, which e.g. reads Stormveil Castle in ~100 ms.

---

## Prerequisites

These libraries are **Windows only (64-bit)**, as they are currently only designed to support (64-bit) FromSoftware
games on Steam. Linux (and Steam Deck) support may come in the (very distant) future.

Before building the project, ensure you have the following tools installed:

1. **CMake**: Version 3.20 or higher.
    - [Download CMake](https://cmake.org/download/)
2. **Ninja** (optional): For faster builds.
    - [Ninja Installation](https://ninja-build.org/)
3. **MinGW** (for GCC/Clang on Windows) or Visual Studio Build Tools.
    - [MinGW Installation](http://mingw-w64.org/)
    - [Visual Studio Build Tools](https://visualstudio.microsoft.com/visual-cpp-build-tools/)
4. **Git**: For cloning the repository.
    - [Git Installation](https://git-scm.com/)

---

## Building the Project

Follow these steps to build the project:

### Clone the Repository
```bash
git clone https://github.com/Grimrukh/Firelink.git
cd Firelink
```
or via SSH:
```bash
git clone git@github.com/Grimrukh/Firelink.git
cd Firelink
```

### Configure the Project with CMake

Using Ninja:
```bash
cmake -S . -B build -G "Ninja" -DCMAKE_BUILD_TYPE=Release
```

Or using your installed version of Visual Studio (e.g. 2022):
```bash
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
```

### Build the DLLs

```bash
cmake --build build --config Release
```

---

## Running Tests (Optional)

If your project includes tests, you can run them using `ctest`. First, ensure that tests are enabled in the CMake configuration:

```bash
cmake -S . -B build -G "Ninja" -DENABLE_TESTING=ON
```

Then build and run the tests:
```bash
cmake --build build --config Release
ctest --test-dir build --output-on-failure
```

---

## Using the DLLs

Once built, the DLLs will be located in the `build` directory. To use them, copy them to the directory of your own C++
application that links against `FirelinkCore` (and optionally `FirelinkDSR`) and use the public `include` headers to
gain access to classes such as `Firelink::BaseHook` and `FirelinkDSR::DSRHook`.

Here's a simple example loop that prints the player's health in ***Dark Souls: Remastered***. See other projects, such
as [DSRWeaponSwap](https://github.com/Grimrukh/DSRWeaponSwap), for more complex examples.

```cpp
#include <atomic>
#include <format>
#include <iostream>
#include <thread>

#include "FirelinkDSR/DSRHook.h"

void PrintHealthEverySecond()
{
    using namespace std;
    using namespace Firelink;
    using namespace FirelinkDSR;

    // We need an atomic flag to pass to `WaitForProcess` to stop the search if needed.
    // It's not used in this example, but the caller could pass it in and set it to `true` in another thread to
    // stop the search or our main loop below.
    atomic<bool> stopFlag = false;

    // Do initial DSR process search. We are the sole owner of the found `ManagedProcess`.
    auto newProcess = ManagedProcess::WaitForProcess(
        DSR_PROCESS_NAME,
        10000,  // 10 second timeout
        500,  // 500 ms search interval (enumerating all Windows processes is expensive)
        stopFlag); 

    // Check if we found the process (as opposed to timing out).
    if (!newProcess)
    {
        cout << "WARNING: Failed to find DSR process." << endl;
        return;
    }
    
    // We create a `DSRHook` and transfer ownership of the `ManagedProcess` to it.
    auto dsrHook = make_unique<DSRHook>(std::move(newProcess));
    
    // Main loop. We can reuse the same atomic stop flag.
    while (!stopFlag.load())
    {
        // Get the player's current and max health.
        pair<int, int> currentAndMaxHealth = dsrHook->GetPlayerHp();
        
        // Print health.
        string msg = format("Player health: {} / {}", currentAndMaxHealth.first, currentAndMaxHealth.second);
        cout << msg << endl;
        
        // Sleep for a second.
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
    
    // Exited loop.
    cout << "Stopped printing player health." << endl;
}
```

---

## Continuous Integration

The project includes a GitHub Actions workflow to automatically build and test the project on every commit. The MSB
file for Stormveil Castle in ***Elden Ring*** is included for testing the MSB format.

### Triggered Events:
- Pushes to the `main` branch.
- Pull requests targeting `main`.

You can view the CI status in the **Actions** tab of the GitHub repository.

---

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

## Contributing

Contributions are welcome! To contribute:
1. Fork the repository.
2. Create a new branch for your feature or bug fix.
3. Submit a pull request with a detailed description of your changes.

---

## Support

If you encounter any issues, please open an issue on the [GitHub repository](https://github.com/Grimrukh/Firelink/issues).

Happy hooking!
