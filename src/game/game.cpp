#include "game.h"

#include "scenewithui.h"
#include "globalui.h"
#include "node/triangle.h"
#include "scene/scenemanager.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init()
{
    SceneManager::Instance().SwitchScene(new SceneWithUI());

    GlobalUI* ui_ = new GlobalUI();
}

void Game::GameLoop()
{

}
