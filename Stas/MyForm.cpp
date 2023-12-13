#include "MyForm.h"
#include<iostream>

using namespace System;
using namespace System::Windows::Forms;


[System::STAThread]
int main() {
	/*name = argv[1];
	n = std::stoi(argv[2]);
	if (argv[3] == "1") {
		isInGroup = true;
	}
	namesAllProcess = "";
	for (int i = 3; i < args; i++) {
		namesAllProcess += argv[i];
	}
	hSemaphore = CreateSemaphore(nullptr, n, n, L"SEMAPHORE");
	hMutex = CreateMutex(nullptr, FALSE, L"MUTEX");*/
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	Stas::MyForm form;
	Application::Run(% form);
}