#ifndef MAINDATABASE_H
#define MAINDATABASE_H

#include<QString>
#include<QDebug>
#include<QImage>
#include<memory>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlError>
#include<QWidget>

#include<databasemanage.h>
#include<person.h>

class MainDataBase :public DataBaseManage
{
public:
    explicit MainDataBase(const QString &dataBaseName, const QString &driverDB);

    bool conectDataBase(const QString &hostName, const QString &userName = nullptr, const QString &pasword = nullptr);
    bool addTable(const QString &nameTable);
    bool saveAll();
    bool deleteTable(const QString &nameTable);

    bool add_values_in_the_table(const QString &tableName, const Person &newElemen);
    bool change_value_in_the_table(const QString &tableName, const Person &newElemen);
    QStringList getItemsList(const QString &tableName);
    Person get_item_from_the_table(const QString &tableName, const int &id);
    bool delete_item_from_the_table(const QString &tableName,const int &id);


    ~MainDataBase();

public:
    std::shared_ptr<QSqlQuery> sqlQuery;
    class Tables{
    public:
        explicit Tables(const QString &tableName, const QSqlDatabase &database);

        bool addItem(const Person &newElement);
        bool changeItem(const Person &changedElement);
        QStringList showItems();
        Person getTtem(const int &id);

        bool deleteItem(const int & id);

        QString getTableName() const;

    private:
        std::shared_ptr<QString> tableName;
        std::shared_ptr<QSqlQuery> sqlQuery;
        std::shared_ptr<QSqlDatabase> dataBase;
    };
private:
    QVector<Tables> TablesArray;
};

#endif // MAINDATABASE_H
