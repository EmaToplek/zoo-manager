# Zoo Manager

### Desired Features

- display a list of all animals with their name, species, category, age, and weight
- health status is color-code in list 
- add a new animal via a form dialog with input validation
- remove a selected animal from the list + confirm dialog
- edit an existing animal's information

- animal base class with subclasses: mammal, bird, fish
- each subclass implements feeding type, habitat requirement, min enclosure size
- selected animaös subclass-specific info swhon into detail panel
- assign an animal to an enclosure (e.g. "Savanna", "Aquarium")
- set the health status of an animal (Healthy / Sick / In Treatment)

- sick animals automatically progress to In Treatment after xy ticks
- In Treatment animals automatically progress to Healthy after xy ticks

- search animals in real time by name or species
- filter the list by animal category via dropdown (Mammal, Bird, Reptile, Fish)
- filter the list by health status via dropdown

- show basic statistics: total number of animals, count per category
- save all data to a JSON file on exit and reload it on startup
- if no save file exists, load a set od default demo animals 