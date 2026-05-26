#include <wx/wx.h>

#include "zoo_app.hpp"
#include "../gui/main_frame.hpp"



bool ZooApp::OnInit() 
{
    MainFrame* mainFrame = new MainFrame("Zoo Manager"); 
    mainFrame->SetMinSize(wxSize(1280, 720));
    mainFrame->Fit(); 
    mainFrame->Center();
    mainFrame->Show(); 
    return true; 

}; 

wxIMPLEMENT_APP(ZooApp);