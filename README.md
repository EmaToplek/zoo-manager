# Zoo Manager

A desktop application for managing a zoo's animal inventory, built with **C++**, **wxWidgets**, and **nlohmann/json**. The application provides a graphical interface to add, edit, remove, search, and filter animals, view species-specific details, track health status, and persist data between sessions.

## Features

- **Animal list** – displays all animals in a table with name, species, category, age, weight, enclosure, and health status.
- **Color-coded health status** – Healthy (green), Sick (red), In Treatment (yellow) shown directly in the table.
- **Add animal** – form dialog with input validation (required fields, numeric checks for age/weight/special info).
- **Edit animal** – pre-filled form dialog; changing category recreates the animal as the correct subclass.
- **Remove animal** – with confirmation dialog before deletion.
- **Detail panel** – shows subclass-specific information (feeding type, habitat, minimum enclosure size, special info) for the selected animal.
- **Enclosure assignment** – each animal is assigned to an enclosure (e.g. Savanna, Aquarium, Aviary, Terrarium...).
- **Health status management** – set an animal's status to Healthy, Sick, or In Treatment via dropdown.
- **Live search** – filter animals in real time by name or species.
- **Category & status filters** – dropdowns to filter the list by animal category (Mammal, Bird, Reptile, Fish, Amphibian) and by health status.
- **Statistics overview** – total animal count plus per-category and per-health-status counts, shown in the status bar and overview panel.
- **Persistence** – all data is saved to `data.json` on every change and reloaded automatically on startup. If no save file exists, a set of demo animals is loaded instead.

## Architecture

### Class overview

```mermaid
classDiagram
    class Animal {
        <<abstract>>
        -id
        -name
        -species
        -age
        -weight
        -enclosure
        -health_status
        +get_category()
        +get_feeding_type()
        +get_habitat()
        +get_min_enclosure_size()
        +get_special_info_map()
    }

    class Mammal
    class Bird
    class Fish
    class Reptile
    class Amphibian

    Animal <|-- Mammal
    Animal <|-- Bird
    Animal <|-- Fish
    Animal <|-- Reptile
    Animal <|-- Amphibian

    class Animal_Manager {
        -animals_list_ : vector~Animal*~
        -species_list_
        -default_traits_
        +load()
        +save()
        +add_animal()
        +remove_animal(uint64_t id)
        +search()
        +category_count()
        +health_count()
        +get_default_traits()
        +get_species_for_category()
    }

    Animal_Manager o-- "0..*" Animal

    class MainFrame {
        -table_
        -animal_manager_
        -detail_panel_
        -on_add_animal(wxCommandEvent& event)
        -on_edit_animal()
        -on_remove_animal()
        -on_filter_changed()
        -refresh_stats(const std::vector<Animal*>& animals)
    }

    class DetailPanel {
        +show_animal(Animal* animal)
        +update_stats()
        +clear()
    }

    class AddEditDialog {
        +get_special_info()
        -on_category_changed(wxCommandEvent& event)
        -on_ok(wxCommandEvent& event)
    }

    MainFrame --> Animal_Manager : uses
    MainFrame --> DetailPanel : contains
    MainFrame --> AddEditDialog : opens
    AddEditDialog --> Animal_Manager : queries species/defaults
```

### Project structure

```
zoo-manager/
├── animals/
│   ├── animal.hpp / animal.cpp        # abstract base class
│   ├── mammal.hpp / mammal.cpp
│   ├── bird.hpp / bird.cpp
│   ├── fish.hpp / fish.cpp
│   ├── reptile.hpp / reptile.cpp
│   └── amphibian.hpp / amphibian.cpp
├── app/
│   ├── animal_manager.hpp / .cpp      # data storage, JSON load/save, search & filtering
│   ├── zoo_app.hpp / .cpp             # wxApp entry point
├── gui/
│   ├── main_frame.hpp / .cpp          # main window, table, buttons, filters
│   ├── detail_panel.hpp / .cpp        # subclass-specific detail view + stats overview
│   └── add_edit.hpp / .cpp            # add/edit dialog with dynamic special-info fields
├── data.json                          # persisted animal data (created on first save)
├── species.json                       # species lists and default special-info templates
├── CMakeLists.txt
└── README.md
```

### Design notes

- Each animal subclass stores its category-specific attributes in a `special_info_` map (`std::map<std::string, std::string>`) instead of individual member variables. This allows new fields to be added via `species.json` without changing any class headers.
- `Animal_Manager` owns all `Animal*` instances and is responsible for their lifetime (allocation in `add_animal()`, deallocation in `remove_animal()` and its destructor).
- `species.json` is the single source of truth for both the species dropdown lists and the default special-info templates used when adding a new animal.

## Build instructions

### Requirements

- CMake ≥ 3.16
- A C++17-compatible compiler (GCC, Clang, or MSVC)
- [wxWidgets](https://www.wxwidgets.org/) (3.x)
- [nlohmann/json](https://github.com/nlohmann/json) (header-only; fetched automatically or installed via package manager)

### Build steps

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

### Running

From the `build` directory:

```bash
./ZooManager
```

The application looks for `data.json` and `species.json` in the parent directory of the build folder (`../data.json`, `../species.json`). If `data.json` does not exist, a set of demo animals is loaded automatically and a new file is created on the first save.

## User Manual

### 1. Launching the Application

After building the project (see **Build Instructions**), run the executable.
The application loads data from `data.json` on startup (if the file doesn't exist, it generates a few demo entries).

### 2. Main Window

The main window is split into two sections:
- **Left panel** – search bar, filters, action buttons (Add/Edit/Remove, Tick time), and a table listing all animals
- **Right panel** – details of the selected animal and an overview with statistics (Total / Healthy / Sick / In Treatment)

<img src="docs/images/mainWindow.jpg" alt="Main window" width="600">

The status bar at the bottom shows the total number of animals and a breakdown by category.

### 3. Search and Filtering

Type a name or species into the **Search** field – the table updates in real time.
The **Category** and **Status** dropdowns further narrow down the results (filters are combined with the search).

<img src="docs/images/search.jpg" alt="search " width="600">

### 4. Adding a New Animal

Click **+Add animal** to open the input dialog. Fields include:
- Name, Category, Species, Age, Weight, Enclosure, Health
- Dynamic **Special info** fields that change depending on the selected category (e.g. Bird, Reptile, Mammal...)

<img src="docs/images/add.jpg" alt="Add Dialog" width="300">


After clicking **Save**, the new animal is added to the table and saved to `data.json`.

### 5. Editing an Animal

Select a row in the table (click any cell), then click **Edit**.
The dialog opens pre-filled with the animal's existing data, including its special info fields.

<img src="docs/images/edit.jpg" alt="Edit Dialog" width="300">


### 6. Removing an Animal

Select a row, click **Remove**, and confirm in the dialog that appears.

<img src="docs/images/remove.jpg" alt="Remove Confirmation" width="400">


### 7. Viewing Details and Statistics

Clicking a row in the table updates the right-hand panel with:
- Basic info (Name, Species, Category, Age, Weight, Enclosure, Health)
- Species-specific info (Feeding type, Habitat, Min enclosure size, Special info)
- Overview boxes showing the total number of animals per health status (updated after every add/edit/remove/filter action)

<img src="docs/images/ov.jpg" alt="Overview Stats" width="300">

## Authors

- Viktor Borosnyai  
- Ema Toplek 

## Division of Work

**Viktor**
- `Animal` base class, `Mammal`, `Amphibian` and `Fish` subclasses
- Health state machine (Sick → In Treatment → Healthy ticks)
- JSON save/load with demo-animal fallback
- Animal list view with color-coded health status, real-time search & filter wiring
- Autotests for own classes/logic

**Ema**
- `Bird` and `Reptile` subclasses
- Search & filter logic (name, species, category, health status)
- Enclosure assignment and health status updates
- Detail panel, Add/Edit dialog with validation, Remove confirmation, statistics panel
- Autotests for own classes/logic


## License

This project is licensed under the [MIT License](LICENSE).