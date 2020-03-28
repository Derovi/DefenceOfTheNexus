#include "gtest/gtest.h"
#include "src/core/serializer.h"
#include <iostream>

TEST(Object, Simple) {
    QVector<QPointF> my_vec;
    my_vec.push_back(QPointF(34, 34));
    core::Object my_obj(42, QPointF(42, 42), QPolygonF(my_vec), 42);
    core::Object second_obj(42 * 2, QPointF(42, 42 * 2), QPolygonF(my_vec));
    QString serialized;
    core::Serializer ser;
    ser.serialize(my_obj, serialized);
    //std::cout<<serialized.toStdString();
    EXPECT_EQ(ser.deserialize(second_obj, serialized), true);
    EXPECT_EQ(my_obj.getId(), second_obj.getId());
    EXPECT_EQ(my_obj.getHitbox(), second_obj.getHitbox());
    core::Moving my_mov(QVector2D(0, 0), 0, 0);
    ser.serialize(my_mov, serialized);
    //std::cout << serialized.toStdString();
    EXPECT_TRUE(ser.deserialize(my_mov, serialized));
    core::Resource my_res(core::ResourceType::kStone, 42);
    ser.serialize(my_res, serialized);
    EXPECT_TRUE(ser.deserialize(my_res, serialized));
    core::Damageable my_damag(42, 43);
    ser.serialize(my_damag, serialized);
    EXPECT_TRUE(ser.deserialize(my_damag, serialized));
    EXPECT_EQ(my_damag.getMaxHealth(), 43);
    //std::cout << endl;
    core::ResourceBundle my_bundle(my_obj.getId(), my_res.getType(), my_damag.getMaxHealth(),
                                   my_obj.getPosition(), my_obj.getHitbox(),
                                   my_obj.getRotationAngle());
    ser.serialize(my_bundle, serialized);
    EXPECT_TRUE(ser.deserialize(my_bundle, serialized));
    core::Building my_build(my_obj.getId(), my_obj.getPosition(), my_obj.getHitbox(),
                            my_obj.getRotationAngle(), core::Damageable());
    ser.serialize(my_build, serialized);
    EXPECT_TRUE(ser.deserialize(my_build, serialized));
    core::Damaging my_damaging(42, 43, 45, "kek");
    ser.serialize(my_damaging, serialized);
    EXPECT_TRUE(ser.deserialize(my_damaging, serialized));
    EXPECT_EQ(my_damaging.getAttackRadius(), 43);
    core::Unit my_unit(my_obj.getId(), my_obj.getPosition(), my_obj.getHitbox(),
                       my_obj.getRotationAngle(), core::Moving(), core::Damaging(),
                       core::Damageable());
    ser.serialize(my_unit, serialized);

    EXPECT_TRUE(ser.deserialize(my_unit, serialized));

    std::cout << serialized.toStdString();

}
