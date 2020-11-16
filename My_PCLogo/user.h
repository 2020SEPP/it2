#ifndef USER_H
#define USER_H

#include <QString>

class User
{
private:
    int id;
    QString name;
    QString phone;
    QString password;

public:
    User(){}
    User(QString ph, QString pw) : phone(ph), password(pw){}
    User(int i, QString n, QString ph, QString pw) : id(i), name(n), phone(ph), password(pw){}
    ~User(){}

public:
    int getId() { return id; }
    QString getName() { return name; }
    QString getPhone() { return phone; }
    QString getPassword() { return password; }

    void setId(int i) { id = i; }
    void setName(QString n) { name = n; }
    void setPhone(QString ph) { phone = ph; }
    void setPassword(QString pw) { password = pw; }

    QString toJsonObeject(bool withId) {
        QString Json = "{";
        if (withId) {
            Json += "\"id\": " + QString::number(id) + ", ";
        }

        Json += "\"phone\": \"" + phone + "\", \
                 \"password\": \"" + password + "\"}";
        return Json;
    }

};



#endif // USER_H