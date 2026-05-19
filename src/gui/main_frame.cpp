#include "main_frame.hpp"

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) 
{
    //creates animal manager and loads animals from data.json on startup
    animal_manager_ = new Animal_Manager();
    animal_manager_->load();

    //main panel that fills the entire window
    panel_ = new wxPanel(this);
    left_panel_ = new wxPanel(panel_);
    right_panel_ = new wxPanel(panel_);

    //aranges left and right panels side by side 
    wxBoxSizer* panel_sizer = new wxBoxSizer(wxHORIZONTAL);
        panel_sizer->Add(left_panel_, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
        panel_sizer->Add(right_panel_, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
        panel_->SetSizer(panel_sizer);
    
    //search field for filtering animals 
    wxTextCtrl* search_ = new wxTextCtrl(left_panel_, wxID_ANY);
    search_->SetHint("Search by name or species...");  

    //dropdown for categories
    wxArrayString category_choices;
    category_choices.Add("All categories");
    category_choices.Add("Mammal");
    category_choices.Add("Fish");
    category_choices.Add("Bird");
    category_choices.Add("Reptile");
    category_choices.Add("Amphibian");

    wxChoice* category_dropdown_ = new wxChoice(left_panel_, wxID_ANY, wxPoint(50, 50), wxSize(200, 30), category_choices);
    category_dropdown_->SetSelection(0);

    //dropdown for statuses
    wxArrayString status_choices;
    status_choices.Add("All statuses");
    status_choices.Add("Healthy");
    status_choices.Add("In Treatment");
    status_choices.Add("Sick");

    wxChoice* status_dropdown_ = new wxChoice(left_panel_, wxID_ANY, wxPoint(50, 50), wxSize(200, 30), status_choices);
    status_dropdown_->SetSelection(0);

    //panel holding add, edit,remove btns in row
    wxPanel* button_panel_ = new wxPanel(left_panel_);
    wxButton* add_button_ = new wxButton(button_panel_, wxID_ANY, "+Add animal", wxDefaultPosition, wxDefaultSize);
    wxButton* edit_button_ = new wxButton(button_panel_, wxID_ANY, "Edit",  wxDefaultPosition, wxDefaultSize);
    wxButton* remove_button_ = new wxButton(button_panel_, wxID_ANY, "Remove", wxDefaultPosition, wxDefaultSize);
    wxBoxSizer* button_panel_sizer = new wxBoxSizer(wxHORIZONTAL);
    button_panel_sizer->Add(add_button_, 0,wxLEFT, 10);
    button_panel_sizer->Add(edit_button_, 0,wxLEFT, 10);
    button_panel_sizer->Add(remove_button_, 0,wxLEFT, 10);
    button_panel_->SetSizer(button_panel_sizer);

    //table showing all animals with columns
    table_ = new wxGrid(left_panel_,wxID_ANY, wxDefaultPosition, wxSize(700, 400));
    table_->CreateGrid(0, 7);
    table_->HideRowLabels();
    table_->SetColLabelValue(0, "Name");
    table_->SetColLabelValue(1, "Species");
    table_->SetColLabelValue(2, "Category");
    table_->SetColLabelValue(3, "Age");
    table_->SetColLabelValue(4, "Weight");
    table_->SetColLabelValue(5, "Enclosure");
    table_->SetColLabelValue(6, "Health");
    for(int i = 0; i < table_->GetNumberCols(); i++){
        table_->SetColSize(i, 100);
        
    }
    
    
    //fetches all animals from the manager and populates the table
    const std::vector<Animal*> animals = animal_manager_->get_all_animals();
    fill_table(animals);
    
    //stacks all left animals from the manager and populates the table
    wxBoxSizer* left_panel_sizer = new wxBoxSizer(wxVERTICAL);
        left_panel_sizer->Add(search_, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
        left_panel_sizer->Add(category_dropdown_, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
        left_panel_sizer->Add(status_dropdown_, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
        left_panel_sizer->Add(button_panel_, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
        left_panel_sizer->Add(table_, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
        left_panel_->SetSizer(left_panel_sizer);
    
    //status bar at the bottom of the window
    CreateStatusBar();
    update_status_text();
    
        
}

void MainFrame::update_status_text(){
    uint64_t mammal_count, fish_count, bird_count, reptile_count, amphibian_count;
    animal_manager_->category_count(mammal_count, fish_count, bird_count, reptile_count, amphibian_count);
    uint64_t total = animal_manager_->total_count(); 
    SetStatusText(std::to_string(total) + " animals total | Mammals: " + std::to_string(mammal_count) + 
                                            "   Birds: " + std::to_string(bird_count) + 
                                            "   Fish: " + std::to_string(fish_count) + 
                                            "   Reptile: " + std::to_string(reptile_count) + 
                                            "   Amphibian: " + std::to_string(amphibian_count));
} 


void MainFrame::fill_table(const std::vector<Animal*> animals)
{
    if(table_->GetNumberRows() > 0){
        table_->DeleteRows(0, table_->GetNumberRows());
    }

    int row_id = 0;
    for(Animal* animal : animals){
        table_->AppendRows(1);
        table_->SetCellValue(row_id, 0, animal->get_name());
        table_->SetCellValue(row_id, 1, animal->get_species());
        table_->SetCellValue(row_id, 2, animal->get_category_to_string());
        table_->SetCellValue(row_id, 3, std::to_string(animal->get_age()));
        table_->SetCellValue(row_id, 4, std::to_string(animal->get_weight()));
        table_->SetCellValue(row_id, 5, animal->get_enclosure());
        table_->SetCellValue(row_id, 6, animal->get_health_status_to_string());
        switch (animal->get_health_status())
        {
        case HealthStatus::Healthy:
            table_->SetCellBackgroundColour(row_id, 6, wxColour(173, 247, 180));
            table_->SetCellTextColour(row_id, 6, wxColour(8, 45, 12));
            break;
        case HealthStatus::Sick:
            table_->SetCellBackgroundColour(row_id, 6, wxColour(239, 93, 132));
            table_->SetCellTextColour(row_id, 6, wxColour(63, 13, 26));
            break;
        
        case HealthStatus::In_Treatment:
            table_->SetCellBackgroundColour(row_id, 6, wxColour(237, 221, 45));
            table_->SetCellTextColour(row_id, 6, wxColour(63, 59, 12));
            break;
        
        }
        row_id++;    
    }
    table_->Refresh();
     
}

