#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include "core/gameObject.h"
#include "screens/screen.h"
#include "screens/gameScreen.h"


class ScreenManager {

    enum class ScreenType {
        GAME,
        MENU,
        CINEMA
    };

    public:
        ScreenManager(GameObject& gameObject);
        ~ScreenManager();

        // Scene management
        void loadScene(Scene* scene);
        void changeScene(const std::string& sceneName);
        void changeScreen(ScreenType type);
        void openMenu();
        void closeMenu();
        void playCinematic();
        void stopCinematic();

        // Render section
        void draw();
        void update();

    private:
        void loadMaps();

        GameObject& gameObject;
        GameScreen* gameRender;
        Screen* menuRender;
        Screen* cinemaRender;
        Scene* currentScene;
        std::vector<Scene*> mapList;

        ScreenType screenType;

        bool isPaused;
};

#endif
