#include <windows.h>
#include <stdio.h>

volatile int global = 0; 

DWORD WINAPI increment_thread(LPVOID arg) {
    for (int i = 0; i < 10; i++) {
        global++;
        printf("Increment thread: global = %d\n", global);
        Sleep(500); 
    }
    return 0;
}

DWORD WINAPI decrement_thread(LPVOID arg) {
    for (int i = 0; i < 10; i++) {
        global--;
        printf("Decrement thread: global = %d\n", global);
        Sleep(500); 
    }
    return 0;
}

int main() {
    HANDLE hThreadInc, hThreadDec;

    hThreadInc = CreateThread(NULL, 0, increment_thread, NULL, 0, NULL);
    hThreadDec = CreateThread(NULL, 0, decrement_thread, NULL, 0, NULL);

    SetThreadPriority(hThreadDec, THREAD_PRIORITY_HIGHEST);

    WaitForSingleObject(hThreadInc, INFINITE);
    WaitForSingleObject(hThreadDec, INFINITE);

    CloseHandle(hThreadInc);
    CloseHandle(hThreadDec);

    printf("Final global value: %d\n", global);
    return 0;
}