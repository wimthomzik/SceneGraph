#include "dialog.h"
#include "ui_dialog.h"
#include "node.h"
#include "circle.h"
#include "polygon.h"
#include <memory>
#include "transform.h"
#include "group.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}
