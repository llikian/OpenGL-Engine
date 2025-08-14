/***************************************************************************************************
 * @file  EventHandler.hpp
 * @brief Declaration of the EventHandler class
 **************************************************************************************************/

#pragma once

#include <functional>
#include <queue>
#include <unordered_map>
#include "assets/Camera.hpp"
#include "maths/vec2.hpp"

using Action = std::function<void()>;

/**
 * @class EventHandler
 * @brief Handles all events.
 */
class EventHandler {
public:
    EventHandler(const EventHandler&) = delete;            ///< Delete copy constructor.
    EventHandler& operator=(const EventHandler&) = delete; ///< Deleted copy operator.

    static EventHandler& get() {
        static EventHandler event_handler;
        return event_handler;
    }

    /**
     * @brief Associates an action to the press of a key.
     * @param key The key to press in order to perform the action.
     * @param repeatable Whether the action is repeated when holding down the key.
     * @param action What happens when the key is pressed.
     */
    static void associate_action_to_key(int key, bool repeatable, const Action& action) {
        get().do_associate_action_to_key(key, repeatable, action);
    }

    /**
     * @brief Destroys the action associated to a key and if the key is repeatable, removes it from
     * the map.
     * @param key The key whose action we want to dissociate.
     */
    static void dissociate_key_action(int key) {
        get().do_dissociate_key_action(key);
    }

    /**
     * @brief Polls GLFW events, handles all of them and updates all event related variables.
     */
    static void poll_and_handle_events() {
        get().do_poll_and_handle_events();
    }

    /**
     * @brief Changes the active camera.
     * @param camera The new active camera.
     */
    static void set_active_camera(Camera* camera) {
        get().do_set_active_camera(camera);
    }

    /**
     * @brief Handles what happens when the window is resized.
     * @param width The window's new width.
     * @param height The window's new height.
     */
    static void handle_window_size_event(int width, int height) {
        get().do_handle_window_size_event(width, height);
    }

    /**
     * @brief Handles what happens when the frambuffer is resized.
     * @param width The framebuffer's new width.
     * @param height The framebuffer's new height.
     */
    static void handle_framebuffer_size_event(int width, int height) {
        get().do_handle_framebuffer_size_event(width, height);
    }

    /**
     * @brief Handles what happens when a key is pressed.
     * @param key The pressed key.
     */
    static void handle_key_press_event(int key) {
        get().do_handle_key_press_event(key);
    }

    /**
     * @brief Handles what happens when a key is released.
     * @param key The pressed key.
     */
    static void handle_key_release_event(int key) {
        get().do_handle_key_release_event(key);
    }

    /**
     * @brief Handles what happens when the mouse is moved.
     * @param position_x The mouse's new horizontal position.
     * @param position_y The mouse's new vertical position.
     */
    static void handle_cursor_position_event(int position_x, int position_y) {
        get().do_handle_cursor_position_event(position_x, position_y);
    }

    /**
     * @return The position of the cursor of the mouse on the window.
     */
    static vec2 get_mouse_position() { return get().mouse_position; }

    /**
     * @return How much time elapsed since the beginning of the program.
     */
    static float get_time() { return get().time; }

    /**
     * @return  How much time passed since the last frame.
     */
    static float get_delta() { return get().delta; }

    /**
     * @return Whether the mouse's cursor is visible.
     */
    static bool is_cursor_visible() { return get().b_is_cursor_visible; }

    /**
     * @return Whether face culling is enabled.
     */
    static bool is_face_culling_enabled() { return get().b_is_face_culling_enabled; }

    /**
     * @return Whether wireframe mode is enabled.
     */
    static bool is_wireframe_enabled() { return get().b_is_wireframe_enabled; }

private:
    /**
     * @brief Creates an event handler.
     */
    explicit EventHandler();

    /**
     * @brief Destructor.
     */
    ~EventHandler() = default;

    /**
     * @brief Associates an action to the press of a key.
     * @param key The key to press in order to perform the action.
     * @param repeatable Whether the action is repeated when holding down the key.
     * @param action What happens when the key is pressed.
     */
    void do_associate_action_to_key(int key, bool repeatable, const Action& action);

    /**
     * @brief Destroys the action associated to a key and if the key is repeatable, removes it from
     * the map.
     * @param key The key whose action we want to dissociate.
     */
    void do_dissociate_key_action(int key);

    /**
     * @brief Polls GLFW events, handles all of them and updates all event related variables.
     */
    void do_poll_and_handle_events();

    /**
     * @brief Changes the active camera.
     * @param camera The new active camera.
     */
    void do_set_active_camera(Camera* camera);

    /**
     * @brief Handles what happens when the window is resized.
     * @param width The window's new width.
     * @param height The window's new height.
     */
    void do_handle_window_size_event(int width, int height);

    /**
     * @brief Handles what happens when the frambuffer is resized.
     * @param width The framebuffer's new width.
     * @param height The framebuffer's new height.
     */
    void do_handle_framebuffer_size_event(int width, int height);

    /**
     * @brief Handles what happens when a key is pressed.
     * @param key The pressed key.
     */
    void do_handle_key_press_event(int key);

    /**
     * @brief Handles what happens when a key is released.
     * @param key The pressed key.
     */
    void do_handle_key_release_event(int key);

    /**
     * @brief Handles what happens when the mouse is moved.
     * @param position_x The mouse's new horizontal position.
     * @param position_y The mouse's new vertical position.
     */
    void do_handle_cursor_position_event(int position_x, int position_y);

    std::unordered_map<int, Action> key_actions;   ///< Stores the action associated with each key.
    std::unordered_map<int, bool> repeatable_keys; ///< Stores repeatable keys and whether they are active.

    vec2 mouse_position; ///< The position of the cursor of the mouse on the window.

    float time;  ///< How much time elapsed since the beginning of the program.
    float delta; ///< How much time passed since the last frame.

    Camera* active_camera; ///< A pointer to the active camera.

    bool b_is_cursor_visible;       ///< Whether the mouse's cursor is visible.
    bool b_is_face_culling_enabled; ///< Whether face culling is enabled.
    bool b_is_wireframe_enabled;    ///< Whether wireframe mode is enabled.
};
