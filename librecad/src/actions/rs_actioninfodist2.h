/****************************************************************************
**
** This file is part of the LibreCAD project, a 2D CAD program
**
** Copyright (C) 2010 R. van Twisk (librecad@rvt.dds.nl)
** Copyright (C) 2001-2003 RibbonSoft. All rights reserved.
**
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software 
** Foundation and appearing in the file gpl-2.0.txt included in the
** packaging of this file.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
** 
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**
** This copyright notice MUST APPEAR in all copies of the script!  
**
**********************************************************************/

#ifndef RS_ACTIONINFODIST2_H
#define RS_ACTIONINFODIST2_H

#include <memory>

#include "rs_previewactioninterface.h"


/**
 * This action class can handle user events to measure distances between
 * entities and points.
 *
 * @author Andrew Mustun
 */
class RS_ActionInfoDist2 : public RS_PreviewActionInterface {
	Q_OBJECT
public:
    /**
     * Action States.
     */
    enum Status {
        SetEntity,    /**< Setting the entity. */
        SetPoint      /**< Setting the point of the distance. */
    };

public:
    RS_ActionInfoDist2(RS_EntityContainer& container,
                        RS_GraphicView& graphicView);
	~RS_ActionInfoDist2() override;

	void init(int status=0) override;
	void trigger() override;
	
	void mouseMoveEvent(QMouseEvent* e) override;
	void mouseReleaseEvent(QMouseEvent* e) override;
	void coordinateEvent(RS_CoordinateEvent* e) override;

	void updateMouseButtonHints() override;
	void updateMouseCursor() override;

private:
    RS_Entity* entity = nullptr;
	std::unique_ptr<RS_Vector> point;
};

#endif
