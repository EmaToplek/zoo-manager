#include "main_frame.hpp"
#include "add_edit.hpp"

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(1200, 750)) 
{
    //creates animal manager and loads animals from data.json on startup
    animal_manager_ = new Animal_Manager();
    animal_manager_->load();

    //main panel that fills the entire window
    panel_ = new wxPanel(this);

    left_panel_ = new wxPanel(panel_);
    detail_panel_ = new DetailPanel(panel_);

    //search field for filtering animals 
    search_ = new wxTextCtrl(left_panel_, wxID_ANY);
    search_->SetHint("Search by name or species..."); 

   //dropdown for categories
    wxArrayString category_choices;
    category_choices.Add("All categories");
    category_choices.Add("Mammal");
    category_choices.Add("Fish");
    category_choices.Add("Bird");
    category_choices.Add("Reptile");
    category_choices.Add("Amphibian");

    category_dropdown_ = new wxChoice(left_panel_, wxID_ANY, wxDefaultPosition, wxDefaultSize, category_choices);
    category_dropdown_->SetSelection(0);

    //dropdown for statuses
    wxArrayString status_choices;
    status_choices.Add("All statuses");
    status_choices.Add("Healthy");
    status_choices.Add("In Treatment");
    status_choices.Add("Sick");

    status_dropdown_ = new wxChoice(left_panel_, wxID_ANY, wxDefaultPosition, wxDefaultSize, status_choices);
    status_dropdown_->SetSelection(0); //aranges left and right panels side by side 

    //panel holding add, edit,remove btns in row
    wxPanel* button_panel_ = new wxPanel(left_panel_);
    
    add_button_ = new wxButton(button_panel_, wxID_ANY, "+Add animal", wxDefaultPosition, wxDefaultSize);
    edit_button_ = new wxButton(button_panel_, wxID_ANY, "Edit",  wxDefaultPosition, wxDefaultSize);
    edit_button_->Disable();

    remove_button_ = new wxButton(button_panel_, wxID_ANY, "Remove", wxDefaultPosition, wxDefaultSize);
    remove_button_->Disable();

    tick_button_ = new wxButton(button_panel_, wxID_ANY, "Tick time", wxDefaultPosition, wxDefaultSize);

    wxBoxSizer* button_panel_sizer = new wxBoxSizer(wxHORIZONTAL);
    button_panel_sizer->Add(add_button_, 0,wxLEFT, 10);
    button_panel_sizer->Add(edit_button_, 0,wxLEFT, 10);
    button_panel_sizer->Add(remove_button_, 0,wxLEFT, 10);
    button_panel_sizer->Add(tick_button_, 0, wxLEFT, 10);
    button_panel_->SetSizer(button_panel_sizer);

    //table showing all animals with columns
    table_ = new wxGrid(left_panel_,wxID_ANY);
    table_->SetDefaultCellAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
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
        table_->SetColSize(i, 120);
        
    }

    //stacks all left animals from the manager and populates the table
    wxBoxSizer* left_panel_sizer = new wxBoxSizer(wxVERTICAL);
        left_panel_sizer->Add(search_, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
        left_panel_sizer->Add(category_dropdown_, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
        left_panel_sizer->Add(status_dropdown_, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
        left_panel_sizer->Add(button_panel_, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
        left_panel_sizer->Add(table_, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 0);
        left_panel_->SetSizer(left_panel_sizer);
    
    wxBoxSizer* panel_sizer = new wxBoxSizer(wxHORIZONTAL);
        panel_sizer->Add(left_panel_, 2, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 0);
        panel_sizer->Add(detail_panel_, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 0);
        panel_->SetSizer(panel_sizer);

   // populate table and overview stats on startup
    fill_table(animal_manager_->get_all_animals());
    refresh_stats(animal_manager_->get_all_animals());
 

    // bind grid cell selection to detail panel update
    table_->Bind(wxEVT_GRID_SELECT_CELL, &MainFrame::on_animal_selected, this);
    
    remove_button_->Bind(wxEVT_BUTTON, &MainFrame::on_remove_animal, this);
    edit_button_->Bind(wxEVT_BUTTON, &MainFrame::on_edit_animal, this); 
    add_button_->Bind(wxEVT_BUTTON, &MainFrame::on_add_animal, this); 
    tick_button_->Bind(wxEVT_BUTTON, &MainFrame::on_tick_button, this);

    search_->Bind(wxEVT_TEXT, &MainFrame::on_search_changed, this);
    category_dropdown_->Bind(wxEVT_CHOICE, &MainFrame::on_filter_changed, this);
    status_dropdown_->Bind(wxEVT_CHOICE, &MainFrame::on_filter_changed, this);
    
    //status bar at the bottom of the window
    CreateStatusBar();
    update_status_text();
    
        
}

// counts health statuses in given list and pushes numbers to the overview boxes
void MainFrame::refresh_stats(const std::vector<Animal*>& animals)
{
    uint64_t healthy = 0, sick = 0, in_treatment = 0;
    for (Animal* a : animals)
    {
        switch (a->get_health_status())
        {
            case HealthStatus::Healthy: 
                healthy++; 
                break;
            case HealthStatus::Sick:     
                sick++; 
                break;
            case HealthStatus::In_Treatment: 
                in_treatment++; 
                break;
        }
    }
    detail_panel_->update_stats(animals.size(), healthy, sick, in_treatment);
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


//reads from animal_manager and draw table
void MainFrame::fill_table(const std::vector<Animal*> animals)
{
    if (table_->GetNumberRows() > 0)
        table_->DeleteRows(0, table_->GetNumberRows());
        
    int row_id = 0;
    for(Animal* animal : animals){
        table_->AppendRows(1);
        table_->SetCellValue(row_id, 0, animal->get_name());
        table_->SetCellValue(row_id, 1, animal->get_species());
        table_->SetCellValue(row_id, 2, animal->get_category_to_string());
        table_->SetCellValue(row_id, 3, std::to_string(animal->get_age()));
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << animal->get_weight();
        table_->SetCellValue(row_id, 4, oss.str());
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

// called when user clicks a cell in the grid
// wxGridEvent::GetRow() replaces wxListEvent::GetIndex()
void MainFrame::on_animal_selected(wxGridEvent& event)
{
    selected_index_ = event.GetRow();
    if (selected_index_ >= 0 && selected_index_ < (long)animal_manager_->get_all_animals().size())
    {
        Animal* selected = animal_manager_->get_all_animals()[selected_index_];
        detail_panel_->show_animal(selected);
        edit_button_->Enable();
        remove_button_->Enable();
    }
    event.Skip(); // event.Skip() is required — without it wxGrid internal selection breaks
}


void MainFrame::on_remove_animal(wxCommandEvent& event) 
{
    //get animal on remembered index
    Animal* selected = animal_manager_->get_all_animals()[selected_index_];

    // show confirmation dialog
    wxString msg = wxString::Format("Are you sure you want to remove %s?", selected->get_name());
    wxMessageDialog dialog(this, msg, "Confirm Remove", wxYES_NO | wxNO_DEFAULT | wxICON_WARNING);
    
    //if confirmed delete
    if(dialog.ShowModal() == wxID_YES) 
    {
        animal_manager_->remove_animal(selected->get_id());
        animal_manager_->save();
        fill_table(animal_manager_->get_all_animals());
        refresh_stats(animal_manager_->get_all_animals());
        update_status_text();
        detail_panel_->clear();
        remove_button_->Disable();
        edit_button_->Disable();
        selected_index_ = -1;
    }
}

// called when user clicks Add animal 
// opens empty dialog and creates new animal on save
void MainFrame::on_add_animal(wxCommandEvent& event) 
{ 
    AddEditDialog dialog(this, animal_manager_, nullptr); 

    if(dialog.ShowModal() == wxID_OK) 
    {
        uint64_t new_id = animal_manager_->get_all_animals().size() + 1;
        animal_manager_->add_animal(new_id, 
            dialog.get_name().ToStdString(), 
            dialog.get_species().ToStdString(), 
            dialog.get_category().ToStdString(),
            dialog.get_age(), 
            dialog.get_weight(),
            dialog.get_enclosure().ToStdString(), 
            dialog.get_health().ToStdString(),
            -1, dialog.get_special_info()); 
        
        animal_manager_->save();
        fill_table(animal_manager_->get_all_animals());
        refresh_stats(animal_manager_->get_all_animals());
        update_status_text();
    }
}

void MainFrame::on_tick_button(wxCommandEvent& event)
{   
    for(Animal* animal : animal_manager_->get_all_animals())
    {
        animal->tickhealth();  // thicking the healthclock of the animal
        
    }
    fill_table(animal_manager_->get_all_animals());
    refresh_stats(animal_manager_->get_all_animals());
    update_status_text();    
}

// called when user clicks edit
// opens dialog pre-filled with selected animals data and updates it on save
// if the user changes the category, the old object (wrong subclass type) is destroyed
// and a new object of the correct subclass is created — because an object's type
// is fixed at construction in C++ and cannot be changed in-place
void MainFrame::on_edit_animal(wxCommandEvent& event) 
{
    Animal* selected = animal_manager_->get_all_animals()[selected_index_];
    uint64_t id = selected->get_id();
    AddEditDialog dialog(this, animal_manager_, selected);

    if(dialog.ShowModal() == wxID_OK)
    {
        size_t position = selected_index_;
        animal_manager_->remove_animal(id);

        animal_manager_->add_animal(id, 
            dialog.get_name().ToStdString(),
            dialog.get_species().ToStdString(), 
            dialog.get_category().ToStdString(),
            dialog.get_age(), dialog.get_weight(), 
            dialog.get_enclosure().ToStdString(),
            dialog.get_health().ToStdString(),
            position, dialog.get_special_info());
      
        animal_manager_->save();
        fill_table(animal_manager_->get_all_animals());
        refresh_stats(animal_manager_->get_all_animals());
        update_status_text();
        detail_panel_->clear();
        selected_index_ = -1;
        edit_button_->Disable();
        remove_button_->Disable();
    }
}

// applies all active filters (search, category, status) and refreshes the table
// filters are cumulative — each one narrows down the previous result
void MainFrame::on_filter_changed(wxCommandEvent& event)
{
    std::string query = search_->GetValue().ToStdString();
    std::string category = category_dropdown_->GetStringSelection().ToStdString();
    std::string status = status_dropdown_->GetStringSelection().ToStdString();

    std::vector<Animal*> result;
    if (query.empty())
    {
        result = animal_manager_->get_all_animals();
    }
    else
    {
        result = animal_manager_->search(query);
    }
    
    result = animal_manager_->filter(result, category, status);

    fill_table(result);
    refresh_stats(result);
    selected_index_ = -1;
    edit_button_->Disable();
    remove_button_->Disable();
    detail_panel_->clear();
}

// called on every keystroke — rebuilds table from search results
void MainFrame::on_search_changed(wxCommandEvent& event)
{
    on_filter_changed(event);
}