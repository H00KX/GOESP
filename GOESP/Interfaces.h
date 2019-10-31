#pragma once

#include <sstream>
#include <type_traits>
#include <Windows.h>

class Client;
class DebugOverlay;
class Engine;
class EntityList;
class InputSystem;

class Interfaces {
public:
    Client* client = find<Client>(L"client_panorama", "VClient018");
    DebugOverlay* debugOverlay = find<DebugOverlay>(L"engine", "VDebugOverlay004");
    Engine* engine = find<Engine>(L"engine", "VEngineClient014");
    EntityList* entityList = find<EntityList>(L"client_panorama", "VClientEntityList003");
    InputSystem* inputSystem = find<InputSystem>(L"inputsystem", "InputSystemVersion001");
private:
    template <typename T>
    static auto find(const wchar_t* module, const char* name) noexcept
    {
        if (const auto createInterface = reinterpret_cast<std::add_pointer_t<T* __cdecl (const char* name, int* returnCode)>>(GetProcAddress(GetModuleHandleW(module), "CreateInterface")))
            if (T* foundInterface = createInterface(name, nullptr))
                return foundInterface;

        MessageBoxA(nullptr, (std::ostringstream{ } << "Failed to find " << name << " interface!").str().c_str(), "GOESP", MB_OK | MB_ICONERROR);
        std::exit(EXIT_FAILURE);
    }
};

extern const Interfaces interfaces;