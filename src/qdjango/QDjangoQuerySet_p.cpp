#include <QSqlDriver>

#include "QDjango.h"
#include "QDjangoQuerySet.h"
#include "QDjangoQuerySet_p.h"
QDjangoQuerySetPrivate::QDjangoQuerySetPrivate(const QString &modelName)
: counter(1),
hasResults(false),
lowMark(0),
highMark(0),
selectRelated(false),
m_modelName(modelName)
{
}


void QDjangoQuerySetPrivate::addFilter(const QDjangoWhere &where)
{
	// it is not possible to add filters once a limit has been set
	Q_ASSERT(!lowMark && !highMark);

	whereClause = whereClause && where;
}

QDjangoWhere QDjangoQuerySetPrivate::resolvedWhere(const QSqlDatabase &db) const
{
	QDjangoCompiler compiler(m_modelName, db);
	QDjangoWhere resolvedWhere(whereClause);
	compiler.resolve(resolvedWhere);
	return resolvedWhere;
}

int QDjangoQuerySetPrivate::sqlCount() const
{
	QSqlDatabase db = QDjango::database();

	// build query
	QDjangoCompiler compiler(m_modelName, db);
	QDjangoWhere resolvedWhere(whereClause);
	compiler.resolve(resolvedWhere);

	const QString where = resolvedWhere.sql();
	const QString limit = compiler.orderLimitSql(orderBy, lowMark, highMark);
	QString sql = "SELECT COUNT(*) FROM " + compiler.fromSql();
	if (!where.isEmpty())
		sql += " WHERE " + where;
	sql += limit;
	QDjangoQuery query(db);
	query.prepare(sql);
	resolvedWhere.bindValues(query);

	// execute query
	if (!query.exec() || !query.next())
		return -1;
	return query.value(0).toInt();
}

bool QDjangoQuerySetPrivate::sqlDelete()
{
	// DELETE on an empty queryset doesn't need a query
	if (whereClause.isNone())
		return true;

	// FIXME : it is not possible to remove entries once a limit has been set
	// because SQLite does not support limits on DELETE unless compiled with the
	// SQLITE_ENABLE_UPDATE_DELETE_LIMIT option
	if (lowMark || highMark)
		return false;

	QSqlDatabase db = QDjango::database();

	// build query
	QDjangoCompiler compiler(m_modelName, db);
	QDjangoWhere resolvedWhere(whereClause);
	compiler.resolve(resolvedWhere);

	const QString where = resolvedWhere.sql();
	const QString limit = compiler.orderLimitSql(orderBy, lowMark, highMark);
	QString sql = "DELETE FROM " + compiler.fromSql();
	if (!where.isEmpty())
		sql += " WHERE " + where;
	sql += limit;
	QDjangoQuery query(db);
	query.prepare(sql);
	resolvedWhere.bindValues(query);

	// execute query
	if (!query.exec())
		return false;

	// invalidate cache
	if (hasResults)
	{
		properties.clear();
		hasResults = false;
	}
	return true;
}

bool QDjangoQuerySetPrivate::sqlFetch()
{
	if (hasResults || whereClause.isNone())
		return true;

	QSqlDatabase db = QDjango::database();

	// build query
	QDjangoCompiler compiler(m_modelName, db);
	QDjangoWhere resolvedWhere(whereClause);
	compiler.resolve(resolvedWhere);

	const QStringList fields = compiler.fieldNames(selectRelated);
	const QString where = resolvedWhere.sql();
	const QString limit = compiler.orderLimitSql(orderBy, lowMark, highMark);
	QString sql = "SELECT " + fields.join(", ") + " FROM " + compiler.fromSql();
	if (!where.isEmpty())
		sql += " WHERE " + where;
	sql += limit;
	QDjangoQuery query(db);
	query.prepare(sql);
	resolvedWhere.bindValues(query);

	// execute query
	if (!query.exec())
		return false;

	// store results
	while (query.next()) {
		QVariantList props;
		for (int i = 0; i < fields.size(); ++i)
			props << query.value(i);
		properties.append(props);
	}
	hasResults = true;
	return true;
}

bool QDjangoQuerySetPrivate::sqlLoad(QObject *model, int index)
{
	if (!sqlFetch())
		return false;

	if (index < 0 || index >= properties.size())
	{
		qWarning("QDjangoQuerySet out of bounds");
		return false;
	}

	const QDjangoMetaModel metaModel = QDjango::metaModel(m_modelName);
	int pos = 0;
	metaModel.load(model, properties.at(index), pos);
	return true;
}

QList<QVariantMap> QDjangoQuerySetPrivate::sqlValues(const QStringList &fields)
{
	QList<QVariantMap> values;
	if (!sqlFetch())
		return values;

	const QDjangoMetaModel metaModel = QDjango::metaModel(m_modelName);

	// build field list
	QMap<QString, int> fieldPos;
	if (fields.isEmpty()) {
		for (int i = 0; i < metaModel.m_localFields.size(); ++i)
			fieldPos.insert(QString::fromAscii(metaModel.m_localFields[i].name), i);
	} else {
		foreach (const QString &name, fields) {
			int pos = 0;
			foreach (const QDjangoMetaField &field, metaModel.m_localFields) {
				if (field.name == name)
					break;
				pos++;
			}
			Q_ASSERT_X(pos < metaModel.m_localFields.size(), "QDjangoQuerySet<T>::values", "unknown field requested");
			fieldPos.insert(name, pos);
		}
	}

	// extract values
	foreach (const QVariantList &props, properties) {
		QVariantMap map;
		QMap<QString, int>::const_iterator i;
		for (i = fieldPos.constBegin(); i != fieldPos.constEnd(); ++i)
			map[i.key()] = props[i.value()];
		values.append(map);
	}
	return values;
}

QList<QVariantList> QDjangoQuerySetPrivate::sqlValuesList(const QStringList &fields)
{
	QList<QVariantList> values;
	if (!sqlFetch())
		return values;

	const QDjangoMetaModel metaModel = QDjango::metaModel(m_modelName);

	// build field list
	QList<int> fieldPos;
	if (fields.isEmpty()) {
		for (int i = 0; i < metaModel.m_localFields.size(); ++i)
			fieldPos << i;
	} else {
		foreach (const QString &name, fields) {
			int pos = 0;
			foreach (const QDjangoMetaField &field, metaModel.m_localFields) {
				if (field.name == name)
					break;
				pos++;
			}
			Q_ASSERT_X(pos < metaModel.m_localFields.size(), "QDjangoQuerySet<T>::valuesList", "unknown field requested");
			fieldPos << pos;
		}
	}

	// extract values
	foreach (const QVariantList &props, properties) {
		QVariantList list;
		foreach (int pos, fieldPos)
			list << props.at(pos);
		values.append(list);
	}
	return values;
}
