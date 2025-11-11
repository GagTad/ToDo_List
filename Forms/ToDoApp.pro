QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    Executor.cpp \
    Lexer.cpp \
    Parser.cpp \
    ResponseFormatter.cpp \
    Task.cpp \
    TaskManager.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ExecutionResult.h \
    Executor.h \
    Lexer.h \
    ParsedCommand.h \
    Parser.h \
    ResponseFormatter.h \
    Task.h \
    TaskManager.h \
    Token.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

