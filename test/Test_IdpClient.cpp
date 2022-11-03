#include <IdPClient.h>
#include <Logger.h>

#include <QtTest>

class TestIdpClient : public QObject {
    Q_OBJECT

   private slots:
    void TokenRefreshTest();
};

void TestIdpClient::TokenRefreshTest() {
    auto token = IdPClient::Instance().token();
    QVERIFY(token.token.isEmpty());
    QVERIFY(IdPClient::Instance().updateToken());
    token = IdPClient::Instance().token();
    QVERIFY(!token.token.isEmpty());
    QVERIFY(!token.isExpired());
    qDebug() << token.token;
}

Logger gLogger("px-org-remote-status-service");

QTEST_MAIN(TestIdpClient)
#include <Test_IdpClient.moc>