#include "ProcessManager.h"
#include <Windows.h>
#include <TlHelp32.h>

ProcessManager::ProcessManager(const wchar_t* exe) : m_proc_name(exe)
{
    while (!getProcessHandle()) {
        Sleep(3000);
    }
}

ProcessManager::~ProcessManager() { CloseHandle(m_handle); }

bool ProcessManager::getProcessHandle()
{
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (Process32First(snapshot, &entry) == TRUE) {
        while (Process32Next(snapshot, &entry) == TRUE) {
            if (wcscmp(entry.szExeFile, m_proc_name) == 0) {
                m_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);
                CloseHandle(snapshot);
                return true;
            }
        }
    }
    CloseHandle(snapshot);
    return false;
}

void ProcessManager::Patch(const char patch[], DWORD memoryLocation, size_t patch_size)
{
    DWORD oldProt, tempProt;
    if (VirtualProtectEx(m_handle, (LPVOID)memoryLocation, patch_size, PAGE_READWRITE, &oldProt)) {
        if (WriteProcessMemory(m_handle, (LPVOID)memoryLocation, patch, patch_size, NULL)) {
            VirtualProtectEx(m_handle, (LPVOID)memoryLocation, patch_size, oldProt, &tempProt);
        }
    }
}

bool ProcessManager::WriteInt(DWORD memory_location, int value) { return WriteProcessMemory(m_handle, (LPVOID)memory_location, &value, sizeof(value), 0); }
bool ProcessManager::ReadInt(DWORD memory_location, int& value) { return ReadProcessMemory(m_handle, (LPCVOID)memory_location, (LPVOID)&value, sizeof(value), NULL); }
bool ProcessManager::Write(LPVOID memory_location, LPCVOID value, size_t size) { return WriteProcessMemory(m_handle, memory_location, value, size, 0); }
bool ProcessManager::Read(LPCVOID memory_location, LPVOID value, size_t size) { return ReadProcessMemory(m_handle, memory_location, value, size, NULL); }

bool ProcessManager::IsRunning()
{
    DWORD exit_code{ 0 };
    GetExitCodeProcess(m_handle, &exit_code);
    return (exit_code == STILL_ACTIVE);
}
