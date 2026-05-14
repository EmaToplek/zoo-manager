#include "main_frame.hpp"

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) 
{
    // Create animal manager 
    animal_manager_ = new Animal_Manager();
    animal_manager_->load();
    
    // Size of the window
    SetSize(1200, 800);

    // Create main panel
    panel_ = new wxPanel(this);

    // Create left panel
    left_panel_ = new wxPanel(panel_);

    // right panel come here TODO

    // Sizer organise the panels

    wxBoxSizer* panel_sizer = new wxBoxSizer(wxHORIZONTAL);
    panel_sizer->Add(left_panel_, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
    panel_->SetSizer(panel_sizer);

    // Search field for filtering animals
    wxTextCtrl* search_ = new wxTextCtrl(left_panel_, wxID_ANY);
    search_->SetHint("Search by name or species...");

    // Category dropdown - using vector to avoid repetition
    std::vector<std::string> categories = {"All categories", "Mammal", "Fish", "Bird", "Reptile", "Amphibian"};
    wxArrayString category_choices;
    for(const auto& cat : categories) {
        category_choices.Add(cat);
    }

    wxChoice* category_dropdown_ = new wxChoice(left_panel_, wxID_ANY, wxDefaultPosition, wxSize(200, 30), category_choices);
    category_dropdown_->SetSelection(0);

    // Status dropdown - same pattern as categories
    std::vector<std::string> statuses = {"All statuses", "Healthy", "In Treatment", "Sick"};
    wxArrayString status_choices;
    for(const auto& status : statuses) {
        status_choices.Add(status);
    }
    wxChoice* status_dropdown_ = new wxChoice(left_panel_, wxID_ANY, wxDefaultPosition, wxSize(200, 30), status_choices);
    status_dropdown_->SetSelection(0);

     // Button panel - holds Add, Edit, Remove buttons in a row
    button_panel_ = new wxPanel(left_panel_);
    wxBoxSizer* button_panel_sizer = new wxBoxSizer(wxHORIZONTAL);
    
    std::vector<std::string> button_labels = {"+Add animal", "Edit", "Remove"};
    for(const auto& label : button_labels) {
        wxButton* btn = new wxButton(button_panel_, wxID_ANY, label);
        button_panel_sizer->Add(btn, 0, wxLEFT, 10);
    }
    
    button_panel_->SetSizer(button_panel_sizer);

    // Table creation - displays all animals
    table_ = new wxListCtrl(left_panel_, wxID_ANY, wxDefaultPosition, wxSize(700, 400), wxLC_REPORT);
    
    // Columns - using vector of pairs (name, width)
    std::vector<std::pair<std::string, int>> columns = {
        {"Name", 100}, {"Species", 100}, {"Category", 100}, 
        {"Age", 100}, {"Weight", 100}, {"Enclosure", 100}, {"Health", 120}
    };
    
    for(const auto& col : columns) {
        table_->AppendColumn(col.first, wxLIST_FORMAT_LEFT, col.second);
    }

    // Get all animals and populate table
    const std::vector<Animal*> animals = animal_manager_->get_all_animals();
    fill_table(animals);
    
    // Left panel layout - stack all widgets vertically
    left_panel_sizer_ = new wxBoxSizer(wxVERTICAL);
    
    std::vector<wxWindow*> widgets = {search_, category_dropdown_, status_dropdown_, button_panel_, table_};

    for(auto* widget : widgets) {
        left_panel_sizer_->Add(widget, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10); 

    }

    left_panel_->SetSizer(left_panel_sizer_);

    
    // Status bar at bottom of window
    CreateStatusBar();
    SetStatusText("Hello");


}

void MainFrame::fill_table(const std::vector<Animal*> animals)
{
    // Clear existing rows
    table_->DeleteAllItems();

    // Loop through each animal
    for(Animal* animal : animals) {
        // Insert new row with animal name in first column
        long index = table_->InsertItem(table_->GetItemCount(), animal->get_name());
        
        // Prepare data for remaining columns using vector
        std::vector<std::string> row_data = {
            animal->get_species(),
            animal->get_category_to_string(),
            std::to_string(animal->get_age()),
            std::to_string(animal->get_weight()),
            animal->get_enclosure(),
            animal->get_health_status_to_string()
        };
        
        // Fill columns 1-6 (column 0 already has name)
        for(size_t i = 0; i < row_data.size(); i++) {
            table_->SetItem(index, i + 1, row_data[i]);
        }
    }
    
    // Refresh table display
    table_->Refresh();
}