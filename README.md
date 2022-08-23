# WarBird Obfuscate
An analysis of WarBird obfuscation in the MSVC compiler

## Background
WarBird is an obfuscation framework used by Microsoft in their DRM technology.  It supports multiple forms of obfuscation including code packing and virtual-machine obfuscation.
It is used to protect critical components such as PatchGuard and licensing information from reverse engineers.

WarBird functionality is also exposed through the `NtQuerySystemInformation` system call when supplied with the `SystemControlFlowTransition` (185) information class.  It dispatches to `WbDispatchOperation` where it supports functionality to decrypt and execute a signed feistel cipher payload on the heap.  More information regarding it can be found in [Alex Ionescu's talk](https://www.youtube.com/watch?v=gu_i6LYuePg).  Other research has provided insight in its usage to protect [client licensing](https://github.com/NtTuna/SystemPolicyInfo) and [code integrity](https://github.com/airbus-seclab/warbirdvm) images.

Given its prevalent usage by Microsoft, one should be curious enough to investigate whether any references are found in the MSVC compiler.  String references can be discovered in the backend compiler (`c2.dll`) and linker (`link.exe`) images. 

In `ProcessLinkerSwitches`, there are four linker flags related to WarBird: `/wbrdcfg`, `/wbrddll`, `/wbrdlog`, and `/wbrdschema` with options to test encryption or to provide a log schema.

If the configuration and dll WarBird linker flags are supplied during the building process of the executable then it will call `Warbird::CWarbirdServer::CreateObfuscator2`.  The routine will load the DLL supplied by the flag and call an exported function named `CreateObfuscator2` with the linker flag arguments, the machine type and the obfuscator base.

Other WarBird function names reveals that there are code transformations similar to the ones mentioned earlier.
```cpp
void __fastcall Enclave::CObfuscationEnclave::Initialize(Enclave::CObfuscationEnclave *this)
{
  if ( (int)Enclave::CEnclave::AddRuntimeSymbol((__int64)this, (__int64)"NtQuerySystemInformation", 0, 2) >= 0
    && (int)Enclave::CEnclave::AddRuntimeSymbol((__int64)this, (__int64)"WarbirdRuntime::EnclaveWrapper", 1, 1) >= 0 )
  {
    Enclave::CEnclave::AddRuntimeSymbol((__int64)this, (__int64)"WarbirdRuntime::g_ulSubSystemCallID", 2, 3);
  }
}
```

## Example
```powershell
cl /Zi .\example\main.cpp /link /wbrddll:warbird-obfuscate.dll /wbrdcfg:wbrd.cfg
```

## References
- [Warbird Runtime Reversed Engineered Code](https://github.com/KiFilterFiberContext/microsoft-warbird/)

## Compiler Info
- `cl.exe: aa9374078fcdce84bca034fd1bb395fdd3825614656e898017435ced17ff1061`
- `link.exe: 849e7bd1f234957b5e9be65f94a864e45ea4e05fea598b2164523b398603f615`
- Version: `14.28.29336.0`
