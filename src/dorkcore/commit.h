#ifndef DORK_COMMIT_H
#define DORK_COMMIT_H

#include <QDjangoModel.h>
#include "libdork_global.h"
namespace dork {

class Branch;

class LIBDORKSHARED_EXPORT Commit  : public QDjangoModel
{
    Q_OBJECT
public:
	Commit(QObject *parent = 0);
	QString CommitId() const { return mCommitId; }
	void CommitId(QString val) { mCommitId = val; }
	
private:
	QString mCommitId;
	QString mParentOurs;
	QString ParentOurs() const;
	void ParentOurs(QString val);
	QString mParentTheirs;
	QString ParentTheirs() const;
	void ParentTheirs(QString val);
	QString mBranchId;
	QString BranchId() const;
	void BranchId(QString val);
	QString mRootTreeId;
	QString RootTreeId() const;
	void RootTreeId(QString val);
	QDateTime mCommitTimestamp;
	QDateTime CommitTimestamp() const;
	void CommitTimestamp(QDateTime val);
	QString mCommitMessage;
	QString CommitMessage() const;
	void CommitMessage(QString val);
};

} // namespace dork

#endif // DORK_COMMIT_H
