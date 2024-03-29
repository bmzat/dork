/*
 * QDjango
 * Copyright (C) 2010-2011 Bolloré telecom
 * See AUTHORS file for a full list of contributors.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QtTest>

#include "QDjangoScript.h"

#include "auth_models.h"
#include "main.h"
#include "script.h"

Q_DECLARE_METATYPE(QDjangoQuerySet<User>)

void TestScript::cleanupTestCase()
{
    metaModel.dropTable();

    delete engine;
}

void TestScript::initTestCase()
{
    metaModel = QDjango::registerModel<User>();
    QCOMPARE(metaModel.isValid(), true);
    QCOMPARE(metaModel.createTable(), true);

    engine = new QScriptEngine(this);
    QDjangoScript::registerWhere(engine);
    QDjangoScript::registerModel<User>(engine);
}

void TestScript::testWhereConstructor()
{
    QScriptValue result;
    QDjangoWhere where;

    // equals
    result = engine->evaluate("Q({'username': 'foobar'})");
    where = engine->fromScriptValue<QDjangoWhere>(result);
    CHECKWHERE(where, QLatin1String("username = ?"), QVariantList() << "foobar");

    // less than
    result = engine->evaluate("Q({'username__lt': 'foobar'})");
    where = engine->fromScriptValue<QDjangoWhere>(result);
    CHECKWHERE(where, QLatin1String("username < ?"), QVariantList() << "foobar");

    // less than or equal to
    result = engine->evaluate("Q({'username__lte': 'foobar'})");
    where = engine->fromScriptValue<QDjangoWhere>(result);
    CHECKWHERE(where, QLatin1String("username <= ?"), QVariantList() << "foobar");

    // greater than
    result = engine->evaluate("Q({'username__gt': 'foobar'})");
    where = engine->fromScriptValue<QDjangoWhere>(result);
    CHECKWHERE(where, QLatin1String("username > ?"), QVariantList() << "foobar");

    // greater than or equal to
    result = engine->evaluate("Q({'username__gte': 'foobar'})");
    where = engine->fromScriptValue<QDjangoWhere>(result);
    CHECKWHERE(where, QLatin1String("username >= ?"), QVariantList() << "foobar");

    // starts with
    result = engine->evaluate("Q({'username__startswith': 'foobar'})");
    where = engine->fromScriptValue<QDjangoWhere>(result);
    CHECKWHERE(where, QLatin1String("username LIKE ? ESCAPE ?"), QVariantList() << "foobar%" << "\\");

    // ends with
    result = engine->evaluate("Q({'username__endswith': 'foobar'})");
    where = engine->fromScriptValue<QDjangoWhere>(result);
    CHECKWHERE(where, QLatin1String("username LIKE ? ESCAPE ?"), QVariantList() << "%foobar" << "\\");

    // contains
    result = engine->evaluate("Q({'username__contains': 'foobar'})");
    where = engine->fromScriptValue<QDjangoWhere>(result);
    CHECKWHERE(where, QLatin1String("username LIKE ? ESCAPE ?"), QVariantList() << "%foobar%" << "\\");

    // in
    result = engine->evaluate("Q({'username__in': ['foobar', 'wiz']})");
    where = engine->fromScriptValue<QDjangoWhere>(result);
    CHECKWHERE(where, QLatin1String("username IN (?, ?)"), QVariantList() << "foobar" << "wiz");

    // double constructor
    result = engine->evaluate("Q(Q({'username': 'foobar'}))");
    where = engine->fromScriptValue<QDjangoWhere>(result);
    CHECKWHERE(where, QLatin1String("username = ?"), QVariantList() << "foobar");
}

void TestScript::testWhereOperators()
{
    QScriptValue result;
    QDjangoWhere where;

    // AND operator
    result = engine->evaluate("Q({'username': 'foobar'}).and(Q({'password': 'foopass'}))");
    where = engine->fromScriptValue<QDjangoWhere>(result);
    CHECKWHERE(where, QLatin1String("username = ? AND password = ?"), QVariantList() << "foobar" << "foopass");

    // OR operator
    result = engine->evaluate("Q({'username': 'foobar'}).or(Q({'password': 'foopass'}))");
    where = engine->fromScriptValue<QDjangoWhere>(result);
    CHECKWHERE(where, QLatin1String("username = ? OR password = ?"), QVariantList() << "foobar" << "foopass");
}

void TestScript::testModel()
{
    // create model instance
    QScriptValue result = engine->evaluate("user = User();");
    User *user = qobject_cast<User*>(result.toQObject());
    QVERIFY(user != 0);

    // set properties
    engine->evaluate("user.username = 'foobar';");
    QCOMPARE(user->username(), QLatin1String("foobar"));
}

