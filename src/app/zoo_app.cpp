#include "zoo_app.hpp"


bool ZooApp::OnInit(){
    MainFrame* main_frame = new MainFrame("Zoo Manager");
    main_frame->Show(true);
    main_frame->SetSize(1280,720);
    return true;
}
