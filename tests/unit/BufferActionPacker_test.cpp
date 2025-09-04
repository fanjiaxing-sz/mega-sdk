#include "utils.h"
//#include "mega.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <mega/megaapp.h>
#include <mega/megaclient.h>

namespace
{
    //std::shared_ptr<mega::MegaClient> client;
    std::string json;
    std::string buffer;
#if 0
class BufferActionPacket_test : public testing::Test {
protected:
    void SetUp()
    {
        mega::MegaApp app;
        client = mt::makeClient(app);
    }

    std::shared_ptr<mega::MegaClient> client;
    std::string json;
    std::string buffer;
};
#endif

TEST(BufferActionPacket, the_start_isnot_ap)
{
    mega::MegaApp app;
    auto client = mt::makeClient(app);

    json = R"({"a":[{"a":"t","t":{"f":[{"a":"123","h":"MTIzNDU2"},{"b":"456","h":"MjM0NTY3"}]}}])";
    mega::BufferActionPacket bap(json.c_str(), client.get());
    buffer = bap.getBuffer();
    ASSERT_EQ(buffer, "");
}

TEST(BufferActionPacket, is_ap)
{
    mega::MegaApp app;
    auto client = mt::makeClient(app);

    json = R"([{"a":"s","t":{"f":[{"a":"123","h":"MTIzNDU2"},{"b":"456","h":"MjM0NTY3"}]}}])";
    std::string expected = R"([{"a":"s","t":{"f":[{"a":"123","h":"MTIzNDU2"},{"b":"456","h":"MjM0NTY3"}]}}])";
    mega::BufferActionPacket bap(json.c_str(), client.get());
    buffer = bap.getBuffer();
    ASSERT_EQ(buffer, expected);
}

TEST(BufferActionPacket, more_at_ap_end)
{
    mega::MegaApp app;
    auto client = mt::makeClient(app);

    json = R"([{"a":"s","t":{"f":[{"a":"123","h":"MTIzNDU2"},{"b":"456","h":"MjM0NTY3"}]}}]more)";
    std::string expected = R"([{"a":"s","t":{"f":[{"a":"123","h":"MTIzNDU2"},{"b":"456","h":"MjM0NTY3"}]}}])";
    mega::BufferActionPacket bap(json.c_str(), client.get());
    buffer = bap.getBuffer();
    ASSERT_EQ(buffer, expected);
}

TEST(BufferActionPacket, is_not_ap)
{
    mega::MegaApp app;
    auto client = mt::makeClient(app);

    json = R"([{"a":"a","t":{"f":[{"a":"123","h":"MTIzNDU2"},{"b":"456","h":"MjM0NTY3"}]}}])";
    mega::BufferActionPacket bap(json.c_str(), client.get());
    buffer = bap.getBuffer();
    ASSERT_EQ(buffer, "");
}

TEST(BufferActionPacket, is_t)
{
    mega::MegaApp app;
    auto client = mt::makeClient(app);

    json = R"([{"a":"t","t":{"f":[{"a":"123","h":"MTIzNDU2","t":0,"p":"MzQ1Njc4","k":"123","s":100},{"a":"456","h":"MjM0NTY3","t":0,"p":"MzQ1Njc4","k":"123","s":100}]}}])";
    mega::BufferActionPacket bap(json.c_str(), client.get());
    buffer = bap.getBuffer();
    ASSERT_EQ(buffer, "");
}

TEST(BufferActionPacket, more_at_t_end)
{
    mega::MegaApp app;
    auto client = mt::makeClient(app);

    json = R"([{"a":"t","t":{"f":[{"a":"123","h":"MTIzNDU2","t":0,"p":"MzQ1Njc4","k":"123","s":100},{"a":"456","h":"MjM0NTY3","t":0,"p":"MzQ1Njc4","k":"123","s":100}]}}]more)";
    mega::BufferActionPacket bap(json.c_str(), client.get());
    buffer = bap.getBuffer();
    ASSERT_EQ(buffer, "");
}

}
