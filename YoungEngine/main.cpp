#include "YoungEngine.h"
#include "Game.h"
#include <memory>
Engine engineRef;

int main() {
    std::shared_ptr<Game> InitGameState = std::make_shared<Game>();
    engineRef.Init();
    engineRef.SetGameState(InitGameState);
    engineRef.Run();
    engineRef.Shutdown();
    return 0;
}