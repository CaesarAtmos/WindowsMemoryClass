#include "Memory.h"
#include <TlHelp32.h>

uintptr_t Memory::GetModuleBaseAddress(int ProcessId, const wchar_t* ModuleName)
{
    uintptr_t modBaseAddr = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, ProcessId);
    if (hSnap != INVALID_HANDLE_VALUE)
    {
        MODULEENTRY32 modEntry;
        modEntry.dwSize = sizeof(modEntry);
        if (Module32First(hSnap, &modEntry))
        {
            do
            {
                if (!_wcsicmp(modEntry.szModule, ModuleName))
                {
                    modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
                    break;
                }
            } while (Module32Next(hSnap, &modEntry));
        }
    }
    CloseHandle(hSnap);
    return modBaseAddr;
}

bool Memory::ProcessAttach(const wchar_t* procName)
{
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (Process32First(snapshot, &entry) == TRUE)
    {
        while (Process32Next(snapshot, &entry) == TRUE)
        {
            if (_wcsicmp(entry.szExeFile, procName) == 0)
            {
                ProcessID = entry.th32ProcessID;
                hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);
                ModuleBaseAddress = GetModuleBaseAddress(entry.th32ProcessID, procName);
            }
        }
    }

    CloseHandle(snapshot);
    if (hProcess == NULL)
        return false;
    if (ModuleBaseAddress == NULL)
        return false;

    return true;
}

bool Memory::ProcessDetach()
{
    CloseHandle(hProcess);
    if (hProcess)
        return false;
    return true;
}