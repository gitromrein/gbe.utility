#include <gtest/gtest.h>

#include <gobeyond/utility/version.hpp>

TEST(VersionTest, Constructor) {
    gobeyond::utility::Version v{1, 2, 3};
    EXPECT_EQ(v.major, 2);
    EXPECT_EQ(v.minor, 2);
    EXPECT_EQ(v.patch, 3);

    gobeyond::utility::Version v2{1, 2, 0};
    EXPECT_EQ(v2.major, 1);
    EXPECT_EQ(v2.minor, 2);
    EXPECT_EQ(v2.patch, 0);

    gobeyond::utility::Version v3{1, 0, 0};
    EXPECT_EQ(v3.major, 1);
    EXPECT_EQ(v3.minor, 0);
    EXPECT_EQ(v3.patch, 0);
}

TEST(VersionTest, Conversion) {
    gobeyond::utility::Version v{1, 2, 3};
    EXPECT_EQ(static_cast<std::uint32_t>(v), 10203);
}

TEST(VersionTest, Equality) {
    gobeyond::utility::Version v1{1, 2, 3};
    gobeyond::utility::Version v2{1, 2, 3};
    gobeyond::utility::Version v3{1, 2, 4};
    gobeyond::utility::Version v4{1, 3, 3};
    gobeyond::utility::Version v5{2, 2, 3};

    EXPECT_EQ(v1, v2);
    EXPECT_NE(v1, v3);
    EXPECT_NE(v1, v4);
    EXPECT_NE(v1, v5);
}

TEST(VersionTest, LessThan) {
    gobeyond::utility::Version v1{1, 2, 3};
    gobeyond::utility::Version v2{1, 2, 4};
    gobeyond::utility::Version v3{1, 3, 3};
    gobeyond::utility::Version v4{2, 2, 3};

    EXPECT_LT(v1, v2);
    EXPECT_LT(v1, v3);
    EXPECT_LT(v1, v4);
}

TEST(VersionTest, GreaterThan) {
    gobeyond::utility::Version v1{1, 2, 3};
    gobeyond::utility::Version v2{1, 2, 4};
    gobeyond::utility::Version v3{1, 3, 3};
    gobeyond::utility::Version v4{2, 2, 3};

    EXPECT_GT(v2, v1);
    EXPECT_GT(v3, v1);
    EXPECT_GT(v4, v1);
}

TEST(VersionTest, LessThanOrEqual) {
    gobeyond::utility::Version v1{1, 2, 3};
    gobeyond::utility::Version v2{1, 2, 4};
    gobeyond::utility::Version v3{1, 3, 3};
    gobeyond::utility::Version v4{2, 2, 3};

    EXPECT_LE(v1, v2);
    EXPECT_LE(v1, v3);
    EXPECT_LE(v1, v4);
    EXPECT_LE(v1, v1);
}

TEST(VersionTest, GreaterThanOrEqual) {
    gobeyond::utility::Version v1{1, 2, 3};
    gobeyond::utility::Version v2{1, 2, 4};
    gobeyond::utility::Version v3{1, 3, 3};
    gobeyond::utility::Version v4{2, 2, 3};

    EXPECT_GE(v2, v1);
    EXPECT_GE(v3, v1);
    EXPECT_GE(v4, v1);
    EXPECT_GE(v1, v1);
}

