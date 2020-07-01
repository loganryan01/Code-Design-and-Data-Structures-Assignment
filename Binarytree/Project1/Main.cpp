/*----------------------------
    File Name: Main.cpp
    Purpose: Run the app.
    Author: Logan Ryan
    Modified: 28 June 2020
------------------------------
    Copyright 2020 Logan Ryan.
----------------------------*/

#include "App.h"

int main(int argc, char* argv[])
{
    {
        App app;
        app.Startup();
        app.Run();
        app.Shutdown();
    }
    
    return 0;
}