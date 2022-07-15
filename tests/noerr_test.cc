#include <gtest/gtest.h>

extern "C"
{
#include "noerr.h"
}

TEST(NoErr, GetError)
{
    EXPECT_STREQ(get_error(ENOMEM), "Cannot allocate memory");
    EXPECT_STREQ(get_error(ENOTSOCK), "Socket operation on non-socket");
    EXPECT_STREQ(get_error(EPIPE), "Broken pipe");
}
