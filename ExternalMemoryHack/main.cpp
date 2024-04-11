#include <iostream>
#include <Windows.h>


/*
	Runs external memory hack on "The Battle for Wesnoth 1.14.9.

	External memory hack in general work by using the Windows API to gain a handle over
	applications. Once the Application can be referenced, the application's memory
	can be manipulated.
*/
void ExternalMemoryHack() {

	// Unsigned 32-bit int,										will store gold memory address.
	DWORD gold_value = 0;
	// Max number of bytes to which a pointer can point,		will store number of bytes read.
	size_t bytes_read = 0;
	// Unsigned 32-bit int,										will store wensnoth process id.
	DWORD process_id = 0;

	// Retrieve window handle.
	HWND wesnoth_window = FindWindow(NULL, L"The Battle for Wesnoth - 1.14.9");

	// Retrieve process id, store in process_id.
	GetWindowThreadProcessId(wesnoth_window, &process_id);

	// Get wesnoth process
	HANDLE wesnoth_process = OpenProcess(PROCESS_ALL_ACCESS, true, process_id);


	// Gold Address = [[BS + 0x60] + 0xA90] + 4.
	// Each bracket indicates a search.
	ReadProcessMemory(wesnoth_process, (void*)0x017EED18, &gold_value, 4, &bytes_read);

	// Add additional offset and re-search.
	gold_value += 0xA90;
	ReadProcessMemory(wesnoth_process, (void*)gold_value, &gold_value, 4, &bytes_read);

	// Final offset added.
	gold_value += 4;

	// Gold value in game is set to new_gold_value.
	DWORD new_gold_value = 999;
	size_t bytes_written;

	// Write new gold value to the game.
	WriteProcessMemory(wesnoth_process, (void*)gold_value, &new_gold_value, 4, &bytes_written);

}


/*
	Runs injected DLL hack on "The Battle for Wesnoth 1.14.9.

	Injected DLL hack in general work by gaining access to the application's internal memory
	and using pointers to manipulated that memory. 

*/
void InternalMemoryHack() {

}


int main(int argc, char** argv) {

	ExternalMemoryHack();

	return 0;
}