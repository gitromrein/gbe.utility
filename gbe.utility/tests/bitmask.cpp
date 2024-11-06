#include <gtest/gtest.h>

#include <cstdint>

#include <gobeyond/utility/bitmask.hpp>

enum class LogLocation : std::uint32_t {
  NONE = 0,
  DEBUG = 1,
  LOGFILE = 2,
  MQTT = 4,
  BROWSER = 8,
  PUSHNOTIFICATION = 16,

  ALL = 31
};

TEST(BitMaskTest, Default) {
  gobeyond::utility::BitMask<LogLocation> mask;
  EXPECT_EQ(mask, LogLocation::NONE);
}

TEST(BitMaskTest, Construct) {
  gobeyond::utility::BitMask mask{LogLocation::DEBUG};
  EXPECT_EQ(mask, LogLocation::DEBUG);
}

TEST(BitMaskTest, Copy) {
  gobeyond::utility::BitMask mask1{LogLocation::DEBUG};
  gobeyond::utility::BitMask mask2{mask1};
  EXPECT_EQ(mask2, LogLocation::DEBUG);
}

TEST(BitMaskTest, ConstructOr) {
  using bitmask_type = gobeyond::utility::BitMask<LogLocation>;
  using underlying_type = std::underlying_type_t<LogLocation>;

  bitmask_type mask{LogLocation::DEBUG | LogLocation::LOGFILE};
  underlying_type expected = static_cast<underlying_type>(LogLocation::DEBUG) | static_cast<underlying_type>(LogLocation::LOGFILE);

  EXPECT_EQ(static_cast<underlying_type>(mask), expected);
}

TEST(BitMaskTest, ConstructOr2) {
  using bitmask_type = gobeyond::utility::BitMask<LogLocation>;
  using underlying_type = std::underlying_type_t<LogLocation>;

  bitmask_type mask{LogLocation::DEBUG | LogLocation::LOGFILE | LogLocation::MQTT};
  underlying_type expected = static_cast<underlying_type>(LogLocation::DEBUG) 
    | static_cast<underlying_type>(LogLocation::LOGFILE)
    | static_cast<underlying_type>(LogLocation::MQTT);

  EXPECT_EQ(static_cast<underlying_type>(mask), expected);
}

TEST(BitMaskTest, ConstructAnd) {
  using bitmask_type = gobeyond::utility::BitMask<LogLocation>;
  using underlying_type = std::underlying_type_t<LogLocation>;

  bitmask_type mask{LogLocation::ALL & LogLocation::LOGFILE};
  EXPECT_EQ(mask, LogLocation::LOGFILE);
}

TEST(BitMaskTest, Assign) {
  gobeyond::utility::BitMask<LogLocation> mask;
  mask = LogLocation::DEBUG;
  EXPECT_EQ(mask, LogLocation::DEBUG);
}

TEST(BitMaskTest, MaskOrMask) {
  using underlying_type = std::underlying_type_t<LogLocation>;

  gobeyond::utility::BitMask mask1{LogLocation::DEBUG};
  gobeyond::utility::BitMask mask2{LogLocation::LOGFILE};
  gobeyond::utility::BitMask mask3 = mask1 | mask2;

  underlying_type expected = static_cast<underlying_type>(LogLocation::DEBUG) | static_cast<underlying_type>(LogLocation::LOGFILE);
  EXPECT_EQ(static_cast<underlying_type>(mask3), expected);
}

TEST(BitMaskTest, MaskOrEnum) {
  using underlying_type = std::underlying_type_t<LogLocation>;

  gobeyond::utility::BitMask mask1{LogLocation::DEBUG};
  gobeyond::utility::BitMask mask2 = mask1 | LogLocation::LOGFILE;

  underlying_type expected = static_cast<underlying_type>(LogLocation::DEBUG) | static_cast<underlying_type>(LogLocation::LOGFILE);
  EXPECT_EQ(static_cast<underlying_type>(mask2), expected);
}

TEST(BitMaskTest, EnumOrMask) {
  using underlying_type = std::underlying_type_t<LogLocation>;

  gobeyond::utility::BitMask mask1{LogLocation::DEBUG};
  gobeyond::utility::BitMask mask2 = LogLocation::LOGFILE | mask1;

  underlying_type expected = static_cast<underlying_type>(LogLocation::DEBUG) | static_cast<underlying_type>(LogLocation::LOGFILE);
  EXPECT_EQ(static_cast<underlying_type>(mask2), expected);
}

TEST(BitMaskTest, MaskAndMask) {
  using bitmask_type = gobeyond::utility::BitMask<LogLocation>;
  using underlying_type = std::underlying_type_t<LogLocation>;

  bitmask_type mask1;
  mask1 = bitmask_type{LogLocation::DEBUG} | bitmask_type{LogLocation::LOGFILE};

  bitmask_type mask2 = mask1 & bitmask_type{LogLocation::LOGFILE};
  EXPECT_EQ(mask2, LogLocation::LOGFILE);
}

TEST(BitMaskTest, MaskAndEnum) {
  using bitmask_type = gobeyond::utility::BitMask<LogLocation>;
  using underlying_type = std::underlying_type_t<LogLocation>;

  bitmask_type mask1;
  mask1 = bitmask_type{LogLocation::DEBUG} | bitmask_type{LogLocation::LOGFILE};

  bitmask_type mask2 = mask1 & LogLocation::LOGFILE;
  EXPECT_EQ(mask2, LogLocation::LOGFILE);
}

TEST(BitMaskTest, EnumAndMask) {
  using bitmask_type = gobeyond::utility::BitMask<LogLocation>;
  using underlying_type = std::underlying_type_t<LogLocation>;

  bitmask_type mask1;
  mask1 = bitmask_type{LogLocation::DEBUG} | bitmask_type{LogLocation::LOGFILE};

  bitmask_type mask2 = LogLocation::LOGFILE & mask1;
  EXPECT_EQ(mask2, LogLocation::LOGFILE);
}

TEST(BitMaskTest, Enable) {
  using bitmask_type = gobeyond::utility::BitMask<LogLocation>;
  using underlying_type = std::underlying_type_t<LogLocation>;

  bitmask_type mask1;
  mask1.enable(LogLocation::DEBUG);

  EXPECT_EQ(mask1, LogLocation::DEBUG);
}

TEST(BitMaskTest, Disable) {
  using bitmask_type = gobeyond::utility::BitMask<LogLocation>;
  using underlying_type = std::underlying_type_t<LogLocation>;

  bitmask_type mask1;
  mask1 = bitmask_type{LogLocation::DEBUG} | bitmask_type{LogLocation::LOGFILE};
  mask1.disable(LogLocation::DEBUG);

  EXPECT_EQ(mask1, LogLocation::LOGFILE);
}

TEST(BitMaskTest, EnableAssign) {
  using bitmask_type = gobeyond::utility::BitMask<LogLocation>;
  using underlying_type = std::underlying_type_t<LogLocation>;

  bitmask_type mask1{LogLocation::DEBUG};
  mask1 = bitmask_type::Enable{LogLocation::MQTT};

  underlying_type expected = static_cast<underlying_type>(LogLocation::DEBUG) | static_cast<underlying_type>(LogLocation::MQTT);
  EXPECT_EQ(static_cast<underlying_type>(mask1), expected);
}

TEST(BitMaskTest, DisableAssign) {
  using bitmask_type = gobeyond::utility::BitMask<LogLocation>;
  using underlying_type = std::underlying_type_t<LogLocation>;

  bitmask_type mask1{LogLocation::DEBUG};
  mask1 = bitmask_type::Disable{LogLocation::DEBUG};

  EXPECT_EQ(mask1, LogLocation::NONE);
}

TEST(BitMaskTest, Enabled) {
  using bitmask_type = gobeyond::utility::BitMask<LogLocation>;
  using underlying_type = std::underlying_type_t<LogLocation>;

  bitmask_type mask1{LogLocation::DEBUG};
  bitmask_type mask2{LogLocation::LOGFILE};

  EXPECT_TRUE(mask1.isEnabled(LogLocation::DEBUG));
  EXPECT_FALSE(mask1.isEnabled(LogLocation::LOGFILE));
  EXPECT_TRUE(mask2.isEnabled(LogLocation::LOGFILE));
  EXPECT_FALSE(mask2.isEnabled(LogLocation::DEBUG));
}

TEST(BitMaskTest, Disabled) {
  using bitmask_type = gobeyond::utility::BitMask<LogLocation>;
  using underlying_type = std::underlying_type_t<LogLocation>;

  bitmask_type mask1{LogLocation::DEBUG};
  bitmask_type mask2{LogLocation::LOGFILE};

  EXPECT_FALSE(mask1.isDisabled(LogLocation::DEBUG));
  EXPECT_TRUE(mask1.isDisabled(LogLocation::LOGFILE));
  EXPECT_FALSE(mask2.isDisabled(LogLocation::LOGFILE));
  EXPECT_TRUE(mask2.isDisabled(LogLocation::DEBUG));
}

TEST(BitMaskTest, EnabledAssign) {
  using bitmask_type = gobeyond::utility::BitMask<LogLocation>;
  using underlying_type = std::underlying_type_t<LogLocation>;

  bitmask_type mask1{LogLocation::DEBUG};
  bitmask_type mask2{LogLocation::LOGFILE};

  EXPECT_TRUE(mask1 == bitmask_type::Enabled{LogLocation::DEBUG});
  EXPECT_FALSE(mask1 == bitmask_type::Enabled{LogLocation::LOGFILE});
  EXPECT_TRUE(mask2 == bitmask_type::Enabled{LogLocation::LOGFILE});
  EXPECT_FALSE(mask2 == bitmask_type::Enabled{LogLocation::DEBUG});
}

TEST(BitMaskTest, DisabledAssign) {
  using bitmask_type = gobeyond::utility::BitMask<LogLocation>;
  using underlying_type = std::underlying_type_t<LogLocation>;

  bitmask_type mask1{LogLocation::DEBUG};
  bitmask_type mask2{LogLocation::LOGFILE};

  EXPECT_FALSE(mask1 == bitmask_type::Disabled{LogLocation::DEBUG});
  EXPECT_TRUE(mask1 == bitmask_type::Disabled{LogLocation::LOGFILE});
  EXPECT_FALSE(mask2 == bitmask_type::Disabled{LogLocation::LOGFILE});
  EXPECT_TRUE(mask2 == bitmask_type::Disabled{LogLocation::DEBUG});
}

