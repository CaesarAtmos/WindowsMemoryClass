
# Windows Memory Class

A Short and sweet Read/WriteProcessMemory wrapper singleton class in C++.
## Usage

Download the Memory.cpp and Memory.h files and include them in your project.

## Reading an integer

```cpp
#include <iostream>
#include "Memory.h"

int main()
{
    Memory& mem = mem.Get(); // Fetch our singleton instance
    if (mem.ProcessAttach(L"Example.exe")) // Attach to the process (open a handle)
    {
        int examplevalue = mem.Read<int>(0xD3ADB33F); // Read the value of an integer stored at address '0xD3ADB33F'
        std::cout << "Example Value: " << examplevalue << std::endl; // Print our example value to the console
        mem.ProcessDetach(); // Detach from the process (closes our handle)
    }
    return 0;
}
```
## Writing a boolean at an offset

```cpp
#include <iostream>
#include "Memory.h"

int main()
{
    Memory& mem = mem.Get(); // Fetch our singleton instance
    if (mem.ProcessAttach(L"Example.exe")) // Attach to the process (open a handle)
    {
        mem.Write<bool>(mem.ProcessBaseAddress + 0xD3ADB33F, true); // Write a boolean value of 'true' at the address of the base address + 0xD3ADB33F
        mem.ProcessDetach(); // Detach from the process (closes our handle)
    }
    return 0;
}
```
## Reading a string from a DLL running in the process

```cpp
#include <iostream>
#include "Memory.h"

int main()
{
    Memory& mem = mem.Get(); // Fetch our singleton instance
    if (mem.ProcessAttach(L"Example.exe")) // Attach to the process (open a handle)
    {
        uintptr_t uExampleModule = mem.GetModuleBaseAddress(L"Example.dll"); // Get the base address of the DLL by name
        const char* examplestring = mem.Read<const char*>(uExampleModule + 0xD3ADB33F); // Add the base address of the DLL with your offset to get the address and read from it
        std::cout << "Example String: " << examplestring << std::endl;
        mem.ProcessDetach(); // Detach from the process (closes our handle)
    }
    return 0;
}
```
