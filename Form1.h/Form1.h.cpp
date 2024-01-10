#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>

// Global variables
std::wstring encryptionKey;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Function prototypes
void SaveToFile(HWND hwnd);
void ReadFromFile(HWND hwnd);
void ShowAboutDialog();
void SetEncryptionKey(HWND hwnd);
std::wstring EncryptData(const std::wstring& data, const std::wstring& key);
std::wstring DecryptData(const std::wstring& encryptedData, const std::wstring& key);
int InputBox(HWND hwnd, const wchar_t* title, const wchar_t* prompt, wchar_t* value, int valueSize);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    // Register the window class.
    const wchar_t CLASS_NAME[] = L"SD1_GUI_CLASS";

    WNDCLASS wc = {};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.
    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"SD1 Version 1.0",             // Window text (L prefix for wide string)
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 300,

        NULL,       // Parent window
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE: {
        // Create menus
        HMENU hMenu, hSubMenu;

        hMenu = CreateMenu();
        hSubMenu = CreatePopupMenu();

        AppendMenu(hSubMenu, MF_STRING, 1, L"Save to File");
        AppendMenu(hSubMenu, MF_STRING, 2, L"Read from File");
        AppendMenu(hSubMenu, MF_STRING, 3, L"Set Encryption Key");
        AppendMenu(hSubMenu, MF_STRING, 4, L"About");
        AppendMenu(hSubMenu, MF_STRING, 5, L"Exit");

        AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hSubMenu, L"File");

        SetMenu(hwnd, hMenu);
    } break;

    case WM_COMMAND: {
        switch (LOWORD(wParam)) {
        case 1: // Save to File
            SaveToFile(hwnd);
            break;

        case 2: // Read from File
            ReadFromFile(hwnd);
            break;

        case 3: // Set Encryption Key
            SetEncryptionKey(hwnd);
            break;

        case 4: // About
            ShowAboutDialog();
            break;

        case 5: // Exit
            DestroyWindow(hwnd);
            break;
        }
    } break;

    case WM_DESTROY: {
        PostQuitMessage(0);
    } break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void SaveToFile(HWND hwnd) {
    // Get user input (e.g., from TextBox or custom input)
    std::wstring dataToSave;
    // ...

    // Encrypt data before saving
    std::wstring encryptedData = EncryptData(dataToSave, encryptionKey);

    // Save encrypted data to a file
    std::wofstream outputFile(L"output.dat", std::ios::binary);
    if (outputFile.is_open()) {
        outputFile.write(encryptedData.c_str(), encryptedData.size());
        outputFile.close();
        MessageBox(hwnd, L"Data saved to file.", L"Info", MB_OK | MB_ICONINFORMATION);
    }
    else {
        MessageBox(hwnd, L"Error: Unable to open the file for writing.", L"Error", MB_OK | MB_ICONERROR);
    }
}

void ReadFromFile(HWND hwnd) {
    // Read encrypted data from the file
    std::wifstream inputFile(L"output.dat", std::ios::binary | std::ios::ate);
    if (inputFile.is_open()) {
        std::streamsize size = inputFile.tellg();
        inputFile.seekg(0, std::ios::beg);

        std::wstring encryptedData(size, L'\0');
        if (inputFile.read(&encryptedData[0], size)) {
            inputFile.close();

            // Decrypt data after reading
            std::wstring decryptedData = DecryptData(encryptedData, encryptionKey);

            // Display decrypted data (e.g., in TextBox or custom output)
            MessageBox(hwnd, decryptedData.c_str(), L"Read Data", MB_OK | MB_ICONINFORMATION);
        }
        else {
            inputFile.close();
            MessageBox(hwnd, L"Error: Unable to read from the file.", L"Error", MB_OK | MB_ICONERROR);
        }
    }
    else {
        MessageBox(hwnd, L"Error: Unable to open the file for reading.", L"Error", MB_OK | MB_ICONERROR);
    }
}

void ShowAboutDialog() {
    MessageBox(NULL, L"SD1 Version 1.0\nCreated by Your Name\nOrganization: VVK", L"About", MB_OK | MB_ICONINFORMATION);
}

void SetEncryptionKey(HWND hwnd) {
    wchar_t buffer[100];
    if (InputBox(hwnd, L"Enter Encryption Key", L"Key:", buffer, sizeof(buffer) / sizeof(buffer[0])) == IDOK) {
        encryptionKey = buffer;
        MessageBox(hwnd, L"Encryption key set successfully.", L"Info", MB_OK | MB_ICONINFORMATION);
    }
}

std::wstring EncryptData(const std::wstring& data, const std::wstring& key) {
    // Implement encryption logic based on your requirements
    // This is a placeholder, you should replace it with actual encryption
    return data;
}

std::wstring DecryptData(const std::wstring& encryptedData, const std::wstring& key) {
    // Implement decryption logic based on your requirements
    // This is a placeholder, you should replace it with actual decryption
    return encryptedData;
}

int InputBox(HWND hwnd, const wchar_t* title, const wchar_t* prompt, wchar_t* value, int valueSize) {
    int result = MessageBox(hwnd, prompt, title, MB_OKCANCEL | MB_ICONQUESTION);

    if (result == IDOK) {
        // Provide your implementation to get user input, for example:
        // Here, I'm using a simple edit control to simulate an input box
        HWND inputBox = CreateWindowEx(
            0, L"EDIT", L"",
            WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
            10, 10, 200, 25,
            hwnd, NULL, GetModuleHandle(NULL), NULL);

        SetWindowText(inputBox, value);

        result = MessageBox(hwnd, prompt, title, MB_OKCANCEL | MB_ICONQUESTION);

        if (result == IDOK) {
            GetWindowText(inputBox, value, valueSize);
        }

        DestroyWindow(inputBox);
    }

    return result;
}