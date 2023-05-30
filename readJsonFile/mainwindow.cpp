#include <QMap>
#include <QVariant>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include "mainwindow.h"


QMap<QString, QVariant>MainWindow:: extractJsonObject(const QString& prefix, const QJsonObject& jsonObject)
{
    QMap<QString, QVariant> ret;

    QStringList keys = jsonObject.keys();

    for (const QString& k : keys)
        {
            QString key = prefix.isEmpty() ? k : prefix + "_" + k;
            const QJsonValue& jsonVal = jsonObject.value(k);
            if (jsonVal.isNull()) {
                       ret[key] = "null";
                   } else if (jsonVal.isUndefined()) {
                       ret[key] = "undef";
                   } else if (jsonVal.isBool()) {
                       bool value = jsonVal.toBool();
                       ret[key] = value;
                   } else if (jsonVal.isObject()) {
                       QMap<QString, QVariant> nestedMap = extractJsonObject(key, jsonVal.toObject());
                       ret.unite(nestedMap);
                   } else if (jsonVal.isArray()) {
                       QJsonArray jsonArray = jsonVal.toArray();
                       QMap<QString, QVariant> nestedMap = extractJsonArray(key, jsonArray);
                       ret.unite(nestedMap);
                   } else {
                       ret[key] = jsonVal.toVariant();
                   }
         }


    return ret;
}


QMap<QString, QVariant> MainWindow:: extractJsonArray(const QString& prefix, const QJsonArray& jsonArray)
{
    QMap<QString, QVariant> ret;

    for (int i = 0; i < jsonArray.size(); ++i) {
            QString key = prefix + "_" + QString::number(i);
            const QJsonValue& jsonValue = jsonArray[i];

            if (jsonValue.isNull()) {
                ret[key] = "null";
            } else if (jsonValue.isUndefined()) {
                ret[key] = "undef";
            } else if (jsonValue.isBool()) {
                bool value = jsonValue.toBool();
                ret[key] = value;
            } else if (jsonValue.isObject()) {
                QMap<QString, QVariant> nestedMap = extractJsonObject(key, jsonValue.toObject());
                ret.unite(nestedMap);
            } else if (jsonValue.isArray()) {
                QJsonArray nestedJsonArray = jsonValue.toArray();
                QMap<QString, QVariant> nestedMap = extractJsonArray(key, nestedJsonArray);
                ret.unite(nestedMap);
            } else {
                ret[key] = jsonValue.toVariant();
            }
        }
    return ret;
}





