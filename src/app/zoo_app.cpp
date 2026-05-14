#include "zoo_app.hpp"


bool ZooApp::OnInit() 
{
    MainFrame* mainFrame = new MainFrame("Zoo Manager"); 
    mainFrame->Center();
    mainFrame->Show(); 
    return true; 

}; 

wxIMPLEMENT_APP(ZooApp); 
