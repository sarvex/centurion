/*
 * MIT License
 *
 * Copyright (c) 2019-2020 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CENTURION_MESSAGE_BOX_HEADER
#define CENTURION_MESSAGE_BOX_HEADER

#include <SDL.h>

#include <optional>
#include <string>
#include <type_traits>
#include <vector>

#include "centurion_api.h"
#include "centurion_utils.h"
#include "color.h"

namespace centurion {
namespace messagebox {

/**
 * The ButtonDataHint enum class mirrors the SDL_MessageBoxButtonFlags enum.
 *
 * @since 3.0.0
 */
enum class ButtonDataHint {
  None = 0,
  ReturnKey = SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT,
  EscapeKey = SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT
};

/**
 * Indicates whether or not the flags represent the same value.
 *
 * @param a the lhs Centurion message box button data hint.
 * @param b the rhs SDL message box button data flags.
 * @return true if the values represent the same thing; false otherwise.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator==(ButtonDataHint a,
                              SDL_MessageBoxButtonFlags b) noexcept;

/**
 * Indicates whether or not the flags represent the same value.
 *
 * @param a the lhs SDL message box button data flags.
 * @param b the rhs Centurion message box button data hint.
 * @return true if the values represent the same thing; false otherwise.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator==(SDL_MessageBoxButtonFlags a,
                              ButtonDataHint b) noexcept;

/**
 * Indicates whether or not the flags don't represent the same value.
 *
 * @param a the lhs Centurion message box button data hint.
 * @param b the rhs SDL message box button data flags.
 * @return true if the values don't represent the same thing; false otherwise.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator!=(ButtonDataHint a,
                              SDL_MessageBoxButtonFlags b) noexcept;

/**
 * Indicates whether or not the flags don't represent the same value.
 *
 * @param a the lhs SDL message box button data flags.
 * @param b the rhs Centurion message box button data hint.
 * @return true if the values don't represent the same thing; false otherwise.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator!=(SDL_MessageBoxButtonFlags a,
                              ButtonDataHint b) noexcept;

/**
 * The ButtonData class represents the data associated with a message box
 * button.
 *
 * @since 3.0.0
 */
class ButtonData final {
 public:
  /**
   * @param hint the button data hint that will be used.
   * @param id the ID of the button.
   * @param text the text that will be displayed on the button.
   * @since 3.0.0
   */
  CENTURION_API
  ButtonData(ButtonDataHint hint, int id, std::string text);

  /**
   * Converts the button data into an SDL_MessageBoxButtonData instance.
   *
   * @return an SDL_MessageBoxButtonData instance.
   * @since 3.0.0
   */
  CENTURION_API
  operator SDL_MessageBoxButtonData() const noexcept;

 private:
  ButtonDataHint m_buttonDataHint;
  int m_id;
  std::string m_text;
};

/**
 * The ColorType enum class mirrors the SDL_MessageBoxColorType enum.
 *
 * @since 3.0.0
 */
enum class ColorType {
  Background = SDL_MESSAGEBOX_COLOR_BACKGROUND,
  ButtonBorder = SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
  ButtonBackground = SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
  ButtonSelected = SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
};

/**
 * Indicates whether or not the message box color types represent the same
 * value.
 *
 * @param a the lhs SDL message box color type.
 * @param b the rhs Centurion message box color type.
 * @return true if the color types represent the same value; false otherwise.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API
bool operator==(SDL_MessageBoxColorType a, ColorType b) noexcept;

/**
 * Indicates whether or not the message box color types represent the same
 * value.
 *
 * @param a the lhs Centurion message box color type.
 * @param b the rhs SDL message box color type.
 * @return true if the color types represent the same value; false otherwise.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API
bool operator==(ColorType a, SDL_MessageBoxColorType b) noexcept;

/**
 * Indicates whether or not the message box color types don't represent the same
 * value.
 *
 * @param a the lhs SDL message box color type.
 * @param b the rhs Centurion message box color type.
 * @return true if the color types don't represent the same value; false
 * otherwise.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API
bool operator!=(SDL_MessageBoxColorType a, ColorType b) noexcept;

/**
 * Indicates whether or not the message box color types don't represent the same
 * value.
 *
 * @param a the lhs Centurion message box color type.
 * @param b the rhs SDL message box color type.
 * @return true if the color types don't represent the same value; false
 * otherwise.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API
bool operator!=(ColorType a, SDL_MessageBoxColorType b) noexcept;

/**
 * The ColorScheme class is a simple wrapper around an SDL_MessageBoxColorScheme
 * struct.
 *
 * @since 3.0.0
 */
class ColorScheme final {
 public:
  /**
   * @since 3.0.0
   */
  CENTURION_API
  ColorScheme() noexcept;

  /**
   * Sets the color of a color scheme component.
   *
   * @param type the color scheme component that will be set.
   * @param color the color that will be used.
   * @since 3.0.0
   */
  CENTURION_API
  void set_color(ColorType type, const video::Color& color) noexcept;

  /**
   * Returns the internal SDL_MessageBoxColorScheme.
   *
   * @return the internal SDL_MessageBoxColorScheme.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  const SDL_MessageBoxColorScheme& get() const noexcept;

  /**
   * Converts the ColorScheme to an SDL_MessageBoxColorScheme.
   *
   * @return an SDL_MessageBoxColorScheme.
   * @since 3.0.0
   */
  CENTURION_API
  explicit operator SDL_MessageBoxColorScheme() const noexcept;

 private:
  SDL_MessageBoxColorScheme m_scheme{};

  /**
   * Returns the array index associated with the supplied color scheme type.
   *
   * @param type color scheme type to obtain the index for.
   * @return the array index associated with the supplied color scheme type.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  int index(ColorType type) const noexcept { return static_cast<int>(type); }
};

/**
 * The MessageBoxID enum class mirrors the values of the SDL_MessageBoxFlags
 * enum. It's safe to statically cast values of the SDL_MessageBoxFlags to
 * MessageBoxID values. It's also possible to compare MessageBoxID and
 * SDL_MessageBoxFlags values with the == and != operators.
 *
 * @since 3.0.0
 */
enum class MessageBoxID {
  Info = SDL_MESSAGEBOX_INFORMATION,
  Warning = SDL_MESSAGEBOX_WARNING,
  Error = SDL_MESSAGEBOX_ERROR
};

/**
 * Indicates whether or not two message box flag values are the same.
 *
 * @param a the lhs Centurion message box ID value.
 * @param b the rhs SDL message box flag value.
 * @return true if the values are the same; false otherwise.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API
bool operator==(MessageBoxID a, SDL_MessageBoxFlags b) noexcept;

/**
 * Indicates whether or not two message box flag values are the same.
 *
 * @param a the lhs SDL message box flag value.
 * @param b the rhs Centurion message box ID value.
 * @return true if the values are the same; false otherwise.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API
bool operator==(SDL_MessageBoxFlags a, MessageBoxID b) noexcept;

/**
 * Indicates whether or not two message box flag values aren't the same.
 *
 * @param a the lhs Centurion message box ID value.
 * @param b the rhs SDL message box flag value.
 * @return true if the values aren't the same; false otherwise.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API
bool operator!=(MessageBoxID a, SDL_MessageBoxFlags b) noexcept;

/**
 * Indicates whether or not two message box flag values aren't the same.
 *
 * @param a the lhs SDL message box flag value.
 * @param b the rhs Centurion message box ID value.
 * @return true if the values aren't the same; false otherwise.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API
bool operator!=(SDL_MessageBoxFlags a, MessageBoxID b) noexcept;

/**
 * The MessageBox class represents a modal message box that can be used display
 * information, warnings and errors.
 *
 * @since 3.0.0
 */
class MessageBox final {
 public:
  /**
   * @since 3.0.0
   */
  MessageBox() = default;

  /**
   * @param title the title of the message box, can be null.
   * @since 3.0.0
   */
  CENTURION_API
  explicit MessageBox(const char* title);

  /**
   * @param title the title of the message box, can be null.
   * @param message the message of the message box, can be null.
   * @since 3.0.0
   */
  CENTURION_API
  MessageBox(const char* title, const char* message);

  CENTURION_API
  ~MessageBox() noexcept;

  /**
   * Displays the message box. If no buttons have been added, the message box
   * will feature an "OK" button.
   *
   * @param window a pointer to the parent window, can safely be null to
   * indicate no parent.
   * @return the ID of the pressed button; -1 if no button was pressed.
   * @throws CenturionException if the message box cannot be displayed.
   * @since 3.0.0
   */
  CENTURION_API
  int show(SDL_Window* window = nullptr);

  /**
   * Creates and displays a message box. This method provides a simpler way to
   * create message boxes, compared to creating instances of the MessageBox
   * class.
   *
   * @param title the title of the message box window, can be null.
   * @param message the message of the message box window, can be null.
   * @param type the type of the message.
   * @param window a pointer to the parent window, can safely be null to
   * indicate no parent.
   * @since 3.0.0
   */
  CENTURION_API
  static void show(const char* title,
                   const char* message,
                   MessageBoxID type,
                   SDL_Window* window = nullptr) noexcept;

  /**
   * Adds a button to the message box.
   *
   * @param hint the data hint of the button.
   * @param id the ID of the button.
   * @param text the text of the button.
   * @since 3.0.0
   */
  CENTURION_API
  void add_button(ButtonDataHint hint, int id, std::string text) noexcept;

  /**
   * Sets the title of the message box.
   *
   * @param title the title of the message box, can be null.
   * @since 3.0.0
   */
  CENTURION_API
  void set_title(const char* title) noexcept;

  /**
   * Sets the message of the message box.
   *
   * @param message the message of the message box, can be null.
   * @since 3.0.0
   */
  CENTURION_API
  void set_message(const char* message) noexcept;

  /**
   * Sets what kind of message box the message box is. By default, this property
   * is set to MessageBoxID::Info.
   *
   * @param type the type of the message box.
   * @since 3.0.0
   */
  CENTURION_API
  void set_type(MessageBoxID type) noexcept;

  /**
   * Sets the color scheme that will be used by the message box. Color schemes
   * aren't supported on all platforms, so the default value is nullopt for
   * the color scheme.
   *
   * @param scheme the color scheme that will be used; nullopt indicates
   * that the system defaults should be used.
   * @since 3.0.0
   */
  CENTURION_API
  void set_color_scheme(Optional<ColorScheme> scheme) noexcept;

  /**
   * Returns the type of the message box.
   *
   * @return the type of the message box.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  MessageBoxID type() const noexcept;

 private:
  Optional<ColorScheme> m_colorScheme;
  std::vector<ButtonData> m_buttons;
  const char* m_title = "Centurion message box";
  const char* m_message = "N/A";
  MessageBoxID m_type = MessageBoxID::Info;

  /**
   * Creates and returns a vector of SDL_MessageBoxButtonData instances.
   *
   * @return a vector of SDL_MessageBoxButtonData instances.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  std::vector<SDL_MessageBoxButtonData> create_sdl_button_data() const noexcept;

  /**
   * Creates and returns an SDL_MessageBoxData based on the MessageBox.
   *
   * @param window the parent window, can safely be null.
   * @param data a pointer to the first element in the array of buttons.
   * @param scheme a pointer to the color scheme that will be used, set to null
   * by default.
   * @return an SDL_MessageBoxData based on the MessageBox.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  SDL_MessageBoxData create_sdl_message_box_data(
      SDL_Window* window,
      const SDL_MessageBoxButtonData* data,
      const SDL_MessageBoxColorScheme* scheme = nullptr) const noexcept;
};

#ifdef CENTURION_HAS_IS_FINAL_TYPE_TRAIT
static_assert(std::is_final<ButtonData>::value, "ButtonData isn't final!");
#endif

static_assert(std::is_nothrow_destructible<ButtonData>::value,
              "ButtonData isn't nothrow destructible!");

static_assert(std::is_convertible<ButtonData, SDL_MessageBoxButtonData>::value,
              "ButtonData isn't convertible to SDL_MessageBoxButtonData!");

#ifdef CENTURION_HAS_IS_FINAL_TYPE_TRAIT
static_assert(std::is_final<ColorScheme>::value, "ColorScheme isn't final!");
#endif

static_assert(std::is_nothrow_default_constructible<ColorScheme>::value,
              "ColorScheme isn't nothrow default constructible!");

static_assert(std::is_nothrow_destructible<ColorScheme>::value,
              "ColorScheme isn't nothrow destructible!");

}  // namespace messagebox
}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "message_box.cpp"
#endif

#endif  // CENTURION_MESSAGE_BOX_HEADER
