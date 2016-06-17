#pragma once
#include <vector>

namespace Project1 
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Diagnostics;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

	enum  draw_tools
	{
		Arrow, Line, Rectangle, Ellipse, Eraser, Pencil, Grid_Square, Grid_Triangle
	};

	/// <summary>
	/// MyForm 的摘要
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();

			is_drawing = false;
			using_color = 1;
			fore_color = Color::Black;
			back_color = Color::White;

			grid_num = 8;
			default_width = default_height = 640;
			canvas = gcnew Bitmap(default_width, default_height);
			graphicer = Graphics::FromImage(canvas);
			graphicer->Clear(back_color);
			pictureBox1->Image = canvas;
			
			drawing_canvas = gcnew Bitmap(default_width, default_height);
			drawing_graphicer = Graphics::FromImage(drawing_canvas);

			pen_size = 10;

			pen = gcnew Pen(fore_color);
			pen->Width = pen_size;
			pen->StartCap = Drawing2D::LineCap::Round;
			pen->EndCap = Drawing2D::LineCap::Round;
			
			eraser = gcnew Pen(back_color);
			eraser->Width = pen_size;
			eraser->StartCap = Drawing2D::LineCap::Round;
			eraser->EndCap = Drawing2D::LineCap::Round;

			brush = gcnew SolidBrush(fore_color);
			
			save_path = gcnew String("");
			folder_path = gcnew String("");
			result_file = gcnew String("result_file.txt");
			restore_buttpn->Text = "Restore(" + (trace_images.Count).ToString() + ")";
			draw_tool = Arrow;

			search_process = gcnew Process();
		}

		static bool callback(void)
		{
			return false;
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		bool using_color;			//1->fore_color, 0->back_color
		bool is_drawing;
		Color fore_color, back_color;
		Graphics ^graphicer, ^drawing_graphicer;
		Pen ^pen, ^eraser;
		int pen_size;
		SolidBrush ^brush;
		int default_width, default_height, grid_num;
		Image ^canvas, ^drawing_canvas, ^result_image;
		int result_index;
		String ^save_path, ^folder_path, ^result_file;
		List<Image^> trace_images;
		List<String^> result_names;
		Point ^start_point, ^previous_point;
		draw_tools draw_tool;
		Process^ search_process;

		#pragma region declare componets
		System::ComponentModel::BackgroundWorker^  backgroundWorker1;
		System::Windows::Forms::ColorDialog^  colorDialog1;
		System::Windows::Forms::Panel^  panel1;
		System::Windows::Forms::MenuStrip^  main_menu;
		System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem1;
		System::Windows::Forms::ToolStripMenuItem^  save_button;
		System::Windows::Forms::ToolStripMenuItem^  load_button;
		System::Windows::Forms::ToolStripMenuItem^  save_as_button;
		System::Windows::Forms::ToolStripContainer^  toolStripContainer1;
		System::Windows::Forms::ToolStrip^  tool_menu;
		System::Windows::Forms::StatusStrip^  statusStrip1;
		System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
		System::Windows::Forms::OpenFileDialog^  openFileDialog1;
		System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog1;
		System::ComponentModel::IContainer^  components;
		System::Windows::Forms::ToolStripLabel^  toolStripLabel1;
		System::Windows::Forms::ToolStripButton^  arrow_button;
		System::Windows::Forms::ToolStripButton^  pen_button;
		System::Windows::Forms::ToolStripButton^  eraser_button;
		System::Windows::Forms::ToolStripButton^  ellipse_button;
		System::Windows::Forms::ToolStripButton^  rectangle_button;
		System::Windows::Forms::ToolStripButton^  line_button;
		System::Windows::Forms::ToolStrip^  color_menu;
		System::Windows::Forms::ToolStripButton^  fore_color_button;
		System::Windows::Forms::ToolStripButton^  back_color_button;
		System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
		System::Windows::Forms::ToolStripButton^  red_button;
		System::Windows::Forms::ToolStripButton^  orange_button;
		System::Windows::Forms::ToolStripButton^  yellow_button;
		System::Windows::Forms::ToolStripButton^  green_button;
		System::Windows::Forms::ToolStripButton^  aquamarine_button;
		System::Windows::Forms::ToolStripButton^  blue_button;
		System::Windows::Forms::ToolStripButton^  purple_button;
		System::Windows::Forms::ToolStripButton^  pink_button;
		System::Windows::Forms::ToolStripButton^  white_button;
		System::Windows::Forms::ToolStripButton^  gray_button;
		System::Windows::Forms::ToolStripButton^  brown_button;
		System::Windows::Forms::ToolStripButton^  black_button;
		System::Windows::Forms::ToolStripButton^  color_picker_button;
		System::Windows::Forms::Panel^  panel2;
		System::Windows::Forms::PictureBox^  pictureBox1;
		System::Windows::Forms::ToolStripMenuItem^  new_file_button;
		System::Windows::Forms::ToolStripSeparator^  toolStripSeparator2;
		System::Windows::Forms::ToolStripSplitButton^  pen_size_selector;
		System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem6;
		System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem7;
		System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem8;
		System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem9;
		System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem10;
		System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem11;
		System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem12;
		System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem13;
		System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem14;
		System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem15;
		System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem16;
		System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem17;
		System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem18;
		System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem19;
		System::Windows::Forms::ToolStripMenuItem^  restore_buttpn;
		System::Windows::Forms::ToolStripButton^  grid_square_button;
		System::Windows::Forms::ToolStripButton^  grid_triangle_button;
		System::Windows::Forms::ToolStripButton^  ignore_button;
		System::Windows::Forms::ToolStripSplitButton^  grid_num_selector;

		System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem3;
		System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem4;
		System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem5;
		System::Windows::Forms::ToolStripMenuItem^  set_folder_button;

		System::Windows::Forms::GroupBox^  result_box;
		System::Windows::Forms::PictureBox^  result_image_box;
private: System::Windows::Forms::Label^  result_label;

		System::Windows::Forms::Button^  next_button;
		System::Windows::Forms::Button^  previous_button;
		System::Windows::Forms::Label^  result_title;
		System::Windows::Forms::ToolStripButton^  search_button;
		System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog2;
private: System::Windows::Forms::Button^  close_button;
		 System::Windows::Forms::ToolStripStatusLabel^  status_label;

	#pragma endregion

		#pragma region Windows Form Designer generated code
			/// <summary>
			/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器
			/// 修改這個方法的內容。
			/// </summary>
			void InitializeComponent(void)
			{
				System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
				this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
				this->colorDialog1 = (gcnew System::Windows::Forms::ColorDialog());
				this->panel1 = (gcnew System::Windows::Forms::Panel());
				this->main_menu = (gcnew System::Windows::Forms::MenuStrip());
				this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->save_button = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->load_button = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->save_as_button = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->new_file_button = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->restore_buttpn = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->set_folder_button = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->toolStripContainer1 = (gcnew System::Windows::Forms::ToolStripContainer());
				this->color_menu = (gcnew System::Windows::Forms::ToolStrip());
				this->fore_color_button = (gcnew System::Windows::Forms::ToolStripButton());
				this->back_color_button = (gcnew System::Windows::Forms::ToolStripButton());
				this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
				this->red_button = (gcnew System::Windows::Forms::ToolStripButton());
				this->orange_button = (gcnew System::Windows::Forms::ToolStripButton());
				this->yellow_button = (gcnew System::Windows::Forms::ToolStripButton());
				this->green_button = (gcnew System::Windows::Forms::ToolStripButton());
				this->aquamarine_button = (gcnew System::Windows::Forms::ToolStripButton());
				this->blue_button = (gcnew System::Windows::Forms::ToolStripButton());
				this->purple_button = (gcnew System::Windows::Forms::ToolStripButton());
				this->pink_button = (gcnew System::Windows::Forms::ToolStripButton());
				this->white_button = (gcnew System::Windows::Forms::ToolStripButton());
				this->gray_button = (gcnew System::Windows::Forms::ToolStripButton());
				this->brown_button = (gcnew System::Windows::Forms::ToolStripButton());
				this->black_button = (gcnew System::Windows::Forms::ToolStripButton());
				this->ignore_button = (gcnew System::Windows::Forms::ToolStripButton());
				this->color_picker_button = (gcnew System::Windows::Forms::ToolStripButton());
				this->panel2 = (gcnew System::Windows::Forms::Panel());
				this->result_box = (gcnew System::Windows::Forms::GroupBox());
				this->close_button = (gcnew System::Windows::Forms::Button());
				this->result_title = (gcnew System::Windows::Forms::Label());
				this->result_label = (gcnew System::Windows::Forms::Label());
				this->result_image_box = (gcnew System::Windows::Forms::PictureBox());
				this->next_button = (gcnew System::Windows::Forms::Button());
				this->previous_button = (gcnew System::Windows::Forms::Button());
				this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
				this->tool_menu = (gcnew System::Windows::Forms::ToolStrip());
				this->toolStripLabel1 = (gcnew System::Windows::Forms::ToolStripLabel());
				this->arrow_button = (gcnew System::Windows::Forms::ToolStripButton());
				this->pen_button = (gcnew System::Windows::Forms::ToolStripButton());
				this->eraser_button = (gcnew System::Windows::Forms::ToolStripButton());
				this->line_button = (gcnew System::Windows::Forms::ToolStripButton());
				this->ellipse_button = (gcnew System::Windows::Forms::ToolStripButton());
				this->rectangle_button = (gcnew System::Windows::Forms::ToolStripButton());
				this->grid_square_button = (gcnew System::Windows::Forms::ToolStripButton());
				this->grid_triangle_button = (gcnew System::Windows::Forms::ToolStripButton());
				this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
				this->pen_size_selector = (gcnew System::Windows::Forms::ToolStripSplitButton());
				this->toolStripMenuItem6 = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->toolStripMenuItem7 = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->toolStripMenuItem8 = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->toolStripMenuItem9 = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->toolStripMenuItem10 = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->toolStripMenuItem11 = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->toolStripMenuItem12 = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->toolStripMenuItem13 = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->toolStripMenuItem14 = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->toolStripMenuItem15 = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->toolStripMenuItem16 = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->toolStripMenuItem17 = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->toolStripMenuItem18 = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->toolStripMenuItem19 = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->grid_num_selector = (gcnew System::Windows::Forms::ToolStripSplitButton());
				this->toolStripMenuItem3 = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->toolStripMenuItem4 = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->toolStripMenuItem5 = (gcnew System::Windows::Forms::ToolStripMenuItem());
				this->search_button = (gcnew System::Windows::Forms::ToolStripButton());
				this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
				this->status_label = (gcnew System::Windows::Forms::ToolStripStatusLabel());
				this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
				this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
				this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
				this->folderBrowserDialog2 = (gcnew System::Windows::Forms::FolderBrowserDialog());
				this->main_menu->SuspendLayout();
				this->toolStripContainer1->ContentPanel->SuspendLayout();
				this->toolStripContainer1->SuspendLayout();
				this->color_menu->SuspendLayout();
				this->panel2->SuspendLayout();
				this->result_box->SuspendLayout();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->result_image_box))->BeginInit();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
				this->tool_menu->SuspendLayout();
				this->statusStrip1->SuspendLayout();
				this->SuspendLayout();
				// 
				// panel1
				// 
				this->panel1->Location = System::Drawing::Point(210, 180);
				this->panel1->Name = L"panel1";
				this->panel1->Size = System::Drawing::Size(200, 100);
				this->panel1->TabIndex = 1;
				// 
				// main_menu
				// 
				this->main_menu->BackColor = System::Drawing::SystemColors::ActiveCaption;
				this->main_menu->Font = (gcnew System::Drawing::Font(L"Microsoft JhengHei UI", 12));
				this->main_menu->ImageScalingSize = System::Drawing::Size(20, 20);
				this->main_menu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
					this->toolStripMenuItem1,
						this->restore_buttpn, this->set_folder_button
				});
				this->main_menu->Location = System::Drawing::Point(0, 0);
				this->main_menu->Name = L"main_menu";
				this->main_menu->Size = System::Drawing::Size(1001, 33);
				this->main_menu->TabIndex = 4;
				this->main_menu->Text = L"menuStrip2";
				// 
				// toolStripMenuItem1
				// 
				this->toolStripMenuItem1->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
					this->save_button,
						this->load_button, this->save_as_button, this->new_file_button
				});
				this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
				this->toolStripMenuItem1->Size = System::Drawing::Size(56, 29);
				this->toolStripMenuItem1->Text = L"File";
				// 
				// save_button
				// 
				this->save_button->Name = L"save_button";
				this->save_button->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::S));
				this->save_button->Size = System::Drawing::Size(279, 30);
				this->save_button->Text = L"Save";
				this->save_button->Click += gcnew System::EventHandler(this, &MyForm::save_button_click);
				// 
				// load_button
				// 
				this->load_button->Name = L"load_button";
				this->load_button->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::O));
				this->load_button->Size = System::Drawing::Size(279, 30);
				this->load_button->Text = L"Load";
				this->load_button->Click += gcnew System::EventHandler(this, &MyForm::load_button_click);
				// 
				// save_as_button
				// 
				this->save_as_button->Name = L"save_as_button";
				this->save_as_button->ShortcutKeys = static_cast<System::Windows::Forms::Keys>(((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Shift)
					| System::Windows::Forms::Keys::S));
				this->save_as_button->Size = System::Drawing::Size(279, 30);
				this->save_as_button->Text = L"Save as";
				this->save_as_button->Click += gcnew System::EventHandler(this, &MyForm::save_as_button_click);
				// 
				// new_file_button
				// 
				this->new_file_button->Name = L"new_file_button";
				this->new_file_button->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::N));
				this->new_file_button->Size = System::Drawing::Size(279, 30);
				this->new_file_button->Text = L"New File";
				this->new_file_button->Click += gcnew System::EventHandler(this, &MyForm::new_file_button_click);
				// 
				// restore_buttpn
				// 
				this->restore_buttpn->Name = L"restore_buttpn";
				this->restore_buttpn->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Z));
				this->restore_buttpn->Size = System::Drawing::Size(95, 29);
				this->restore_buttpn->Text = L"Restore";
				this->restore_buttpn->Click += gcnew System::EventHandler(this, &MyForm::restore_button_click);
				// 
				// set_folder_button
				// 
				this->set_folder_button->Name = L"set_folder_button";
				this->set_folder_button->Size = System::Drawing::Size(118, 29);
				this->set_folder_button->Text = L"Set Folder";
				this->set_folder_button->Click += gcnew System::EventHandler(this, &MyForm::set_folder_button_click);
				// 
				// toolStripContainer1
				// 
				// 
				// toolStripContainer1.ContentPanel
				// 
				this->toolStripContainer1->ContentPanel->BackColor = System::Drawing::SystemColors::AppWorkspace;
				this->toolStripContainer1->ContentPanel->Controls->Add(this->color_menu);
				this->toolStripContainer1->ContentPanel->Controls->Add(this->panel2);
				this->toolStripContainer1->ContentPanel->Controls->Add(this->tool_menu);
				this->toolStripContainer1->ContentPanel->Size = System::Drawing::Size(1001, 771);
				this->toolStripContainer1->Dock = System::Windows::Forms::DockStyle::Fill;
				this->toolStripContainer1->Location = System::Drawing::Point(0, 33);
				this->toolStripContainer1->Name = L"toolStripContainer1";
				this->toolStripContainer1->Size = System::Drawing::Size(1001, 771);
				this->toolStripContainer1->TabIndex = 5;
				this->toolStripContainer1->Text = L"toolStripContainer1";
				this->toolStripContainer1->TopToolStripPanelVisible = false;
				// 
				// color_menu
				// 
				this->color_menu->ImageScalingSize = System::Drawing::Size(40, 40);
				this->color_menu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(17) {
					this->fore_color_button,
						this->back_color_button, this->toolStripSeparator1, this->red_button, this->orange_button, this->yellow_button, this->green_button,
						this->aquamarine_button, this->blue_button, this->purple_button, this->pink_button, this->white_button, this->gray_button, this->brown_button,
						this->black_button, this->ignore_button, this->color_picker_button
				});
				this->color_menu->Location = System::Drawing::Point(0, 47);
				this->color_menu->Name = L"color_menu";
				this->color_menu->Size = System::Drawing::Size(1001, 47);
				this->color_menu->TabIndex = 3;
				this->color_menu->Text = L"toolStrip2";
				// 
				// fore_color_button
				// 
				this->fore_color_button->BackColor = System::Drawing::Color::Black;
				this->fore_color_button->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->fore_color_button->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"fore_color_button.Image")));
				this->fore_color_button->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->fore_color_button->Name = L"fore_color_button";
				this->fore_color_button->Size = System::Drawing::Size(44, 44);
				this->fore_color_button->Text = L"fore_color_button";
				this->fore_color_button->Click += gcnew System::EventHandler(this, &MyForm::fore_color_button_Click);
				// 
				// back_color_button
				// 
				this->back_color_button->BackColor = System::Drawing::Color::White;
				this->back_color_button->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->back_color_button->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"back_color_button.Image")));
				this->back_color_button->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->back_color_button->Name = L"back_color_button";
				this->back_color_button->Size = System::Drawing::Size(44, 44);
				this->back_color_button->Text = L"toolStripButton1";
				this->back_color_button->ToolTipText = L"back_color_button";
				this->back_color_button->Click += gcnew System::EventHandler(this, &MyForm::back_color_button_Click_1);
				// 
				// toolStripSeparator1
				// 
				this->toolStripSeparator1->Name = L"toolStripSeparator1";
				this->toolStripSeparator1->Size = System::Drawing::Size(6, 47);
				// 
				// red_button
				// 
				this->red_button->BackColor = System::Drawing::Color::Red;
				this->red_button->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->red_button->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"red_button.Image")));
				this->red_button->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->red_button->Name = L"red_button";
				this->red_button->Size = System::Drawing::Size(44, 44);
				this->red_button->Text = L"red_button";
				this->red_button->Click += gcnew System::EventHandler(this, &MyForm::color_button_Click);
				// 
				// orange_button
				// 
				this->orange_button->BackColor = System::Drawing::Color::Orange;
				this->orange_button->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->orange_button->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"orange_button.Image")));
				this->orange_button->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->orange_button->Name = L"orange_button";
				this->orange_button->Size = System::Drawing::Size(44, 44);
				this->orange_button->Text = L"orange_button";
				this->orange_button->Click += gcnew System::EventHandler(this, &MyForm::color_button_Click);
				// 
				// yellow_button
				// 
				this->yellow_button->BackColor = System::Drawing::Color::Yellow;
				this->yellow_button->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->yellow_button->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"yellow_button.Image")));
				this->yellow_button->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->yellow_button->Name = L"yellow_button";
				this->yellow_button->Size = System::Drawing::Size(44, 44);
				this->yellow_button->Text = L"yellow_button";
				this->yellow_button->Click += gcnew System::EventHandler(this, &MyForm::color_button_Click);
				// 
				// green_button
				// 
				this->green_button->BackColor = System::Drawing::Color::Green;
				this->green_button->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->green_button->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"green_button.Image")));
				this->green_button->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->green_button->Name = L"green_button";
				this->green_button->Size = System::Drawing::Size(44, 44);
				this->green_button->Text = L"green_button";
				this->green_button->Click += gcnew System::EventHandler(this, &MyForm::color_button_Click);
				// 
				// aquamarine_button
				// 
				this->aquamarine_button->BackColor = System::Drawing::Color::Aquamarine;
				this->aquamarine_button->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->aquamarine_button->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"aquamarine_button.Image")));
				this->aquamarine_button->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->aquamarine_button->Name = L"aquamarine_button";
				this->aquamarine_button->Size = System::Drawing::Size(44, 44);
				this->aquamarine_button->Text = L"aquamarine_button";
				this->aquamarine_button->Click += gcnew System::EventHandler(this, &MyForm::color_button_Click);
				// 
				// blue_button
				// 
				this->blue_button->BackColor = System::Drawing::Color::Blue;
				this->blue_button->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->blue_button->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"blue_button.Image")));
				this->blue_button->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->blue_button->Name = L"blue_button";
				this->blue_button->Size = System::Drawing::Size(44, 44);
				this->blue_button->Text = L"blue_button";
				this->blue_button->Click += gcnew System::EventHandler(this, &MyForm::color_button_Click);
				// 
				// purple_button
				// 
				this->purple_button->BackColor = System::Drawing::Color::Purple;
				this->purple_button->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->purple_button->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"purple_button.Image")));
				this->purple_button->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->purple_button->Name = L"purple_button";
				this->purple_button->Size = System::Drawing::Size(44, 44);
				this->purple_button->Text = L"purple_button";
				this->purple_button->Click += gcnew System::EventHandler(this, &MyForm::color_button_Click);
				// 
				// pink_button
				// 
				this->pink_button->BackColor = System::Drawing::Color::Pink;
				this->pink_button->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->pink_button->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pink_button.Image")));
				this->pink_button->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->pink_button->Name = L"pink_button";
				this->pink_button->Size = System::Drawing::Size(44, 44);
				this->pink_button->Text = L"pink_button";
				this->pink_button->Click += gcnew System::EventHandler(this, &MyForm::color_button_Click);
				// 
				// white_button
				// 
				this->white_button->BackColor = System::Drawing::Color::White;
				this->white_button->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->white_button->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"white_button.Image")));
				this->white_button->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->white_button->Name = L"white_button";
				this->white_button->Size = System::Drawing::Size(44, 44);
				this->white_button->Text = L"white_button";
				this->white_button->Click += gcnew System::EventHandler(this, &MyForm::color_button_Click);
				// 
				// gray_button
				// 
				this->gray_button->BackColor = System::Drawing::Color::Gray;
				this->gray_button->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->gray_button->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"gray_button.Image")));
				this->gray_button->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->gray_button->Name = L"gray_button";
				this->gray_button->Size = System::Drawing::Size(44, 44);
				this->gray_button->Text = L"gray_button";
				this->gray_button->Click += gcnew System::EventHandler(this, &MyForm::color_button_Click);
				// 
				// brown_button
				// 
				this->brown_button->BackColor = System::Drawing::Color::Brown;
				this->brown_button->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->brown_button->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"brown_button.Image")));
				this->brown_button->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->brown_button->Name = L"brown_button";
				this->brown_button->Size = System::Drawing::Size(44, 44);
				this->brown_button->Text = L"brown_button";
				this->brown_button->Click += gcnew System::EventHandler(this, &MyForm::color_button_Click);
				// 
				// black_button
				// 
				this->black_button->BackColor = System::Drawing::Color::Black;
				this->black_button->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->black_button->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"black_button.Image")));
				this->black_button->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->black_button->Name = L"black_button";
				this->black_button->Size = System::Drawing::Size(44, 44);
				this->black_button->Text = L"black_button";
				this->black_button->Click += gcnew System::EventHandler(this, &MyForm::color_button_Click);
				// 
				// ignore_button
				// 
				this->ignore_button->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(52)),
					static_cast<System::Int32>(static_cast<System::Byte>(48)));
				this->ignore_button->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->ignore_button->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ignore_button.Image")));
				this->ignore_button->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->ignore_button->Name = L"ignore_button";
				this->ignore_button->Size = System::Drawing::Size(44, 44);
				this->ignore_button->Text = L"toolStripButton1";
				this->ignore_button->ToolTipText = L"ignore_button";
				this->ignore_button->Click += gcnew System::EventHandler(this, &MyForm::color_button_Click);
				// 
				// color_picker_button
				// 
				this->color_picker_button->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->color_picker_button->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"color_picker_button.Image")));
				this->color_picker_button->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->color_picker_button->Name = L"color_picker_button";
				this->color_picker_button->Size = System::Drawing::Size(44, 44);
				this->color_picker_button->Text = L"color_picker_button";
				this->color_picker_button->Click += gcnew System::EventHandler(this, &MyForm::color_picker_button_Click);
				// 
				// panel2
				// 
				this->panel2->AutoScroll = true;
				this->panel2->BackColor = System::Drawing::SystemColors::ControlLight;
				this->panel2->Controls->Add(this->result_box);
				this->panel2->Controls->Add(this->pictureBox1);
				this->panel2->Dock = System::Windows::Forms::DockStyle::Fill;
				this->panel2->Location = System::Drawing::Point(0, 47);
				this->panel2->Name = L"panel2";
				this->panel2->Size = System::Drawing::Size(1001, 724);
				this->panel2->TabIndex = 1;
				// 
				// result_box
				// 
				this->result_box->BackColor = System::Drawing::SystemColors::Control;
				this->result_box->Controls->Add(this->close_button);
				this->result_box->Controls->Add(this->result_title);
				this->result_box->Controls->Add(this->result_label);
				this->result_box->Controls->Add(this->result_image_box);
				this->result_box->Controls->Add(this->next_button);
				this->result_box->Controls->Add(this->previous_button);
				this->result_box->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				this->result_box->Font = (gcnew System::Drawing::Font(L"新細明體", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(136)));
				this->result_box->Location = System::Drawing::Point(668, 86);
				this->result_box->Name = L"result_box";
				this->result_box->RightToLeft = System::Windows::Forms::RightToLeft::No;
				this->result_box->Size = System::Drawing::Size(333, 350);
				this->result_box->TabIndex = 4;
				this->result_box->TabStop = false;
				this->result_box->Visible = false;
				this->result_box->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &MyForm::result_box_drag);
				// 
				// close_button
				// 
				this->close_button->Location = System::Drawing::Point(273, 6);
				this->close_button->Name = L"close_button";
				this->close_button->Size = System::Drawing::Size(54, 23);
				this->close_button->TabIndex = 6;
				this->close_button->Text = L"close";
				this->close_button->UseVisualStyleBackColor = true;
				this->close_button->Click += gcnew System::EventHandler(this, &MyForm::close_button_click);
				// 
				// result_title
				// 
				this->result_title->AutoSize = true;
				this->result_title->Font = (gcnew System::Drawing::Font(L"新細明體", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(136)));
				this->result_title->Location = System::Drawing::Point(92, 0);
				this->result_title->Name = L"result_title";
				this->result_title->Size = System::Drawing::Size(135, 24);
				this->result_title->TabIndex = 5;
				this->result_title->Text = L"Search Result";
				this->result_title->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				// 
				// result_label
				// 
				this->result_label->AutoSize = true;
				this->result_label->Location = System::Drawing::Point(6, 287);
				this->result_label->Name = L"result_label";
				this->result_label->Size = System::Drawing::Size(101, 15);
				this->result_label->TabIndex = 4;
				this->result_label->Text = L"result_file_name";
				// 
				// result_image_box
				// 
				this->result_image_box->Location = System::Drawing::Point(0, 34);
				this->result_image_box->Name = L"result_image_box";
				this->result_image_box->Size = System::Drawing::Size(333, 250);
				this->result_image_box->TabIndex = 1;
				this->result_image_box->TabStop = false;
				// 
				// next_button
				// 
				this->next_button->Location = System::Drawing::Point(252, 319);
				this->next_button->Name = L"next_button";
				this->next_button->Size = System::Drawing::Size(75, 23);
				this->next_button->TabIndex = 3;
				this->next_button->Text = L"next";
				this->next_button->UseVisualStyleBackColor = true;
				this->next_button->Click += gcnew System::EventHandler(this, &MyForm::next_button_click);
				// 
				// previous_button
				// 
				this->previous_button->Location = System::Drawing::Point(0, 319);
				this->previous_button->Name = L"previous_button";
				this->previous_button->Size = System::Drawing::Size(75, 23);
				this->previous_button->TabIndex = 2;
				this->previous_button->Text = L"previous";
				this->previous_button->UseVisualStyleBackColor = true;
				this->previous_button->Click += gcnew System::EventHandler(this, &MyForm::previous_button_click);
				// 
				// pictureBox1
				// 
				this->pictureBox1->BackColor = System::Drawing::SystemColors::Window;
				this->pictureBox1->Location = System::Drawing::Point(3, 50);
				this->pictureBox1->MaximumSize = System::Drawing::Size(1920, 1920);
				this->pictureBox1->Name = L"pictureBox1";
				this->pictureBox1->Size = System::Drawing::Size(640, 640);
				this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
				this->pictureBox1->TabIndex = 2;
				this->pictureBox1->TabStop = false;
				this->pictureBox1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::mouse_down);
				this->pictureBox1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::mouse_move);
				this->pictureBox1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::mouse_up);
				// 
				// tool_menu
				// 
				this->tool_menu->AllowDrop = true;
				this->tool_menu->BackColor = System::Drawing::SystemColors::ActiveBorder;
				this->tool_menu->ImageScalingSize = System::Drawing::Size(40, 40);
				this->tool_menu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(13) {
					this->toolStripLabel1, this->arrow_button,
						this->pen_button, this->eraser_button, this->line_button, this->ellipse_button, this->rectangle_button, this->grid_square_button,
						this->grid_triangle_button, this->toolStripSeparator2, this->pen_size_selector, this->grid_num_selector, this->search_button
				});
				this->tool_menu->Location = System::Drawing::Point(0, 0);
				this->tool_menu->Name = L"tool_menu";
				this->tool_menu->Size = System::Drawing::Size(1001, 47);
				this->tool_menu->TabIndex = 0;
				this->tool_menu->Text = L"toolStrip1";
				// 
				// toolStripLabel1
				// 
				this->toolStripLabel1->Name = L"toolStripLabel1";
				this->toolStripLabel1->Size = System::Drawing::Size(0, 44);
				// 
				// arrow_button
				// 
				this->arrow_button->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->arrow_button->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"arrow_button.Image")));
				this->arrow_button->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->arrow_button->Name = L"arrow_button";
				this->arrow_button->Size = System::Drawing::Size(44, 44);
				this->arrow_button->Text = L"arrow_button";
				this->arrow_button->Click += gcnew System::EventHandler(this, &MyForm::tool_button_Click);
				// 
				// pen_button
				// 
				this->pen_button->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->pen_button->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pen_button.Image")));
				this->pen_button->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->pen_button->Name = L"pen_button";
				this->pen_button->Size = System::Drawing::Size(44, 44);
				this->pen_button->Text = L"pen_button";
				this->pen_button->Click += gcnew System::EventHandler(this, &MyForm::tool_button_Click);
				// 
				// eraser_button
				// 
				this->eraser_button->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->eraser_button->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"eraser_button.Image")));
				this->eraser_button->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->eraser_button->Name = L"eraser_button";
				this->eraser_button->Size = System::Drawing::Size(44, 44);
				this->eraser_button->Text = L"eraser_button";
				this->eraser_button->Click += gcnew System::EventHandler(this, &MyForm::tool_button_Click);
				// 
				// line_button
				// 
				this->line_button->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->line_button->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"line_button.Image")));
				this->line_button->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->line_button->Name = L"line_button";
				this->line_button->Size = System::Drawing::Size(44, 44);
				this->line_button->Text = L"line_button";
				this->line_button->Click += gcnew System::EventHandler(this, &MyForm::tool_button_Click);
				// 
				// ellipse_button
				// 
				this->ellipse_button->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->ellipse_button->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"ellipse_button.Image")));
				this->ellipse_button->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->ellipse_button->Name = L"ellipse_button";
				this->ellipse_button->Size = System::Drawing::Size(44, 44);
				this->ellipse_button->Text = L"ellipse_button";
				this->ellipse_button->Click += gcnew System::EventHandler(this, &MyForm::tool_button_Click);
				// 
				// rectangle_button
				// 
				this->rectangle_button->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->rectangle_button->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"rectangle_button.Image")));
				this->rectangle_button->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->rectangle_button->Name = L"rectangle_button";
				this->rectangle_button->Size = System::Drawing::Size(44, 44);
				this->rectangle_button->Text = L"rectangle_button";
				this->rectangle_button->Click += gcnew System::EventHandler(this, &MyForm::tool_button_Click);
				// 
				// grid_square_button
				// 
				this->grid_square_button->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->grid_square_button->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"grid_square_button.Image")));
				this->grid_square_button->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->grid_square_button->Name = L"grid_square_button";
				this->grid_square_button->Size = System::Drawing::Size(44, 44);
				this->grid_square_button->Text = L"toolStripButton1";
				this->grid_square_button->ToolTipText = L"square_grid";
				this->grid_square_button->Click += gcnew System::EventHandler(this, &MyForm::tool_button_Click);
				// 
				// grid_triangle_button
				// 
				this->grid_triangle_button->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->grid_triangle_button->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"grid_triangle_button.Image")));
				this->grid_triangle_button->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->grid_triangle_button->Name = L"grid_triangle_button";
				this->grid_triangle_button->Size = System::Drawing::Size(44, 44);
				this->grid_triangle_button->Text = L"toolStripButton1";
				this->grid_triangle_button->ToolTipText = L"triangle_grid";
				this->grid_triangle_button->Click += gcnew System::EventHandler(this, &MyForm::tool_button_Click);
				// 
				// toolStripSeparator2
				// 
				this->toolStripSeparator2->Name = L"toolStripSeparator2";
				this->toolStripSeparator2->Size = System::Drawing::Size(6, 47);
				// 
				// pen_size_selector
				// 
				this->pen_size_selector->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->pen_size_selector->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(14) {
					this->toolStripMenuItem6,
						this->toolStripMenuItem7, this->toolStripMenuItem8, this->toolStripMenuItem9, this->toolStripMenuItem10, this->toolStripMenuItem11,
						this->toolStripMenuItem12, this->toolStripMenuItem13, this->toolStripMenuItem14, this->toolStripMenuItem15, this->toolStripMenuItem16,
						this->toolStripMenuItem17, this->toolStripMenuItem18, this->toolStripMenuItem19
				});
				this->pen_size_selector->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pen_size_selector.Image")));
				this->pen_size_selector->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->pen_size_selector->Name = L"pen_size_selector";
				this->pen_size_selector->Size = System::Drawing::Size(56, 44);
				this->pen_size_selector->Text = L"toolStripSplitButton1";
				this->pen_size_selector->ToolTipText = L"pen_size";
				// 
				// toolStripMenuItem6
				// 
				this->toolStripMenuItem6->Name = L"toolStripMenuItem6";
				this->toolStripMenuItem6->Size = System::Drawing::Size(96, 24);
				this->toolStripMenuItem6->Text = L"6";
				this->toolStripMenuItem6->Click += gcnew System::EventHandler(this, &MyForm::pen_size_select);
				// 
				// toolStripMenuItem7
				// 
				this->toolStripMenuItem7->Name = L"toolStripMenuItem7";
				this->toolStripMenuItem7->Size = System::Drawing::Size(96, 24);
				this->toolStripMenuItem7->Text = L"8";
				this->toolStripMenuItem7->Click += gcnew System::EventHandler(this, &MyForm::pen_size_select);
				// 
				// toolStripMenuItem8
				// 
				this->toolStripMenuItem8->Name = L"toolStripMenuItem8";
				this->toolStripMenuItem8->Size = System::Drawing::Size(96, 24);
				this->toolStripMenuItem8->Text = L"10";
				this->toolStripMenuItem8->Click += gcnew System::EventHandler(this, &MyForm::pen_size_select);
				// 
				// toolStripMenuItem9
				// 
				this->toolStripMenuItem9->Name = L"toolStripMenuItem9";
				this->toolStripMenuItem9->Size = System::Drawing::Size(96, 24);
				this->toolStripMenuItem9->Text = L"12";
				this->toolStripMenuItem9->Click += gcnew System::EventHandler(this, &MyForm::pen_size_select);
				// 
				// toolStripMenuItem10
				// 
				this->toolStripMenuItem10->Name = L"toolStripMenuItem10";
				this->toolStripMenuItem10->Size = System::Drawing::Size(96, 24);
				this->toolStripMenuItem10->Text = L"16";
				this->toolStripMenuItem10->Click += gcnew System::EventHandler(this, &MyForm::pen_size_select);
				// 
				// toolStripMenuItem11
				// 
				this->toolStripMenuItem11->Name = L"toolStripMenuItem11";
				this->toolStripMenuItem11->Size = System::Drawing::Size(96, 24);
				this->toolStripMenuItem11->Text = L"18";
				this->toolStripMenuItem11->Click += gcnew System::EventHandler(this, &MyForm::pen_size_select);
				// 
				// toolStripMenuItem12
				// 
				this->toolStripMenuItem12->Name = L"toolStripMenuItem12";
				this->toolStripMenuItem12->Size = System::Drawing::Size(96, 24);
				this->toolStripMenuItem12->Text = L"20";
				this->toolStripMenuItem12->Click += gcnew System::EventHandler(this, &MyForm::pen_size_select);
				// 
				// toolStripMenuItem13
				// 
				this->toolStripMenuItem13->ForeColor = System::Drawing::Color::Black;
				this->toolStripMenuItem13->Name = L"toolStripMenuItem13";
				this->toolStripMenuItem13->Size = System::Drawing::Size(96, 24);
				this->toolStripMenuItem13->Text = L"22";
				this->toolStripMenuItem13->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
				this->toolStripMenuItem13->TextImageRelation = System::Windows::Forms::TextImageRelation::TextAboveImage;
				this->toolStripMenuItem13->Click += gcnew System::EventHandler(this, &MyForm::pen_size_select);
				// 
				// toolStripMenuItem14
				// 
				this->toolStripMenuItem14->Name = L"toolStripMenuItem14";
				this->toolStripMenuItem14->Size = System::Drawing::Size(96, 24);
				this->toolStripMenuItem14->Text = L"24";
				this->toolStripMenuItem14->Click += gcnew System::EventHandler(this, &MyForm::pen_size_select);
				// 
				// toolStripMenuItem15
				// 
				this->toolStripMenuItem15->Name = L"toolStripMenuItem15";
				this->toolStripMenuItem15->Size = System::Drawing::Size(96, 24);
				this->toolStripMenuItem15->Text = L"30";
				this->toolStripMenuItem15->Click += gcnew System::EventHandler(this, &MyForm::pen_size_select);
				// 
				// toolStripMenuItem16
				// 
				this->toolStripMenuItem16->Name = L"toolStripMenuItem16";
				this->toolStripMenuItem16->Size = System::Drawing::Size(96, 24);
				this->toolStripMenuItem16->Text = L"36";
				this->toolStripMenuItem16->Click += gcnew System::EventHandler(this, &MyForm::pen_size_select);
				// 
				// toolStripMenuItem17
				// 
				this->toolStripMenuItem17->Name = L"toolStripMenuItem17";
				this->toolStripMenuItem17->Size = System::Drawing::Size(96, 24);
				this->toolStripMenuItem17->Text = L"48";
				this->toolStripMenuItem17->Click += gcnew System::EventHandler(this, &MyForm::pen_size_select);
				// 
				// toolStripMenuItem18
				// 
				this->toolStripMenuItem18->Name = L"toolStripMenuItem18";
				this->toolStripMenuItem18->Size = System::Drawing::Size(96, 24);
				this->toolStripMenuItem18->Text = L"60";
				this->toolStripMenuItem18->Click += gcnew System::EventHandler(this, &MyForm::pen_size_select);
				// 
				// toolStripMenuItem19
				// 
				this->toolStripMenuItem19->Name = L"toolStripMenuItem19";
				this->toolStripMenuItem19->Size = System::Drawing::Size(96, 24);
				this->toolStripMenuItem19->Text = L"72";
				this->toolStripMenuItem19->Click += gcnew System::EventHandler(this, &MyForm::pen_size_select);
				// 
				// grid_num_selector
				// 
				this->grid_num_selector->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
				this->grid_num_selector->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
					this->toolStripMenuItem3,
						this->toolStripMenuItem4, this->toolStripMenuItem5
				});
				this->grid_num_selector->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"grid_num_selector.Image")));
				this->grid_num_selector->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->grid_num_selector->Name = L"grid_num_selector";
				this->grid_num_selector->Size = System::Drawing::Size(98, 44);
				this->grid_num_selector->Text = L"Grid_Num";
				// 
				// toolStripMenuItem3
				// 
				this->toolStripMenuItem3->Name = L"toolStripMenuItem3";
				this->toolStripMenuItem3->Size = System::Drawing::Size(96, 24);
				this->toolStripMenuItem3->Text = L"8";
				this->toolStripMenuItem3->Click += gcnew System::EventHandler(this, &MyForm::grid_num_select);
				// 
				// toolStripMenuItem4
				// 
				this->toolStripMenuItem4->Name = L"toolStripMenuItem4";
				this->toolStripMenuItem4->Size = System::Drawing::Size(96, 24);
				this->toolStripMenuItem4->Text = L"16";
				this->toolStripMenuItem4->Click += gcnew System::EventHandler(this, &MyForm::grid_num_select);
				// 
				// toolStripMenuItem5
				// 
				this->toolStripMenuItem5->Name = L"toolStripMenuItem5";
				this->toolStripMenuItem5->Size = System::Drawing::Size(96, 24);
				this->toolStripMenuItem5->Text = L"32";
				this->toolStripMenuItem5->Click += gcnew System::EventHandler(this, &MyForm::grid_num_select);
				// 
				// search_button
				// 
				this->search_button->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
				this->search_button->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"search_button.Image")));
				this->search_button->ImageTransparentColor = System::Drawing::Color::Magenta;
				this->search_button->Name = L"search_button";
				this->search_button->Size = System::Drawing::Size(44, 44);
				this->search_button->Text = L"search_button";
				this->search_button->Click += gcnew System::EventHandler(this, &MyForm::search_button_click);
				// 
				// statusStrip1
				// 
				this->statusStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
				this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->status_label });
				this->statusStrip1->Location = System::Drawing::Point(0, 804);
				this->statusStrip1->Name = L"statusStrip1";
				this->statusStrip1->Size = System::Drawing::Size(1001, 22);
				this->statusStrip1->TabIndex = 3;
				this->statusStrip1->Text = L"statusStrip1";
				// 
				// status_label
				// 
				this->status_label->Name = L"status_label";
				this->status_label->Size = System::Drawing::Size(0, 17);
				// 
				// openFileDialog1
				// 
				this->openFileDialog1->FileName = L"openFileDialog1";
				// 
				// MyForm
				// 
				this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				this->BackColor = System::Drawing::SystemColors::ActiveBorder;
				this->ClientSize = System::Drawing::Size(1001, 826);
				this->Controls->Add(this->toolStripContainer1);
				this->Controls->Add(this->statusStrip1);
				this->Controls->Add(this->panel1);
				this->Controls->Add(this->main_menu);
				this->Name = L"MyForm";
				this->Text = L"Painter";
				this->main_menu->ResumeLayout(false);
				this->main_menu->PerformLayout();
				this->toolStripContainer1->ContentPanel->ResumeLayout(false);
				this->toolStripContainer1->ContentPanel->PerformLayout();
				this->toolStripContainer1->ResumeLayout(false);
				this->toolStripContainer1->PerformLayout();
				this->color_menu->ResumeLayout(false);
				this->color_menu->PerformLayout();
				this->panel2->ResumeLayout(false);
				this->panel2->PerformLayout();
				this->result_box->ResumeLayout(false);
				this->result_box->PerformLayout();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->result_image_box))->EndInit();
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
				this->tool_menu->ResumeLayout(false);
				this->tool_menu->PerformLayout();
				this->statusStrip1->ResumeLayout(false);
				this->statusStrip1->PerformLayout();
				this->ResumeLayout(false);
				this->PerformLayout();

			}
	#pragma endregion
		
		Void save_button_click(Object^  sender, EventArgs^  e);
		Void load_button_click(Object^  sender, EventArgs^  e);
		Void save_as_button_click(Object^  sender, EventArgs^  e);
		Void new_file_button_click(Object^ sender, EventArgs^ e);
		Void fore_color_button_Click(Object^  sender, EventArgs^  e);
		Void back_color_button_Click_1(Object^  sender, EventArgs^  e);
		Void color_button_Click(Object^  sender, EventArgs^  e);
		Void color_picker_button_Click(Object^  sender, EventArgs^  e);
		Void tool_button_Click(Object^  sender, EventArgs^  e);
		Void mouse_down(Object^ sender, MouseEventArgs^ e);
		Void mouse_move(Object^ sender, MouseEventArgs^ e);
		Void mouse_up(Object^ sender, MouseEventArgs^ e);
		Void pen_size_select(Object^ sender, EventArgs^ e);
		Void restore_button_click(Object^ sender, EventArgs^ e);
		Void grid_num_select(Object^ sender, EventArgs^ e);
		Void set_folder_button_click(Object^ sender, EventArgs^ e);
		Void search_button_click(Object^ sender, EventArgs^ e);
		Void previous_button_click(Object^ sender, EventArgs^ e);
		Void next_button_click(Object^ sender, EventArgs^ e);
		Void close_button_click(Object^ sender, EventArgs^ e);
		Void result_box_drag(Object^ sender, DragEventArgs^  e);
};
}
