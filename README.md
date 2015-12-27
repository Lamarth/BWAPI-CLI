# BWAPI-CLI
## .NET wrapper for the Broodwar API (BWAPI)
.NET wrapper for the Broodwar API (BWAPI) written in C++/CLI

Currently wraps BWAPI 4.1.2

This project is a C++/CLI wrapper for the Broodwar API. This project is also aimed to provide APIs that are higher level or more suited to F#/C# style than original BWAPI.

WARNING: API will change during development. It is recommended that maintain your own copy be prepared to manually merge any changes you specifically desire.

Project is in alpha stage, but library can run dll AI modules. Project is built with Visual Studio 2013, using BWAPI libraries directly.

It is highly recommended that you have experience in setting up a BWAPI bot before dealing with this library. For now we do not provide any binaries so you'll have to build it by yourself.

To use AI you have to place Broodwar.dll, Broodwar.dll.config and your AI module into same folder. BWAPI config must point to Broodwar.dll as AI module. Edit .config file. Assembly key must point to your AI assembly (with extension), and Module key must point to class, which implements AiBase. ExampleAIModule ported to C# and to F# is also provided.

## Original Version
Previous BWAPI-CLI for version 3.7.3 was created by ZeroFusion at http://bwapicli.codeplex.com/

## Issues
This project a port from VS 2010 + BWAPI 3.7.3 to VS 2013 + BWAPI 4.1.2 of an Alpha project by someone with minimal C++ experience and no BWAPI experience.

Everything appears to be working aside from unit filter based functions. These require changes to the supplied BWAPI headers to make the project compile. For example:

// Does not compile - IntelliSense: argument of type "decltype(nullptr)" is incompatible with parameter of type "const decltype(nullptr) &"  
Unitset getUnitsOnTile(BWAPI::TilePosition tile, const UnitFilter &pred = nullptr) const;

// Does compile, but is obviously incorrect  
Unitset getUnitsOnTile(BWAPI::TilePosition tile, const UnitFilter &pred = Filter::IsTransport) const;
