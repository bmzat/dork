#ifndef tst_BranchTest_h__
#define tst_BranchTest_h__


#include <QDir>
#include <QtTest/QtTest>
#include <QObject>
namespace dork{
class Repository;
}

class BranchTest : public QObject
{
	Q_OBJECT

public:
        BranchTest();
        virtual ~BranchTest();

private Q_SLOTS:
		void initTestCase();
		void cleanupTestCase();
		void simpleAddElement();
		void simpleGetElement();

private:
        dork::Repository *repo;
		QDir trd;
		QString urlstring;
		void delRecursive(QDir d,int rec=0);


};





#endif // tst_BranchTest_h__
