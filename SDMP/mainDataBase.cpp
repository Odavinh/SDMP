#include "mainDataBase.h"
#include<QSqlRecord>
#include<algorithm>

#define DEBUG

MainDataBase::MainDataBase(const QString &dataBaseName, const QString &driverDB)
    :DataBaseManage(dataBaseName,driverDB)
{

}

bool MainDataBase::conectDataBase(const QString &hostName, const QString &userName, const QString &pasword)
{
    return DataBaseManage::conectDataBase(hostName,userName,pasword);
}

bool MainDataBase::addTable(const QString &nameTable)
{
    this->sqlQuery = std::make_shared<QSqlQuery>(dataBase);
    //std::shared_ptr<Tables> table = std::make_shared<Tables>(nameTable, this->dataBase);
    //this->TablesArray.push_back(*table.get());
    return sqlQuery.get()->exec("CREATE TABLE [dbo].["+nameTable+"]("
                                "[ID] [bigint] IDENTITY(1,1) NOT NULL,"
                                "[First Name] [nvarchar](20) NOT NULL,"
                                "[Surname] [nvarchar](20) NOT NULL,"
                                "[Last Name] [nvarchar](20) NULL,"
                                "[Gender] [nvarchar](1) NULL,"
                                "[Born] [nvarchar](10) NULL,"
                                "[Number1] [nvarchar](12) NULL,"
                                "[Number2] [nvarchar](12) NULL,"
                                "[Email] [nvarchar](30) NULL,"
                                "[Address] [nvarchar](50) NULL,"
                                "[Web-site] [nvarchar](50) NULL,"
                                "[Detail] [varchar](max) NULL,"
                             "CONSTRAINT [PK_"+nameTable+"] PRIMARY KEY CLUSTERED ("
                                "[ID] ASC"
                            ")WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF,"
                                " IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]"
                            ") ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]");
}

bool MainDataBase::saveAll()
{
    return DataBaseManage::saveAll();
}

bool MainDataBase::deleteTable(const QString &nameTable)
{
    this->sqlQuery = std::make_shared<QSqlQuery>(dataBase);
    return sqlQuery.get()->exec("DROP TABLE "+nameTable);
}

bool MainDataBase::add_values_in_the_table(const QString &tableName, const Person &newElemen)
{
    auto result = std::find_if(this->TablesArray.begin(),
                 this->TablesArray.end(),
                 [tableName](const QString &str){return tableName == str;});
    if (result == this->TablesArray.end())
        return false;

    return result->addItem(newElemen);
}

bool MainDataBase::change_value_in_the_table(const QString &tableName, const Person &newElemen)
{
    auto result = std::find_if(this->TablesArray.begin(),
                 this->TablesArray.end(),
                 [tableName](const QString &str){return tableName == str;});
    if (result == this->TablesArray.end())
        return false;
    return result->changeItem(newElemen);
}

QStringList MainDataBase::getItemsList(const QString &tableName)
{
    auto result = std::find_if(this->TablesArray.begin(),
                 this->TablesArray.end(),
                 [tableName](const QString &str){return tableName == str;});
    if (result == this->TablesArray.end())
        return QStringList();
    return result->showItems();

}

Person MainDataBase::get_item_from_the_table(const QString &tableName, const int &id)
{
    auto result = std::find_if(this->TablesArray.begin(),
                 this->TablesArray.end(),
                 [tableName](const QString &str){return tableName == str;});
    if (result == this->TablesArray.end())
        return Person();
    return result->getTtem(id);
}

bool MainDataBase::delete_item_from_the_table(const QString &tableName, const int &id)
{
    auto result = std::find_if(this->TablesArray.begin(),
                 this->TablesArray.end(),
                 [tableName](const QString &str){return tableName == str;});
    if (result == this->TablesArray.end())
        return false;
    return result->deleteItem(id);
}



MainDataBase::~MainDataBase(){}

//Class Table
MainDataBase::Tables::Tables(const QString &tableName, const QSqlDatabase &database)
{
    this->tableName = std::make_shared<QString>(tableName);
    this->dataBase = std::make_shared<QSqlDatabase>(database);
}

bool MainDataBase::Tables::addItem(const Person &newElement)
{
    this->sqlQuery = std::make_shared<QSqlQuery>(*this->dataBase.get());
    return sqlQuery.get()->exec("INSERT INTO [dbo].["+*this->tableName.get()+"]"
                                "([First Name]"
                                ",[Surname]"
                                ",[Last Name]"
                                ",[Gender]"
                                ",[Born]"
                                ",[Number1]"
                                ",[Number2]"
                                ",[Email]"
                                ",[Address]"
                                ",[Web-site]"
                                ",[Detail])"
                          "VALUES"
                                "("+newElement.getFirstName()+
                                ","+newElement.getSurname()+
                                ","+newElement.getLastName()+
                                ","+newElement.getGender()+
                                ","+newElement.getBorn()+
                                ","+newElement.getNumber1()+
                                ","+newElement.getNumber2()+
                                ","+newElement.getEmail()+
                                ","+newElement.getAddress()+
                                ","+newElement.getWebSite()+
                                ","+newElement.getDetail()+")");
}

bool MainDataBase::Tables::changeItem(const Person &changedElement)
{
     this->sqlQuery = std::make_shared<QSqlQuery>(*this->dataBase.get());
     return sqlQuery->exec("UPDATE [dbo].[LVIV]"
                           "SET [First Name] = " +changedElement.getFirstName()+
                              ",[Surname] = "+changedElement.getSurname()+
                              ",[Last Name] = "+changedElement.getLastName()+
                              ",[Gender] = "+changedElement.getGender()+
                              ",[Born] = "+changedElement.getBorn()+
                              ",[Number1] = "+changedElement.getNumber1()+
                              ",[Number2] = "+changedElement.getNumber2()+
                              ",[Email] = "+changedElement.getEmail()+
                              ",[Address] = "+changedElement.getAddress()+
                              ",[Web-site] = "+changedElement.getWebSite()+
                              ",[Detail] = "+changedElement.getDetail()+
                         "WHERE ID = "+QString::number(changedElement.getId()));
}

QStringList MainDataBase::Tables::showItems()
{
    this->sqlQuery = std::make_shared<QSqlQuery>(*dataBase.get());
            if(!sqlQuery.get()->exec("SELECT * FROM "+*this->tableName.get())){
#ifdef DEBUG
                qDebug()<< dataBase.get()->lastError().databaseText();
                qDebug() << dataBase.get()->lastError().driverText();
#endif //DEBUG
                return QStringList();
            }
            QStringList list;
               while (sqlQuery.get()->next()) {
                   list << sqlQuery.get()->value(0).toString() + "\t"+
                           sqlQuery.get()->value(1).toString() + " " +
                           sqlQuery.get()->value(2).toString();
              }
    this-> sqlQuery.get()->clear();
    return list;
}

Person MainDataBase::Tables::getTtem(const int &id)
{
    this->sqlQuery = std::make_shared<QSqlQuery>(*this->dataBase.get());
            if(!sqlQuery.get()->exec("SELECT * FROM "+*tableName.get()+ " WHERE ID = " +  QString::number(id))){
#ifdef DEBUG
                qDebug()<< dataBase.get()->lastError().databaseText();
                qDebug() << dataBase.get()->lastError().driverText();
#endif //DEBUG
                return Person();
            }else {
               sqlQuery.get()->next();
                return Person(sqlQuery.get()->value(0).toInt(),
                                       sqlQuery.get()->value(1).toString(),
                                       sqlQuery.get()->value(2).toString(),
                                       sqlQuery.get()->value(3).toString(),
                                       sqlQuery.get()->value(4).toString(),
                                       sqlQuery.get()->value(5).toString(),
                                       sqlQuery.get()->value(6).toString(),
                                       sqlQuery.get()->value(7).toString(),
                                       sqlQuery.get()->value(8).toString(),
                                       sqlQuery.get()->value(9).toString(),
                                       sqlQuery.get()->value(10).toString(),
                                       sqlQuery.get()->value(11).toString());
            }
}

bool MainDataBase::Tables::deleteItem(const int &id)
{
    this->sqlQuery = std::make_shared<QSqlQuery>(*this->dataBase.get());
    return this->sqlQuery->exec("DELETE FROM [dbo].["+*this->tableName.get()+"]"
                                "WHERE ID = " + QString::number(id));
}

QString MainDataBase::Tables::getTableName() const
{
    return *tableName.get();
}

