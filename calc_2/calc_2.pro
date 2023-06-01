QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    controllercalc.cc \
    controllercredit.cc \
    controllerdeposit.cc \
    controllerlistofwithdrawals.cc \
    controllerreplenishmentlist.cc \
    main.cc \
    modelcalc.cc \
    modelcredit.cc \
    modeldeposit.cc \
    modelvalidation.cc \
    qcustomplot.cpp

HEADERS += \
    controllercalc.h \
    controllercredit.h \
    controllerdeposit.h \
    controllerlistofwithdrawals.h \
    controllerreplenishmentlist.h \
    modelcalc.h \
    modelcredit.h \
    modeldeposit.h \
    modelvalidation.h \
    qcustomplot.h

FORMS += \
  veivcredit.ui \
  viev.ui \
  vievdeposit.ui \
  vievlistofwithdrawals.ui \
  vievreplenishmentlist.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
