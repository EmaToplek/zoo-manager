#pragma once
#include<wx/wx.h>
#include "../gui/main_frame.hpp"


class ZooApp : public wxApp{

public:
    bool OnInit();

};
wxIMPLEMENT_APP(ZooApp);
