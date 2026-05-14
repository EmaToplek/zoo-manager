#pragma once

#include <wx/wx.h>
#include <wx/listctrl.h>
#include "../app/animal_manager.hpp"
#include <vector>

class MainFrame : public wxFrame
{
private:
    wxPanel* panel_;
    wxPanel* left_panel_;
    wxPanel* right_panel_;
    wxListCtrl* table_;
    wxPanel* button_panel_; 
    wxBoxSizer* left_panel_sizer_;
    Animal_Manager* animal_manager_; // manages animal list, load/save, filtering
    void fill_table(const std::vector<Animal*> animals);   

public:
    MainFrame(const wxString& title);  
};
