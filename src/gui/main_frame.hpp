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
    void on_animal_deselected(wxListEvent& event);  

    wxButton* remove_button_; 
    long selected_index_ = -1; // returns index of selected row in table
    void on_remove_animal(wxCommandEvent& event); 

public:
    MainFrame(const wxString& title);  
};
