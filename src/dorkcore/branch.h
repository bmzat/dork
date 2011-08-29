#ifndef DORK_BRANCH_H
#define DORK_BRANCH_H

#include <QObject>
#include <QDjangoModel.h>
#include "libdork_global.h"
#include "c:\qtsdk\desktop\qt\4.7.3\msvc2008\include\qtcore\qstring.h"
#include "c:\qtsdk\desktop\qt\4.7.3\msvc2008\include\qtcore\qstring.h"
namespace dork {

class LIBDORKSHARED_EXPORT Branch : public QDjangoModel
{
    Q_OBJECT
	Q_PROPERTY(QString InitialRevision READ InitialRevision WRITE InitialRevision)
	Q_PROPERTY(QString CurrentHeadId READ CurrentHeadId WRITE CurrentHeadId)
	Q_PROPERTY(QString Desc READ Desc WRITE Desc)
	Q_PROPERTY(QString Name READ Name WRITE Name)
	Q_PROPERTY(QString BranchId READ BranchId WRITE BranchId)
	Q_CLASSINFO("BranchId","primary_key=true")
public:
    explicit Branch(QObject *parent = 0);
	~Branch();

signals:

public slots:

private:
	QString mInitialRevision;

	QString mCurrentHeadId;

	QString mDesc;

	QString mName;

	QString mId;

public:
	QString InitialRevision() const;
	void InitialRevision(QString val);	
	QString CurrentHeadId() const;
	void CurrentHeadId(QString val);	
	QString Desc() const;
	void Desc(QString val) { mDesc = val; }	
	QString Name() const;
	void Name(QString val);
	QString BranchId() const;
	void BranchId(QString val);
};

} // namespace dork

#endif // DORK_BRANCH_H
