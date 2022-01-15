#ifndef CENTURION_COMMON_HPP_
#define CENTURION_COMMON_HPP_

#include <SDL.h>

#ifndef CENTURION_NO_SDL_IMAGE
#include <SDL_image.h>
#endif  // CENTURION_NO_SDL_IMAGE

#ifndef CENTURION_NO_SDL_MIXER
#include <SDL_mixer.h>
#endif  // CENTURION_NO_SDL_MIXER

#ifndef CENTURION_NO_SDL_TTF
#include <SDL_ttf.h>
#endif  // CENTURION_NO_SDL_TTF

#include <chrono>       // duration
#include <exception>    // exception
#include <ostream>      // ostream
#include <ratio>        // ratio, milli, micro, nano
#include <string>       // string
#include <type_traits>  // underlying_type_t, enable_if_t, is_same_v, is_integral_v, ...

#include "features.hpp"
#include "memory.hpp"

#if CENTURION_HAS_FEATURE_CONCEPTS

#include <concepts>  // default_initializable, invocable

#endif  // CENTURION_HAS_FEATURE_CONCEPTS

#define CENTURION_DISABLE_COPY(Class) \
  Class(const Class&) = delete;       \
  Class& operator=(const Class&) = delete;

#define CENTURION_DISABLE_MOVE(Class) \
  Class(Class&&) = delete;            \
  Class& operator=(Class&&) = delete;

namespace cen {

/// \addtogroup core
/// \{

using uint = unsigned int;
using ulonglong = unsigned long long;

using uint8 = Uint8;
using uint16 = Uint16;
using uint32 = Uint32;
using uint64 = Uint64;

using int8 = Sint8;
using int16 = Sint16;
using int32 = Sint32;
using int64 = Sint64;

using unicode_t = uint16;

template <typename T>
using seconds = std::chrono::duration<T>;

template <typename T>
using millis = std::chrono::duration<T, std::milli>;

template <typename T>
using minutes = std::chrono::duration<T, std::ratio<60>>;

using u16ms = millis<uint16>;
using u32ms = millis<uint32>;
using u64ms = millis<uint64>;

#ifdef NDEBUG
inline constexpr bool is_debug_build = false;
inline constexpr bool is_release_build = true;
#else
inline constexpr bool is_debug_build = true;
inline constexpr bool is_release_build = false;
#endif  // NDEBUG

#ifdef _MSC_VER
inline constexpr bool on_msvc = true;
#else
inline constexpr bool on_msvc = false;
#endif  // _MSC_VER

#ifdef __GNUC__
inline constexpr bool on_gcc = true;
#else
inline constexpr bool on_gcc = false;
#endif  // __GNUC__

#ifdef __clang__
inline constexpr bool on_clang = true;
#else
inline constexpr bool on_clang = false;
#endif  // __clang__

template <typename T>
inline constexpr bool is_number =
    !std::is_same_v<T, bool> && (std::is_integral_v<T> || std::is_floating_point_v<T>);

template <typename T>
using RequirePointer = std::enable_if_t<std::is_pointer_v<T>, int>;

/// Enables a template if T is convertible to any of the specified types.
template <typename T, typename... Args>
using RequireConvertible = std::enable_if_t<(std::is_convertible_v<T, Args> || ...), int>;

template <typename T>
using RequireEnum = std::enable_if_t<std::is_enum_v<T>, int>;

template <typename T, RequirePointer<T> = 0>
using NotNull = T;

template <typename T, RequirePointer<T> = 0>
using Owner = T;

template <typename T, RequirePointer<T> = 0>
using MaybeOwner = T;

/// Converts an enum value to the underlying integral value.
template <typename Enum, RequireEnum<Enum> = 0>
[[nodiscard]] constexpr auto ToUnderlying(const Enum value) noexcept
    -> std::underlying_type_t<Enum>
{
  return static_cast<std::underlying_type_t<Enum>>(value);
}

/// Casts a value to a value of another type.
template <typename To, typename From>
[[nodiscard]] constexpr auto cast(const From& from) noexcept -> To
{
  return static_cast<To>(from);
}

/// Obtains the size of a container as an `int`.
template <typename T>
[[nodiscard]] constexpr auto isize(const T& container) noexcept(noexcept(container.size()))
    -> int
{
  return static_cast<int>(container.size());
}

/// Simply returns the string if it isn't null, returning a placeholder otherwise.
[[nodiscard]] inline auto str_or_na(const char* str) noexcept -> const char*
{
  return str ? str : "N/A";
}

class exception : public std::exception {
 public:
  exception() noexcept = default;

  explicit exception(const char* what) noexcept : mWhat{what ? what : "?"} {}

  [[nodiscard]] auto what() const noexcept -> const char* override { return mWhat; }

 private:
  const char* mWhat{"?"};
};

class sdl_error final : public exception {
 public:
  sdl_error() noexcept : exception{SDL_GetError()} {}

  explicit sdl_error(const char* what) noexcept : exception{what} {}
};

#ifndef CENTURION_NO_SDL_IMAGE

class img_error final : public exception {
 public:
  img_error() noexcept : exception{IMG_GetError()} {}

  explicit img_error(const char* what) noexcept : exception{what} {}
};

#endif  // CENTURION_NO_SDL_IMAGE

#ifndef CENTURION_NO_SDL_TTF

class ttf_error final : public exception {
 public:
  ttf_error() noexcept : exception{TTF_GetError()} {}

  explicit ttf_error(const char* what) noexcept : exception{what} {}
};

#endif  // CENTURION_NO_SDL_TTF

#ifndef CENTURION_NO_SDL_MIXER

class mix_error final : public exception {
 public:
  mix_error() noexcept : exception{Mix_GetError()} {}

  explicit mix_error(const char* what) noexcept : exception{what} {}
};

#endif  // CENTURION_NO_SDL_MIXER

/**
 * \brief A simple indicator for the result of different operations.
 *
 * \details The idea behind this class is to make results of various operations
 * unambiguous. Quite an amount of functions in the library may fail, and earlier versions
 * of Centurion would usually return a `bool` in those cases, where `true` and `false`
 * would indicate success and failure, respectively. This class is a development of that
 * practice. For instance, this class is contextually convertible to `bool`, where a
 * successful result is still converted to `true`, and vice versa. However, this class
 * also enables explicit checks against `success` and `failure` constants, which makes
 * code very easy to read and unambiguous.
 * \code{cpp}
 *   cen::window window;
 *
 *   if (window.SetOpacity(0.4f))
 *   {
 *     // Success!
 *   }
 *
 *   if (window.SetOpacity(0.4f) == cen::success)
 *   {
 *     // Success!
 *   }
 *
 *   if (window.SetOpacity(0.4f) == cen::failure)
 *   {
 *     // Failure!
 *   }
 * \endcode
 *
 * \see `success`
 * \see `failure`
 *
 * \since 6.0.0
 */
class Result final {
 public:
  /**
   * \brief Creates a result.
   *
   * \param success `true` if the result is successful; `false` otherwise.
   *
   * \since 6.0.0
   */
  constexpr Result(const bool success) noexcept  // NOLINT implicit
      : mSuccess{success}
  {}

  /* Indicates whether the result is successful. */
  [[nodiscard]] constexpr explicit operator bool() const noexcept { return mSuccess; }

 private:
  bool mSuccess{};
};

[[nodiscard]] constexpr auto operator==(const Result a, const Result b) noexcept -> bool
{
  return a.operator bool() == b.operator bool();
}

[[nodiscard]] constexpr auto operator!=(const Result a, const Result b) noexcept -> bool
{
  return !(a == b);
}

inline constexpr Result success{true};
inline constexpr Result failure{false};

#if CENTURION_HAS_FEATURE_CONCEPTS

template <typename T, typename... Args>
concept is_stateless_callable = std::default_initializable<T> && std::invocable<T, Args...>;

#endif  // CENTURION_HAS_FEATURE_CONCEPTS

[[nodiscard]] inline auto ToString(const Result result) -> std::string
{
  return result ? "success" : "failure";
}

inline auto operator<<(std::ostream& stream, const Result result) -> std::ostream&
{
  return stream << ToString(result);
}

namespace literals {
inline namespace time_literals {

#if SDL_VERSION_ATLEAST(2, 0, 18)

[[nodiscard]] constexpr auto operator""_ms(const ulonglong ms) -> u64ms
{
  return u64ms{static_cast<uint64>(ms)};
}

#else

[[nodiscard]] constexpr auto operator""_ms(const ulonglong ms) -> u32ms
{
  return u32ms{static_cast<uint32>(ms)};
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 18)

}  // namespace time_literals
}  // namespace literals
}  // namespace cen

#ifndef CENTURION_NO_SDL_NAMESPACE_ALIAS
namespace SDL = cen;
#endif  // CENTURION_NO_SDL_NAMESPACE_ALIAS

#endif  // CENTURION_COMMON_HPP_
