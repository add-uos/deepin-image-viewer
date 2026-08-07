// SPDX-FileCopyrightText: 2026 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later


#include <gtest/gtest.h>

class Types;

class TypesTest : public testing::Test
{
protected:
    virtual void SetUp() override;
    virtual void TearDown() override;
};

// SPDX-FileCopyrightText: 2026 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later
#include "types.h"

void TypesTest::SetUp()
{
}

void TypesTest::TearDown()
{
}

// 验证枚举值与预期一致
TEST_F(TypesTest, ImageTypeEnumValues)
{
    EXPECT_EQ(static_cast<int>(Types::NullImage), 0);
    EXPECT_EQ(static_cast<int>(Types::NormalImage), 1);
    EXPECT_EQ(static_cast<int>(Types::DynamicImage), 2);
    EXPECT_EQ(static_cast<int>(Types::SvgImage), 3);
    EXPECT_EQ(static_cast<int>(Types::MultiImage), 4);
    EXPECT_EQ(static_cast<int>(Types::DamagedImage), 5);
    EXPECT_EQ(static_cast<int>(Types::NonexistImage), 6);
}

TEST_F(TypesTest, StackPageEnumValues)
{
    EXPECT_EQ(static_cast<int>(Types::OpenImagePage), 0);
    EXPECT_EQ(static_cast<int>(Types::ImageViewPage), 1);
    EXPECT_EQ(static_cast<int>(Types::SliderShowPage), 2);
}

TEST_F(TypesTest, ItemRoleEnumValues)
{
    EXPECT_EQ(static_cast<int>(Types::ImageUrlRole), Qt::UserRole + 1);
    EXPECT_EQ(static_cast<int>(Types::FrameIndexRole), Qt::UserRole + 2);
    EXPECT_EQ(static_cast<int>(Types::ImageAngleRole), Qt::UserRole + 3);
}

// 验证构造函数(无父对象)与析构函数正常执行
TEST_F(TypesTest, ConstructorDefault_NoParent_HoldsNoParent)
{
    Types types;
    EXPECT_EQ(types.parent(), nullptr);
}

// 验证带父对象的构造函数正确建立父子关系
TEST_F(TypesTest, ConstructorWithParent_ParentGiven_HoldsParent)
{
    QObject parent;
    Types *child = new Types(&parent);
    ASSERT_TRUE(child != nullptr);
    EXPECT_EQ(child->parent(), &parent);
    delete child;
}
