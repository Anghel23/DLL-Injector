#include "Windows.h"
#include "stdio.h"

int main(int argc, const char* argv[]) {
	if (argc != 3) {
		printf("Usage: DLL_Injector.exe <pid> <path-to-DLL>\n");
		return 0;
	}

	auto pid = atoi(argv[1]);

	HANDLE hProcess = OpenProcess(PROCESS_VM_WRITE | PROCESS_VM_OPERATION | PROCESS_CREATE_THREAD, FALSE, pid);
	if (!hProcess) {
		printf("Error: Failed to open target process (%u)\n", GetLastError());
		return 1;
	}

	auto dllAddrPath = VirtualAllocEx(hProcess, nullptr, 1 << 12, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (!dllAddrPath) {
		printf("Error: Failed to allocate memory in target process (%u)\n", GetLastError());
		CloseHandle(hProcess);
		return 1;
	}

	if (!WriteProcessMemory(hProcess, dllAddrPath, argv[2], strlen(argv[2]) + 1, nullptr)) {
		printf("Error: Failed to write memory in target process (%u)\n", GetLastError());
		VirtualFreeEx(hProcess, dllAddrPath, 0, MEM_RELEASE);
		CloseHandle(hProcess);
		return 1;
	}

	auto hThread = CreateRemoteThread(hProcess, nullptr, 0,
		(LPTHREAD_START_ROUTINE)GetProcAddress(
			GetModuleHandle(L"kernel32.dll"), "LoadLibraryA"),
		dllAddrPath, 0, nullptr);

	if (!hThread) {
		printf("Error: Failed to create remote thread (%u)\n", GetLastError());
		VirtualFreeEx(hProcess, dllAddrPath, 0, MEM_RELEASE);
		CloseHandle(hProcess);
		return 1;
	}

	CloseHandle(hThread);
	CloseHandle(hProcess);

	printf("DLL Injection successful\n");

	return 0;
}