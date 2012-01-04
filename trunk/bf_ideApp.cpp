/***************************************************************
 * Name:      bf_ideApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Jeremy Salwen (jeremybubs@gmail.com)
 * Created:   2008-03-23
 * Copyright: Jeremy Salwen ()
 * License:
 **************************************************************/

#include "bf_ideApp.h"

//(*AppHeaders
#include "NewFrame.h"
#include <wx/image.h>
//*)
#include <iostream>
IMPLEMENT_APP(bf_ideApp);
using namespace std;
bool bf_ideApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	NewFrame* Frame = new NewFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
