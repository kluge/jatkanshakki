#include <QtTest/QtTest>

#include <Board.h>

class RunLengthsTest : public QObject
{
    Q_OBJECT
private slots:
    void rowEmptyBoard();
    void rowSmallBoard();

    void colEmptyBoard();
    void colSmallBoard();

    void downwardDiagonal5x5Board();

    void upwardDiagonal5x5Board();
};

void RunLengthsTest::rowEmptyBoard()
{
    Board b{0};

    std::vector<RunLengths> runLengths = rowRunLengths(b);

    QCOMPARE(runLengths.size(), 0u);
}

void RunLengthsTest::rowSmallBoard()
{
    Board b{2};
    b(1,0) = X;
    b(1,1) = X;

    std::vector<RunLengths> runLengths = rowRunLengths(b);

    QCOMPARE(runLengths.size(), 2u);
    QCOMPARE(runLengths[0].size(), 1u);
    QCOMPARE(runLengths[1].size(), 1u);
    QCOMPARE(runLengths[0][0].square, Blank);
    QCOMPARE(runLengths[0][0].length, 2);
    QCOMPARE(runLengths[1][0].square, X);
    QCOMPARE(runLengths[1][0].length, 2);

    b = Board{2};
    b(0,0) = X;
    b(0,1) = O;
    b(1,0) = O;
    b(1,1) = X;

    runLengths = rowRunLengths(b);

    QCOMPARE(runLengths.size(), 2u);
    QCOMPARE(runLengths[0].size(), 2u);
    QCOMPARE(runLengths[1].size(), 2u);
    QCOMPARE(runLengths[0][0].square, X);
    QCOMPARE(runLengths[0][0].length, 1);
    QCOMPARE(runLengths[0][1].square, O);
    QCOMPARE(runLengths[0][1].length, 1);
    QCOMPARE(runLengths[1][0].square, O);
    QCOMPARE(runLengths[1][0].length, 1);
    QCOMPARE(runLengths[1][1].square, X);
    QCOMPARE(runLengths[1][1].length, 1);
}

void RunLengthsTest::colEmptyBoard()
{
    Board b{0};

    std::vector<RunLengths> runLengths = colRunLengths(b);

    QCOMPARE(runLengths.size(), 0u);
}

void RunLengthsTest::colSmallBoard()
{
    Board b{2};
    b(0,1) = X;
    b(1,1) = X;

    std::vector<RunLengths> runLengths = colRunLengths(b);

    QCOMPARE(runLengths.size(), 2u);
    QCOMPARE(runLengths[0].size(), 1u);
    QCOMPARE(runLengths[1].size(), 1u);
    QCOMPARE(runLengths[0][0].square, Blank);
    QCOMPARE(runLengths[0][0].length, 2);
    QCOMPARE(runLengths[1][0].square, X);
    QCOMPARE(runLengths[1][0].length, 2);

    b = Board{2};
    b(0,0) = X;
    b(1,0) = O;
    b(0,1) = O;
    b(1,1) = X;

    runLengths = colRunLengths(b);

    QCOMPARE(runLengths.size(), 2u);
    QCOMPARE(runLengths[0].size(), 2u);
    QCOMPARE(runLengths[1].size(), 2u);
    QCOMPARE(runLengths[0][0].square, X);
    QCOMPARE(runLengths[0][0].length, 1);
    QCOMPARE(runLengths[0][1].square, O);
    QCOMPARE(runLengths[0][1].length, 1);
    QCOMPARE(runLengths[1][0].square, O);
    QCOMPARE(runLengths[1][0].length, 1);
    QCOMPARE(runLengths[1][1].square, X);
    QCOMPARE(runLengths[1][1].length, 1);
}

void RunLengthsTest::downwardDiagonal5x5Board()
{
    Board b{5};

    std::vector<RunLengths> runLengths = downwardDiagonalRunLengths(b);

    QCOMPARE(runLengths.size(), 1u);
    QCOMPARE(runLengths[0].size(), 1u);
    QCOMPARE(runLengths[0][0].square, Blank);
    QCOMPARE(runLengths[0][0].length, 5);

    b = Board{5};
    b(0,0) = X;
    b(1,1) = X;
    b(2,2) = X;
    b(3,3) = X;
    b(4,4) = X;

    runLengths = downwardDiagonalRunLengths(b);

    QCOMPARE(runLengths.size(), 1u);
    QCOMPARE(runLengths[0].size(), 1u);
    QCOMPARE(runLengths[0][0].square, X);
    QCOMPARE(runLengths[0][0].length, 5);

    b = Board{5};
    b(0,0) = O;
    b(1,1) = O;
    b(2,2) = X;
    b(3,3) = X;
    b(4,4) = X;

    runLengths = downwardDiagonalRunLengths(b);

    QCOMPARE(runLengths.size(), 1u);
    QCOMPARE(runLengths[0].size(), 2u);
    QCOMPARE(runLengths[0][0].square, O);
    QCOMPARE(runLengths[0][0].length, 2);
    QCOMPARE(runLengths[0][1].square, X);
    QCOMPARE(runLengths[0][1].length, 3);
}

void RunLengthsTest::upwardDiagonal5x5Board()
{
    Board b{5};

    std::vector<RunLengths> runLengths = upwardDiagonalRunLengths(b);

    QCOMPARE(runLengths.size(), 1u);
    QCOMPARE(runLengths[0].size(), 1u);
    QCOMPARE(runLengths[0][0].square, Blank);
    QCOMPARE(runLengths[0][0].length, 5);

    b = Board{5};
    b(4,0) = X;
    b(3,1) = X;
    b(2,2) = X;
    b(1,3) = X;
    b(0,4) = X;

    runLengths = upwardDiagonalRunLengths(b);

    QCOMPARE(runLengths.size(), 1u);
    QCOMPARE(runLengths[0].size(), 1u);
    QCOMPARE(runLengths[0][0].square, X);
    QCOMPARE(runLengths[0][0].length, 5);

    b = Board{5};
    b(4,0) = O;
    b(3,1) = O;
    b(2,2) = X;
    b(1,3) = X;
    b(0,4) = X;

    runLengths = upwardDiagonalRunLengths(b);

    QCOMPARE(runLengths.size(), 1u);
    QCOMPARE(runLengths[0].size(), 2u);
    QCOMPARE(runLengths[0][0].square, O);
    QCOMPARE(runLengths[0][0].length, 2);
    QCOMPARE(runLengths[0][1].square, X);
    QCOMPARE(runLengths[0][1].length, 3);
}

QTEST_MAIN(RunLengthsTest)
#include "main.moc"
