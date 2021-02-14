/***************************************************************
 * Name:      windowGenMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     (Patryk)
 * Created:   2021-02-14
 * Copyright:  ()
 * License:
 **************************************************************/

#include "windowGenMain.h"
#include <wx/msgdlg.h>

#include <fstream>
#include <string>

//(*InternalHeaders(windowGenFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

using std::ofstream;
using std::string;
using std::endl;

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(windowGenFrame)
const long windowGenFrame::ID_STATICTEXT1 = wxNewId();
const long windowGenFrame::ID_SPINCTRL1 = wxNewId();
const long windowGenFrame::ID_STATICTEXT2 = wxNewId();
const long windowGenFrame::ID_CHOICE1 = wxNewId();
const long windowGenFrame::ID_FILEPICKERCTRL1 = wxNewId();
const long windowGenFrame::ID_BUTTON1 = wxNewId();
const long windowGenFrame::ID_PANEL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(windowGenFrame,wxFrame)
    //(*EventTable(windowGenFrame)
    //*)
END_EVENT_TABLE()

windowGenFrame::windowGenFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(windowGenFrame)
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer3;
    wxBoxSizer* BoxSizer4;

    Create(parent, wxID_ANY, _("windowGen"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    Panel = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    BoxSizer2 = new wxBoxSizer(wxVERTICAL);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    StaticTextSize = new wxStaticText(Panel, ID_STATICTEXT1, _("Size"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    BoxSizer3->Add(StaticTextSize, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrlCount = new wxSpinCtrl(Panel, ID_SPINCTRL1, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 100000, 0, _T("ID_SPINCTRL1"));
    SpinCtrlCount->SetValue(_T("0"));
    BoxSizer3->Add(SpinCtrlCount, 1, wxALL|wxEXPAND, 5);
    BoxSizer2->Add(BoxSizer3, 1, wxEXPAND, 5);
    BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    StaticTextWindow = new wxStaticText(Panel, ID_STATICTEXT2, _("Window"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    BoxSizer4->Add(StaticTextWindow, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ChoiceWindow = new wxChoice(Panel, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
    ChoiceWindow->SetSelection( ChoiceWindow->Append(_("Rectangular")) );
    ChoiceWindow->Append(_("Hamming"));
    ChoiceWindow->Append(_("Hann"));
    ChoiceWindow->Append(_("Bartlett"));
    ChoiceWindow->Append(_("Bartlett-Hann"));
    ChoiceWindow->Append(_("Blackman"));
    ChoiceWindow->Append(_("Nuttall"));
    ChoiceWindow->Append(_("Blackman-Harris"));
    ChoiceWindow->Append(_("Blackman-Nuttall"));
    ChoiceWindow->Append(_("Flat top"));
    BoxSizer4->Add(ChoiceWindow, 2, wxALL|wxEXPAND, 5);
    BoxSizer2->Add(BoxSizer4, 1, wxEXPAND, 5);
    FilePickerCtrl = new wxFilePickerCtrl(Panel, ID_FILEPICKERCTRL1, wxEmptyString, wxEmptyString, _T("*.h"), wxDefaultPosition, wxDefaultSize, wxFLP_SAVE|wxFLP_USE_TEXTCTRL, wxDefaultValidator, _T("ID_FILEPICKERCTRL1"));
    BoxSizer2->Add(FilePickerCtrl, 1, wxALL|wxEXPAND, 5);
    ButtonSave = new wxButton(Panel, ID_BUTTON1, _("Save"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    BoxSizer2->Add(ButtonSave, 1, wxALL|wxEXPAND, 5);
    Panel->SetSizer(BoxSizer2);
    BoxSizer2->Fit(Panel);
    BoxSizer2->SetSizeHints(Panel);
    BoxSizer1->Add(Panel, 1, wxEXPAND, 5);
    SetSizer(BoxSizer1);
    BoxSizer1->Fit(this);
    BoxSizer1->SetSizeHints(this);

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&windowGenFrame::OnButtonSaveClick);
    //*)
}

windowGenFrame::~windowGenFrame()
{
    //(*Destroy(windowGenFrame)
    //*)
}

void windowGenFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void windowGenFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void windowGenFrame::OnButtonSaveClick(wxCommandEvent& event)
{
	int number = SpinCtrlCount->GetValue();
	float calc = 0;

	if(number > 0)
	{
		wxString filename;
		filename = FilePickerCtrl->GetPath();
		if(filename.IsEmpty())
		{
			 wxMessageDialog(NULL, ("No file chosen!"), wxT(""), wxOK | wxICON_EXCLAMATION).ShowModal();
		}
		else
		{
			 ofstream file;
			 file.open((string)filename);
			 file << "#ifndef __WINDOW__H__" << endl;
			 file << "#define __WINDOW__H__" << endl;
			 file << endl;
			 file << "const float window[" << number << "] = " << "\t\t// " << (string)ChoiceWindow->GetString(ChoiceWindow->GetCurrentSelection());
			 file << endl << "{";

			 switch(ChoiceWindow->GetCurrentSelection())
			 {
			 case 0:                                     // Rectangular
				  for(int i=0; i<number; i++)
				  {
						calc = 1;
						if((i%16) == 0) file << endl << "\t";
						file << calc;
						if((number-i) > 1)  file << ", ";
				  }
				  break;

			 case 1:                                     // Hamming
				  for(int i=0; i<number; i++)
				  {
						calc = (0.53836 - 0.46164 * (cos(2*M_PI*i/(number-1))));
						if((i%16) == 0) file << endl << "\t";
						file << calc;
						if((number-i) > 1)  file << ", ";
				  }
				  break;
			 case 2:                                     // Hann
				  for(int i=0; i<number; i++)
				  {
						calc = (0.5 * (1 - cos(2*M_PI*i/(number-1))));
						if((i%16) == 0) file << endl << "\t";
						file << calc;
						if((number-i) > 1)  file << ", ";
				  }
				  break;
			 case 3:                                     // Bartlett
				  for(int i=0; i<number; i++)
				  {
						calc = (((number-1)/2) - abs(i - ((number-1)/2)));
						if((i%16) == 0) file << endl << "\t";
						file << calc;
						if((number-i) > 1)  file << ", ";
				  }
				  break;
			 case 4:                                     // Barlett-Hann
				  for(int i=0; i<number; i++)
				  {
						calc = (0.62 - 0.48*abs((i/(number-1))-0.5) - 0.38*cos((2*M_PI*i)/(number-1)));
						if((i%16) == 0) file << endl << "\t";
						file << calc;
						if((number-i) > 1)  file << ", ";
				  }
				  break;
			 case 5:                                     // Blackmann
				  for(int i=0; i<number; i++)
				  {
						calc = (0.42 - 0.5*cos((2*M_PI*i)/(number-1)) + 0.08*cos((4*M_PI*i)/(number-1)));
						if((i%16) == 0) file << endl << "\t";
						file << calc;
						if((number-i) > 1)  file << ", ";
				  }
				  break;
			 case 6:                                     // Nuttall
				  for(int i=0; i<number; i++)
				  {
						calc = (0.355768 - 0.487396*cos((2*M_PI*i)/(number-1)) + 0.144232*cos((4*M_PI*i)/(number-1)) - 0.012604*cos((6*M_PI*i)/(number-1)));
						if((i%16) == 0) file << endl << "\t";
						file << calc;
						if((number-i) > 1)  file << ", ";
				  }
				  break;
			 case 7:                                     // Blackmann-Harris
				  for(int i=0; i<number; i++)
				  {
						calc = (0.35875 - 0.48829*cos((2*M_PI*i)/(number-1)) + 0.14128*cos((4*M_PI*i)/(number-1)) - 0.01168*cos((6*M_PI*i)/(number-1)));
						if((i%16) == 0) file << endl << "\t";
						file << calc;
						if((number-i) > 1)  file << ", ";
				  }
				  break;
			 case 8:                                     // Blackmann-Nuttall
				  for(int i=0; i<number; i++)
				  {
						calc = (0.3635819 - 0.4891775*cos((2*M_PI*i)/(number-1)) + 0.1365995*cos((4*M_PI*i)/(number-1)) - 0.0106411*cos((6*M_PI*i)/(number-1)));
						if((i%16) == 0) file << endl << "\t";
						file << calc;
						if((number-i) > 1)  file << ", ";
				  }
				  break;
			 case 9:                                     // Flat-Top
				  for(int i=0; i<number; i++)
				  {
						calc = (1 - 1.93*cos((2*M_PI*i)/(number-1)) + 1.29*cos((4*M_PI*i)/(number-1)) - 0.388*cos((6*M_PI*i)/(number-1)) + 0.028*cos((8*M_PI*i)/(number-1)));
						if((i%16) == 0) file << endl << "\t";
						file << calc;
						if((number-i) > 1)  file << ", ";
				  }
				  break;
			 }

			 file << endl << "};" << endl << endl << "#endif" << endl;
			 file.close();

			 wxMessageDialog(NULL, ("OK"), wxT(""), wxOK).ShowModal();
		}
	}
	else
	{
		wxMessageDialog(NULL, ("Number of elements has to be greater than 0!"), wxT(""), wxOK | wxICON_EXCLAMATION).ShowModal();
	}
}
