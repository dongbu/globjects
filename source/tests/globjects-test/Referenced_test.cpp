
#include <gmock/gmock.h>


#include <globjects/base/Referenced.h>

class Referenced_test : public testing::Test
{
public:
};

class ReferencedMock : public glo::Referenced
{
public:
    MOCK_METHOD0(Die, void());
    virtual ~ReferencedMock() { Die(); }
};

TEST_F(Referenced_test, CountsReferences)
{
    glo::Referenced * ref = new glo::Referenced;

    EXPECT_EQ(ref->refCounter(), 0);
    ref->ref();
    EXPECT_EQ(ref->refCounter(), 1);

    ref->destroy();
}

TEST_F(Referenced_test, DeletesItself)
{
    ReferencedMock * ref = new ReferencedMock;

    // check if not referenced

    EXPECT_EQ(ref->refCounter(), 0);
    EXPECT_CALL(*ref, Die()).Times(1);
    ref->unref();

    // check if referenced

    ref = new ReferencedMock;
    ref->ref();
    EXPECT_EQ(ref->refCounter(), 1);
    EXPECT_CALL(*ref, Die()).Times(1);
    ref->unref();
}
