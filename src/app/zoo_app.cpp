#include <wx/wx.h>

#include "zoo_app.hpp"
#include "main_frame.hpp"



bool ZooApp::OnInit() 
{
    MainFrame* mainFrame = new MainFrame("Zoo Manager"); 
    mainFrame->Center();
    mainFrame->Show(); 
    return true; 

}; 

wxIMPLEMENT_APP(ZooApp);