#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
   //explicit MainWindow(QWidget *parent = nullptr);
    QMap<QString, QVariant> extractJsonObject(const QString& prefix, const QJsonObject& jsonObject);
    QMap<QString, QVariant> extractJsonArray(const QString& prefix, const QJsonArray& jsonArray);

};

#endif // MAINWINDOW_H
