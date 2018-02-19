#ifndef SETTINGS_H
#define SETTINGS_H

#include "narob-core_global.h"

#include <QString>

class NAROBCORESHARED_EXPORT Settings
{
public:
    explicit Settings();
    explicit Settings(const Settings &settings);

    int id() const { return mId; }
    void setId(const int &id) { mId = id; }

    QString emailUser() const { return mEmailUser; }
    void setEmailUser(const QString &emailUser) { mEmailUser = emailUser; }

    QString emailPW() const { return mEmailPW; }
    void setEmailPW(const QString &emailPW) { mEmailPW = emailPW; }

    QString emailHost() const { return mEmailHost; }
    void setEmailHost(const QString &emailHost) { mEmailHost = emailHost; }

    QString textNumber() const { return mTextNumber; }
    void setTextNumber(const QString &textNumber) { mTextNumber = textNumber; }

    QString textProvider() const { return mTextProvider; }
    void setTextProvider(const QString textProvider) { mTextProvider = textProvider; }


private:
    int mId;

    QString mEmailUser;
    QString mEmailPW;
    QString mEmailHost;
    QString mTextNumber;
    QString mTextProvider;
};

#endif // SETTINGS_H
