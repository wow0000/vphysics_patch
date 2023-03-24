# vphysics_patch

This projects aims to fix crashes and issues with vphysics. It only supports x86 Windows at the moment and is targeted against Garry's Mod.

## How to install ?

Download the latest release from GitHub release and place it into
```
garrysmod/lua/bin/gmsv_vphysics_patch_win32.dll
```
You may need to create the bin folder.

You will need to load the module using lua, for example
```lua
-- garrysmod/lua/autorun/server/load_vphysics_patch.lua

if util.IsBinaryModuleInstalled('vphysics_patch') then
    require('vphysics_patch')
end
```

## Which crashes does it prevent?

- Crash in check_element when base_elem is null
- Crash in element_at when index is out of bounds

## How to report a vphysics crash?

Please create an issue on GitHub containing steps to reproduce the crash.

## Will this improve performance?

No, since it adds additional checks, it may slightly degrade performance.
However, the current code can be optimized to fully replace some vphysics functions, if done, it could bring performance improvements. 

## Common questions

- Will this support Linux ? No
- Will this support x64 Windows ? Signature and offset needs to be updated