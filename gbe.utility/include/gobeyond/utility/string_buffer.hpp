#pragma once

#include <cstdint>
#include <cstdio>
#include <cstring>

namespace gobeyond::utility 
{
  /**
   * @brief StringBuffer
   * 
   * A simple string buffer that can be used to store messages.
   * 
   * @tparam TBufferSize The size of the buffer
   * 
   * @since 0.1
   * 
   * @author t.schwarzinger@dina.de
   */
  template <std::size_t TBufferSize>
  class StringBuffer 
  {
    public:
      /// The buffer size
      static constexpr std::size_t buffer_size = TBufferSize;

      /**
       * @brief Constructor
       * 
       * Constructs a message with an empty string.
       * 
       * @since 0.1
       * 
       * @author t.schwarzinger@dina.de
       */
      StringBuffer() = default;

      /**
       * @brief Copy constructor
       * 
       * Constructs a message by copying the buffer of another message.
       * 
       * @param other The other message
       * 
       * @since 0.1
       * 
       * @author t.schwarzinger@dina.de
       */
      inline StringBuffer(const StringBuffer& other) noexcept 
      {
        std::memcpy(m_buffer, other.m_buffer, buffer_size);
      }

      /**
       * @brief Move constructor
       * 
       * Constructs a message by moving the buffer of another message.
       * 
       * @param other The other message
       * 
       * @since 0.1
       * 
       * @author t.schwarzinger@dina.de
       */
      inline StringBuffer(StringBuffer&& other) noexcept 
      {
        std::memcpy(m_buffer, other.m_buffer, buffer_size);
        std::memset(other.m_buffer, 0, buffer_size);
      }

      /**
       * @brief Constructor
       * 
       * Constructs a message with the given string.
       * 
       * @param s The string to store
       * 
       * @since 0.1
       * 
       * @author t.schwarzinger@dina.de
       */
      explicit inline StringBuffer(const char* s) 
      {
        if ( nullptr == s ) {
          std::snprintf(m_buffer, buffer_size, "");
          return;
        }
        
        std::snprintf(m_buffer, buffer_size, "%s", s);
      }

      /**
       * @brief Copy assignment
       * 
       * Assigns the buffer of another message to this message.
       * 
       * @param other The other message
       * 
       * @return The assigned message
       * 
       * @since 0.1
       * 
       * @author t.schwarzinger@dina.de
       */
      StringBuffer& operator=(const StringBuffer& other) 
      {
        std::memcpy(m_buffer, other.m_buffer, buffer_size);

        return *this;
      }

      /**
       * @brief Move assignment
       * 
       * Assigns the buffer of another message to this message.
       * 
       * @param other The other message
       * 
       * @return The assigned message
       * 
       * @since 0.1
       * 
       * @author t.schwarzinger@dina.de
       */
      StringBuffer& operator=(StringBuffer&& other) noexcept 
      {
        std::memcpy(m_buffer, other.m_buffer, buffer_size);
        std::memset(other.m_buffer, 0, buffer_size);

        return *this;
      }

      /**
       * @brief Implicit conversion to const char*
       * 
       * Converts the message to a const char*.
       * 
       * @return The message as a const char*
       * 
       * @todo Was on purpose implicit operator, but SonarLint did not 
       * allowed it. How to make sure that SonarLint, knows this is an 
       * explicitly wanted exception of its rule?
       * 
       * @since 0.1
       * 
       * @author t.schwarzinger@dina.de
       */
      [[nodiscard]] explicit operator const char*() const noexcept 
      {
        return m_buffer;
      }

      /**
       * @brief Format
       * 
       * Formats a message with the given format string.
       * 
       * @param fmt The format string
       * 
       * @return The formatted message
       * 
       * @since 0.1
       * 
       * @author t.schwarzinger@dina.de
       */
      [[nodiscard]] static StringBuffer format(const char* fmt) 
      {
        StringBuffer buffer;
        std::snprintf(buffer.m_buffer, buffer_size, "%s", fmt);

        return buffer;
      }

      /**
       * @brief Format
       * 
       * Formats a message with the given format string and arguments.
       * 
       * @tparam TArgs The argument types
       * 
       * @param fmt The format string
       * @param args The arguments
       * 
       * @return The formatted message
       * 
       * @since 0.1
       * 
       * @author t.schwarzinger@dina.de
       */
      template <typename... TArgs>
      [[nodiscard]] static StringBuffer format(const char* fmt, TArgs... args) 
      {
        StringBuffer buffer;
        std::snprintf(buffer.m_buffer, buffer_size, fmt, args...);

        return buffer;
      }

    private:
      /// The buffer
      char m_buffer[TBufferSize] = {0};
  };
}