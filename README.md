# Traffic Simulator for a grid city

University project written with c++20 and sfml. 

![MainScreen](.github/readme-gifs/basic.gif)

## Features 

- **Integrated map editor**: allows for easy saving and loading of custom maps. Feautures automatic intersection and curves detection system.

![MapEditor](.github/readme-gifs/map_editor.gif)

- **Easy simulation configuration**: with settings for speed, display scale and number of cars
- **Modern class structure**: all objects drawn on the screen inherit from a single GraphicalObject class and override the .draw method. This approach allows for just one loop calling ->draw() for every object on the screen every frame.
- **Support for customization**: new road types can be easily added by following few simple rules. Just add a new pattern to the already existing ones. Cars will automaticaly learn to drive on them.

```c++
    //Part of road patterns file
    // Horizontal road
    patterns[RoadTypes::HorizontalRoad] =
    {
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 1, 1, 1, 1, 1, 1, 1, 4 },
        { 1, 1, 1, 1, 1, 1, 1, 4 },
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 3, 1, 1, 1, 1, 1, 1, 1 },
        { 3, 1, 1, 1, 1, 1, 1, 1 },
        { 0, 0, 0, 0, 0, 0, 0, 0 }
    };

    // Bottom right corner
    patterns[RoadTypes::BottomRightCorner] =
    {
        { 0, 1, 1, 0, 0, 1, 1, 0 },
        { 1, 7, 1, 0, 0, 1, 1, 0 },
        { 1, 1, 7, 0, 0, 1, 1, 0 },
        { 0, 0, 0, 0, 0, 1, 1, 0 },
        { 0, 0, 0, 0, 0, 1, 1, 0 },
        { 1, 1, 1, 1, 1, 8, 1, 0 },
        { 1, 1, 1, 1, 1, 1, 8, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 }
    };

    void RoadPatterns::setPossibleTurnDirections()
    {
        possibleTurnDirections[5] = { Direction::RIGHT };
        possibleTurnDirections[6] = { Direction::DOWN };
        possibleTurnDirections[7] = { Direction::LEFT };
        possibleTurnDirections[8] = { Direction::UP };
        possibleTurnDirections[9] = { Direction::UP, Direction::LEFT };
        possibleTurnDirections[10] = { Direction::DOWN, Direction::LEFT };
        possibleTurnDirections[11] = { Direction::UP, Direction::RIGHT };
        possibleTurnDirections[12] = { Direction::DOWN, Direction::RIGHT };
    }
```

## Installation
As this was an university project there is not "simple" way to run it. However here are the steps and programs needed: 
1. Install VS2022.
2. Install ```sfml 2.6.1 64-bit``` to ```C:\sfml\SFML-2.6.1```
3. By default the program looks for sfml files inside ```C:\sfml\SFML-2.6.1``` If you want to use another location follow the guide at https://www.sfml-dev.org/tutorials/2.6/start-vc.php and change the project properties.
4. Clone the repository
5. Copy sfml-audio-2.dll, sfml-graphics-2.dll, sfml-system-2.dll, sfml-window-2.dll from your ```/SFML-2.6.1/bin``` to ```/ncts-files``` directory inside the project.
6. Open ```ncts.sln``` file and run the program with Visual Studio 2022.

## Special credits: 
[javidx9/OneLoneCoder](https://www.youtube.com/@javidx9) - for the automatic road type detection code and excellent tutorial video.<br>
[Aim Studios](https://aim-studios.itch.io/) - for the car sprites. 

