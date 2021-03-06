/*
-----------------------------------------------------------------------------
This source file is part of OGRE
(Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2005 The OGRE Team
Also see acknowledgements in Readme.html

You may use this sample code for anything you like, it is not covered by the
LGPL like the rest of the engine.
-----------------------------------------------------------------------------
*/
/*
-----------------------------------------------------------------------------
Filename:    ExampleApplication.h
Description: Base class for all the OGRE examples
-----------------------------------------------------------------------------
*/

// Note: This file was modifed for the Opal-Ogre sample apps.

#ifndef __ExampleApplication_H__
#define __ExampleApplication_H__

#include <ogre/Ogre.h>
#include <ogre/OgreConfigFile.h>
#include "ExampleFrameListener.h"


/** Base class which manages the standard startup of an Ogre application.
    Designed to be subclassed for specific examples if required.
*/
class ExampleApplication
{
public:
    /// Standard constructor
    ExampleApplication()
    {
        mFrameListener = 0;
        mRoot = 0;
    }
    /// Standard destructor
    virtual ~ExampleApplication()
    {
        if (mFrameListener)
            delete mFrameListener;
        if (mRoot)
            delete mRoot;
    }

    /// Start the example
    virtual void go(void)
    {
        if (!setup())
            return;

        mRoot->startRendering();

        // clean up
        destroyScene();
    }

protected:
    Root *mRoot;
    Camera* mCamera;
    SceneManager* mSceneMgr;
    ExampleFrameListener* mFrameListener;
    RenderWindow* mWindow;

    // These internal methods package up the stages in the startup process
    /** Sets up the application - returns false if the user chooses to abandon configuration. */
	// This function was modifed for the Opal sample apps.
    virtual bool setup(void)
    {
#if defined (WIN32) || defined(_WIN32)
	// It looks like win32 defines _DEBUG and the rest define DEBUG.
	#if defined(_DEBUG)
		mRoot = new Ogre::Root("ogre_plugins_win32_d.cfg");
	#else
		mRoot = new Ogre::Root("ogre_plugins_win32.cfg");
	#endif
#else
	#if defined(DEBUG)
		mRoot = new Ogre::Root("ogre_plugins_unix_d.cfg");
	#else
		mRoot = new Ogre::Root("ogre_plugins_unix.cfg");
	#endif
#endif

        setupResources();

        bool carryOn = configure();
        if (!carryOn) return false;

        chooseSceneManager();
        createCamera();
		createPhysicalCamera();
        createViewports();

        // Set default mipmap level (NB some APIs ignore this)
        TextureManager::getSingleton().setDefaultNumMipmaps(5);

		// Create any resource listeners (for loading screens)
		createResourceListener();
		// Load resources
		loadResources();

		// Create the scene
        createScene();

        createFrameListener();

        return true;

    }
    /** Configures the application - returns false if the user chooses to abandon configuration. */
    virtual bool configure(void)
    {
        // Show the configuration dialog and initialise the system
        // You can skip this and use root.restoreConfig() to load configuration
        // settings if you were sure there are valid ones saved in ogre.cfg
        if(mRoot->showConfigDialog())
        {
            // If returned true, user clicked OK so initialise
            // Here we choose to let the system create a default rendering window by passing 'true'
            mWindow = mRoot->initialise(true, "OPAL-Ogre Sample Application");
            return true;
        }
        else
        {
            return false;
        }
    }

    virtual void chooseSceneManager(void)
    {
        // Get the SceneManager, in this case a generic one
        mSceneMgr = mRoot->createSceneManager(ST_GENERIC);
    }

	// This function was modifed for the Opal sample apps.
    virtual void createCamera(void)
    {
        // Create the camera
        mCamera = mSceneMgr->createCamera("PlayerCam");

        // Position it at the origin.
        mCamera->setPosition(Vector3(0, 0, 0));

        // Look back along -Z
        mCamera->lookAt(Vector3(0,0,-300));

        mCamera->setNearClipDistance(0.5);

		Ogre::SceneNode* camNode = mSceneMgr->getRootSceneNode()->
			createChildSceneNode("cameraNode");
		camNode->attachObject(mCamera);
    }

	// This function was added for the Opal sample apps.
    virtual void createPhysicalCamera() = 0;

	// This function was modifed for the Opal sample apps.
    virtual void createFrameListener()
    {
        //mFrameListener= new ExampleFrameListener(mWindow, mCamera);
        //mFrameListener->showDebugOverlay(true);
        //mRoot->addFrameListener(mFrameListener);
    }

    virtual void createScene(void) = 0;    // pure virtual - this has to be overridden

    virtual void destroyScene(void){}    // Optional to override this

    virtual void createViewports(void)
    {
        // Create one viewport, entire window
        Viewport* vp = mWindow->addViewport(mCamera);
        vp->setBackgroundColour(ColourValue(0,0,0));

        // Alter the camera aspect ratio to match the viewport
        mCamera->setAspectRatio(
            Real(vp->getActualWidth()) / Real(vp->getActualHeight()));
    }

    /// Method which will define the source of resources (other than current folder)
    virtual void setupResources(void)
    {
        // Load resource paths from config file
        ConfigFile cf;
        cf.load("ogre_resources.cfg");

        // Go through all sections & settings in the file
        ConfigFile::SectionIterator seci = cf.getSectionIterator();

        String secName, typeName, archName;
        while (seci.hasMoreElements())
        {
            secName = seci.peekNextKey();
            ConfigFile::SettingsMultiMap *settings = seci.getNext();
            ConfigFile::SettingsMultiMap::iterator i;
            for (i = settings->begin(); i != settings->end(); ++i)
            {
                typeName = i->first;
                archName = i->second;
                ResourceGroupManager::getSingleton().addResourceLocation(
                    archName, typeName, secName);
            }
        }
    }

	/// Optional override method where you can create resource listeners (e.g. for loading screens)
	virtual void createResourceListener(void)
	{

	}

	/// Optional override method where you can perform resource group loading
	/// Must at least do ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	virtual void loadResources(void)
	{
		// Initialise, parse scripts etc
		ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	}



};


#endif
