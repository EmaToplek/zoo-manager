#pragma once

#include <wx/wx.h>
#include <wx/grid.h>
#include "../app/animal_manager.hpp"
#include "detail_panel.hpp"

class MainFrame : public wxFrame
{
private:
    wxPanel* panel_;
    wxPanel* left_panel_;
    DetailPanel* detail_panel_;
    wxGrid* table_;
    Animal_Manager* animal_manager_; // manages animal list, load/save, filtering
    void fill_table(const std::vector<Animal*> animals); 
    void on_animal_selected(wxGridEvent& event);

    wxButton* remove_button_;
    wxButton* add_button_;
    wxButton* edit_button_;
    wxTextCtrl* search_;
    wxChoice* category_dropdown_;
    wxChoice* status_dropdown_;

    long selected_index_ = -1; // returns index of selected row in table
    void on_remove_animal(wxCommandEvent& event); 
    void on_add_animal(wxCommandEvent& event); 
    void on_edit_animal(wxCommandEvent& event); 
    void update_status_text();
    void on_search_changed(wxCommandEvent& event);
    void on_filter_changed(wxCommandEvent& event);
    
public:
    MainFrame(const wxString& title); 
    
};