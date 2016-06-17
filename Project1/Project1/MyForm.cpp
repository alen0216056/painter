#include "MyForm.h"
#include <iostream>
#include <string>

using namespace std;
using namespace Project1;

#pragma region main menu

Void MyForm::save_button_click(Object^  sender, EventArgs^  e)
{
	if (save_path == "" )
	{
		saveFileDialog1->FileName = "image.png";
		if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			save_path = saveFileDialog1->FileName;
		}
		else
		{
			MessageBox::Show("Invalid file name or path !");
		}
	}

	if (save_path != "" )
	{
		canvas->Save(save_path, Imaging::ImageFormat::Png);
	}
}

Void MyForm::load_button_click(Object^  sender, EventArgs^  e)
{
	if ( openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		canvas = Image::FromFile(openFileDialog1->FileName);
		pictureBox1->Image = canvas;
		delete graphicer;
		graphicer = Graphics::FromImage(canvas);
	}
	else
	{
		MessageBox::Show("Invalid file !");
	}
}

Void MyForm::save_as_button_click(Object^  sender, EventArgs^  e)
{
	saveFileDialog1->FileName = "image.png";
	if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		save_path = saveFileDialog1->FileName;
		canvas->Save(save_path, Imaging::ImageFormat::Png);
	}
	else
	{
		MessageBox::Show("Invalid file name or path !");
	}
}

Void MyForm::new_file_button_click(Object^ sender, EventArgs^ e)
{
	if (save_path != "")
	{
		canvas->Save(save_path, Imaging::ImageFormat::Png);
	}
	else
	{
		saveFileDialog1->FileName = "image.png";
		if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			save_path = saveFileDialog1->FileName;
			canvas->Save(save_path, Imaging::ImageFormat::Png);
		}
		else
		{
			MessageBox::Show("file not save !");
		}
	}

	fore_color = Color::Black;
	back_color = Color::White;

	delete canvas;
	delete graphicer;
	canvas = gcnew Bitmap(default_width, default_height);
	graphicer = Graphics::FromImage(canvas);
	graphicer->Clear(back_color);
	pictureBox1->Image = canvas;
	save_path = "";
}

Void MyForm::restore_button_click(Object^ sender, EventArgs^ e)
{
	if (trace_images.Count > 0)
	{
		delete canvas;
		delete graphicer;
		canvas = trace_images[trace_images.Count-1];
		trace_images.RemoveAt(trace_images.Count-1);
		graphicer = Graphics::FromImage(canvas);
		restore_buttpn->Text = "Restore(" + (trace_images.Count).ToString() + ")";
		pictureBox1->Image = canvas;
	}
}

Void MyForm::set_folder_button_click(Object^ sender, EventArgs^ e)
{
	if (folderBrowserDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		folder_path = folderBrowserDialog1->SelectedPath;
	}
	else
	{
		MessageBox::Show("Invalid directory!");
	}
}

#pragma endregion

#pragma region tool menu

Void MyForm::tool_button_Click(Object^  sender, EventArgs^  e)
{
	if (((ToolStripButton^)sender)->Name == "arrow_button")
		draw_tool = Arrow;
	else if (((ToolStripButton^)sender)->Name == "pen_button")
		draw_tool = Pencil;
	else if (((ToolStripButton^)sender)->Name == "line_button")
		draw_tool = Line;
	else if (((ToolStripButton^)sender)->Name == "ellipse_button")
		draw_tool = Ellipse;
	else if (((ToolStripButton^)sender)->Name == "rectangle_button")
		draw_tool = Rectangle;
	else if (((ToolStripButton^)sender)->Name == "eraser_button")
		draw_tool = Eraser;
	else if (((ToolStripButton^)sender)->Name == "grid_square_button")
		draw_tool = Grid_Square;
	else if (((ToolStripButton^)sender)->Name == "grid_triangle_button")
		draw_tool = Grid_Triangle;
}

Void MyForm::pen_size_select(Object^ sender, EventArgs^ e)
{
	pen_size = int::Parse(((ToolStripMenuItem^)sender)->Text);
	pen->Width = pen_size;
	eraser->Width = pen_size;
}

Void MyForm::grid_num_select(Object^ sender, EventArgs^ e)
{
	grid_num = int::Parse(((ToolStripMenuItem^)sender)->Text);
}

Void MyForm::search_button_click(Object^ sender, EventArgs^ e)
{
	if (save_path == "")
	{
		saveFileDialog1->FileName = "image.png";
		if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			save_path = saveFileDialog1->FileName;
			canvas->Save(save_path, Imaging::ImageFormat::Png);
		}
		else
		{
			MessageBox::Show("Invalid file name or path !");
			return;
		}
	}

	if (folder_path == "")
	{
		if (folderBrowserDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			folder_path = folderBrowserDialog1->SelectedPath;
		}
		else
		{
			MessageBox::Show("Invalid directory!");
			return;
		}
	}

	search_process->Start("C:\\Users\\Alen\\Desktop\\0503\\main.exe", folder_path + " " + save_path + " " + folder_path + "\\" + result_file);
	
	result_box->Visible = true;
	for (int i = 0; i < 20; i++)
	{
		result_names.Add(folder_path + "\\" + (i+61).ToString() + ".jpg");
	}
	result_index = 0;
	result_image = Image::FromFile(result_names[result_index]);
	Image::GetThumbnailImageAbort^ my_callback = gcnew Image::GetThumbnailImageAbort(MyForm::callback);
	result_image = result_image->GetThumbnailImage(result_image_box->Width, result_image_box->Height, my_callback, IntPtr::Zero);
	result_image_box->Image = result_image;
	result_label->Text = result_names[result_index];
}

#pragma endregion

#pragma region color menu

Void MyForm::fore_color_button_Click(Object^  sender, EventArgs^  e)
{
	using_color = 1;
}

Void MyForm::back_color_button_Click_1(Object^  sender, EventArgs^  e)
{
	using_color = 0;
}

Void MyForm::color_button_Click(Object^  sender, EventArgs^  e)
{
	if (using_color)
	{
		fore_color = ((ToolStripButton^)sender)->BackColor;
		fore_color_button->BackColor = fore_color;
	}
	else
	{
		back_color = ((ToolStripButton^)sender)->BackColor;
		back_color_button->BackColor = back_color;
	}
}

Void MyForm::color_picker_button_Click(Object^  sender, EventArgs^  e)
{
	
	if (colorDialog1->ShowDialog() == Windows::Forms::DialogResult::OK)
	{
		Color tmp_color = colorDialog1->Color;
		if (using_color)
		{
			fore_color = tmp_color;
			pen->Color = fore_color;
			fore_color_button->BackColor = fore_color;
		}
		else
		{
			back_color = tmp_color;
			pen->Color = back_color;
			back_color_button->BackColor = back_color;
		}
	}
	else
	{
		MessageBox::Show("not choose a color !");
	}
}

#pragma endregion

#pragma region draw

Void MyForm::mouse_down(Object^ sender, MouseEventArgs^ e)
{
	status_label->Text = "DOWN:" + (e->X).ToString() + "," + (e->Y).ToString();
	if (e->Button == System::Windows::Forms::MouseButtons::Left && draw_tool!=Arrow)
	{
		trace_images.Add((Image^)canvas->Clone());
		restore_buttpn->Text = "Restore(" + (trace_images.Count).ToString() + ")";

		if (!is_drawing)
		{
			is_drawing = true;
			pen->Color = fore_color;
			brush->Color = fore_color;
			eraser->Color = back_color;
			start_point = gcnew Point(e->X, e->Y);
			previous_point = gcnew Point(e->X, e->Y);
		}
	}
}

Void MyForm::mouse_move(Object^ sender, MouseEventArgs^ e)
{
	status_label->Text = "MOVE:" + (e->X).ToString() + "," + (e->Y).ToString();
	if (is_drawing)
	{
		int width, height, start_x, start_y;
		delete drawing_canvas;
		delete drawing_graphicer;
		drawing_canvas = (Image^)canvas->Clone();
		drawing_graphicer = Graphics::FromImage(drawing_canvas);

		switch (draw_tool)
		{
			case Pencil:
				//drawing_graphicer->DrawLine(pen, *previous_point, e->Location);
				graphicer->DrawLine(pen, *previous_point, e->Location);	
				previous_point->X = e->X;
				previous_point->Y = e->Y;
				break;
			case Eraser:
				//drawing_graphicer->DrawLine(eraser, *previous_point, e->Location);
				graphicer->DrawLine(eraser, *previous_point, e->Location);
				previous_point->X = e->X;
				previous_point->Y = e->Y;
				break;
			case Line:
				drawing_graphicer->DrawLine(pen, *start_point, e->Location);
				break;
			case Ellipse:
				start_x = (e->X > start_point->X) ? start_point->X : e->X;
				width = (e->X > start_point->X) ? e->X - start_point->X : start_point->X - e->X;
				start_y = (e->Y > start_point->Y) ? start_point->Y : e->Y;
				height = (e->Y > start_point->Y) ? e->Y - start_point->Y : start_point->Y - e->Y;
				drawing_graphicer->DrawEllipse(pen, start_x, start_y, width, height);
				drawing_graphicer->FillEllipse(brush, start_x, start_y, width, height);
				break;
			case Rectangle:
				start_x = (e->X > start_point->X) ? start_point->X : e->X;
				width = (e->X > start_point->X) ? e->X - start_point->X : start_point->X - e->X;
				start_y = (e->Y > start_point->Y) ? start_point->Y : e->Y;
				height = (e->Y > start_point->Y) ? e->Y - start_point->Y : start_point->Y - e->Y;
				drawing_graphicer->DrawRectangle(pen, start_x, start_y, width, height);
				drawing_graphicer->FillRectangle(brush, start_x, start_y, width, height);
				break;
			case Grid_Square:
				width = canvas->Width / grid_num;
				height = canvas->Height / grid_num;
				start_x = (e->X / width)*width;
				start_y = (e->Y / height)*height;
				graphicer->FillRectangle(brush, start_x, start_y, width, height);
				break;
			case Grid_Triangle:
				width = canvas->Width / grid_num;
				height = canvas->Height / grid_num;
				start_x = e->X % width;
				start_y = e->Y % height;

				array<Point> ^points;
				Array::Resize(points, 3);
				if ((e->Y / height) % 2 == 0)
				{
					if (start_x <= width / 2.0)
					{
						if (start_y <= start_x * 2)
						{
							points[0].X = (e->X / width)*width;
							points[0].Y = (e->Y / height)*height;
							points[1].X = (e->X / width + 1)*width;
							points[1].Y = (e->Y / height)*height;
							points[2].X = (e->X / width + 0.5)*width;
							points[2].Y = (e->Y / height + 1)*height;
						}
						else
						{
							points[0].X = ((e->X / width) == 0) ? 0 : (e->X / width - 0.5)*width;
							points[0].Y = (e->Y / height + 1)*height;
							points[1].X = (e->X / width)*width;
							points[1].Y = (e->Y / height)*height;
							points[2].X = (e->X / width + 0.5)*width;
							points[2].Y = (e->Y / height + 1)*height;
						}
					}
					else
					{
						if (start_y <= (width - start_x) * 2)
						{
							points[0].X = (e->X / width)*width;
							points[0].Y = (e->Y / height)*height;
							points[1].X = (e->X / width + 1)*width;
							points[1].Y = (e->Y / height)*height;
							points[2].X = (e->X / width + 0.5)*width;
							points[2].Y = (e->Y / height + 1)*height;
						}
						else
						{
							points[0].X = (e->X / width + 0.5)*width;
							points[0].Y = (e->Y / height + 1)*height;
							points[1].X = (e->X / width + 1)*width;
							points[1].Y = (e->Y / height)*height;
							points[2].X = ((e->X / width + 1) < canvas->Width / width) ? (e->X / width + 1.5)*width : (e->X / width + 1)*width;
							points[2].Y = (e->Y / height + 1)*height;
						}
					}
				}
				else
				{
					if (start_x <= width / 2.0)
					{
						if (start_y <= (width*0.5 - start_x) * 2)
						{
							points[0].X = (e->X / width == 0) ? 0 : (e->X / width - 0.5)*width;
							points[0].Y = (e->Y / height)*height;
							points[1].X = (e->X / width + 0.5)*width;
							points[1].Y = (e->Y / height)*height;
							points[2].X = (e->X / width)*width;
							points[2].Y = (e->Y / height + 1)*height;
						}
						else
						{
							points[0].X = (e->X / width)*width;
							points[0].Y = (e->Y / height + 1)*height;
							points[1].X = (e->X / width + 0.5)*width;
							points[1].Y = (e->Y / height)*height;
							points[2].X = (e->X / width + 1)*width;
							points[2].Y = (e->Y / height + 1)*height;
						}
					}
					else
					{
						if (start_y <= (start_x - width / 2.0) * 2)
						{
							points[0].X = (e->X / width + 0.5)*width;
							points[0].Y = (e->Y / height)*height;
							points[1].X = (e->X / width + 1) == (canvas->Width / width) ? (e->X / width + 1)*width : (e->X / width + 1.5)*width;
							points[1].Y = (e->Y / height)*height;
							points[2].X = (e->X / width + 1)*width;
							points[2].Y = (e->Y / height + 1)*height;
						}
						else
						{
							points[0].X = (e->X / width)*width;
							points[0].Y = (e->Y / height + 1)*height;
							points[1].X = (e->X / width + 0.5)*width;
							points[1].Y = (e->Y / height)*height;
							points[2].X = (e->X / width + 1)*width;
							points[2].Y = (e->Y / height + 1)*height;
						}
					}
				}
				graphicer->FillPolygon(brush, points);
				break;
			default :
				MessageBox::Show("draw_tool value error !");
				break;
		}
		pictureBox1->Image = drawing_canvas;
	}

}

Void MyForm::mouse_up(Object^ sender, MouseEventArgs^ e)
{
	status_label->Text = "UP:" + (e->X).ToString() + "," + (e->Y).ToString();
	if (is_drawing)
	{
		int width, height, start_x, start_y;
		switch (draw_tool)
		{
			case Pencil:
				graphicer->DrawLine(pen, *previous_point, e->Location);
				break;
			case Eraser:
				graphicer->DrawLine(eraser, *previous_point, e->Location);
				break;
			case Line:
				graphicer->DrawLine(pen, *start_point, e->Location);
				break;
			case Ellipse:
				start_x = (e->X > start_point->X) ? start_point->X : e->X;
				width = (e->X > start_point->X) ? e->X - start_point->X : start_point->X - e->X;
				start_y = (e->Y > start_point->Y) ? start_point->Y : e->Y;
				height = (e->Y > start_point->Y) ? e->Y - start_point->Y : start_point->Y - e->Y;
				graphicer->DrawEllipse(pen, start_x, start_y, width, height);
				graphicer->FillEllipse(brush, start_x, start_y, width, height);
				break;
			case Rectangle:
				start_x = (e->X > start_point->X) ? start_point->X : e->X;
				width = (e->X > start_point->X) ? e->X - start_point->X : start_point->X - e->X;
				start_y = (e->Y > start_point->Y) ? start_point->Y : e->Y;
				height = (e->Y > start_point->Y) ? e->Y - start_point->Y : start_point->Y - e->Y;
				graphicer->DrawRectangle(pen, start_x, start_y, width, height);
				graphicer->FillRectangle(brush, start_x, start_y, width, height);
				break;
			case Grid_Square:
				width = canvas->Width / grid_num;
				height = canvas->Height / grid_num;
				start_x = ((e->X) / width)*width;
				start_y = ((e->Y) / height)*height;
				graphicer->FillRectangle(brush, start_x, start_y, width, height);
				break;
			case Grid_Triangle:
				width = canvas->Width / grid_num;
				height = canvas->Height / grid_num;
				start_x = e->X % width;
				start_y = e->Y % height;

				array<Point> ^points;
				Array::Resize(points, 3);
				if ((e->Y / height) % 2 == 0)
				{
					if (start_x <= width / 2.0)
					{
						if (start_y <= start_x * 2)
						{
							points[0].X = (e->X / width)*width;
							points[0].Y = (e->Y / height)*height;
							points[1].X = (e->X / width + 1)*width;
							points[1].Y = (e->Y / height)*height;
							points[2].X = (e->X / width + 0.5)*width;
							points[2].Y = (e->Y / height + 1)*height;
						}
						else
						{
							points[0].X = ((e->X / width) == 0) ? 0 : (e->X / width - 0.5)*width;
							points[0].Y = (e->Y / height + 1)*height;
							points[1].X = (e->X / width)*width;
							points[1].Y = (e->Y / height)*height;
							points[2].X = (e->X / width + 0.5)*width;
							points[2].Y = (e->Y / height + 1)*height;
						}
					}
					else
					{
						if (start_y <= (width - start_x) * 2)
						{
							points[0].X = (e->X / width)*width;
							points[0].Y = (e->Y / height)*height;
							points[1].X = (e->X / width + 1)*width;
							points[1].Y = (e->Y / height)*height;
							points[2].X = (e->X / width + 0.5)*width;
							points[2].Y = (e->Y / height + 1)*height;
						}
						else
						{
							points[0].X = (e->X / width + 0.5)*width;
							points[0].Y = (e->Y / height + 1)*height;
							points[1].X = (e->X / width + 1)*width;
							points[1].Y = (e->Y / height)*height;
							points[2].X = ((e->X / width + 1) < canvas->Width / width) ? (e->X / width + 1.5)*width : (e->X / width + 1)*width;
							points[2].Y = (e->Y / height + 1)*height;
						}
					}
				}
				else
				{
					if (start_x <= width / 2.0)
					{
						if (start_y <= (width*0.5 - start_x) * 2)
						{
							points[0].X = (e->X / width == 0) ? 0 : (e->X / width - 0.5)*width;
							points[0].Y = (e->Y / height)*height;
							points[1].X = (e->X / width + 0.5)*width;
							points[1].Y = (e->Y / height)*height;
							points[2].X = (e->X / width)*width;
							points[2].Y = (e->Y / height + 1)*height;
						}
						else
						{
							points[0].X = (e->X / width)*width;
							points[0].Y = (e->Y / height + 1)*height;
							points[1].X = (e->X / width + 0.5)*width;
							points[1].Y = (e->Y / height)*height;
							points[2].X = (e->X / width + 1)*width;
							points[2].Y = (e->Y / height + 1)*height;
						}
					}
					else
					{
						if (start_y <= (start_x - width / 2.0) * 2)
						{
							points[0].X = (e->X / width + 0.5)*width;
							points[0].Y = (e->Y / height)*height;
							points[1].X = (e->X / width + 1) == (canvas->Width / width) ? (e->X / width + 1)*width : (e->X / width + 1.5)*width;
							points[1].Y = (e->Y / height)*height;
							points[2].X = (e->X / width + 1)*width;
							points[2].Y = (e->Y / height + 1)*height;
						}
						else
						{
							points[0].X = (e->X / width)*width;
							points[0].Y = (e->Y / height + 1)*height;
							points[1].X = (e->X / width + 0.5)*width;
							points[1].Y = (e->Y / height)*height;
							points[2].X = (e->X / width + 1)*width;
							points[2].Y = (e->Y / height + 1)*height;
						}
					}
				}
				graphicer->FillPolygon(brush, points);
				break;
			default:
				MessageBox::Show("draw_tool value error !");
				break;
		}
		is_drawing = false;
		pictureBox1->Image = canvas;
	}
}

#pragma endregion

#pragma region result

Void MyForm::previous_button_click(Object^ sender, EventArgs^ e)
{
	if (result_index > 0)
	{
		result_index--;
		delete result_image;
		result_image = Image::FromFile(result_names[result_index]);
		Image::GetThumbnailImageAbort^ my_callback = gcnew Image::GetThumbnailImageAbort(MyForm::callback);
		result_image = result_image->GetThumbnailImage(result_image_box->Width, result_image_box->Height, my_callback, IntPtr::Zero);
		result_image_box->Image = result_image;
		result_label->Text = result_names[result_index];
	}
}
Void MyForm::next_button_click(Object^ sender, EventArgs^ e)
{
	if (result_index < 19)
	{
		result_index++;
		delete result_image;
		result_image = Image::FromFile(result_names[result_index]);
		Image::GetThumbnailImageAbort^ my_callback = gcnew Image::GetThumbnailImageAbort(MyForm::callback);
		result_image = result_image->GetThumbnailImage(result_image_box->Width, result_image_box->Height, my_callback, IntPtr::Zero);
		result_image_box->Image = result_image;
		result_label->Text = result_names[result_index];
	}
}

Void MyForm::close_button_click(Object^ sender, EventArgs^ e)
{
	result_box->Visible = false;
}

Void MyForm::result_box_drag(Object^ sender, DragEventArgs^  e)
{
	result_box->Location.X = e->X;
	result_box->Location.Y = e->Y;
}

#pragma endregion