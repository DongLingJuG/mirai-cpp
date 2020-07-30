#include <mirai.h>
#include <gtest/gtest.h>

TEST(MessageChain_Test, Set_Plain) {
    using namespace Cyan;
    MessageChain mc;
    json j =
    {
        {{"type","Source"},{"time",1234},{"id",123456}},
        {{"type","Plain"},{"text","textsssss"}}
    };
    mc.Set(j);
    string text = mc.ToJson()[0]["text"];
    ASSERT_TRUE(text == "textsssss");
}

TEST(MessageChain_Test, Add_and_Get) {
    using namespace Cyan;
    MessageChain mc;
    mc.Add(PlainMessage("Hello"));
    auto m = mc.GetFirst<PlainMessage>();
    ASSERT_TRUE(m.GetText() == "Hello");
}

TEST(MessageChain_Test, GetAll) {
    using namespace Cyan;
    MessageChain mc;
    mc.Add(PlainMessage("Hello"));
    mc.Add(PlainMessage("Hi"));
    auto m = mc.GetAll<PlainMessage>();
    ASSERT_TRUE(m.size() == 2);
    ASSERT_TRUE(m[0].GetText() == "Hello");
    ASSERT_TRUE(m[1].GetText() == "Hi");
}

TEST(MessageChain_Test, Count) {
    using namespace Cyan;
    MessageChain mc;
    mc.Add(PlainMessage("Hello"));
    mc.Add(PlainMessage("Hi"));
    ASSERT_TRUE(mc.Count() == 2);
}

TEST(MessageChain_Test, get_at) {
    using namespace Cyan;
    MessageChain mc;
    mc.Add(PlainMessage("Hello"));
    mc.Add(PlainMessage("Hi"));
    ASSERT_TRUE(mc[0]->GetType() == "Plain");
    auto mptr = std::dynamic_pointer_cast<PlainMessage>(mc[1]);
    ASSERT_TRUE(mptr->GetText() == "Hi");
}

TEST(MessageChain_Test, Clear) {
    using namespace Cyan;
    MessageChain mc;
    mc.Add(PlainMessage("Hello"));
    mc.Add(PlainMessage("Hi"));
    mc.Clear();
    ASSERT_TRUE(mc.Count() == 0);
}

TEST(MessageChain_Test, Remove) {
    using namespace Cyan;
    MessageChain mc;
    mc.Add(PlainMessage("Hello"));
    mc.Add(PlainMessage("Hello"));
    mc.Add(PlainMessage("Hi"));
    mc.Remove(PlainMessage("Hello"));
    ASSERT_TRUE(mc.Count() == 1);
    auto mptr = std::dynamic_pointer_cast<PlainMessage>(mc[0]);
    ASSERT_TRUE(mptr->GetText() == "Hi");
}

TEST(MessageChain_Test, GetPlainText) {
    using namespace Cyan;
    MessageChain mc;
    mc.Plain("Number:").Plain(12345);
    string text = mc.GetPlainText();
    ASSERT_TRUE(text == "Number:12345");
}

TEST(MessageChain_Test, ImageMessage) {
    using namespace Cyan;
    MessageChain mc;
    MiraiImage img;
    img.ID = "{qweasd}.png";
    mc.Plain("Image:").Image(img);
    auto img_msg = mc.GetFirst<ImageMessage>();
    ASSERT_TRUE(img_msg.ToMiraiImage().ID == "{qweasd}.png");
}

TEST(MessageChain_Test, FlashImageMessage) {
    using namespace Cyan;
    MessageChain mc;
    MiraiImage img;
    img.ID = "{qweasd}.png";
    mc.Plain("Image:").FlashImage(img);
    auto img_msg = mc.GetFirst<FlashImageMessage>();
    ASSERT_TRUE(img_msg.ToMiraiImage().ID == "{qweasd}.png");
}

TEST(MessageChain_Test, AtMessage) {
    using namespace Cyan;
    MessageChain mc;
    mc.Add(AtMessage(1234_qq));
    auto at = mc.GetFirst<AtMessage>();
    ASSERT_TRUE(at.Target().QQ == 1234);
}

TEST(MessageChain_Test, AtAllMessage) {
    using namespace Cyan;
    MessageChain mc;
    mc.Add(AtAllMessage());
    auto at = mc.GetFirst<AtAllMessage>();
    ASSERT_TRUE(true);
}


TEST(ABC, TEST2) {
    ASSERT_TRUE(2 == 2);
}

TEST(ABC, TEST3) {
    ASSERT_TRUE(2 == 2);
}