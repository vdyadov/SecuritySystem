// #include "schedule.h"

// Schedule::Schedule(QObject *parent)
//     : QObject{parent}
// {}
#include <QFile>
#include <QWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QComboBox>
#include <QPushButton>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QMessageBox>

#include <QVBoxLayout>
#include <QHeaderView>
#include "schedule.h"


Schedule::Schedule(QWidget *parent)
    : QWidget(parent), tableWidget(new QTableWidget(this)) {

    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addWidget(tableWidget);

    setupTable();
}

void Schedule::setupTable() {
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);  // Запрещаем редактирование ячеек
    tableWidget->setSelectionMode(QAbstractItemView::NoSelection);  // Запрещаем выделение ячеек
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    tableWidget->setStyleSheet("QTableWidget::item { text-align: center; }");

    // Подключаем слот к сигналу клика по ячейке
    connect(tableWidget, &QTableWidget::itemClicked, this, &Schedule::onItemClicked);
}

void Schedule::generateSchedule(const QList<Employee> &employees, const QDate &startDate, int numDays) {
    tableWidget->setRowCount(employees.size());
    tableWidget->setColumnCount(numDays);

    QStringList headers;
    for (int i = 0; i < numDays; ++i) {
        headers << startDate.addDays(i).toString("dd.MM");
    }
    tableWidget->setHorizontalHeaderLabels(headers);

    for (int row = 0; row < employees.size(); ++row) {
        // Используем имя сотрудника для первой колонки
        QTableWidgetItem *nameItem = new QTableWidgetItem(employees[row].getLastName() + " " + employees[row].getFirstName());
        tableWidget->setItem(row, 0, nameItem);
        tableWidget->setColumnWidth(0, 200);

        // Заполнение остальных ячеек (график)
        for (int col = 1; col < numDays; ++col) {
            QTableWidgetItem *item = new QTableWidgetItem();
            if ((col % 3) == (row % 3)) {
                item->setText("Рабочий");
                item->setBackground(Qt::green);  // Рабочий день
            } else {
                item->setText("Выходной");
                item->setBackground(Qt::lightGray);  // Выходной
            }
            tableWidget->setItem(row, col, item);
            tableWidget->setColumnWidth(col, 150);
        }
    }
}

void Schedule::toggleDay(int row, int col) {
    QTableWidgetItem *item = tableWidget->item(row, col);
    if (!item) {
        item = new QTableWidgetItem();
        tableWidget->setItem(row, col, item);
    }

    if (item->text() == "Рабочий") {
        item->setText("Выходной");
        item->setBackground(Qt::lightGray);  // Переключаем на выходной
    } else {
        item->setText("Рабочий");
        item->setBackground(Qt::green);  // Переключаем на рабочий
    }
}

void Schedule::onItemClicked(QTableWidgetItem *item) {
    // Получаем строку и столбец ячейки, по которой кликнули
    int row = item->row();
    int col = item->column();

    // Переключаем состояние ячейки (рабочий/выходной)
    toggleDay(row, col);
}

void Schedule::saveToJson() {
    // Создаем объект JSON для сохранения данных
    QJsonArray employeesArray;
    for (int row = 0; row < tableWidget->rowCount(); ++row) {
        QJsonObject employeeObject;
        // Имя сотрудника
        employeeObject["name"] = tableWidget->item(row, 0)->text();

        QJsonArray scheduleArray;
        for (int col = 1; col < tableWidget->columnCount(); ++col) {
            QString dayStatus = tableWidget->item(row, col)->text();
            scheduleArray.append(dayStatus);
        }

        employeeObject["schedule"] = scheduleArray;
        employeesArray.append(employeeObject);
    }

    // Создаем объект JSON, который будет содержать все данные
    QJsonObject rootObject;
    rootObject["employees"] = employeesArray;

    // Сохраняем данные в файл
    QFile file(filePathSchedule);
    if (file.open(QIODevice::WriteOnly)) {
        QJsonDocument doc(rootObject);
        file.write(doc.toJson());
        file.close();
    } else {
        qDebug() << "Ошибка при открытии файла для записи";
    }
}

void Schedule::loadFromJson() {
    QFile file(filePathSchedule);
    if (file.open(QIODevice::ReadOnly)) {
        // Чтение и парсинг JSON документа
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        QJsonObject rootObject = doc.object();
        QJsonArray employeesArray = rootObject["employees"].toArray();

        // Заполняем таблицу из загруженных данных
        for (int row = 0; row < employeesArray.size(); ++row) {
            QJsonObject employeeObject = employeesArray[row].toObject();
            QString name = employeeObject["name"].toString();
            QJsonArray scheduleArray = employeeObject["schedule"].toArray();

            // Устанавливаем имя сотрудника в первую колонку
            tableWidget->setItem(row, 0, new QTableWidgetItem(name));

            // Заполняем график дежурств для сотрудника
            for (int col = 0; col < scheduleArray.size(); ++col) {
                QString dayStatus = scheduleArray[col].toString();
                QTableWidgetItem *item = tableWidget->item(row, col + 1); // Начинаем с 1, так как 0 - это имя
                if (!item) {
                    item = new QTableWidgetItem();
                    tableWidget->setItem(row, col + 1, item);
                }
                item->setText(dayStatus);
                if (dayStatus == "Рабочий") {
                    item->setBackground(Qt::green);
                } else if (dayStatus == "Выходной") {
                    item->setBackground(Qt::lightGray);
                }
            }
        }
        file.close();
    } else {
        qDebug() << "Ошибка при открытии файла для чтения";
    }
}

// Schedule::Schedule(QWidget *parent)
//     : QWidget(parent), tableWidget(new QTableWidget(this)) {
//     QVBoxLayout *layout = new QVBoxLayout(this);
//     layout->addWidget(tableWidget);

//     setupTable();
// }

// void Schedule::setupTable() {
//     tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
//     tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
//     tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//     tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//     tableWidget->setStyleSheet("QTableWidget::item { text-align: center; }");
// }

// void Schedule::generateSchedule(int numGuards, const QDate &startDate, int numDays) {
//     tableWidget->setRowCount(numGuards);
//     tableWidget->setColumnCount(numDays);

//     QStringList headers;
//     for (int i = 0; i < numDays; ++i) {
//         headers << startDate.addDays(i).toString("dd.MM");
//     }
//     tableWidget->setHorizontalHeaderLabels(headers);

//     for (int row = 0; row < numGuards; ++row) {
//         for (int col = 0; col < numDays; ++col) {
//             QTableWidgetItem *item = new QTableWidgetItem();
//             if ((col % 3) == (row % 3)) {
//                 item->setText("Рабочий");
//                 item->setBackground(Qt::green);
//             } else {
//                 item->setText("Выходной");
//                 item->setBackground(Qt::lightGray);
//             }
//             tableWidget->setItem(row, col, item);
//         }
//     }
// }



// --------------------------------------------------------------------
// Schedule::Schedule(QWidget *parent)
//     : QWidget(parent), tableWidget(new QTableWidget(this)),
//     saveButton(new QPushButton("Сохранить график", this)),
//     loadButton(new QPushButton("Загрузить график", this)),
//     validateButton(new QPushButton("Проверить график", this)),
//     statsButton(new QPushButton("Статистика", this)) {

//     QVBoxLayout *layout = new QVBoxLayout(this);
//     layout->addWidget(tableWidget);
//     layout->addWidget(saveButton);
//     layout->addWidget(loadButton);
//     layout->addWidget(validateButton);
//     layout->addWidget(statsButton);
//     setLayout(layout);

//     connect(saveButton, &QPushButton::clicked, this, [this]() {
//         saveToFile("schedule.json");
//     });

//     connect(loadButton, &QPushButton::clicked, this, [this]() {
//         loadFromFile("schedule.json");
//     });

//     connect(validateButton, &QPushButton::clicked, this, &Schedule::validateSchedule);

//     connect(statsButton, &QPushButton::clicked, this, &Schedule::showStatistics);

//     // Настройка таблицы
//     tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
//     tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//     tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
// }

// void Schedule::setGuards(const QStringList &guards) {
//     guardsList = guards;
//     tableWidget->setRowCount(guards.size());
//     tableWidget->setVerticalHeaderLabels(guardsList);
// }

// void Schedule::setMonth(int year, int month) {
//     daysInMonth = QDate(year, month, 1).daysInMonth();

//     tableWidget->setColumnCount(daysInMonth);
//     QStringList dayLabels;
//     for (int i = 1; i <= daysInMonth; ++i) {
//         dayLabels.append(QString::number(i));
//     }
//     tableWidget->setHorizontalHeaderLabels(dayLabels);

//     for (int row = 0; row < guardsList.size(); ++row) {
//         for (int col = 0; col < daysInMonth; ++col) {
//             QComboBox *comboBox = new QComboBox();
//             comboBox->addItems({"День", "Ночь", "Выходной"});
//             tableWidget->setCellWidget(row, col, comboBox);
//         }
//     }
// }

// bool Schedule::saveToFile(const QString &filePath) {
//     QFile file(filePath);
//     if (!file.open(QIODevice::WriteOnly)) {
//         QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для записи.");
//         return false;
//     }

//     QJsonObject json = toJson();
//     file.write(QJsonDocument(json).toJson());
//     file.close();
//     QMessageBox::information(this, "Успех", "График успешно сохранен.");
//     return true;
// }

// bool Schedule::loadFromFile(const QString &filePath) {
//     QFile file(filePath);
//     if (!file.open(QIODevice::ReadOnly)) {
//         QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для чтения.");
//         return false;
//     }

//     QByteArray data = file.readAll();
//     QJsonDocument doc = QJsonDocument::fromJson(data);
//     fromJson(doc.object());
//     file.close();
//     QMessageBox::information(this, "Успех", "График успешно загружен.");
//     return true;
// }

// QJsonObject Schedule::toJson() const {
//     QJsonObject json;
//     QJsonArray guardsArray;

//     for (int row = 0; row < guardsList.size(); ++row) {
//         QJsonArray rowArray;
//         for (int col = 0; col < daysInMonth; ++col) {
//             QComboBox *comboBox = qobject_cast<QComboBox *>(tableWidget->cellWidget(row, col));
//             if (comboBox) {
//                 rowArray.append(comboBox->currentText());
//             }
//         }
//         guardsArray.append(rowArray);
//     }

//     json["guards"] = guardsArray;
//     json["guardsList"] = QJsonArray::fromStringList(guardsList);
//     return json;
// }

// void Schedule::fromJson(const QJsonObject &json) {
//     QJsonArray jsonArray = json["guardsList"].toArray();
//     QStringList guardsList;

//     for (const QJsonValue &value : jsonArray) {
//         guardsList.append(value.toString());
//     }
//     setGuards(guardsList);

//     QJsonArray guardsArray = json["guards"].toArray();
//     for (int row = 0; row < guardsArray.size(); ++row) {
//         QJsonArray rowArray = guardsArray[row].toArray();
//         for (int col = 0; col < rowArray.size(); ++col) {
//             QComboBox *comboBox = qobject_cast<QComboBox *>(tableWidget->cellWidget(row, col));
//             if (comboBox) {
//                 comboBox->setCurrentText(rowArray[col].toString());
//             }
//         }
//     }
// }

// void Schedule::validateSchedule() {
//     for (int col = 0; col < daysInMonth; ++col) {
//         int dayCount = 0;
//         for (int row = 0; row < guardsList.size(); ++row) {
//             QComboBox *comboBox = qobject_cast<QComboBox *>(tableWidget->cellWidget(row, col));
//             if (comboBox && comboBox->currentText() != "Выходной") {
//                 dayCount++;
//             }
//         }
//         if (dayCount > 1) {
//             QMessageBox::warning(this, "Ошибка валидации", QString("На день %1 назначено более одного охранника.").arg(col + 1));
//             return;
//         }
//     }
//     QMessageBox::information(this, "Успех", "График успешно проверен.");
// }

// void Schedule::showStatistics() {
//     QString stats;
//     for (int row = 0; row < guardsList.size(); ++row) {
//         int dayShifts = 0, nightShifts = 0, daysOff = 0;
//         for (int col = 0; col < daysInMonth; ++col) {
//             QComboBox *comboBox = qobject_cast<QComboBox *>(tableWidget->cellWidget(row, col));
//             if (comboBox) {
//                 if (comboBox->currentText() == "День") dayShifts++;
//                 else if (comboBox->currentText() == "Ночь") nightShifts++;
//                 else if (comboBox->currentText() == "Выходной") daysOff++;
//             }
//         }
//         stats += QString("%1: День - %2, Ночь - %3, Выходной - %4\n")
//                      .arg(guardsList[row])
//                      .arg(dayShifts)
//                      .arg(nightShifts)
//                      .arg(daysOff);
//     }
//     QMessageBox::information(this, "Статистика", stats);
// }
// --------------------------------------------------------------------
