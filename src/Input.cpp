#include "Input.h"

#include <cstring>

extern bool run;

Input::Input(SDL_Window* window)
{
    this->window = window;
    Initialize();
}

Input::~Input()
{
    Shutdown(window);
}

bool Input::Initialize()
{
    if (m_initialized)
        return true;

    if (!SDL_InitSubSystem(SDL_INIT_GAMEPAD))
    {
        SDL_Log("Failed to initialize gamepad subsystem: %s", SDL_GetError());
        return false;
    }

    m_currentKeyboardState = SDL_GetKeyboardState(nullptr);
    memcpy(m_previousKeyboardState, m_currentKeyboardState, sizeof(m_previousKeyboardState));

    m_initialized = true;
    return true;
}

void Input::Shutdown(SDL_Window* window)
{
    if (!m_initialized)
        return;

    StopTextInput();

    m_initialized = false;
}

void Input::Update()
{
    memcpy(m_previousKeyboardState, m_currentKeyboardState, sizeof(m_previousKeyboardState));
    m_previousMouseButtons = m_currentMouseButtons;
    m_previousMouseX = m_mouseX;
    m_previousMouseY = m_mouseY;

    m_mouseWheel = 0;

    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        ProcessEvent(event);
    }

    UpdateKeyboard();
    UpdateMouse();
}

void Input::ProcessEvent(const SDL_Event& event)
{
    switch (event.type)
    {
    case SDL_EVENT_QUIT:
        run = false;
        break;

    case SDL_EVENT_KEY_DOWN:
    case SDL_EVENT_KEY_UP:
 
        break;

    case SDL_EVENT_MOUSE_MOTION:
        m_mouseX = event.motion.x;
        m_mouseY = event.motion.y;
        break;

    case SDL_EVENT_MOUSE_BUTTON_DOWN:
    case SDL_EVENT_MOUSE_BUTTON_UP:
        m_currentMouseButtons = SDL_GetMouseState(&m_mouseX, &m_mouseY);
        break;

    case SDL_EVENT_MOUSE_WHEEL:
        m_mouseWheel = event.wheel.y;
        break;

    case SDL_EVENT_TEXT_INPUT:
        m_textInput += event.text.text;
        break;
    }
}

void Input::UpdateKeyboard()
{
   
}

void Input::UpdateMouse()
{

    m_currentMouseButtons = SDL_GetMouseState(&m_mouseX, &m_mouseY);
}

bool Input::IsKeyDown(SDL_Keycode key) const
{
    SDL_Scancode scancode = SDL_GetScancodeFromKey(key, NULL);
    return m_currentKeyboardState[scancode];
}

bool Input::IsKeyPressed(SDL_Keycode key) const
{
    SDL_Scancode scancode = SDL_GetScancodeFromKey(key, NULL);
    return m_currentKeyboardState[scancode] && !m_previousKeyboardState[scancode];
}

bool Input::IsKeyReleased(SDL_Keycode key) const
{
    SDL_Scancode scancode = SDL_GetScancodeFromKey(key, NULL);
    return !m_currentKeyboardState[scancode] && m_previousKeyboardState[scancode];
}

bool Input::IsMouseButtonDown(Uint8 button) const
{
    return (m_currentMouseButtons & SDL_BUTTON_MASK(button)) != 0;
}

bool Input::IsMouseButtonPressed(Uint8 button) const
{
    Uint32 mask = SDL_BUTTON_MASK(button);
    return (m_currentMouseButtons & mask) && !(m_previousMouseButtons & mask);
}

bool Input::IsMouseButtonReleased(Uint8 button) const
{
    Uint32 mask = SDL_BUTTON_MASK(button);
    return !(m_currentMouseButtons & mask) && (m_previousMouseButtons & mask);
}

void Input::GetMousePosition(float& x, float& y) const
{
    x = m_mouseX;
    y = m_mouseY;
}

void Input::GetMouseDelta(float& dx, float& dy) const
{
    dx = m_mouseX - m_previousMouseX;
    dy = m_mouseY - m_previousMouseY;
}

float Input::GetMouseWheel() const
{
    return m_mouseWheel;
}

void Input::StartTextInput()
{
    if (!m_textInputActive)
    {
        SDL_StartTextInput(window);
        m_textInputActive = true;
        m_textInput.clear();
    }
}

void Input::StopTextInput()
{
    if (m_textInputActive)
    {
        SDL_StopTextInput(window);
        m_textInputActive = false;
    }
}

bool Input::IsTextInputActive() const
{
    return m_textInputActive;
}

const std::string& Input::GetTextInput() const
{
    return m_textInput;
}

// Tool Funcation
const char* Input::GetKeyName(SDL_Keycode key) const
{
    return SDL_GetKeyName(key);
}