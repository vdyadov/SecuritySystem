#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QDate>

#include <QWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QComboBox>
#include <QPushButton>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include "employee.h"


class Schedule : public QWidget {
    Q_OBJECT

public:
    explicit Schedule(QWidget *parent = nullptr);

    void generateSchedule(const QList<Employee> &employees, const QDate &startDate, int numDays);
    void saveToJson();
    void loadFromJson();
    void setupTable();
    void toggleDay(int row, int col);  // Переключить день (рабочий/выходной)
    void onItemClicked(QTableWidgetItem *item);  // Слот для обработки клика по ячейке

private:
    QTableWidget *tableWidget;
    QString filePathSchedule = "/Users/vlad_os/study/kursach/SecuritySystem/SecuritySystem/build/schedule.json";
};



// --------------------------------------------------------------------
// #include <QWidget>
// #include <QTableWidget>
// #include <QDate>

// class Schedule : public QWidget {
//     Q_OBJECT

// public:
//     explicit Schedule(QWidget *parent = nullptr);
//     void setupTable();
//     void generateSchedule(int numGuards, const QDate &startDate, int numDays);

// private:
//     QTableWidget *tableWidget;
// };

// #endif // SCHEDULE_H

// --------------------------------------------------------------------
// class Schedule : public QWidget {
//     Q_OBJECT

// public:
//     explicit Schedule(QWidget *parent = nullptr);

//     void setGuards(const QStringList &guards);
//     void setMonth(int year, int month);

//     bool saveToFile(const QString &filePath);
//     bool loadFromFile(const QString &filePath);

//     QJsonObject toJson() const;
//     void fromJson(const QJsonObject &json);

// private:
//     QTableWidget *tableWidget;
//     QStringList guardsList;
//     int daysInMonth;

//     QPushButton *saveButton;
//     QPushButton *loadButton;
//     QPushButton *validateButton;
//     QPushButton *statsButton;

//     void validateSchedule();
//     void showStatistics();
// };
// --------------------------------------------------------------------

// class Schedule : public QObject
// {
//     Q_OBJECT
// protected:
//     QList<QDate> dateWork;
//     QList<QDate> dateFree;

// public:
//     explicit Schedule(QObject *parent = nullptr);

// signals:
// };

#endif // SCHEDULE_H
