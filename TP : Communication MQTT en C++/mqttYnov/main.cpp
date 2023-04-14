#include <QCoreApplication> // Including the QCoreApplication library to create a Qt Core application
#include <QtMqtt/QMqttClient> // Including the QMqttClient library to use an MQTT client
#include <QDebug> // Including the qDebug library to display debug messages

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv); // Creating an instance of Qt Core application

    QMqttClient client; // Creating an MQTT client

    // Configuring MQTT client connection parameters
    client.setHostname("broker.emqx.io"); // Setting the MQTT broker host
    client.setPort(1883); // Setting the MQTT broker port
    client.setUsername("yanis"); // Setting the MQTT broker username
    client.setPassword("testynov"); // Setting the MQTT broker password

    QObject::connect(&client, &QMqttClient::connected, [&](void) {
        qDebug() << "Connected to MQTT broker.";

        QString topic = "/ynov/bordeaux/";
        qint32 qos = 0;
        if (!client.subscribe(topic, qos)) { // Subscribing to an MQTT topic
            qDebug() << "Error subscribing to topic:" << topic;
            return 1;
        } else {
            qDebug() << "Subscribed to topic:" << topic;
        }

        QString message = "AppYanis";
        if (!client.publish(topic, message.toUtf8(), qos)) { // Publishing an MQTT message
            qDebug() << "Published message:" << message << "to topic:" << topic;
            return 1;
        } else {
            qDebug() << "Error publishing message:" << message << "to topic:" << topic;
        }
    });

    QObject::connect(&client, &QMqttClient::messageReceived, [&](const QByteArray &message, const QMqttTopicName &topic) {
        qDebug() << "Received message:" << message << "from topic:" << topic.name();
    });

    client.connectToHost(); // Connecting to the MQTT broker

    return a.exec(); // Starting the Qt Core event loop
}
