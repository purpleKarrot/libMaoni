/*
 * libMaoni common viewing framework
 * Copyright (C) 2009, 2010 Daniel Pfeifer
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MAONI_ICET_TILESWIDGET_HPP
#define MAONI_ICET_TILESWIDGET_HPP

#include <QMap>
#include <QWidget>
#include <qtpropertymanager.h>
#include <qttreepropertybrowser.h>
#include "Tile.hpp"

class TilesWidget: public QWidget
{
Q_OBJECT

public:
	TilesWidget(QWidget *parent = 0);
	void update_browser();

private slots:
	void enum_changed(QtProperty* property, int value);
	void rect_changed(QtProperty* property, const QRect& value);

private:
	std::vector<Tile> tiles;
	QMap<QtProperty*, std::size_t> indices;

	QtTreePropertyBrowser* property_browser;

	QtEnumPropertyManager* enum_manager;
	QtRectPropertyManager* rect_manager;
};

#endif /* MAONI_ICET_TILESWIDGET_HPP */
