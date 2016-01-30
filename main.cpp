#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "Game.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    Game game(nullptr, engine.rootContext());
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
