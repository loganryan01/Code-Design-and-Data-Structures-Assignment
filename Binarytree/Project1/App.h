/*---------------------------------------------------------------
	File Name: App.h
	Purpose: Contain the function declarations for the App class.
	Author: Logan Ryan
	Modified: 28 June 2020
-----------------------------------------------------------------
	Copyright 2020 Logan Ryan.
---------------------------------------------------------------*/

#pragma once

class App
{
public:
	// Default constructor.
	App();

	// Default destructor.
	~App();

	// Create the window.
	void Startup();

	// Close the window.
	void Shutdown();

	// The logic to run the app.
	void Run();
};

