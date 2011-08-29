#include "commit.h"
#define QT_NAMESPACE

namespace dork {

Commit::Commit(QObject *parent) :
    QDjangoModel(parent)
{
}

	QT_NAMESPACE::QString Commit::ParentOurs() const
	{
		return mParentOurs;
	}

	void Commit::ParentOurs( QString val )
	{
		mParentOurs = val;
	}

	QT_NAMESPACE::QString Commit::ParentTheirs() const
	{
		return mParentTheirs;
	}

	void Commit::ParentTheirs( QString val )
	{
		mParentTheirs = val;
	}

	QT_NAMESPACE::QString Commit::BranchId() const
	{
		return mBranchId;
	}

	void Commit::BranchId( QString val )
	{
		mBranchId = val;
	}

	QT_NAMESPACE::QString Commit::RootTreeId() const
	{
		return mRootTreeId;
	}

	void Commit::RootTreeId( QString val )
	{
		mRootTreeId = val;
	}

	QT_NAMESPACE::QDateTime Commit::CommitTimestamp() const
	{
		return mCommitTimestamp;
	}

	void Commit::CommitTimestamp( QDateTime val )
	{
		mCommitTimestamp = val;
	}

	QT_NAMESPACE::QString Commit::CommitMessage() const
	{
		return mCommitMessage;
	}

	void Commit::CommitMessage( QString val )
	{
		mCommitMessage = val;
	}

} // namespace dork
