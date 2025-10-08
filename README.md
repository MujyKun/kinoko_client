## Kinoko Client

Kinoko Client consists of v95 client edits for the popular mushroom game.  
This repo is primarily a CMake-based project. However, it has been altered to support a Visual Studio IDE environment.

If you are interested in a v95 server emulator, check out [Kinoko](https://github.com/iw2d/kinoko). 

## Setup

### Clone

``git clone --recurse-submodules https://github.com/iw2d/kinoko.git && cd kinoko``

OR

```
git clone https://github.com/iw2d/kinoko.git
cd kinoko
git submodule update --init --recursive
```

### IDE
[Download Visual Studio 2022](https://visualstudio.microsoft.com/vs/)


### Mushroom Game Client Downloads
[GMS V95 Client Setup](https://ia600809.us.archive.org/19/items/GMSSetup93-133/GMS0095/GMSSetupv95.exe)  
[GMS v95.1 Localhost](https://mega.nz/file/dWIgyR4I#6cDN_ycLLiFtad07Eby3UfjdY3TqGI65g6X-xEqlmds)


### Manually Inject DLL (After Building DLL)

This project already has auto-injection when launching Kinoko.exe, but manually injecting the DLL into the client is also an option.

This is something that's not really mentioned in many places. So I'll put it here for any first-timers or for anyone having issues.
1. Download CFF Explorer.
2. Open the CFF Explorer App -> File -> Open -> ijl15.dll
3. Click Import Adder -> Add -> Kinoko.dll 
4. Click all of the Exported Functions and "Import By Ordinal"
5. Click "Rebuild Import Table".
6. File -> Save
7. When you run Kinoko.exe or MapleStory.exe, it will now inject the Kinoko.dll. (Kinoko.exe is not needed if you have manually injected the DLL).

### Launch Kinoko.exe
You can set arguments to Kinoko.exe in the format:  `Kinoko.exe <IP ADDRESS> 8484`
