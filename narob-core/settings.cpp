#include "settings.h"

Settings::Settings() :
    mId(1),

    mEmailUser(""),
    mEmailPW(""),
    mEmailHost(""),
    mTextNumber(""),
    mTextProvider("")
{
}

Settings::Settings(const Settings &settings) :
    mId(1),

    mEmailUser(settings.emailUser()),
    mEmailPW(settings.emailPW()),
    mEmailHost(settings.emailHost()),
    mTextNumber(settings.textNumber()),
    mTextProvider(settings.textProvider())
{
}
