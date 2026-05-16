#pragma once

#include <wx/wx.h>
#include <wx/listctrl.h>
#include "../app/animal_manager.hpp"
#include "detail_panel.hpp"

class MainFrame : public wxFrame
{
private:
    wxPanel* panel_;
    wxPanel* left_panel_;
    DetailPanel* detail_panel_;
    wxListCtrl* table_;
    Animal_Manager* animal_manager_; // manages animal list, load/save, filtering
    void fill_table(const std::vector<Animal*> animals); 
    void on_animal_selected(wxListEvent& event);  

public:
    MainFrame(const wxString& title);  
};
