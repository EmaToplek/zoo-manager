#pragma once

#include <wx/wx.h>
#include <wx/listctrl.h>

class MainFrame : public wxFrame{
private:
    wxPanel* panel_;
    wxPanel* left_panel_;
    wxPanel* right_panel_;
    wxListCtrl* table_;

public:
    MainFrame(const wxString& title);
};
