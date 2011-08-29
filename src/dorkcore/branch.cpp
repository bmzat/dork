#include "branch.h"

#define QT_NAMESPACE

namespace dork {

Branch::Branch(QObject *parent) :
    QDjangoModel(parent)
{
}

	Branch::~Branch()
	{

	}

	QT_NAMESPACE::QString Branch::InitialRevision() const
	{
		return mInitialRevision;
	}

	void Branch::InitialRevision( QT_NAMESPACE::QString val )
	{
		mInitialRevision = val;
	}

	QT_NAMESPACE::QString Branch::CurrentHeadId() const
	{
		return mCurrentHeadId;
	}

	void Branch::CurrentHeadId( QT_NAMESPACE::QString val )
	{
		mCurrentHeadId = val;
	}

	QT_NAMESPACE::QString Branch::Desc() const
	{
		return mDesc;
	}

	QT_NAMESPACE::QString Branch::Name() const
	{
		return mName;
	}

	void Branch::Name( QT_NAMESPACE::QString val )
	{
		mName = val;
	}

	QT_NAMESPACE::QString Branch::BranchId() const
	{
		return mId;
	}

	void Branch::BranchId( QT_NAMESPACE::QString val )
	{
		mId = val;
	}

} // namespace dork
