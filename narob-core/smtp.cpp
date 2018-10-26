/*
Copyright (c) 2013 Raivis Strogonovs
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/

#include "smtp.h"

Smtp::Smtp(QObject *parent) :
    QObject(parent),
    mSettingsTable(new Settings),
    mSettings(mSettingsTable->getSettings()),
    mSocket(new QSslSocket(this)),
    mPort(465),
    mTimeout(30000),
    mUser(mSettings->value("emailUser").toString()),
    mPass(mSettings->value("emailPW").toString()),
    mHost(mSettings->value("emailHost").toString()),
    mFrom(mSettings->value("emailUser").toString()),
    mTextStream(new QTextStream(mSocket))
{
    connect(mSocket, &QSslSocket::stateChanged, this, &Smtp::stateChanged);
    connect(mSocket, &QSslSocket::connected, this, &Smtp::connected);
    connect(mSocket, &QSslSocket::readyRead, this, &Smtp::readyRead);
    connect(mSocket, &QSslSocket::disconnected, this, &Smtp::disconnected);
    connect(mSocket,
            static_cast<void (QSslSocket::*)(QAbstractSocket::SocketError)>(&QSslSocket::error),
            this,
            &Smtp::errorReceived);
}

void Smtp::sendMail(const QString &to,
                    const QString &subject,
                    const QString &body)
{
    mMessage = "To: " + to + "\n";
    mMessage.append("From: " + mFrom + "\n");
    mMessage.append("Subject: " + subject + "\n");
    mMessage.append(body);
    mMessage.replace(QString::fromLatin1( "\n" ),
                     QString::fromLatin1( "\r\n" ) );
    mMessage.replace(QString::fromLatin1( "\r\n.\r\n" ),
                     QString::fromLatin1( "\r\n..\r\n" ) );
    mRcpt = to;
    mState = INIT;
    mSocket->connectToHostEncrypted(mHost, mPort);
    if (!mSocket->waitForConnected(mTimeout)) {
         qDebug() << "SMTP Timeout error " << mSocket->errorString();
     }
}

Smtp::~Smtp()
{
    delete mSettingsTable;
    delete mSettings;
    delete mTextStream;
    delete mSocket;
}

void Smtp::stateChanged(QAbstractSocket::SocketState socketState)
{
    //Q_UNUSED(socketState);
    qDebug() <<"SMTP stateChanged " << socketState;
}

void Smtp::errorReceived(QAbstractSocket::SocketError socketError)
{
    qDebug() << "SMTP error " << socketError;
}

void Smtp::disconnected()
{
    qDebug() << "SMTP Disconneted";

    if(mSocket->error() != QAbstractSocket::UnknownSocketError){
        qDebug() << "SMTP Error Code " << mSocket->error();
        qDebug() << "SMPT Error "  << mSocket->errorString();
    }
}

void Smtp::connected()
{
    qDebug() << "SMTP Connected ";
}

void Smtp::readyRead()
{

    qDebug() <<"SMTP ReadyRead";
    // SMTP is line-oriented

    QString responseLine;
    QString response;

    do
    {
        responseLine = mSocket->readLine();
        response += responseLine;
    }
    while ( mSocket->canReadLine() && responseLine[3] != ' ' );

    responseLine.truncate( 3 );

    qDebug() << "SMTP Server response code:" <<  responseLine;
    qDebug() << "SMTP Server response: " << response;

    //GMAIL is using XOAUTH2 protocol, which basically means that
    //password and username has to be sent in base64 coding
    //https://developers.google.com/gmail/xoauth2_protocol

    //Apperantly for Google it is mandatory to have MAIL FROM and RCPT
    //email formated the following way -> <email@gmail.com>

    if(mState == INIT && responseLine == "220") {
        sendLine("EHLO localhost");
        mState = AUTH;
    }else if(mState == AUTH && responseLine == "250") {
        sendLine("AUTH LOGIN");
        mState = USER;
    }else if(mState == USER && responseLine == "334") {
        sendLine(QByteArray().append(mUser).toBase64());
        mState = PASS;
    }else if(mState == PASS && responseLine == "334") {
        sendLine(QByteArray().append(mPass).toBase64());
        mState = MAIL;
    }else if(mState == MAIL && responseLine == "235") {
        sendLine("MAIL FROM:<" + mFrom + ">");
        mState = RCPT;
    }else if(mState == RCPT && responseLine == "250") {
        sendLine("RCPT TO:<" + mRcpt + ">");
        mState = DATA;
    }else if(mState == DATA && responseLine == "250") {
        sendLine("DATA");
        mState = BODY;
    }else if(mState == BODY && responseLine == "354") {
        sendLine(mMessage + "\r\n.");
        mState = QUIT;
    }else if(mState == QUIT && responseLine == "250") {
        sendLine("QUIT");
        mState = CLOSE;
        emit status("Message sent");
    }else if(mState == CLOSE) {
        deleteLater();
    }else{
        // something broke.
        qDebug("SMTP - Page did not send - WRITE CODE");
        QMessageBox::warning(nullptr,
                             "Qt Simple SMTP client",
                             "Unexpected reply from SMTP server:\n\n" + response);
        mState = CLOSE;
        emit status("Failed to send message");
    }

    return;
}

void Smtp::sendLine(QString line)
{
    qDebug() << line;
    *mTextStream << line << "\r\n";
    mTextStream->flush();
}
