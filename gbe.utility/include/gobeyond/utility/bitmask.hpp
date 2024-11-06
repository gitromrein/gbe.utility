#pragma once

#include <type_traits>

namespace gobeyond::utility 
{
  template <typename TEnum>
  class BitMask 
  {
    public:
      using enum_type = TEnum;
      using underlying_type = std::underlying_type_t<enum_type>;

      struct Enable 
      {
        enum_type value;

        explicit inline Enable(const enum_type& value)
          : value(value)
        {}
      };

      struct Disable 
      {
        enum_type value;

        explicit inline Disable(const enum_type& value)
          : value(value)
        {}
      };

      struct Enabled 
      {
        enum_type value;

        explicit inline Enabled(const enum_type& value)
          : value(value)
        {}
      };

      struct Disabled 
      {
        enum_type value;

        explicit inline Disabled(const enum_type& value)
          : value(value)
        {}
      };

      inline BitMask()
        : m_value(static_cast<underlying_type>(enum_type()))
      {}

      explicit inline BitMask(const enum_type& value)
        : m_value(static_cast<underlying_type>(value))
      {}

      inline BitMask(const BitMask& other) noexcept
        : m_value(other.m_value)
      {}

      inline void enable(const enum_type& value) noexcept 
      {
        m_value |= static_cast<underlying_type>(value);
      }

      inline void disable(const enum_type& value) noexcept 
      {
        m_value &= ~static_cast<underlying_type>(value);
      }

      inline bool isEnabled(const enum_type& value) const noexcept 
      {
        return (m_value & static_cast<underlying_type>(value)) == static_cast<underlying_type>(value);
      }

      inline bool isDisabled(const enum_type& value) const noexcept 
      {
        return (m_value & static_cast<underlying_type>(value)) == 0;
      }

      inline BitMask& operator=(const BitMask& other) noexcept 
      {
        m_value = other.m_value;
        return *this;
      }

      inline BitMask& operator=(const enum_type& value) noexcept 
      {
        m_value = static_cast<underlying_type>(value);
        return *this;
      }

      inline BitMask& operator=(const Enable& flag) noexcept 
      {
        enable(flag.value);
        return *this;
      }

      inline BitMask& operator=(const Disable& flag) noexcept 
      {
        disable(flag.value);
        return *this;
      }

      explicit inline operator underlying_type() const noexcept 
      {
        return static_cast<underlying_type>(m_value);
      }

      friend inline bool operator==(const BitMask& lhs, const BitMask& rhs) noexcept 
      {
        return static_cast<underlying_type>(lhs) == static_cast<underlying_type>(rhs);
      }

      friend inline bool operator==(const BitMask& lhs, const enum_type& rhs) noexcept 
      {
        return static_cast<underlying_type>(lhs) == static_cast<underlying_type>(rhs);
      }

      friend inline bool operator==(const BitMask& lhs, const Enabled& rhs) noexcept 
      {
        return lhs.isEnabled(rhs.value);
      }

      friend inline bool operator==(const BitMask& lhs, const Disabled& rhs) noexcept 
      {
        return lhs.isDisabled(rhs.value);
      }

      friend inline bool operator!=(const BitMask& lhs, const BitMask& rhs) noexcept 
      {
        return !(lhs == rhs);
      }

      friend inline bool operator!=(const BitMask& lhs, const enum_type& rhs) noexcept 
      {
        return !(lhs == rhs);
      }

      friend inline BitMask operator|(const BitMask& lhs, const BitMask& rhs) noexcept 
      {
        return BitMask(static_cast<underlying_type>(lhs) | static_cast<underlying_type>(rhs));
      }

      friend inline BitMask operator|(const BitMask& lhs, const enum_type& rhs) noexcept 
      {
        return BitMask(static_cast<underlying_type>(lhs) | static_cast<underlying_type>(rhs));
      }

      friend inline BitMask operator|(const enum_type& lhs, const BitMask& rhs) noexcept 
      {
        return BitMask(static_cast<underlying_type>(lhs) | static_cast<underlying_type>(rhs));
      }

      friend inline BitMask operator&(const BitMask& lhs, const BitMask& rhs) noexcept 
      {
        return BitMask(static_cast<underlying_type>(lhs) & static_cast<underlying_type>(rhs));
      }

      friend inline BitMask operator&(const BitMask& lhs, const enum_type& rhs) noexcept 
      {
        return BitMask(static_cast<underlying_type>(lhs) & static_cast<underlying_type>(rhs));
      }

      friend inline BitMask operator&(const enum_type& lhs, const BitMask& rhs) noexcept 
      {
        return BitMask(static_cast<underlying_type>(lhs) & static_cast<underlying_type>(rhs));
      }

    protected:
      inline explicit BitMask(const underlying_type& value)
        : m_value(value)
      {}

    private:
      underlying_type m_value;
  };
}

template <typename TEnum, typename = std::enable_if_t<std::is_enum_v<TEnum>>>
[[nodiscard]] inline gobeyond::utility::BitMask<TEnum> operator|(const TEnum& lhs, const TEnum& rhs) noexcept {
  return gobeyond::utility::BitMask<TEnum>(lhs) | rhs;
}

template <typename TEnum, typename = std::enable_if_t<std::is_enum_v<TEnum>>>
[[nodiscard]] inline gobeyond::utility::BitMask<TEnum> operator&(const TEnum& lhs, const TEnum& rhs) noexcept {
  return gobeyond::utility::BitMask<TEnum>(lhs) & rhs;
}