#pragma once

#include <wx/wx.h>
#include <wx/listctrl.h>
#include "../app/animal_manager.hpp"

class MainFrame : public wxFrame{
private:
    wxPanel* panel_;
    wxPanel* left_panel_;
    wxPanel* right_panel_;
    wxListCtrl* table_;
    Animal_Manager* animal_manager_;
    void fill_table(const std::vector<Animal*> animals);   

public:
    MainFrame(const wxString& title);
    
};