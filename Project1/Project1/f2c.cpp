
namespace fToC
{

	System::Double converFtoC(double temp)
	{
		return ((temp - 32.0) / 9.0)*5.0;
	}

	System::Double convertCtoF(double temp)
	{
		return (temp / 5.0)*9.0 + 32.0;
	}
}

#include "MyForm.h"
using namespace System;
using namespace System::Windows::Forms;
[STAThread]

void main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Project1::MyForm form;
	Application::Run(%form);

}

