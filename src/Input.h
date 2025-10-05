#ifndef INPUT_H
#define INPUT_H

#include <SDL3/SDL.h>
#include <unordered_map>
#include <string>

class Input
{
public:

    SDL_Window* window;

    Input() { };
    Input(SDL_Window* window);
    ~Input();

    void Update();

    bool IsKeyDown(SDL_Keycode key) const;
    bool IsKeyPressed(SDL_Keycode key) const;
    bool IsKeyReleased(SDL_Keycode key) const;

    bool IsMouseButtonDown(Uint8 button) const;
    bool IsMouseButtonPressed(Uint8 button) const;
    bool IsMouseButtonReleased(Uint8 button) const;

    void GetMousePosition(float& x, float& y) const;
    void GetMouseDelta(float& dx, float& dy) const;
    float GetMouseWheel() const;

    void StartTextInput();
    void StopTextInput();
    bool IsTextInputActive() const;
    const std::string& GetTextInput() const;

    const char* GetKeyName(SDL_Keycode key) const;

private:
    bool Initialize();
    void Shutdown(SDL_Window* window);

    void ProcessEvent(const SDL_Event& event);
    void UpdateKeyboard();
    void UpdateMouse();

private:

    const bool* m_currentKeyboardState = nullptr;
    Uint8 m_previousKeyboardState[SDL_SCANCODE_COUNT] = { 0 };

    Uint32 m_currentMouseButtons = 0;
    Uint32 m_previousMouseButtons = 0;
    float m_mouseX = 0.0f;
    float m_mouseY = 0.0f;
    float m_previousMouseX = 0.0f;
    float m_previousMouseY = 0.0f;
    float m_mouseWheel = 0.0f;

    bool m_textInputActive = false;
    std::string m_textInput;

    bool m_initialized = false;
};

#endif