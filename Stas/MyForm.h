#pragma once
#include<iostream>
#include <msclr/marshal_cppstd.h>
#include <vcclr.h>
#include <Windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <cstring>
#include <sstream>
#include <string>
#include <cmath>
#include <fstream>
#include <msclr/marshal_cppstd.h>
#include<map>
//#include <WinSock2.h>
#define BUF_SIZE 256 
#pragma comment(lib, "ws2_32.lib")

const int PORT = 12345;
const char* SERVER_IP = "192.168.56.1";
std::string name = "Stas";
const char* id = "5";
char* carentIdToSend = "0";

namespace Stas {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace msclr::interop;
	using namespace System::Collections::Generic;
	int startPane = 0;
	std::map<int, std::string> chats;
	std::map<int, std::vector<std::string>> timeChats;
	char* TCHARToChar(const TCHAR* tcharString)
	{

		int length = _tcslen(tcharString) + 1;
		int size = _tcslen(tcharString) * sizeof(char) + 1;

		char* charString = (char*)malloc(size);

#ifdef UNICODE
		wcstombs_s(nullptr, charString, size, tcharString, length);
#else
		strcpy_s(charString, size, tcharString);
#endif

		return charString;
	}



	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{

	private:List<TextBox^>^ items;
	private:List<Label^>^ itemsL;

	private: System::Windows::Forms::Timer^ timer2;
	private: System::Windows::Forms::ComboBox^ comboBox1;
	private: System::Windows::Forms::Button^ button4;
	private:int sizeItems;
	public:
		MyForm(void)
		{
			InitializeComponent();
			items = gcnew List<TextBox^>();
			itemsL = gcnew List<Label^>();
			sizeItems = 0;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Timer^ timer1;


	private: System::Windows::Forms::Panel^ panel1;


	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->timer2 = (gcnew System::Windows::Forms::Timer(this->components));
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(531, 439);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Send";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(25, 439);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(500, 22);
			this->textBox2->TabIndex = 2;
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Interval = 1000;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::OnTimerTick);
			// 
			// panel1
			// 
			this->panel1->AutoScroll = true;
			this->panel1->BackColor = System::Drawing::SystemColors::Control;
			this->panel1->Location = System::Drawing::Point(25, 58);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(500, 370);
			this->panel1->TabIndex = 5;
			// 
			// timer2
			// 
			this->timer2->Enabled = true;
			this->timer2->Interval = 10000;
			this->timer2->Tick += gcnew System::EventHandler(this, &MyForm::timer2_Tick);
			// 
			// comboBox1
			// 
			this->comboBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(6) {
				L"Olia(1)", L"Vlad(9)", L"Nazar(3)", L"KatiaH(6)",
					L"KatiaV(8)", L"Group(0)"
			});
			this->comboBox1->Location = System::Drawing::Point(25, 6);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(226, 39);
			this->comboBox1->TabIndex = 7;
			this->comboBox1->Text = L"Group(0)";
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(0, 0);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(75, 23);
			this->button4->TabIndex = 0;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Control;
			this->ClientSize = System::Drawing::Size(634, 500);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"Stas";
			this->ResumeLayout(false);
			this->PerformLayout();
			timeChats[1] = {};
			timeChats[3] = {};
			timeChats[5] = {};
			timeChats[6] = {};
			timeChats[8] = {};
			timeChats[9] = {};
			timeChats[0] = {};
			this->comboBox1->SelectedIndexChanged += gcnew EventHandler(this, &MyForm::OnComboBoxSelectedIndexChanged);
			this->textBox2->KeyPress += gcnew KeyPressEventHandler(this, &MyForm::MyForm_KeyPress);
		}
#pragma endregion
	private: void sendMessage(const char* message) {
		WSADATA wsaData;
		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
			std::cerr << "Failed to initialize Winsock." << std::endl;
			return;
		}

		SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
		if (clientSocket == INVALID_SOCKET) {
			std::cerr << "Failed to create socket. Error code: " << WSAGetLastError() << std::endl;
			WSACleanup();
			return;
		}
		
		/*chats[5] = "";
			chats[1] = "";
			chats[6] = "";
			chats[3] = "";
			chats[8] = "";
			chats[9] = "";
			chats[0] = "";
			this->comboBox1->SelectedIndexChanged += gcnew EventHandler(this, &MyForm::OnComboBoxSelectedIndexChanged);
			this->textBox2->KeyPress += gcnew KeyPressEventHandler(this, &MyForm::MyForm_KeyPress);
			*/
		sockaddr_in serverAddr;
		serverAddr.sin_family = AF_INET;
		serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
		serverAddr.sin_port = htons(PORT);

		if (connect(clientSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR) {
			std::cerr << "Failed to connect to server. Error code: " << WSAGetLastError() << std::endl;
			closesocket(clientSocket);
			WSACleanup();
			return;
		}

		send(clientSocket, message, strlen(message), 0);

		closesocket(clientSocket);
		WSACleanup();
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		std::string idS = id;
		std::string idToSendS = carentIdToSend;
		if (!String::IsNullOrEmpty(textBox2->Text)) {
			std::string s = "_send " + idS + " " + idToSendS + " " + name + ": " + marshal_as<std::string>(textBox2->Text) + "\n";
			std::cout << s << std::endl;
			textBox2->Text = "";
			sendMessage(s.c_str());
		}
	}

	private: System::Void OnTimerTick(System::Object^ sender, System::EventArgs^ e) {
		requestMessages();
	}
	private:void requestMessages() {
		WSADATA wsaData;
		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
			std::cerr << "Failed to initialize Winsock." << std::endl;
			return;
		}

		SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
		if (clientSocket == INVALID_SOCKET) {
			std::cerr << "Failed to create socket. Error code: " << WSAGetLastError() << std::endl;
			WSACleanup();
			return;
		}

		sockaddr_in serverAddr;
		serverAddr.sin_family = AF_INET;
		serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
		serverAddr.sin_port = htons(PORT);

		if (connect(clientSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR) {
			std::cerr << "Failed to connect to server. Error code: " << WSAGetLastError() << std::endl;
			closesocket(clientSocket);
			WSACleanup();
			return;
		}

		const char* request1 = "get_messages ";
		char* request = new char[strlen(request1) + strlen(id) + strlen(carentIdToSend) + 2];
		strcpy(request, request1);
		strcat(request, id);
		strcat(request, " ");
		strcat(request, carentIdToSend);
		send(clientSocket, request, strlen(request), 0);

		char buffer[100];
		int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
		if (bytesReceived > 0) {
			std::string str(buffer);
			std::vector<std::string> lines1;

			// Шукати позначення нового рядка
			size_t pos = 0;
			while ((pos = str.find('\n')) != std::string::npos) {
				// Додаємо підстроку до вектору
				lines1.push_back(str.substr(0, pos));
				// Видаляємо оброблену частину з рядка
				str.erase(0, pos + 1);
			}

			// Додаємо останній рядок, який може залишитися у рядку s
			lines1.push_back(str);

			String^ s = msclr::interop::marshal_as<String^>(buffer);


			s = s->Replace("\n", Environment::NewLine);
			chats[atoi(carentIdToSend)] += msclr::interop::marshal_as<std::string>(s);
			std::vector<std::string> times = timeChats[atoi(carentIdToSend)];
			//textBox1->Text += s;

			array<String^>^ lines = s->Split(Environment::NewLine->ToCharArray(), StringSplitOptions::None);


			for (const auto& line1 : lines1) {
				String^ line = msclr::interop::marshal_as<String^>(line1);
				int spaceIndex = line->IndexOf(L' ');
				//std::cout << msclr::interop::marshal_as<std::string>(line1) << std::endl;
				if (spaceIndex < 0) {
					break;
				}
				String^ labelText = line->Substring(0, spaceIndex);
				String^ textBoxText = line->Substring(spaceIndex + 1);
				if (spaceIndex < 0 || String::IsNullOrWhiteSpace(textBoxText)) {
					continue;
				}
				int q = 25 * panel1->Controls->Count / 3;
				if (q > panel1->Height) {
					q = panel1->Height;

				}
				Label^ newLabel = gcnew Label();
				newLabel->Text = labelText;
				newLabel->Location = Drawing::Point(20, q + 5);
				newLabel->Size = Drawing::Size(50, 20);
				panel1->Controls->Add(newLabel);

				TextBox^ newTextBox = gcnew TextBox();
				newTextBox->Text = textBoxText;
				int textWidth = TextRenderer::MeasureText(newTextBox->Text, newTextBox->Font).Width;
				newTextBox->Location = Drawing::Point(70, q);
				newTextBox->ReadOnly = true;
				newTextBox->Size = Drawing::Size(textWidth + 5, 20);
				panel1->Controls->Add(newTextBox);

				Label^ newLabel1 = gcnew Label();
				DateTime currentTime = DateTime::Now;
				newLabel1->Text = currentTime.ToString("HH:mm");
				times.push_back(msclr::interop::marshal_as<std::string>(currentTime.ToString("HH:mm")));
				timeChats[atoi(carentIdToSend)] = times;
				newLabel1->Location = Drawing::Point(20 + textWidth + 5 + 50, q + 10);
				newLabel1->Size = Drawing::Size(50, 10);
				newLabel1->Font = gcnew Drawing::Font(newLabel1->Font->FontFamily, 6, newLabel1->Font->Style);

				panel1->Controls->Add(newLabel1);




				q += 30;
				panel1->VerticalScroll->Value = panel1->VerticalScroll->Maximum;
			}
			/*for each (String ^ line in lines)
			{
				int spaceIndex = line->IndexOf(L' ');
				std::cout << msclr::interop::marshal_as<std::string>(line) << std::endl;
				if (spaceIndex < 0) {
					break;
				}
				String^ labelText = line->Substring(0, spaceIndex);
				String^ textBoxText = line->Substring(spaceIndex + 1);
				int q = 25 * panel1->Controls->Count / 3;
				if (q > panel1->Height) {
					q = panel1->Height;

				}
				Label^ newLabel = gcnew Label();
				newLabel->Text = labelText;
				newLabel->Location = Drawing::Point(20, q + 5);
				newLabel->Size = Drawing::Size(50, 20);
				panel1->Controls->Add(newLabel);

				TextBox^ newTextBox = gcnew TextBox();
				newTextBox->Text = textBoxText;
				int textWidth = TextRenderer::MeasureText(newTextBox->Text, newTextBox->Font).Width;
				newTextBox->Location = Drawing::Point(70, q);
				newTextBox->ReadOnly = true;
				newTextBox->Size = Drawing::Size(textWidth + 5, 20);
				panel1->Controls->Add(newTextBox);

				Label^ newLabel1 = gcnew Label();
				DateTime currentTime = DateTime::Now;
				newLabel1->Text = currentTime.ToString("HH:mm");
				times.push_back(msclr::interop::marshal_as<std::string>(currentTime.ToString("HH:mm")));
				timeChats[atoi(carentIdToSend)] = times;
				newLabel1->Location = Drawing::Point(20 + textWidth + 5 + 50, q + 10);
				newLabel1->Size = Drawing::Size(50, 10);
				newLabel1->Font = gcnew Drawing::Font(newLabel1->Font->FontFamily, 6, newLabel1->Font->Style);

				panel1->Controls->Add(newLabel1);




				q += 30;
				panel1->VerticalScroll->Value = panel1->VerticalScroll->Maximum;
			}		*/

		}
		closesocket(clientSocket);
		WSACleanup();
	}


private: System::Void timer2_Tick(System::Object^ sender, System::EventArgs^ e) {
}
	   void DeleteTextBoxes() {
		   for (int i = panel1->Controls->Count - 1; i >= 0; --i)
		   {
			   panel1->Controls->RemoveAt(i);
		   }
	   }
	   void OnComboBoxSelectedIndexChanged(Object^ sender, EventArgs^ e)
	   {
		   ComboBox^ comboBox = dynamic_cast<ComboBox^>(sender);
		   String^ selectedValue = safe_cast<String^>(comboBox->SelectedItem);
		   std::string str = msclr::interop::marshal_as<std::string>(selectedValue);
		   char lastChar = str[str.size() - 2];
		   std::string newString(1, lastChar);

		   carentIdToSend = new char[newString.size() + 1];
		   for (int i = 0; i < newString.size(); i++) {
			   carentIdToSend[i] = newString[i];
		   }
		   carentIdToSend[newString.size()] = '\0';

		  // textBox1->Text = msclr::interop::marshal_as<System::String^>(chats[atoi(carentIdToSend)]);


		   DeleteTextBoxes();

		   String^ s = msclr::interop::marshal_as<System::String^>(chats[atoi(carentIdToSend)]);
		   s = s->Replace("\n", Environment::NewLine);
		   array<String^>^ lines = s->Split(Environment::NewLine->ToCharArray(), StringSplitOptions::None);
		   std::vector<std::string> times = timeChats[atoi(carentIdToSend)];
		   int i = 0;
		   for each (String ^ line in lines)
		   {
			   std::cout << msclr::interop::marshal_as<std::string>(line) << std::endl;
			   int spaceIndex = line->IndexOf(L' ');

			   if (spaceIndex < 0 || String::IsNullOrWhiteSpace(line)) {
				   continue;
			   }
			   std::cout << panel1->Controls->Count << std::endl;
			   String^ labelText = line->Substring(0, spaceIndex);
			   String^ textBoxText = line->Substring(spaceIndex + 1);
			   if (spaceIndex < 0 || String::IsNullOrWhiteSpace(textBoxText)) {
				   continue;
			   }
			   int q = 25 * panel1->Controls->Count / 3;
			   if (q > panel1->Height) {
				   q = panel1->Height;

			   }
			   Label^ newLabel = gcnew Label();
			   newLabel->Text = labelText;
			   newLabel->Location = Drawing::Point(20, q + 5);
			   newLabel->Size = Drawing::Size(50, 20);
			   panel1->Controls->Add(newLabel);
			   TextBox^ newTextBox = gcnew TextBox();
			   newTextBox->Text = textBoxText;
			   int textWidth = TextRenderer::MeasureText(newTextBox->Text, newTextBox->Font).Width;
			   newTextBox->Location = Drawing::Point(70, q);
			   newTextBox->ReadOnly = true;
			   newTextBox->Size = Drawing::Size(textWidth + 5, 20);

			   panel1->Controls->Add(newTextBox);

			   Label^ newLabel1 = gcnew Label();

			   newLabel1->Text = msclr::interop::marshal_as<System::String^>(times[i]);
			   newLabel1->Location = Drawing::Point(20 + textWidth + 5 + 50, q + 10);
			   newLabel1->Size = Drawing::Size(50, 10);
			   newLabel1->Font = gcnew Drawing::Font(newLabel1->Font->FontFamily, 6, newLabel1->Font->Style);

			   panel1->Controls->Add(newLabel1);

			   q += 30;
			   i++;
			   panel1->VerticalScroll->Value = panel1->VerticalScroll->Maximum;
		   }
	   }

private: System::Void MyForm_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
	if (e->KeyChar == (char)Keys::Enter) {
		std::string idS = id;
		std::string idToSendS = carentIdToSend;
		std::string s = "_send " + idS + " " + idToSendS + " " + name + ": " + marshal_as<std::string>(textBox2->Text) + "\n";
		std::cout << s << std::endl;
		textBox2->Text = "";
		sendMessage(s.c_str());
	}
}
};
}