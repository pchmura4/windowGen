/***************************************************************
 * Name:      windowGenApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2021-02-14
 * Copyright:  ()
 * License:
 **************************************************************/

#include "windowGenApp.h"

//(*AppHeaders
#include "windowGenMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(windowGenApp);

bool windowGenApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    windowGenFrame* Frame = new windowGenFrame(0);
    Frame->Show();
    SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
