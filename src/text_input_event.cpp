#ifndef CENTURION_TEXT_INPUT_EVENT_SOURCE
#define CENTURION_TEXT_INPUT_EVENT_SOURCE

#include "event.hpp"

namespace centurion::event {

CENTURION_DEF
TextInputEvent::TextInputEvent() noexcept : CommonEvent{}
{}

CENTURION_DEF
TextInputEvent::TextInputEvent(const SDL_TextInputEvent& event) noexcept
    : CommonEvent{event}
{}

CENTURION_DEF
void TextInputEvent::set_window_id(Uint32 id) noexcept
{
  m_event.windowID = id;
}

CENTURION_DEF
auto TextInputEvent::window_id() const noexcept -> Uint32
{
  return m_event.windowID;
}

CENTURION_DEF
auto TextInputEvent::text() const noexcept -> gsl::czstring
{
  return m_event.text;
}

}  // namespace centurion::event

#endif  // CENTURION_TEXT_INPUT_EVENT_SOURCE