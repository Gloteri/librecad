/*****************************************************************************/
/*  Asciifile.h - ascii file importer                                        */
/*                                                                           */
/*  Copyright (C) 2011 Rallaz, rallazz@gmail.com                             */
/*                                                                           */
/*  This library is free software, licensed under the terms of the GNU       */
/*  General Public License as published by the Free Software Foundation,     */
/*  either version 2 of the License, or (at your option) any later version.  */
/*  You should have received a copy of the GNU General Public License        */
/*  along with this program.  If not, see <http://www.gnu.org/licenses/>.    */
/*****************************************************************************/

#ifndef DRAWPOINTS_H
#define DRAWPOINTS_H

#include <QWidget>
#include <QFile>
#include <QLabel>
#include <QGroupBox>
#include <QCheckBox>
#include <QLineEdit>
#include <QComboBox>
#include <QDialog>
#include "qc_plugininterface.h"
#include "document_interface.h"

class pointBox;
class textBox;
class QVBoxLayout;
struct PointData;

class AsciiFile : public QObject, QC_PluginInterface
{
    Q_OBJECT
    Q_INTERFACES(QC_PluginInterface)
    Q_PLUGIN_METADATA(IID LC_DocumentInterface_iid FILE  "asciifile.json")

 public:
    PluginCapabilities getCapabilities() const override;
    QString name() const override;
    void execComm(Document_Interface *doc,
                          QWidget *parent, QString cmd) override;
};

namespace DPT {
    enum txtposition {N, S, E, O, NE, SE, SO, NO};
}

class dibPunto : public QDialog
{
    Q_OBJECT

public:
    explicit dibPunto(QWidget *parent = nullptr);
    ~dibPunto();
    void SetupUI(QWidget *parent);

public slots:
    void dptFile();
    void procesFile(Document_Interface *doc);
    void checkAccept();

private:
    void readSettings();
    void writeSettings();
    void procesfileODB(QFile* file, QString sep);
#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)
    void procesfileNormal(QFile* file, QString sep, Qt::SplitBehaviorFlags skip = Qt::KeepEmptyParts);
#else
    void procesfileNormal(QFile* file, QString sep, QString::SplitBehavior skip = QString::KeepEmptyParts);
#endif
    void drawLine();
    void draw2D();
    void draw3D();
    void drawNumber();
    void drawElev();
    void drawCode();
    bool failGUI(QString *msg);
    void calcPos(DPI::VAlign *v, DPI::HAlign *h, double sep,
                 double *x, double *y, DPT::txtposition sit);

private:
    QString errmsg;
    pointBox *pt2d;
    pointBox *pt3d;
    textBox *ptnumber;
    textBox *ptelev;
    textBox *ptcode;
    QLineEdit *fileedit;
    QComboBox *formatedit;
    QCheckBox *connectPoints;
    QList<PointData*> dataList;

    Document_Interface *currDoc;

};


class imgLabel : public QLabel
{
    Q_OBJECT

public:
    imgLabel(QWidget * parent = nullptr, Qt::WindowFlags f = {} );

    void setPos(DPT::txtposition pos = DPT::N);
    DPT::txtposition getPos() { return currPos;}

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    void drawImage();
    void changePos(int x, int y);

private:
    QPicture *posimage;
    DPT::txtposition currPos;
};

/***********/
class pointBox : public QGroupBox
{
    Q_OBJECT

public:
    pointBox(const QString & title, const QString & label, QWidget * parent = nullptr );
    void setInLayout(QLayout *lo);
    bool checkOn() { return rb->isChecked();}
    void setCheck(bool val) { rb->setChecked(val);}
    QString getLayer() { return layedit->text();}
    void setLayer(QString l) { layedit->setText(l);}
private:
    QCheckBox *rb;
    QLineEdit *layedit;
    QVBoxLayout *vbox;
};

/***********/
class textBox : public pointBox
{
    Q_OBJECT

public:
    textBox(const QString & title, const QString & label, QWidget * parent = nullptr );
    void setPos(DPT::txtposition p) { img->setPos(p); }
    QString getStyleStr() { return combostyle->currentText();}
    void setStyleIdx(int idx) { combostyle->setCurrentIndex(idx);}
    int getStyleIdx() { return combostyle->currentIndex();}
    void setHeight(double data) { heightedit->setText( QString::number(data,'f'));}
//    double getHeight();
    QString getHeightStr() { return heightedit->text();}
    double getHeight() { return heightedit->text().toDouble();}
    void setSeparation(double data) { sepedit->setText( QString::number(data,'f'));}
    QString getSeparationStr() { return sepedit->text();}
    double getSeparation() { return sepedit->text().toDouble();}
    void setPosition(DPT::txtposition p) { img->setPos(p);}
    DPT::txtposition getPosition() { return img->getPos();}

private:
    QComboBox *combostyle;
    QLineEdit *heightedit;
    QLineEdit *sepedit;
    imgLabel *img;
};
/***********/
struct PointData
{
    QString number;
    QString x;
    QString y;
    QString z;
    QString code;
};
/***********/
#endif // ECHOPLUG_H
