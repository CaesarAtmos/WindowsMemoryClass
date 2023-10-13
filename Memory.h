#pragma once
#include <Windows.h>

class Memory
{
public:
	static Memory& Get()
	{
		static Memory instance;
		return instance;
	}
	uintptr_t ModuleBaseAddress;
	int ProcessID;
	bool ProcessAttach(const wchar_t* procName);
	bool ProcessDetach();
	uintptr_t GetModuleBaseAddress(int ProcessId, const wchar_t* ModuleName);
	template <typename valueType>
	valueType Read(uintptr_t address)
	{
		valueType buf;
		ReadProcessMemory(hProcess, (BYTE*)address, &buf, sizeof(buf), 0);
		return buf;
	}
	template <typename valueType>
	void Write(uintptr_t address, valueType value)
	{
		WriteProcessMemory(hProcess, (BYTE*)address, &value, sizeof(value), 0);
	}

private:
	// Private constructor to prevent external instantiation
	Memory() {}
	// Private copy constructor and assignment operator to prevent copying
	Memory(const Memory&) = delete;
	Memory& operator=(const Memory&) = delete;
	// We'll keep the handle variable private because nothing needs this besides our internal functions
	HANDLE hProcess;
};