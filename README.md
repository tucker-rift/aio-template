# [Rift] AIO Plugin Template. 
Getting started with plugin development on Rift is a little more difficult than I think it should be. So I made this to help people get started. This is setup to easily allow you to support one or more champions in a single plugin without the hassle of setting up a project.

## Installation Instructions
First you need to make sure you have Git installed. You can download git [here](https://git-scm.com/downloads), I **highly recommend** that during the installation you opt to install **Git Bash**. Secondly you're going to need the DirextX9 SDK (June 2010 Release) which you can get from Microsoft's website [here](https://www.microsoft.com/en-us/download/details.aspx?id=6812) and lastly you're going to need [Visual Studio 2017](https://visualstudio.microsoft.com/vs/). 

**Important**:  When installing Visual Studio 2017 make sure to select the latest Windows 10 SDK as an additional component. During the installation process there will be checkboxes on the bottom right. Look for it and make sure it's checked.

**Already have Visual Studio?** You can open the Visual Studio Installer and select "modify" under your installation, from there go to the individual components tab and scroll all the way to the bottom and you can then select the Windows 10 SDK from there for installation. 

## Clone the project.

Once you have git installed, you need to open Git Bash. You can use the `cd` command to navigate your filesystem until you're where you want the project to reside. If you're not familliar with how to navigate using the filesystem, [here's some videos to get you started](https://www.youtube.com/watch?v=MBBWVgE0ewk). 

Once you're ready to clone, simply run the following commands.

```git
git clone --recurse-submodules https://github.com/tucker-rift/aio-template.git my-project-name
```

**NOTE**: `--recurse-submodules` requires a git version of 2.13 or higher. 

## Moving Forward

You can now open the `.sln` file which will bring up the project in Visual Studio 2017. Make sure that up top you are set to "Release" and "x86" as shown in the picture below. 

![enter image description here](https://i.gyazo.com/9d622374d6275535eb2bd3c263146b35.png)

You can now open the "Plugins" filter to see the example Ashe plugin that's provided. 

![enter image description here](https://gyazo.com/abb36b5d905b93ef0239c1839668e83e.png)

This is not a full plugin by any means, it's simply an example to get you started. You can open the `ChampionPlugin.h` file to see all of the different [virtual functions](https://www.geeksforgeeks.org/virtual-function-cpp/) that you can use to create your plugin. You don't need to register any SDK Events as that's all handled for you, simply override the `On____` handler that you need to use and it will work out of the box.

When you create a new Plugin you will need to modify `GetChampionPlugin` method in `Plugin.cpp`  to include the champion you want to add. For example, to add Garen you'd do this:

```c++
	if (strcmp(Player.GetCharName(), "Garen") == 0) 
		championPlugin = std::make_shared<GarenPlugin>();
```


## Video Tutorials
I'm currently working on a list of tutorials that teaches people how to develop plugins, please standby :)
