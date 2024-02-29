#include <Windows.h>
#include <chrono>
#include <iostream>
#include <string>
#include <sstream>
#include "Gen_App/Config/AppConfig.h"

#ifdef USE_DEBUG
    #include "App/Tools/Debug/AYCDebugLayer.h"
    #include "App/Tools/Debug/AYCLog.h"
#endif

#include "App/Handler/WindowHandler.h"
using namespace AYCDX;
int main(int argc, char* argv[])
{
    //INIT
    #ifdef USE_DEBUG
    AYCLog::Log(LOG_DISPLAY, TEXT("Let's go"));

    if (!AYCDebugLayer::Get().Init()) {
        AYCLog::Log(LOG_EXCEPTION, TEXT("Cannot initialize debug layer !"));
        return 0;
    }
    #endif

    WindowHandler* window = &WindowHandler::Get();
    if (!window || !window->Init()) {
        #ifdef USE_DEBUG
        AYCLog::Log(LOG_EXCEPTION, TEXT("Cannot initialize a window !"));
        #endif
        return 0;
    }

    //delta time initialisation
    auto lastTime = std::chrono::high_resolution_clock::now();
    double deltaTime = 0.0;


    //boucle de rendu
    do {
        window->Update();

        // Calcul du Delta time
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> timeElapsed = currentTime - lastTime;
        deltaTime = timeElapsed.count();

        lastTime = currentTime;

        // Convertir deltaTime en une chaîne de caractères
        std::ostringstream ss;
        ss << std::fixed << std::setprecision(6) << deltaTime;
        std::string deltaTimeStr = ss.str();

        #ifdef USE_DEBUG
        AYCLog::Log(LOG_DISPLAY, TEXT(deltaTimeStr));
        #endif
    } while (!WindowHandler::Get().GetClose());

    WindowHandler::Get().Shutdown();

    #ifdef USE_DEBUG
    AYCDebugLayer::Get().Shutdown();
    #endif
    return 0;
}