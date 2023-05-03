#include <QCoreApplication> // Including the QCoreApplication library to create a Qt Core application
#include <QtMqtt/QMqttClient> // Including the QMqttClient library to use an MQTT client
#include <QDebug> // Including the qDebug library to display debug messages

int main(int argc_var, char *argv_t[])
{
    QCoreApplication A(argc_var, argv_t); // Creating an instance of Qt Core application

    QMqttClient Client; // Creating an MQTT client

    // Configuring MQTT client connection parameters
    Client.setHostname("broker.emqx.io"); // Setting the MQTT broker host
    Client.setPort(1883); // Setting the MQTT broker port
    Client.setUsername("yanis"); // Setting the MQTT broker username
    Client.setPassword("testynov"); // Setting the MQTT broker password

    QObject::connect(&Client, &QMqttClient::connected, [&](void) {
        qDebug() << "Connected to MQTT broker.";

        QString s_topic = "/ynov/bordeaux/";
        qint32 qos_var = 0;
        if (!Client.subscribe(s_topic, qos_var)) { // Subscribing to an MQTT topic
            qDebug() << "Error subscribing to topic:" << s_topic;
            return 1;
        } else {
            qDebug() << "Subscribed to topic:" << s_topic;
        }

        QString s_message = "AppYanis";
        if (!Client.publish(s_topic, s_message.toUtf8(), qos_var)) { // Publishing an MQTT message
            qDebug() << "Published message:" << s_message << "to topic:" << s_topic;
            return 1; //définir de préférence des constantes pour les retours, ca permet de rendre le code plus lisible
        } else {
            qDebug() << "Error publishing message:" << s_message << "to topic:" << s_topic;
        }
    });

    QObject::connect(&Client, &QMqttClient::messageReceived, [&](const QByteArray &message, const QMqttTopicName &topic) {
        qDebug() << "Received message:" << message << "from topic:" << topic.name();
    });

    Client.connectToHost(); // Connecting to the MQTT broker

    return A.exec(); // Starting the Qt Core event loop
}
