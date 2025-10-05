This is project Rocumentation so I dont forget what im doing and why

Main structure

Main.cpp
 - Just calling Game object and other behind scene objects

    Game.cpp
    - Main object of the game, callin GameObject, Managers, Utilities and other helper fuctions

        GameObject
        - Main hub for game varables and progress holding, everything here is mostly for save purpose

        ScreenManager
        - Serving as manager for render system everything with render is managed here 

            SceneObject
            - Hold map details and instruction what to load and how to render scene

        InputManager
        - Serving and calling action based on mouse/keyborad inputs and calling correct actions

        NavigationManager
        - Serving for AI and pawns find path and called updates on theirs positions

        QuestManager
        - Serving for handling quest and updating GameObject with proper variables

        DialogueManager
        - Serving for handling which text should ScreenManager render based on varables

        PawnManager
        - Serving for handling animatied objects and player itself
            
            Pawn
            - Animated objects with some function handling onClick action
            
            Player
            - Instance of pawn with key input and logic for ingame chars  
