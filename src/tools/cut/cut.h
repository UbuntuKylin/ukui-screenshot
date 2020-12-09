/*
 *
 * Copyright: 2020 KylinSoft Co., Ltd.
 * Authors:
 *   huanhuan zhang <zhanghuanhuan@kylinos.cn>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */


#ifndef CUT_H
#define CUT_H

#include "src/tools/abstractactiontool.h"
class Cut : public AbstractActionTool {
    Q_OBJECT
public:
    explicit Cut(QObject *parent = nullptr);

    bool closeOnButtonPressed() const;
    QIcon icon(const QColor &background, bool inEditor) const override;
#ifdef SUPPORT_UKUI
    QIcon icon(const QColor &background, bool inEditor, const CaptureContext &context ) const override;
#endif
    QString name() const override;
    static QString nameID();
    QString description() const override;

    CaptureTool* copy(QObject *parent = nullptr) override;

public slots:
    void pressed(const CaptureContext &context) override;
};

#endif // CUT_H
