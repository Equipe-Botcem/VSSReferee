#ifndef VISION_H
#define VISION_H

#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QReadWriteLock>

#include <src/utils/types/object/object.h>
#include <src/utils/types/color/color.h>
#include <src/world/entities/entity.h>
#include <src/constants/constants.h>

class Vision : public Entity
{
public:
    Vision(Constants *constants);
    ~Vision();

    // Getters
    QList<quint8> getAvailablePlayers(Colors::Color teamColor);
    Position getPlayerPosition(Colors::Color teamColor, quint8 playerId);
    Position getBallPosition();
    Velocity getBallVelocity();

private:
    // Entity inherited methods
    void initialization();
    void loop();
    void finalization();

    // Constants
    Constants *_constants;
    Constants* getConstants();

    // Socket to receive vision data
    QUdpSocket *_visionClient;
    void bindAndConnect();

    // Network
    QString _visionAddress;
    quint16 _visionPort;

    // Objects
    Object *_ballObject;
    QMap<Colors::Color, QHash<quint8, Object*>*> _objects;
    QMap<Colors::Color, QHash<quint8, bool>*> _objectsControl;
    void initObjects();
    void deleteObjects();
    void clearObjectsControl();

    // Data management
    QReadWriteLock _dataMutex;
};

#endif // VISION_H