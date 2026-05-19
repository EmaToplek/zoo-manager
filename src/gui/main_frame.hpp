#pragma once

#include <wx/wx.h>
#include <wx/grid.h>
#include "../app/animal_manager.hpp"

class MainFrame : public wxFrame
{
private:
    wxPanel* panel_;
    wxPanel* left_panel_;
    wxPanel* right_panel_;
    wxGrid* table_;
    Animal_Manager* animal_manager_; // manages animal list, load/save, filtering
    void fill_table(const std::vector<Animal*> animals);
    void update_status_text();    
public:
    MainFrame(const wxString& title); 
    
};
