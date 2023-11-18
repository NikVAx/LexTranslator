#pragma once

#include "../LEXER/lexer.cpp"

#include <msclr/marshal_cppstd.h>

#include <string>
#include <sstream>

LexAnalizer::Lexer lexer;

namespace GUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form {
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TabControl^ Tabs;
	protected:
	private: System::Windows::Forms::TabPage^ PageSource;
	private: System::Windows::Forms::TextBox^ SourceCodeTxt;

	private: System::Windows::Forms::TextBox^ SourceFileTxt;


	private: System::Windows::Forms::TabPage^ PageLab1;
	private: System::Windows::Forms::Button^ ExecuteBtn;

	private: System::Windows::Forms::Button^ ClearSourceBtn;


	private: System::Windows::Forms::Button^ FileBtn;
	private: System::Windows::Forms::DataGridView^ TokensTable;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Index;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Token;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ TokenType;






	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->Tabs = (gcnew System::Windows::Forms::TabControl());
			this->PageSource = (gcnew System::Windows::Forms::TabPage());
			this->ExecuteBtn = (gcnew System::Windows::Forms::Button());
			this->ClearSourceBtn = (gcnew System::Windows::Forms::Button());
			this->FileBtn = (gcnew System::Windows::Forms::Button());
			this->SourceCodeTxt = (gcnew System::Windows::Forms::TextBox());
			this->SourceFileTxt = (gcnew System::Windows::Forms::TextBox());
			this->PageLab1 = (gcnew System::Windows::Forms::TabPage());
			this->TokensTable = (gcnew System::Windows::Forms::DataGridView());
			this->Index = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Token = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->TokenType = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Tabs->SuspendLayout();
			this->PageSource->SuspendLayout();
			this->PageLab1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TokensTable))->BeginInit();
			this->SuspendLayout();
			// 
			// Tabs
			// 
			this->Tabs->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->Tabs->Controls->Add(this->PageSource);
			this->Tabs->Controls->Add(this->PageLab1);
			this->Tabs->Location = System::Drawing::Point(22, 22);
			this->Tabs->Margin = System::Windows::Forms::Padding(6, 7, 6, 7);
			this->Tabs->Name = L"Tabs";
			this->Tabs->SelectedIndex = 0;
			this->Tabs->Size = System::Drawing::Size(824, 530);
			this->Tabs->TabIndex = 0;
			// 
			// PageSource
			// 
			this->PageSource->BackColor = System::Drawing::Color::LightGray;
			this->PageSource->Controls->Add(this->ExecuteBtn);
			this->PageSource->Controls->Add(this->ClearSourceBtn);
			this->PageSource->Controls->Add(this->FileBtn);
			this->PageSource->Controls->Add(this->SourceCodeTxt);
			this->PageSource->Controls->Add(this->SourceFileTxt);
			this->PageSource->Location = System::Drawing::Point(4, 34);
			this->PageSource->Margin = System::Windows::Forms::Padding(6, 7, 6, 7);
			this->PageSource->Name = L"PageSource";
			this->PageSource->Padding = System::Windows::Forms::Padding(6, 7, 6, 7);
			this->PageSource->Size = System::Drawing::Size(816, 492);
			this->PageSource->TabIndex = 0;
			this->PageSource->Text = L"Исходный код";
			// 
			// ExecuteBtn
			// 
			this->ExecuteBtn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->ExecuteBtn->Location = System::Drawing::Point(679, 13);
			this->ExecuteBtn->Margin = System::Windows::Forms::Padding(6, 7, 6, 7);
			this->ExecuteBtn->Name = L"ExecuteBtn";
			this->ExecuteBtn->Size = System::Drawing::Size(124, 33);
			this->ExecuteBtn->TabIndex = 4;
			this->ExecuteBtn->Text = L"Запустить";
			this->ExecuteBtn->UseVisualStyleBackColor = true;
			this->ExecuteBtn->Click += gcnew System::EventHandler(this, &MainForm::ExecuteBtn_Click);
			// 
			// ClearSourceBtn
			// 
			this->ClearSourceBtn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->ClearSourceBtn->Location = System::Drawing::Point(543, 13);
			this->ClearSourceBtn->Margin = System::Windows::Forms::Padding(6, 7, 6, 7);
			this->ClearSourceBtn->Name = L"ClearSourceBtn";
			this->ClearSourceBtn->Size = System::Drawing::Size(124, 33);
			this->ClearSourceBtn->TabIndex = 3;
			this->ClearSourceBtn->Text = L"Очистить";
			this->ClearSourceBtn->UseVisualStyleBackColor = true;
			this->ClearSourceBtn->Click += gcnew System::EventHandler(this, &MainForm::ClearSourceBtn_Click);
			// 
			// FileBtn
			// 
			this->FileBtn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->FileBtn->Location = System::Drawing::Point(407, 13);
			this->FileBtn->Margin = System::Windows::Forms::Padding(6, 7, 6, 7);
			this->FileBtn->Name = L"FileBtn";
			this->FileBtn->Size = System::Drawing::Size(124, 33);
			this->FileBtn->TabIndex = 2;
			this->FileBtn->Text = L"Файл";
			this->FileBtn->UseVisualStyleBackColor = true;
			this->FileBtn->Click += gcnew System::EventHandler(this, &MainForm::FileBtn_Click);
			// 
			// SourceCodeTxt
			// 
			this->SourceCodeTxt->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->SourceCodeTxt->Font = (gcnew System::Drawing::Font(L"Courier New", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->SourceCodeTxt->Location = System::Drawing::Point(12, 58);
			this->SourceCodeTxt->Margin = System::Windows::Forms::Padding(6, 7, 6, 7);
			this->SourceCodeTxt->Multiline = true;
			this->SourceCodeTxt->Name = L"SourceCodeTxt";
			this->SourceCodeTxt->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->SourceCodeTxt->Size = System::Drawing::Size(790, 421);
			this->SourceCodeTxt->TabIndex = 1;
			this->SourceCodeTxt->WordWrap = false;
			// 
			// SourceFileTxt
			// 
			this->SourceFileTxt->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->SourceFileTxt->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->SourceFileTxt->Location = System::Drawing::Point(12, 13);
			this->SourceFileTxt->Margin = System::Windows::Forms::Padding(6, 7, 6, 7);
			this->SourceFileTxt->Name = L"SourceFileTxt";
			this->SourceFileTxt->ReadOnly = true;
			this->SourceFileTxt->Size = System::Drawing::Size(384, 35);
			this->SourceFileTxt->TabIndex = 0;
			// 
			// PageLab1
			// 
			this->PageLab1->Controls->Add(this->TokensTable);
			this->PageLab1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->PageLab1->Location = System::Drawing::Point(4, 34);
			this->PageLab1->Margin = System::Windows::Forms::Padding(6, 7, 6, 7);
			this->PageLab1->Name = L"PageLab1";
			this->PageLab1->Padding = System::Windows::Forms::Padding(6, 7, 6, 7);
			this->PageLab1->Size = System::Drawing::Size(816, 492);
			this->PageLab1->TabIndex = 1;
			this->PageLab1->Text = L"Таблица лексем";
			this->PageLab1->UseVisualStyleBackColor = true;
			// 
			// TokensTable
			// 
			this->TokensTable->AllowUserToAddRows = false;
			this->TokensTable->AllowUserToDeleteRows = false;
			this->TokensTable->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->TokensTable->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->TokensTable->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->TokensTable->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {
				this->Index, this->Token,
					this->TokenType
			});
			this->TokensTable->Location = System::Drawing::Point(10, 9);
			this->TokensTable->Name = L"TokensTable";
			this->TokensTable->Size = System::Drawing::Size(798, 467);
			this->TokensTable->TabIndex = 0;
			// 
			// Index
			// 
			this->Index->FillWeight = 10;
			this->Index->HeaderText = L"№";
			this->Index->Name = L"Index";
			this->Index->ReadOnly = true;
			// 
			// Token
			// 
			this->Token->HeaderText = L"Лексема";
			this->Token->Name = L"Token";
			this->Token->ReadOnly = true;
			// 
			// TokenType
			// 
			this->TokenType->HeaderText = L"Тип лексемы";
			this->TokenType->Name = L"TokenType";
			this->TokenType->ReadOnly = true;
			this->TokenType->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(11, 25);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::LightGray;
			this->ClientSize = System::Drawing::Size(868, 576);
			this->Controls->Add(this->Tabs);
			this->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Margin = System::Windows::Forms::Padding(6, 7, 6, 7);
			this->Name = L"MainForm";
			this->Text = L"ИС-42. Василенко Н.А. Вариант №5";
			this->Tabs->ResumeLayout(false);
			this->PageSource->ResumeLayout(false);
			this->PageSource->PerformLayout();
			this->PageLab1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TokensTable))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void FileBtn_Click(System::Object^ sender, System::EventArgs^ e) {
		OpenFileDialog openFileDialog;
		openFileDialog.DefaultExt = "sсv5";
		openFileDialog.Filter = "Файлы кода (*.scv5)|*.scv5";
		openFileDialog.ShowDialog();

		System::String^ fileName = openFileDialog.FileName;

		if (!System::String::IsNullOrWhiteSpace(fileName)) {
			SourceFileTxt->Text = fileName;
			System::String^ sourceCode = System::IO::File::ReadAllText(fileName);
			SourceCodeTxt->Text = sourceCode;
		}
		else {
			MessageBox::Show(this, "Выбор файла был отменен!", "Сообщение");
		}
	}

	private: System::Void ClearSourceBtn_Click(System::Object^ sender, System::EventArgs^ e) {	
		SourceFileTxt->Clear();
		SourceCodeTxt->Clear();
		TokensTable->Rows->Clear();
	}

	private: System::Void ExecuteBtn_Click(System::Object^ sender, System::EventArgs^ e) {
		if (String::IsNullOrWhiteSpace(SourceCodeTxt->Text)) {
			MessageBox::Show(this, "Нет данных для распознавания!", "Сообщение");
			return;
		}

		std::string unmanaged = msclr::interop::marshal_as<std::string>(SourceCodeTxt->Text);

		LexAnalizer::ParseResult result = lexer.parse(unmanaged);

		TokensTable->Rows->Clear();

		if (result.success()) {
			for (int i = 0; i < result.tokens.size(); ++i) {
				String^ tokenString = gcnew String(result.tokens[i].value.c_str());
				String^ typeNameString = gcnew String(result.tokens[i].typeName.c_str());

				TokensTable->Rows->Add(System::Int32(i + 1), tokenString, typeNameString);
			}

			MessageBox::Show(this, "Анализ текста выполнен успешно!", "Сообщение");
		}
		else {
			std::stringstream ss;
			char inputChar = unmanaged[result.current.index];
			ss  << "Встречена ошибка на этапе \"Лексический анализ\":\n\n"
				<< "В строке: " << result.current.row << "; столбце: " << result.current.column << ";\n"
				<< "Входной симол \'" << inputChar << " \'(ascii:" << (int)inputChar << ")\n\n"
				<< "Сообщение: " << result.message() << ".";

			String^ message = gcnew String(ss.str().c_str());

			MessageBox::Show(message);
		}
	}
	};
}
