#pragma once

#include <wx/wx.h>

class MainFrame : public wxFrame{
private:
    wxPanel* panel_;

public:
    MainFrame(const wxString& title);
};
