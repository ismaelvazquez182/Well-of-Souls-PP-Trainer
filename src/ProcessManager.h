#pragma once
#include <Windows.h>

class ProcessManager {
public:
	ProcessManager(const wchar_t* executable_name);
	~ProcessManager();
	void Patch(const char patch[], DWORD memoryLocation, size_t patch_size);
	bool WriteInt(DWORD memory_location, int value);
	bool ReadInt(DWORD memory_location, int& value);
	bool Write(LPVOID memory_location, LPCVOID value, size_t size);
	bool Read(LPCVOID memory_location, LPVOID value, size_t size);
	bool IsRunning();
private:
	HANDLE m_handle;
	bool getProcessHandle();
	const wchar_t* m_proc_name;
};
