#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "Game.h"

int main(int argc, char *argv[])
{
    QGuiApplication app{argc, argv};

    QQmlApplicationEngine engine;
    Game game;
    engine.rootContext()->setContextProperty("game", &game);
    engine.load(QUrl{"qrc:/main.qml"});

    return app.exec();
}
