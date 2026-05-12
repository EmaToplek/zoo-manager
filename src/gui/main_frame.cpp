#include "main_frame.hpp"


MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title){

    animal_manager_ = new Animal_Manager();
    animal_manager_->load();

    panel_ = new wxPanel(this);
    left_panel_ = new wxPanel(panel_);
    right_panel_ = new wxPanel(panel_);


    wxBoxSizer* panel_sizer = new wxBoxSizer(wxHORIZONTAL);
        panel_sizer->Add(left_panel_, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
        panel_sizer->Add(right_panel_, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
        panel_->SetSizer(panel_sizer);
    
    wxTextCtrl* search_ = new wxTextCtrl(left_panel_, wxID_ANY);
    search_->SetHint("Search by name or species...");  
    
    wxArrayString category_choices;
    category_choices.Add("All categories");
    category_choices.Add("Mammal");
    category_choices.Add("Fish");
    category_choices.Add("Bird");
    category_choices.Add("Reptile");
    category_choices.Add("Amphibian");


    wxChoice* category_dropdown_ = new wxChoice(left_panel_, wxID_ANY, wxPoint(50, 50), wxSize(200, 30), category_choices);
    category_dropdown_->SetSelection(0);

    wxArrayString status_choices;
    status_choices.Add("All statuses");
    status_choices.Add("Healthy");
    status_choices.Add("In Treatment");
    status_choices.Add("Sick");

    wxChoice* status_dropdown_ = new wxChoice(left_panel_, wxID_ANY, wxPoint(50, 50), wxSize(200, 30), status_choices);
    status_dropdown_->SetSelection(0);
    
    wxPanel* button_panel_ = new wxPanel(left_panel_);
    wxButton* add_button_ = new wxButton(button_panel_, wxID_ANY, "+Add animal", wxDefaultPosition, wxDefaultSize);
    wxButton* edit_button_ = new wxButton(button_panel_, wxID_ANY, "Edit",  wxDefaultPosition, wxDefaultSize);
    wxButton* remove_button_ = new wxButton(button_panel_, wxID_ANY, "Remove", wxDefaultPosition, wxDefaultSize);
    wxBoxSizer* button_panel_sizer = new wxBoxSizer(wxHORIZONTAL);
    button_panel_sizer->Add(add_button_, 0,wxLEFT, 10);
    button_panel_sizer->Add(edit_button_, 0,wxLEFT, 10);
    button_panel_sizer->Add(remove_button_, 0,wxLEFT, 10);
    button_panel_->SetSizer(button_panel_sizer);

    table_ = new wxListCtrl(left_panel_,wxID_ANY, wxDefaultPosition, wxSize(700, 400), wxLC_REPORT);
    table_->AppendColumn("Name", wxLIST_FORMAT_LEFT, 100);
    table_->AppendColumn("Species", wxLIST_FORMAT_LEFT, 100);
    table_->AppendColumn("Category", wxLIST_FORMAT_LEFT, 100);
    table_->AppendColumn("Age", wxLIST_FORMAT_LEFT, 100);
    table_->AppendColumn("Weight", wxLIST_FORMAT_LEFT, 100);
    table_->AppendColumn("Enclosure", wxLIST_FORMAT_LEFT, 100);
    table_->AppendColumn("Health", wxLIST_FORMAT_LEFT, 100);
    
    const std::vector<Animal*> animals = animal_manager_->get_all_animals();
    fill_table(animals);
    
    wxBoxSizer* left_panel_sizer = new wxBoxSizer(wxVERTICAL);
        left_panel_sizer->Add(search_, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
        left_panel_sizer->Add(category_dropdown_, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
        left_panel_sizer->Add(status_dropdown_, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
        left_panel_sizer->Add(button_panel_, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
        left_panel_sizer->Add(table_, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
        left_panel_->SetSizer(left_panel_sizer);
    
    
    CreateStatusBar();
    SetStatusText("Hello");
        
}
void MainFrame::fill_table(const std::vector<Animal*> animals){

    table_->DeleteAllItems();

    for(Animal* animal : animals){
        long index = table_->InsertItem(table_->GetItemCount(), animal->get_name());
        table_->SetItem(index, 1, animal->get_species());
        table_->SetItem(index, 2, animal->get_category_to_string());
        table_->SetItem(index, 3, std::to_string(animal->get_age()));
        table_->SetItem(index, 4, std::to_string(animal->get_weight()));
        table_->SetItem(index, 5, animal->get_enclosure());
        table_->SetItem(index, 6, animal->get_health_status_to_string());
    }
    table_->Refresh();
     
}

 
