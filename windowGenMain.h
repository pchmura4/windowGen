/***************************************************************
 * Name:      windowGenMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2021-02-14
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef WINDOWGENMAIN_H
#define WINDOWGENMAIN_H

//(*Headers(windowGenFrame)
#include <wx/button.h>
#include <wx/choice.h>
#include <wx/filepicker.h>
#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/spinctrl.h>
#include <wx/stattext.h>
//*)

class windowGenFrame: public wxFrame
{
    public:

        windowGenFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~windowGenFrame();

    private:

        //(*Handlers(windowGenFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnButtonSaveClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(windowGenFrame)
        static const long ID_STATICTEXT1;
        static const long ID_SPINCTRL1;
        static const long ID_STATICTEXT2;
        static const long ID_CHOICE1;
        static const long ID_FILEPICKERCTRL1;
        static const long ID_BUTTON1;
        static const long ID_PANEL1;
        //*)

        //(*Declarations(windowGenFrame)
        wxButton* ButtonSave;
        wxChoice* ChoiceWindow;
        wxFilePickerCtrl* FilePickerCtrl;
        wxPanel* Panel;
        wxSpinCtrl* SpinCtrlCount;
        wxStaticText* StaticTextSize;
        wxStaticText* StaticTextWindow;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // WINDOWGENMAIN_H
