#pragma once

#include <cstdint>

namespace gobeyond::utility 
{
  /**
   * @brief Version
   * 
   * The version of the library. This is a simple struct that contains 
   * the major, minor and patch version of the library. 
   * 
   * @since 0.1
   * 
   * @author
   */
  struct Version 
  {
    /**
     * @brief Constructor
     * 
     * Constructs a version with the given major, minor and patch version.
     * 
     * @param major The major version
     * @param minor The minor version (defaulted to 0)
     * @param patch The patch version (defaulted to 0)
     * 
     * @since 0.1
     * 
     * @author t.schwarzinger@dina.de
     */
    constexpr Version(std::uint8_t major, std::uint8_t minor, std::uint8_t patch)
      : major(major),
        minor(minor),
        patch(patch)
    {}

    /**
     * @brief Conversion to uint32_t
     * 
     * Converts the version to a uint32_t value. This is done by 
     * concatenating the major, minor and patch version to a single 
     * integer value.
     * 
     * @note uint32 = major * 100 * 100 + minor * 100 + patch
     * 
     * @return The version as a single integer value
     * 
     * @since 0.1
     * 
     * @author t.schwarzinger@dina.de
     */
    [[nodiscard]] constexpr explicit operator std::uint32_t() const noexcept 
    {
      return (major * 100 * 100) + (minor * 100) + patch;
    }

    /**
     * @brief Equality operator
     * 
     * Compares two versions for equality. Two versions are equal if 
     * their uint32_t representation is equal.
     * 
     * @param lhs The left hand side version
     * @param rhs The right hand side version
     * 
     * @return true if the versions are equal, false otherwise
     * 
     * @since 0.1
     * 
     * @author t.schwarzinger@dina.de
     */
    [[nodiscard]] friend constexpr bool operator==(const Version& lhs, const Version& rhs) noexcept 
    {
      return static_cast<std::uint32_t>(lhs) == static_cast<std::uint32_t>(rhs);
    }

    /**
     * @brief Inequality operator
     * 
     * Compares two versions for inequality. Two versions are not equal if
     * their uint32_t representation is not equal.
     * 
     * @param lhs The left hand side version
     * @param rhs The right hand side version
     * 
     * @return true if the versions are not equal, false otherwise
     * 
     * @since 0.1
     * 
     * @author t.schwarzinger@dina.de
     */
    [[nodiscard]] friend constexpr bool operator!=(const Version& lhs, const Version& rhs) noexcept 
    {
      return !(lhs == rhs);
    }

    /**
     * @brief Less than operator
     * 
     * Compares two versions for less than. A version is less than another 
     * version if its uint32_t representation is less than the other version.
     * 
     * @param lhs The left hand side version
     * @param rhs The right hand side version
     * 
     * @return true if the left hand side version is less than the right hand side version, false otherwise
     * 
     * @since 0.1
     * 
     * @author t.schwarzinger@dina.de
     */
    friend constexpr bool operator<(const Version& lhs, const Version& rhs) noexcept 
    {
      return static_cast<std::uint32_t>(lhs) < static_cast<std::uint32_t>(rhs);
    }

    /**
     * @brief Greater than operator
     * 
     * Compares two versions for greater than. A version is greater than another
     * version if its uint32_t representation is greater than the other version.
     * 
     * @param lhs The left hand side version
     * @param rhs The right hand side version
     * 
     * @return true if the left hand side version is greater than the right hand side version, false otherwise
     * 
     * @since 0.1
     * 
     * @author t.schwarzinger@dina.de
     */
    [[nodiscard]] friend constexpr bool operator>(const Version& lhs, const Version& rhs) noexcept 
    {
      return static_cast<std::uint32_t>(lhs) > static_cast<std::uint32_t>(rhs);
    }

    /**
     * @brief Less than or equal operator
     * 
     * Compares two versions for less than or equal. A version is less than or
     * equal to another version if its uint32_t representation is less than or
     * equal to the other version.
     * 
     * @param lhs The left hand side version
     * @param rhs The right hand side version
     * 
     * @return true if the left hand side version is less than or equal to the right hand side version, false otherwise
     * 
     * @since 0.1
     * 
     * @author t.schwarzinger@dina.de
     */
    [[nodiscard]] friend constexpr bool operator<=(const Version& lhs, const Version& rhs) noexcept 
    {
      return !(lhs > rhs);
    }

    /**
     * @brief Greater than or equal operator
     * 
     * Compares two versions for greater than or equal. A version is greater than
     * or equal to another version if its uint32_t representation is greater than
     * or equal to the other version.
     * 
     * @param lhs The left hand side version
     * @param rhs The right hand side version
     * 
     * @return true if the left hand side version is greater than or equal to the right hand side version, false otherwise
     * 
     * @since 0.1
     * 
     * @author t.schwarzinger@dina.de
     */
    [[nodiscard]] friend constexpr bool operator>=(const Version& lhs, const Version& rhs) noexcept 
    {
      return !(lhs < rhs);
    }

    /// Major version
    std::uint8_t major;
    /// Minor version
    std::uint8_t minor;
    /// Patch version
    std::uint8_t patch;
  };  
}