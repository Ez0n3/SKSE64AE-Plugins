# SKSE64AE-Plugins  
  
 * [Description](#description)  
 * [Construction](#construction)  
 * [Integration](#integration)  
 * [Duplication](#duplication)  
 * [Donation](#donation)  
  
## Description:  
  
Updated: **August 20, 2025**  
  
This repo contains Plugins for Skyrim Anniversary and Special Edition - SKSE64AE, including a Plugin Example (**Status: Tested and Working**).  
  
 * **SKSE64AE** is an SDK created by [Ian Patterson](https://github.com/ianpatt), which extends the functionality of **Skyrim Anniversary and Special Edition** for mod authors.  
 * The original SDK used for building the SKSE64AE EXE can be found here: [SKSE64AE](https://skse.silverlock.org/) [SKSE64-AE-SE](https://github.com/ianpatt/skse64)  
 * Using SKSE64AE in your mod will then make SKSE64AE a **Dependency** which you must must inform your users of and provide a link to ([SKSE64AE](https://www.nexusmods.com/skyrimspecialedition/mods/30379?tab=files)).  
  
This mirror of the SDK is currently set to support Skyrim Anniversary and Special Edition runtime version: **1.6.1170.0** - SKSE64AE version: **0.2.2.6**, other versions will need to be manually configured.  
It has also been pre-configured to build **Plugins** and is not intended for building the full EXE (Core and Loader).  
  
All necessary projects have been migrated to and built with **Visual Studio 2022 (v143)**, which can be downloaded here: [Visual Studio 2022](https://visualstudio.microsoft.com/downloads/)  
  
The highest version of VS officially supported before it was abandoned for CMake, is Visual Studio 2019 (v142). Building Plugins with v143 is **experimental**, but functioning.  
> [!TIP]  
> Using [GitHub Desktop](https://desktop.github.com/download/) can make downloading and updating repositories a much simpler process.

  
> [!TIP]  
> See Also:  
> [SKSE64](https://github.com/Ez0n3/SKSE64-Plugins)  
> [SKSE](https://github.com/Ez0n3/SKSE-Plugins)  

  
[Back to top](#skse64ae-plugins)  
  
## Construction:  
  
To build plugins, open "SKSE64AE-Plugins/skse64_plugins" and then open the plugin folder you want to build. EG: **ez_skse64ae_plugin_example**.  
  
For "Ez" plugins, there are 2 solutions to choose from, each with their pros and cons.  
  * ez_skse64ae_plugin_example.sln - **Links to the SDK as a .lib file**, making it unlikely to encounter dependency issues while coding - but can significantly increase compile time.
  * ez_skse64ae_plugin_example_lean.sln - **Does not link to the SDK as a lib file**, each file from the SDK that is needed in the project must be added to the ez_skse64ae_plugin_example_lean.vcxproj.  
  
After choosing a solution, simply open it with Visual Studio and select the **Configuration** (either Debug or Release) and then select **Build Solution**.  
It will then compile the code and output to a **./Builds/** folder along side the solution.  
Inside "Builds/Configuration", you will find the plugin .dll file which can then be added to "Skyrim Special Edition/Data/SKSE/plugins".  
Post compile options have been removed for all projects, but can be re-added in-order to automatically copy the .dll file to the game folder for testing.  
  
> [!NOTE]  
> All necessary projects have been configured to use a .prop file which controls runtime versioning, output folders, additional includes, additional preprocessor defines and warning suppression.  
> This configuration file can be found in "SKSE64AE-Plugins/config/**_Plugins.prop**" and is set to the latest runtime version for the game.  
> To build plugins for other runtime versions, you will need to edit the "_Plugin.prop" file and change the version there.  
> For new projects, you can add the following project settings to the .vcxproj and then remove any "OutDir" and "IntDir" settings.  
```
<ImportGroup Label="PropertySheets">  
  <Import Project="..\..\config\_Plugins.props" />  
</ImportGroup>  
```
  
> [!NOTE]
> In-order to get debug output in Skyrim Special Edition, you will need to add these ini settings to the following file:  
> C:/Users/%username%/Documents/My Games/Skyrim Special Edition/SkyrimCustom.ini  
```
[Papyrus]  
bEnableLogging=1  
bEnableTrace=1  
bLoadDebugInformation=1  
bEnableProfiling=0  
sDefaultLogOverlay=Papyrus  
```
  
[Back to top](#skse64ae-plugins)  
  
## Integration:  
  
Integrating the example plugin with Skyrim Special Edition involves creating a new Plugin Script which interfaces with the plugin dll.  
To start, create a new CK Plugin.esp which can be loaded with Vortex, ModManager2, or whatever mod manager you use.  
In the new Plugin.esp, create a **Quest** that will be used to execute a script (Note: **Uncheck** Run Once and **Check** Allow Repeated Stages for testing).  
Then create a **Quest Script** and attach that to the Quest created above. In that Quest Script will be the calls to the new Plugin Script (dll).  
This an not always necessary, but it is required for the Ez plugin example because it adds a new function to the game to print "Hello World!".  
  
For example:  

 * Create a new **Class** Script defined in the plugin example. EG: EzSkse64aeTestClass.psc  
 * Add this to EzSkse64aeTestClass.psc:  
```
Scriptname EzSkse64aeTestClass Hidden  
  
bool Function Test() global native  
``` 
 * Create a new Plugin. EG: EzSkse64aePluginExample.esp  
 * Create a new Quest. EG: EzSkse64aePluginExampleQuest  
 * Create a new **Quest** Script. EG: EzSkse64aePluginExampleQuestScript.psc  
 * Attach EzSkse64aePluginExampleQuestScript to the Quest  
 * Add this to EzSkse64aePluginExampleQuestScript.psc:  
``` 
Scriptname EzSkse64aePluginExampleQuestScript extends Quest  
  
Event OnInit()  
	; Test the new class the plugin example added  
	if (EzSkse64aeTestClass.Test())  
		Debug.Trace(self +" EzSkse64aeTestClass.Test()")  
		Debug.Notification("EzSkse64aePluginExampleQuest : EzSkse64aeTestClass.Test()")  
		Debug.MessageBox("EzSkse64aePluginExampleQuest : EzSkse64aeTestClass.Test()")  
	endif  
EndEvent  
```
 * Use the PapyrusCompiler.exe to compile the 2 newly created Scripts into .pex files.
  
[Back to top](#skse64ae-plugins)  
  
## Duplication:  
  
Duplicating the plugin example to make your own plugin is quite easy if you follow these steps:  
 * Generate a new GUID for the new plugin:  
   * In Visual Studio, open the "C# Interactive" window (if not opened) by pressing Ctrl+Q and typing "C# Interactive".  
   * Type the following in the window and press enter:  
```
System.Guid.NewGuid().ToString().ToUpper()  
```
  
 * Save the new GUID for later use in your new plugin.  
 * Copy the ./skse64_plugins/ez_skse64ae_plugin_example/ folder.  
 * Paste it into ./skse64_plugins/ and name it without spaces. EG: ./skse64_plugins/my_cool_new_plugin/  
 * Open the existing example solution(s) (ez_skse64ae_plugin_example.sln and/or ez_skse64ae_plugin_example_lean.sln) in Visual Studio.  
 * Delete the existing ez_skse64ae_plugin_example from the solutions(s) and then save.  
 * Rename the example project(s) and solution(s) to your new plugins name. EG:  
   * ez_skse64ae_plugin_example.sln to **my_cool_new_plugin.sln**  
   * ez_skse64ae_plugin_example_lean.sln to **my_cool_new_plugin_lean.sln**  
   * ez_skse64ae_plugin_example.vcxproj to **my_cool_new_plugin.vcxproj**  
   * ez_skse64ae_plugin_example_lean.vcxproj to **my_cool_new_plugin_lean.vcxproj**  
  
 * Open the .vcxproj file(s) with a text editor and replace these few lines:  
```
    <ProjectGuid>{XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX}</ProjectGuid>  
    <ProjectName>ez_skse64ae_plugin_example</ProjectName>  
    <RootNamespace>ez_skse64ae_plugin_example</RootNamespace>  
```
 * Replace "ProjectGuid" with the GUID you generated above, this must be unique to the project.  
 * Replace "ProjectName" and "RootNamespace" to your new plugins "short" name. EG:  
```
    <ProjectGuid>{11111111-2222-3333-4444-555555555555}</ProjectGuid>  
    <ProjectName>my_cool_new_plugin</ProjectName>  
    <RootNamespace>my_cool_new_plugin</RootNamespace>  
```
  
 * Open "config.h" in the plugin folder and change these few lines to suit your new plugin: EG:  
```
// Plugin info  
#define PLUGIN_AUTHOR				"The Plugin Maker"		// Author of the plugin  
  
#define PLUGIN_NAME_SHORT			"my_cool_new_plugin"	// Plugin name without spaces - same as in the vcxproj  
#define PLUGIN_NAME_LONG			"My Cool New Plugin"	// Plugin name with spaces - shown in various places once loaded  
  
// Plugin version, Major, Minor, Build. EG: (1.0.0) equals (Major.Minor.Build)  
#define PLUGIN_VERSION_MAJOR		1  
#define PLUGIN_VERSION_MINOR		0  
#define PLUGIN_VERSION_BUILD		0  
```
  
You should then be able to open the solution file(s) in Visual Studio and then add your new project. EG: Solution Explorer -> Right-Click the solution -> Add -> Existing Project  
Select your new "my_cool_new_plugin.vcxproj" or "my_cool_new_plugin_lean.vcxproj", depending on the solution file.  
  
Select a Configuration (Debug or Release) and then Build the solution to test it.  
After completion, open the ./Builds/Configuration/ folder and there should be your new dll file. EG: **my_cool_new_plugin.dll**  
  
[Back to top](#skse64ae-plugins)  
  
## Donation:  
  
If you enjoy and/or find this content useful, consider [buying me a coffee!](https://www.paypal.com/donate/?hosted_button_id=757K44LRCMVRW) :coffee:  
  
[Back to top](#skse64ae-plugins)


