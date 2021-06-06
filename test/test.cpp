#include "pch.h"

#include "../src/Mower.h"
#include "../src/Mower.cpp"
#include "../src/action.h"
#include "../src/lawn.h"
#include "../src/position.h"
#include "../src/direction.h"
#include "../src/FileReader.h"
#include "../src/FileReader.cpp"
#include "../src/MowingSimulation.h"
#include "../src/MowingSimulation.cpp"
#include "../src/Except.h"

/***TEST MOWER***/
TEST(MowerConstruction, MowerConstructionWithActions) {
    Position p;
    p.x = 0;
    p.y = 0;
    Mower mower(p, Direction::N);

    ASSERT_EQ(mower.pos.x, 0);
}



/***TEST FILE READER***/
TEST(FileReading, FileNotFound) {
    FileReader fr("../data/test_file_doesnt_exist.txt");
    vector<Mower> mowers;
    Lawn lawn;

    EXPECT_THROW(fr.read(mowers, lawn), Except);
}

TEST(FileReading, NoError) {
    FileReader fr("../data/test_file_no_error.txt");
    vector<Mower> mowers;
    Lawn lawn;

    fr.read(mowers, lawn);

    ASSERT_EQ(mowers[0].pos.x, 1);
    ASSERT_EQ(mowers[0].pos.y, 2);
    ASSERT_EQ(mowers[0].dir, Direction::N);
    ASSERT_EQ(mowers[0].actions[0], Action::L);

    ASSERT_EQ(lawn.xTopRight, 5);
    ASSERT_EQ(lawn.yTopRight, 5);

}

TEST(FileReading, ErrorPositionMower) {
    FileReader fr("../data/test_file_error_mower_pos.txt");
    vector<Mower> mowers;
    Lawn lawn;

    EXPECT_THROW(fr.read(mowers, lawn), Except);
}

TEST(FileReading, ErrorDirectionMower) {
    FileReader fr("../data/test_file_error_mower_dir.txt");
    vector<Mower> mowers;
    Lawn lawn;

    EXPECT_THROW(fr.read(mowers, lawn), Except);
}

TEST(FileReading, ErrorNegativeValueLawn) {
    FileReader fr("../data/test_file_error_lawn.txt");
    vector<Mower> mowers;
    Lawn lawn;

    EXPECT_THROW(fr.read(mowers, lawn), Except);
}



/***TEST MOWING SIMULATION***/
TEST(MowingSimulation) {
    vector<Mower> mowers;
    Lawn lawn = { 5, 5 };

    Mower m;
    m.pos = { 1, 2 };
    m.dir = Direction::N;
    m.actions.push_back(Action::L);

    mowers.push_back(m);

    MowingSimulation ms(mowers, lawn);

    EXPECT_NO_THROW(ms.start());
}


TEST(MowingSimulation, MowerMoveWithoutCollisionAndInsideBorders) {
    vector<Mower> mowers;
    vector<Action> actions;

    Position p;
    p.x = 2;
    p.y = 2;
    Mower m(p, Direction::N);

    Action a = Action::F;
    actions.push_back(a);
    actions.push_back(a);

    m.actions = actions;

    Lawn l;
    l.xTopRight = 5;
    l.yTopRight = 5;

    mowers.push_back(m);
    MowingSimulation ms(mowers, l);
    ms.start();

    EXPECT_EQ(ms.mowers[0].pos.x, 2);
    EXPECT_EQ(ms.mowers[0].pos.y, 4);
}

TEST(MowingSimulation, MowerMoveOutsideBorders) {
    vector<Mower> mowers;
    vector<Action> actions;

    Position p;
    p.x = 0;
    p.y = 0;
    Mower m(p, Direction::E);

    Action a = Action::F;
    actions.push_back(a);
    actions.push_back(a);
    actions.push_back(a);
    actions.push_back(a);

    m.actions = actions;

    Lawn l = { 0, 0 };

    mowers.push_back(m);
    MowingSimulation ms(mowers, l);
    ms.start();

    EXPECT_EQ(ms.mowers[0].pos.x, 0);
    EXPECT_EQ(ms.mowers[0].pos.y, 0);
}

TEST(MowingSimulation, MowersCollision) {
    vector<Mower> mowers;
    Lawn lawn;
    FileReader fr("../data/test_race_condition.txt");
    fr.read(mowers, lawn);

    MowingSimulation ms(mowers, lawn);
    ms.start();

    EXPECT_EQ(ms.mowers[0].pos.x, 0);
    EXPECT_EQ(ms.mowers[0].pos.y, 1);

    EXPECT_EQ(ms.mowers[1].pos.x, 0);
    EXPECT_EQ(ms.mowers[1].pos.y, 2);
}